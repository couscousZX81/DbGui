

namespace DbGui
{         
  struct ItemId
  {
    bool m_bExists;
    int m_Name;
    
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
  };
                     
  struct Context
  {
    Menu* m_pActiveMenu;
    ItemID m_currentItem;
    ItemID m_previousItem;
    int m_keyDown;
    int m_atY;
    
    void Process();
    void DoCursorInput();
    void FinishedItem();
    
    bool Button(const char *label);
  };
  
  struct Menu
  {
    ItemId m_cursorItem;
    
    void (*fnProcess)(void);
  };
}
