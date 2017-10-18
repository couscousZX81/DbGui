#include "DbGui.h"

namespace DbGui
{ 
	const static int INPUT_NEXT = 0x0001;
	const static int INPUT_PREV = 0x0002;
	const static int INPUT_INC = 0x0004;
	const static int INPUT_DEC = 0x0008;
	const static int INPUT_PUSH = 0x0010;
	const static int INPUT_POP = 0x0020;

	static float _debounceFirst = 0.3f;
	static float _debounceSubsequent = 0.08f;

	static float _lineX = 0.0f;
	static float _lineY = 2000.0f;
	static float _lineW = 4000.0f;
	static float _lineH = 80.0f;

	static float _textScale = 0.5f;
	static float _textX = 400.0f;
	static float _textY = 62.0f;
	
	static float _subMenuToggleX = -80.0f;
	static float _subMenuTab = 120.0f;

	static float _fieldX = 0.65f;
	static float _fieldY = 0.1f;
	static float _fieldW = 0.32f;
	static float _fieldH = 0.8f;

	static float _sliderW = 50.0f;

	static MyColour _colourBG = MyColour(20,40,255,20);
	static MyColour _colourBGHigh = MyColour(224,224,224,20);
	static MyColour _colourField = MyColour(40,80,255,255);
	static MyColour _colourFieldHigh = MyColour(255,255,255,255);
	static MyColour _colourSlider = MyColour(255,128,0,255);
	static MyColour _colourSliderHigh = MyColour(255,128,0,255);
	static MyColour _colourText = MyColour(255,255,255,255);
	static MyColour _colourTextHigh = MyColour(0,0,0,255);

	struct RenderContext
	{
		float bgX;
		float bgY;
		float bgW;
		float bgH;

		float fieldX;
		float fieldY;
		float fieldW;
		float fieldH;

		float tab;
		bool bHighlight;
	} _render;
  
	void StartNewItem(Context *pContext)
	{
		int line = pContext->m_pMenuStack[pContext->m_menuStackPos]->m_highlightedLine - pContext->m_line;
		if (line == 0)
			_render.bHighlight = true;
		else
			_render.bHighlight = false;

		_render.bgX = _lineX;
		_render.bgY = _lineY - _lineH*line;
		_render.bgW = _lineW;
		_render.bgH = _lineH;
		
		_render.fieldX = _render.bgX + _render.bgW * _fieldX;
		_render.fieldY = _render.bgY + _render.bgH * _fieldY;
		_render.fieldW = _render.bgW * _fieldW;
		_render.fieldH = _render.bgH * _fieldH;

		_render.tab = pContext->m_subMenuStackPos * _subMenuTab;
	}	
	
	void RenderBackground()
	{
		MyColour col = (_render.bHighlight ? _colourBGHigh : _colourBG);
		MyPrim::Draw2DRect(_render.bgX, _render.bgY, _render.bgW, _render.bgH, col);
	}
  
	void RenderFieldBackground()
	{
		MyColour col = (_render.bHighlight ? _colourFieldHigh : _colourField);
		MyPrim::Draw2DRect(_render.fieldX, _render.fieldY, _render.fieldW, _render.fieldH, col);
	}

	void RenderSliderInt(const int i, int min, int max)
	{
		MyColour col = (_render.bHighlight ? _colourSliderHigh : _colourSlider);

		float t = ((float)i - (float)min) / ((float)max - (float)min);
		float halfW = _sliderW*0.5f;
		float x = (_render.fieldX+halfW) + (_render.fieldW-_sliderW)*t - halfW;
		MyPrim::Draw2DRect(x, _render.fieldY, _sliderW, _render.fieldH, col);
	}

	void RenderFieldBool(const bool b)
	{
		MyColour col = (_render.bHighlight ? _colourTextHigh : _colourText);

		float x = _render.fieldX + _render.fieldW*0.5f;
		float y = _render.bgY + _textY;		

		char str[100];
		sprintf(str, (b ? "true" : "false"));

		MyFont::SetColour(deafultFont, col);
		MyFont::Print(deafultFont, x, y, MYFONT_ALIGN_CENTER, "%s", str);
	}

	void RenderFieldInt(const int i)
	{
		MyColour col = (_render.bHighlight ? _colourTextHigh : _colourText);

		float x = _render.fieldX + _render.fieldW*0.5f;
		float y = _render.bgY + _textY;		
		
		char str[100];
		sprintf(str, "%d", i);

		MyFont::SetColour(deafultFont, col);
		MyFont::Print(deafultFont, x, y, MYFONT_ALIGN_CENTER, "%s", str);
	}

	void RenderLabel(const char* label)
	{
		MyColour col = (_render.bHighlight ? _colourTextHigh : _colourText);

		float x = _render.bgX + _textX + _render.tab;
		float y = _render.bgY + _textY;		

		MyFont::SetColour(deafultFont, col);
		MyFont::Print(deafultFont, x, y, MYFONT_ALIGN_LEFT, "%s", label);
	}

	void RenderSubMenuToggle(bool bOpen)
	{
		MyColour col = (_render.bHighlight ? _colourTextHigh : _colourText);

		float x = _render.bgX + _textX + _render.tab + _subMenuToggleX;
		float y = _render.bgY + _textY;		
		
		char str[100];
		sprintf(str, (bOpen ? "[ - ]" : "[+]"));

		MyFont::SetColour(deafultFont, col);
		MyFont::Print(deafultFont, x, y, MYFONT_ALIGN_CENTER, "%s", str);
	}
  
