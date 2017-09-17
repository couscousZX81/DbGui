

namespace DbGui
{
  static const int lineSpacing = 10;
  
  static const int INPUT_NEXT = 0x001;
  static const int INPUT_PREV = 0x002;
  static const int INPUT_GO   = 0x004;
  static const int INPUT_BACK = 0x008;
  
  struct Context
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
    
    void Clear() {m_bExists = 0;}
    bool Exists() {return m_bExists;}
    
  private:
    bool m_bExists;
    int m_Name;
  }
  
  void Menu::Start()
  {
    m_hotItem.Clear();
  }
  
  void Menu::Finish()
  {
  }
  
  void Menu::Process()
  {
    Start();
    DoMenu();
    Finish();
  }
  
  void Process()
  {
    if (!pCurrentMenu)
      return;
    
    _context.keyDown = 0;
    if (inputNext)
      _context.keyDown &= INPUT_NEXT;
    if (inputPrev)
      _context.keyDown &= INPUT_PREV;
    if (inputGo)
      _context.keyDown &= INPUT_GO;
    if (inputBack)
      _context.KeyDown &= INPUT_BACK;
      
    pCurrentMenu->ProcessMenu();
  }
  
  void SetMenuLayout(int x, int y, int labelWidth, int fieldWidth)
  {
    _context.currentX = x;
    _context.currentY = y;
    _context.labelWidth = labelWidth;
    _context.fieldWidth = fieldWidth;
  }
  
  bool Navigate(itemId &thisItem)
  {
     if (!pCurrentMenu->m_hotItem.Exists())
      pCurrentMenu->hotItem = thisItem;
      
    if (pCurrentMenu->hotItem == thisItem)
    {
      else if (_context.KeyDown & INPUT_NEXT)
      {
        pCurrentMenu->hotItem.Clear();
        _context.KeyDown = 0;
      }
      else if (_context.KeyDown & INPUT_PREV)
        pCurrentMenu->hotItem = _context.lastItem; 
    }
  }
  
  void FinishWidget(itemId &thisItem)
  {
    _context.lastItem = thisItem;
    _context.currentY += lineSpacing;
  }
  
  bool Button(const char* label)
  {
    if (!pCurrentMenu)
      return false;
    
    itemId thisItem(label);
    Navigate(thisItem);
    
    bool retVal = false;
    if (pCurrentMenu->hotItem == thisItem)
    {
      if (_context.KeyDown & INPUT_GO)
        retVal = true;
    }
    
    //draw
      
    FinishWidget(thisItem);
    return retVal;
  }
}
