

namespace DbGui
{   
  struct Menu
  {
    Menu() : m_pFn(NULL), m_highlightedLine(0) {}
    void (*m_pFn)(void);
    int m_highlightedLine;
  };
                     
  struct Context
  {
    Context(Menu* pFirstMenu) : m_pMenu(pFirstMenu) {};
    
    Menu* m_pMenu;
    int m_line;
    int m_keyDown;
    
    void Process();
    bool Pop();
    bool Button(const char *label);
  };
}
