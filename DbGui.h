

namespace DbGui
{ 
  class Menu
  {
  public:
    void process();
    
  private:
    void start();
    void finish();
    virtual void run();
    
    itemId m_hotItem;
  }
  
  Menu* _menu;
  
  void process();
  void init(int x, int y, int labelWidth, int fieldWidth();
  void button(const char *label);
}
