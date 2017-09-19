

namespace DbGui
{         
  struct ItemId
  {
    ItemId();
    
    bool m_bEmpty;
    int m_Name;
    
    inline ItemId& operator=(const ItemID& other){ return Assign(other); }
    inline bool operator==(const X& lhs, const X& rhs){ return Compare(lhs,rhs) == 0; }
    inline bool operator!=(const X& lhs, const X& rhs){ return Compare(lhs,rhs) != 0; }
    ItemId& Assign(const ItemId& other);
    bool Compare(const ItemId& lhs, const ItemId& rhs);

    void Init();
  };
  
  struct Menu
  {
    Menu(void (*f)(void));
    
    ItemId m_cursorItem;
    
    void (*m_fnProcess)(void);
  };
                     
  struct Context
  {
    Context();
    
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
}
