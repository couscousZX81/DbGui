

namespace DbGui
{ 
  class Menu
  {
  public:
    virtual void DoMenu();
    void ProcessMenu();
    
  private:
    void Start();
    void Finish();
    
    itemId m_hotItem;
  }
  
  Menu* _menu;
  
  void Process();
  void SetMenuLayout(int x, int y, int labelWidth, int fieldWidth();
  void Button(const char *label);
}
