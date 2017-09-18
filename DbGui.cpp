

namespace DbGui
{ 
  static const int INPUT_NEXT = 0x001;
  static const int INPUT_PREV = 0x002;
  static const int INPUT_GO   = 0x004;
  static const int INPUT_BACK = 0x008;
  
  struct ItemId
  {
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
    
    void Init() {m_bExists = 1;}
    void Clear() {m_bExists = 0;}
    bool Exists() {return m_bExists;}
    
    bool m_bExists;
    int m_Name;
  }
  
  //---------------------------------------------------------------------------
  
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
  
  //---------------------------------------------------------------------------
  
  void Context::Init()
  {
    m_previousItem.Clear();
  }
  
  void Context::Process()
  {
    if (!m_pActiveMenu)
      return;
    
    m_keyDown = 0;
    if (inputNext)
      m_keyDown &= INPUT_NEXT;
    if (inputPrev)
      m_keyDown &= INPUT_PREV;
    if (inputGo)
      m_keyDown &= INPUT_GO;
    if (inputBack)
      m_keyDown &= INPUT_BACK;
    
    m_atY = 100;
    m_pActiveMenu->Process();
  }
  
  void Context::DoCursorInput()
  {
     if (!m_pActiveMenu->m_hotItem.Exists())
      m_pActiveMenu->m_cursorItem = m_currentItem;
      
    if (m_pActiveMenu->m_cursorItem == m_currentItem)
    {
      else if (m_keyDown & INPUT_NEXT)
      {
        m_pActiveMenu->m_cursorItem.Clear();
        m_keyDown = 0;
      }
      else if (m_keyDown & INPUT_PREV)
        m_pActiveMenu->m_cursorItem = _context.m_previousItem; 
    }
  }
  
  void Context::FinishedItem()
  {
    m_previousItem = m_currentItem;
    m_atY += 50;
  }
  
  bool Context::Button(const char* label)
  {
    m_currentItem.Init(label);
    DoCursorInput();
    
    bool bPressed = false;
    if (m_pActiveMenu->hotItem == thisItem)
    {
      if (_context.KeyDown & INPUT_GO)
        bPressed = true;
    }
    
    //draw
      
    FinishedItem();
    return bPressed;
  }
}
