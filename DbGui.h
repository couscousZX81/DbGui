

namespace DbGui
{ 
  class Menu
  {
  public:
    void ProcessMenu();
    
  protected:
    virtual void DoMenu();
    
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
