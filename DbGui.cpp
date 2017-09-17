

namespace DbGui
{
  struct context
  {
    int keybits;
    int lastitem;
    int currentX;
    int currentY;
    int labelWidth;
    int fieldWidth;
  } _context;
  
  void menu::start()
  {
    m_hotItem = 0;
  }
}
