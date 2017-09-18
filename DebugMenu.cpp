
namespace DebugMenu
{
  DbGui::Context _context;
  
  class MenuWaiting : public DbGui::Menu
  {
  public:
    virtual void Process() override;
  } _menuInactive;

  class MenuMain : public DbGui::Menu
  {
  public:
    virtual void Process() override;
  } _menuMain;
  
  void MenuWaiting::Process()
  {
    if (L1+Select)
      _context.m_pActiveMenu = &_menuMain;
  }
  
  void MenuMain::Process()
  {
    if (_context.Button(this, "Button1")
      //do Button1 stuff

    if (_context.Button(this, "Button2")
      //do Button2 stuff
  }
  
  void Init()
  {
    _context.Init();
    _context.m_pActiveMenu = &_menuInactive;
  }
  
  void Process()
  {
    _context.Process();
  }
}

