#pragma once

namespace YimMenu::Features
{
	class PhoneFreeShopping
	{
	private:
		static PhoneFreeShopping& GetInstance()
		{
			static PhoneFreeShopping instance;
			return instance;
		}

		void RunScriptImpl();

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}
	};
}