	//---------------------------------------------------------------------------------------------------------------

	void Context::Process()
	{
		if (!m_pMenuStack[m_menuStackPos])
			return;

		int keyDownOld = m_keyDown;

		Menu* pMenu = m_pMenuStack[m_menuStackPos];
		m_subMenuStackPos = 0;
		m_line = 0;
		m_keyDown = 0;

		MyInput::GamePad* pGamePad = game.GetGamePad(0);
		if (pGamePad->paddata & GAMEPAD_DDOWN)
			m_keyDown |= INPUT_NEXT;
		if (pGamePad->paddata & GAMEPAD_DUP)
			m_keyDown |= INPUT_PREV;
		if (pGamePad->paddata & GAMEPAD_DRIGHT)
			m_keyDown |= INPUT_INC;
		if (pGamePad->paddata & GAMEPAD_DLEFT)
			m_keyDown |= INPUT_DEC;
		if (pGamePad->paddata_db & GAMEPAD_SOUTH)
			m_keyDown |= INPUT_PUSH;
		if (pGamePad->paddata_db & GAMEPAD_EAST)
			m_keyDown |= INPUT_POP;

		if (m_keyDown != keyDownOld)
			ResetDebounce();

		if (m_keyDown & INPUT_POP)
		{
			PopMenu();
		}
		else
		{
			MyFont::Set(defaultFont);
			MyFont::SetScale(defaultFont, _textScale);

			pMenu->Process();

			if ((m_keyDown & INPUT_NEXT) && UpdateDebounce())
			{
				pMenu->m_highlightedLine++;
				if (pMenu->m_highlightedLine >= m_line)
					pMenu->m_highlightedLine = 0;
			}
			if ((m_keyDown & INPUT_PREV) && UpdateDebounce())
			{
				pMenu->m_highlightedLine--;
				if (pMenu->m_highlightedLine < 0)
					pMenu->m_highlightedLine = m_line-1;
			}
		}
	}

	void Context::ResetDebounce()
	{
		m_dbFirst = true;
		m_dbTimer = 0.0f;
	}

	bool Context::UpdateDebounce()
	{
		m_dbTimer -= 0.03f;
		if (m_dbTimer <= 0.0f)
		{
			if (m_dbFirst)
				m_dbTimer = _debounceFirst;
			else
				m_dbTimer = _debounceSubsequent;
			m_dbFirst = false;
			return true;
		}
		return false;
	}

	void Context::PushMenu(Menu* pMenu)
	{
		MyAssert(m_menuStackPos < MENU_STACK_LIMIT, "Trying to PushMenu but the stack is full. Increase MENU_STACK_LIMIT.");
		if (m_menuStackPos < MENU_STACK_LIMIT)
		{
			m_menuStackPos++;
			m_pMenuStack[m_menuStackPos] = pMenu;
		}
	}
  
	void Context::PopMenu()
	{
		MyAssert(m_menuStackPos > 0, "Trying to PopMenu when there's nothing on the stack.");
		if (m_menuStackPos > 0)
		{
			m_pMenuStack[m_menuStackPos] = NULL;
			m_menuStackPos--;
		}
	}
  
	void Context::PushSubMenu(const char* label, bool& bToggle)
	{
		StartNewItem(this);
		RenderBackground();
		RenderLabel(label);
		RenderSubMenuToggle(bToggle);
		
		if (_render.bHighlight)
		{
			if (m_keyDown & INPUT_PUSH)
				bToggle = !bToggle;
		}

		m_subMenuStackPos++;
		m_line++;
	}
		
	void Context::PopSubMenu()
	{
		MyAssert(m_subMenuStackPos > 0, "Trying to PopSubMenu when there's nothing on the stack.");
		m_subMenuStackPos--;
	}

	bool Context::ItemButton(const char* label)
	{
		StartNewItem(this);
		RenderBackground();
		RenderLabel(label);

		bool bPressed = false;
		if (_render.bHighlight)
		{
			if (m_keyDown & INPUT_PUSH)
				bPressed = true;
		}

		m_line++;
		return bPressed;
	}

	bool Context::ItemBool(const char* label, bool& b)
	{
		StartNewItem(this);
		RenderBackground();
		RenderFieldBackground();
		RenderFieldBool(b);
		RenderLabel(label);
		
		bool bOld = b;
		if (_render.bHighlight)
		{
			if (m_keyDown & INPUT_PUSH)
				b = !b;

			if (m_keyDown & INPUT_INC)
				b = true;

			if (m_keyDown & INPUT_DEC)
				b = false;
		}

		m_line++;
		return (bOld != b) ? true : false;
	}

	bool Context::ItemInt(const char* label, int& i, int min, int max, int step)
	{
		StartNewItem(this);
		RenderBackground();
		RenderFieldBackground();
		RenderSliderInt(i, min, max);
		RenderFieldInt(i);
		RenderLabel(label);
		
		int iOld = i;
		if (_render.bHighlight)
		{
			if ((m_keyDown & INPUT_INC) && UpdateDebounce())
			{
				i += step;
				if (i > max)
					i = max;
			}

			if ((m_keyDown & INPUT_DEC) && UpdateDebounce())
			{
				i -= step;
				if (i < min)
					i = min;
			}
		}

		m_line++;
		return (iOld != i) ? true : false;
	}
}
