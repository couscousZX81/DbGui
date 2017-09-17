

namespace DbGui
{
  static const int lineSpacing = 10;
  
  static const int INPUT_NEXT = 0x001;
  static const int INPUT_PREV = 0x002;
  static const int INPUT_GO   = 0x004;
  static const int INPUT_BACK = 0x008;
  
  struct context
  {
    itemID lastItem;
    int keyDown;
    int currentX;
    int currentY;
    int labelWidth;
    int fieldWidth;
  } _context;
  
  class ItemId
  {
  public:
    ItemId() 
      : m_bExists(0)
    {
    }
    
    ItemId(int name)
      : m_bExists(true)
      , m_Name(name)
    {
    }
    
    virtual ~ItemId()
    {
    }
    
    ItemId operator=(const ItemID& other)
    {
      m_Name = other.m_Name;
      m_bExists = other.m_bExists;
    }
    
    ItemId operator==(const ItemID& other)
    {
      if (m_bExists != other.m_bExists)
        return false;
      
      if (m_Name != other.m_Name)
        return false;
      
      return true;
    }
    
    void set();
    void clear() {m_bExists = 0;}
    bool exists() {return m_bExists;}
    
  private:
    bool m_bExists;
    int m_Name;
  }
  
  void Menu::start()
  {
    m_hotItem.clear();
  }
  
  void Menu::finish()
  {
    if (!(_context.KeyDown & INPUT_GO))
      m_activeItem->clear();
  }
  
  void Menu::process()
  {
    start();
    run();
    finish();
  }
  
  void process()
  {
    _context.keyDown = 0;
    if (inputNext)
      _context.keyDown &= INPUT_NEXT;
    if (inputPrev)
      _context.keyDown &= INPUT_PREV;
    if (inputGo)
      _context.keyDown &= INPUT_GO;
    if (inputBack)
      _context.KeyDown &= INPUT_BACK;
      
    if (_menu)
      _menu->process();
  }
  
  void init(int x, int y, int labelWidth, int fieldWidth)
  {
    _context.currentX = x;
    _context.currentY = y;
    _context.labelWidth = labelWidth;
    _context.fieldWidth = fieldWidth;
  }
  
  bool button(Menu* menu, const char* label)
  {
    bool retVal = false;
    itemId thisItem(label);
    
    if (!menu->m_hotItem.exists())
      menu->hotItem = thisItem;
      
    if (menu->hotItem == thisItem)
    {
      if (_context.KeyDown & INPUT_GO)
        retVal = true;
      else if (_context.KeyDown & INPUT_NEXT)
        menu->hotItem.clear();
      else if (_context.KeyDown & INPUT_PREV)
        menu->hotItem = _context.lastItem;
    }
    
    //draw
      
    _context.lastItem = thisItem;
    _context.currentY += lineSpacing;
    
    return retVal;
  }
}
