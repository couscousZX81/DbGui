

namespace DbGui
{
  static const int lineSpacing = 10;
  
  static const int INPUT_NEXT = 0x001;
  static const int INPUT_PREV = 0x002;
  static const int INPUT_GO   = 0x004;
  static const int INPUT_BACK = 0x008;
  
  class ItemId
  {
  public:
    ItemId() 
      : m_bEmpty(0)
    {
    }
    
    virtual ~ItemId()
    {
    }
    
    void set();
    void clear() {m_bEmpty = 0;}
    
  private:
    int m_name;
    bool m_bEmpty;
  }
  
  class Menu
  {
  public:
    void process();
    
  private:
    void start();
    void finish();
    virtual void run();
    
    itemId m_hotItem;
    itemId m_activeItem;
  }
  
  Menu* _menu;
  
  void process();
  void init(int x, int y, int labelWidth, int fieldWidth();
  void button(const char *label);
}
