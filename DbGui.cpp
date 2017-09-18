

namespace DbGui
{ 
  static const int INPUT_NEXT = 0x001;
  static const int INPUT_PREV = 0x002;
  static const int INPUT_GO   = 0x004;
  static const int INPUT_BACK = 0x008;
  
  //---------------------------------------------------------------------------
  
  void Context::Process()
  {
    if (!m_pActiveMenu || !m_pActiveMenu->fnProcess)
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
    m_pActiveMenu->fnProcess();
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
