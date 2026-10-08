#pragma once

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace YimMenu::ShopJson
{
	// Length-preserving in-place rewrite: "price":123456 -> "price":0<spaces>
	inline void ZeroNumericField(char* begin, char* end, const char* key)
	{
		const std::string needle = std::string("\"") + key + "\":";
		const std::size_t keyLen = needle.size();

		for (char* p = begin; p + keyLen < end; ++p)
		{
			if (std::memcmp(p, needle.c_str(), keyLen) != 0)
				continue;

			char* num = p + keyLen;
			if (num >= end || (*num != '-' && (*num < '0' || *num > '9')))
				continue;

			char* numEnd = num;
			if (*numEnd == '-')
				++numEnd;
			while (numEnd < end && *numEnd >= '0' && *numEnd <= '9')
				++numEnd;
			if (numEnd == num || (numEnd == num + 1 && *num == '-'))
				continue;

			const std::size_t span = static_cast<std::size_t>(numEnd - num);
			num[0] = '0';
			if (span > 1)
				std::memset(num + 1, ' ', span - 1);

			p = num + span - 1;
		}
	}

	// Any buffer that holds a price/bank/wallet numeric field from a shop txn.
	inline bool LooksLikeTxnJson(const char* json, std::size_t capacity)
	{
		if (!json || capacity < 16)
			return false;

		bool hasPrice = false;
		bool hasShop  = false;
		// Bounded scan — buffer may not be NUL-terminated.
		const std::size_t n = capacity < 0x8000 ? capacity : 0x8000;
		for (std::size_t i = 0; i + 8 < n; ++i)
		{
			if (!hasPrice && std::memcmp(json + i, "\"price\":", 8) == 0)
				hasPrice = true;
			if (!hasShop
			    && (std::memcmp(json + i, "\"catalogVersion\"", 16) == 0
			        || std::memcmp(json + i, "\"items\"", 7) == 0
			        || std::memcmp(json + i, "\"TransactionNonce\"", 18) == 0))
			{
				hasShop = true;
			}
			if (hasPrice && hasShop)
				return true;
		}
		return false;
	}

	inline bool RewriteTransactionJson(char* json, std::size_t capacity)
	{
		if (!LooksLikeTxnJson(json, capacity))
			return false;

		ZeroNumericField(json, json + capacity, "price");
		ZeroNumericField(json, json + capacity, "bank");
		ZeroNumericField(json, json + capacity, "wallet");
		return true;
	}

	inline bool IsLikelyUserPtr(std::uint64_t v)
	{
		return v >= 0x10000 && v < 0x00007FFFFFFFFFFFULL && (v & 7) == 0;
	}

	inline bool TryRewriteWindow(void* candidate, std::size_t window)
	{
		if (!candidate || window < 32)
			return false;

		auto* base = reinterpret_cast<char*>(candidate);

		__try
		{
			if (RewriteTransactionJson(base, window))
				return true;

			// Find any "{\"" / " price" region — JSON may sit mid-buffer.
			for (std::size_t i = 0; i + 16 < window; ++i)
			{
				if (base[i] != '{' && std::memcmp(base + i, "\"price\":", 8) != 0)
					continue;
				if (RewriteTransactionJson(base + i, window - i))
					return true;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}

		return false;
	}

	// Walk an object: direct window, then every likely pointer (and one level deep).
	inline bool TryRewriteObjectGraph(void* obj, std::size_t directWindow, int maxPtrs = 64)
	{
		if (!obj)
			return false;

		if (TryRewriteWindow(obj, directWindow))
			return true;

		auto* slots = reinterpret_cast<std::uint64_t*>(obj);
		__try
		{
			for (int i = 0; i < maxPtrs; ++i)
			{
				const std::uint64_t p = slots[i];
				if (!IsLikelyUserPtr(p))
					continue;
				auto* child = reinterpret_cast<void*>(p);
				if (TryRewriteWindow(child, 0x4000))
					return true;

				// One more hop: body often lives behind a small wrapper.
				auto* inner = reinterpret_cast<std::uint64_t*>(child);
				for (int j = 0; j < 8; ++j)
				{
					const std::uint64_t q = inner[j];
					if (!IsLikelyUserPtr(q))
						continue;
					if (TryRewriteWindow(reinterpret_cast<void*>(q), 0x4000))
						return true;
				}
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
		}

		return false;
	}

	inline bool HuntAndRewrite(void* a, void* b)
	{
		if (TryRewriteObjectGraph(a, 0x8000, 80))
			return true;
		if (b && b != a && TryRewriteObjectGraph(b, 0x8000, 80))
			return true;
		return false;
	}

	inline std::string DumpToLine(const char* tag, const void* p, std::size_t n)
	{
		std::string out;
		if (!p || n == 0)
		{
			out += tag;
			out += " = null";
			return out;
		}

		auto* b = static_cast<const unsigned char*>(p);
		char buf[80];
		out += tag;
		out += " @";
		std::snprintf(buf, sizeof(buf), "%p", p);
		out += buf;

		const std::size_t show = n < 128 ? n : 128;
		for (std::size_t i = 0; i < show; i += 16)
		{
			out += "\n  +";
			std::snprintf(buf, sizeof(buf), "%04zX:", i);
			out += buf;
			char asc[20];
			std::size_t a = 0;
			for (std::size_t j = i; j < show && j < i + 16; ++j)
			{
				std::snprintf(buf, sizeof(buf), " %02X", b[j]);
				out += buf;
				const unsigned char c = b[j];
				asc[a++] = (c >= 32 && c < 127) ? static_cast<char>(c) : '.';
			}
			while (a < 16)
				asc[a++] = ' ';
			asc[16] = 0;
			out += "  |";
			out += asc;
			out += '|';
		}
		return out;
	}

	// True if the window already has every money field at 0 (or no money fields).
	inline bool AlreadyZeroed(const char* json, std::size_t capacity)
	{
		if (!json || capacity < 16)
			return false;
		const std::size_t n = capacity < 0x4000 ? capacity : 0x4000;
		for (std::size_t i = 0; i + 16 < n; ++i)
		{
			if (std::memcmp(json + i, "\"price\":", 8) != 0)
				continue;
			const char* v = json + i + 8;
			if (*v == '-' || (*v >= '1' && *v <= '9'))
				return false;
		}
		return true;
	}
}
