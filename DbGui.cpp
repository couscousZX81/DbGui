

namespace DbGui
{ 
  static const int INPUT_NEXT = 0x0001;
  static const int INPUT_PREV = 0x0002;
  static const int INPUT_INC = 0x0004;
  static const int INPUT_DEC = 0x0008;
  static const int INPUT_PUSH = 0x0010;
  static const int INPUT_POP = 0x0020;
  
  //---------------------------------------------------------------------------
  
  ItemId::ItemID()
    : m_bExists(false)
  {
      
  }
  
  ItemId::Init()
  {
    m_bExists = 1;
  }
  
  //---------------------------------------------------------------------------
  
  Menu::Menu(void (*f)(void))
    : m_fnProcess(f)
  {
    
  }
  
  //---------------------------------------------------------------------------
  
  Context::Context()
    : m_pActiveMenu(NULL)
  {
    
  }
  
  void Context::Process()
  {
    if (!m_pActiveMenu || !m_pActiveMenu->fnProcess)
      return;
    
    m_currentItem.Clear();
    m_previousItem.Clear();
    m_atY = 100;
    
    m_keyDown = 0;
    if (inputNext)
      m_keyDown &= INPUT_NEXT;
    if (inputPrev)
      m_keyDown &= INPUT_PREV;
    if (inputInc)
      m_keyDown &= INPUT_INC;
    if (inputDec)
      m_keyDown &= INPUT_DEC;
    if (inputPush)
      m_keyDown &= INPUT_PUSH;
    if (inputPop)
      m_keyDown &= INPUT_POP;
    
    m_pActiveMenu->fnProcess();
  }
  
  void Context::DoCursorInput()
  {
    if (!m_pActiveMenu->m_hotItem.Exists())
      m_pActiveMenu->m_cursorItem = m_currentItem;
      
    if (m_pActiveMenu->m_cursorItem == m_currentItem)
    {
      if (m_keyDown & INPUT_NEXT)
        m_pActiveMenu->m_cursorItem.Clear();
      else if (m_keyDown & INPUT_PREV)
        m_pActiveMenu->m_cursorItem = m_previousItem; 
    }
    
    if (m_pActiveMenu->m_cursorItem != m_currentItem)
        m_keyDown = 0;
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
    if (m_pActiveMenu->m_cursorItem == thisItem)
    {
      if (_context.KeyDown & INPUT_PUSH)
        bPressed = true;
    }
    
    //draw
      
    FinishedItem();
    return bPressed;
  }
}
