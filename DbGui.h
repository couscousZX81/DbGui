

namespace DbGui
{ 
  class Menu
  {
  public:
    void ProcessMenu();
    
  private:
    void Start();
    void Finish();
    virtual void DoMenu();
    
    itemId m_hotItem;
  }
  
  Menu* _menu;
  
  void Process();
  void SetMenuLayout(int x, int y, int labelWidth, int fieldWidth();
  void Button(Menu* pOwningMenu, const char *label);
}
