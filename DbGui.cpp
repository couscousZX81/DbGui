

namespace DbGui
{ 
  static const int INPUT_NEXT = 0x0001;
  static const int INPUT_PREV = 0x0002;
  static const int INPUT_INC = 0x0004;
  static const int INPUT_DEC = 0x0008;
  static const int INPUT_PUSH = 0x0010;
  static const int INPUT_POP = 0x0020;
  
  void Context::Process()
  {
    if (!m_pMenu || !m_pMenu->m_pFn)
      return;
    
    m_line = 0;
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
    
    m_pMenu->m_pFn();
    
    if (m_keyDown & INPUT_NEXT)
      m_pMenu->m_highlightedLine++;
    else if (m_keyDown & INPUT_PREV)
      m_pMenu->m_highlightedLine--;
    
    if (m_pMenu->m_highlightedLine < 0)
      m_pMenu->m_highlightedLine += m_line;
    else if (m_pMenu->m_highlightedLine >= m_line)
      m_pMenu->m_highlightedLine -= m_line;
  }
  
  bool Context::Pop()
  {
      return (m_keyDown & INPUT_POP);
  }
  
  bool Context::Button(const char* label)
  {
    bool bPressed = false;
    if (m_line == m_pMenu->m_highlightedLine)
    {
      if (m_keyDown & INPUT_PUSH)
        bPressed = true;
    }
    
    //draw
      
    m_line++;
    return bPressed;
  }
}
