

namespace DbGui
{ 
  class Menu
  {
  public:
    void Process();
    
  private:
    void Start();
    void Finish();
    virtual void Run();
    
    itemId m_hotItem;
  }
  
  Menu* _menu;
  
  void Process();
  void Init(int x, int y, int labelWidth, int fieldWidth();
  void Button(Menu* pOwningMenu, const char *label);
}
