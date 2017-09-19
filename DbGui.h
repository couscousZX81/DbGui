

namespace DbGui
{   
  struct Menu
  {
    Menu();
    
    int m_highlightedLine;
    
    void (*m_pFn)(void);
  };
                     
  struct Context
  {
    Context();
    
    Menu* m_pMenu;
    int m_line;
    int m_keyDown;
    
    void Process();
    
    bool Button(const char *label);
  };
}
