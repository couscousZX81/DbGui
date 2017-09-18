
namespace DebugMenu
{
  DbGui::Context _context;
  
  void ProcessMenuWaiting()
  {
    if (L1+Select)
      _context.m_pActiveMenu = &_menuMain;
  }
  DBGui::Menu _menuWaiting(&ProcessMenuWaiting);
  
  void ProcessMenuMain()
  {
    if (_context.Button(this, "Button1")
      //do Button1 stuff

    if (_context.Button(this, "Button2")
      //do Button2 stuff
  }
  DBGui::Menu _menuMain(&ProcessMenuMain);
  
  void Init()
  {   
    _context.m_pActiveMenu = &_menuInactive;
  }
  
  void Process()
  {
    _context.Process();
  }
}

