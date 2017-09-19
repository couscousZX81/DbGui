

namespace DebugMenu
{
  DBGui::Menu _waiting;
  DBGui::Menu _mainMenu;
  DbGui::Context _context(&_waiting);
  
  //---------------------------------------------------------------------------
  
  void Waiting()
  {
    if (L1+Select)
      _context.m_pMenu = &_mainMenu;
  }
  _waiting.m_pFn = Waiting;
  
  //---------------------------------------------------------------------------
  
  void MainMenu()
  {
    if (_context.Pop())
    {
      _context.m_pMenu = &_waiting;
      return;
    }
    
    if (_context.Button(this, "Button1"))
      //do Button1 stuff

    if (_context.Button(this, "Button2"))
      //do Button2 stuff
  }
  _mainMenu.m_pFn = MainMenu;
        
  //---------------------------------------------------------------------------
  
  void Enable(bEnable)
  {
    if (bEnable)
      //registerProcessJob
    else
      //deregisterProcessJob
  }
  
  void Process()
  {
    _context.Process();
  }
}

