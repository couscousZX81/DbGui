

namespace DbGui
{ 
  void Button(const char *label);
                     
  struct Menu
  {
    virtual void Process();
    ItemId m_cursorItem;
  }
                     
  struct Context
  {
    Menu* m_pActiveMenu;
    ItemID m_currentItem;
    ItemID m_previousItem;
    int m_keyDown;
    int m_atY;
    
    void Init();
    void Process();
    void DoCursorInput();
    void FinishedItem();
  };
}
