

namespace DebugMenu
{
  DbGui::Context _context;
  
  DBGui::Menu _waiting;
  DBGui::Menu _mainMenu;
  
  void Waiting()
  {
    if (L1+Select)
      _context.m_pActiveMenu = &_mainMenu;
  }
  _waiting.m_pFn = Waiting;
  
  void MainMenu()
  {
    if (_context.Button(this, "Button1")
      //do Button1 stuff

    if (_context.Button(this, "Button2")
      //do Button2 stuff
  }
  _mainMenu.m_pFn = MainMenu;
  
  void Init()
  {   
    _context.m_pActiveMenu = &_waiting;
  }
  
  void Exit()
  {   
    _context.m_pActiveMenu = NULL;
  }
  
  void Process()
  {
    _context.Process();
  }
}

