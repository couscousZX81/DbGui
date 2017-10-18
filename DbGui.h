#pragma once

namespace DbGui
{   
	struct Menu
	{
		Menu() : m_highlightedLine(0) {}
		
		int m_highlightedLine;

		virtual void Process() {};
	};
                     
	struct Context
	{
		Context() : m_menuStackPos(0) {};
    
		#define MENU_STACK_LIMIT 20
		Menu* m_pMenuStack[MENU_STACK_LIMIT];
		int m_menuStackPos;
		int m_subMenuStackPos;
		int m_line;
		int m_keyDown;
		bool m_dbFirst;
		float m_dbTimer;
    
		void Process();
		void Close() {m_menuStackPos = 0;}

		void ResetDebounce();
		bool UpdateDebounce();

		void PushMenu(Menu* pMenu);
		void PopMenu();

		void PushSubMenu(const char* label, bool& bToggle);
		void PopSubMenu();

		bool ItemButton(const char* label);
		bool ItemBool(const char* label, bool& b);
		bool ItemInt(const char* label, int& i, int min, int max, int step = 1);
	};
}
