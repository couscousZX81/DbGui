#include "DebugMenu.h"
#include "DbGui.h"
#include "MyGame.h"

namespace DebugMenu
{
	DbGui::Context _context;

	struct MainMenu : public DbGui::Menu
	{
		void Process() override;
	} _mainMenu;

	struct GoToLevel : public DbGui::Menu
	{
		void Process() override;
	} _goToLevel;

	struct EditSave : public DbGui::Menu
	{
		void Process() override;
	} _editSave;

	struct TestMenu : public DbGui::Menu
	{
		void Process() override;
	} _testMenu;

	//-----------------------------------------------------------------------------------------------------------------------------------------------
  
	void MainMenu::Process()
	{
		if (_context.ItemButton("Go To Level..."))
		{
			_context.PushMenu(&_goToLevel);
			return;
		}

		if (_context.ItemButton("Edit Save Game..."))
		{
			_context.PushMenu(&_editSave);
			return;
		}

		if (_context.ItemButton("Test Menu..."))
		{
			_context.PushMenu(&_testMenu);
			return;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------
  
	void GoToLevel::Process()
	{	
		for (unsigned int i = 0; i < game.GetLevelCount(); i++)
		{
			MyLevel::Level* pLevel = game.GetLevel(i);
			if (_context.ItemButton(pLevel->GetName()))
			{
				game.GoToLevel(pLevel);
				return;
			}
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------

	void EditSave::Process()
	{	
		MySave::Save* pSave = &game.GetSave(0);
		if (!pSave)
		{
			_context.ItemButton("Could not find save!");
			return;
		}

		for (unsigned int i = 0; i < pSave->GetUnlockableCount(); i++)
		{
			MySave::Unlockable* pUnlockable = pSave->GetUnlockable(i);
			if (_context.ItemBool(pUnlockable->GetName()), pUnlockable->IsUnlocked())
			{
				pUnlockable->Toggle();
				return;
			}
		}

		_context.ItemInt("Credit Balance", pSave->GetCreditBalance(), MySave::_minCreditBalance, MySave::_maxCreditBalance);
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------

	void TestMenu::Process()
	{	
		static bool bSubMenuOpen;
		_context.PushSubMenu("SubMenu", bSubMenuOpen);
		if (bSubMenuOpen)
		{
			static bool bSubSubMenuOpen;
			_context.PushSubMenu("SubSubMenu", bSubSubMenuOpen);
			if (bSubSubMenuOpen)
			{
				static int scooby;
				_context.ItemInt("Scooby", scooby, 0, 100, 1);
				static int dooby;
				_context.ItemInt("Dooby", dooby, 0, 100, 3);
				static int doo;
				_context.ItemInt("Doo", doo, 0, 100, 5);
			}
			_context.PopSubMenu();
			_context.ItemButton("Button1");
			_context.ItemButton("Button2");
			_context.ItemButton("Button3");
			_context.ItemButton("Button4");
		}
		_context.PopSubMenu();

		static bool boolTest;
		_context.ItemBool("Bool Item Test", boolTest);

		static int intTest;
		_context.ItemInt("Int Item Test", intTest, -10, 10);
	}
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------

	void OnDebugMenuOpen();
	{
	}

	void OnDebugMenuClose();
	{
	}

	static int _stackPosPrevious = 0;
	void Process()
	{
		MyInput::GamePad* pGamePad = game.GetGamePad(0);
		if (pGamePad->paddata & GAMEPAD_L1 && pGamePad->paddata_db & GAMEPAD_SELECT)
		{
			if (_context.m_menuStackPos > 0)
				_context.Close();
			else
				_context.PushMenu(&_mainMenu);
			return;
		}

		_context.Process();

		if (_context.m_menuStackPos != _stackPosPrevious)
		{
			if (_context.m_menuStackPos > 0)
				OnDebugMenuOpen();
			else
				OnDebugMenuClose();
		}
		_stackPosPrevious = _context.m_menuStackPos;
	};
}
