


class DebugMenuInactive : public DbGui::Menu
{
public:
  virtual void Run() override
  {
    if (L1+Select)
      DbGui::SetMenu(&_debugMenuMain)
  }
} _debugMenuInactive;

class DebugMenuMenu : public DbGui::Menu
{
public:
  virtual void Run() override
  {
    DbGui::Init(100, 100, 400, 400)
    
    if (DbGui::Button(this, "Button1")
      //do Button1 stuff
      
    if (DbGui::Button(this, "Button2")
      //do Button2 stuff
  }
} _debugMenuMain;
