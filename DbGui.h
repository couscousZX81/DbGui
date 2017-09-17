

namespace DbGui
{
  class Menu
  {
  public:
    void Process();
    
  private:
    void Start();
    void Finish();
    virtual void Update();
    
    itemId m_hotItem;
    itemId m_activeItem;
  }
}
