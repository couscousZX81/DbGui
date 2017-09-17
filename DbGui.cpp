

namespace DbGui
{
  struct context
  {
    int keyDown;
    int lastItem;
    int currentX;
    int currentY;
    int labelWidth;
    int fieldWidth;
  } _context;
  
  void Menu::start()
  {
    m_hotItem.clear();
  }
  
  void Menu::finish()
  {
    if (!(_context.KeyDown & INPUT_GO))
      m_activeItem->clear();
  }
  
  void Menu::process()
  {
    start();
    run();
    finish();
  }
  
  void process()
  {
    _context.keyDown = 0;
    if (inputNext)
      _context.keyDown &= INPUT_NEXT;
    if (inputPrev)
      _context.keyDown &= INPUT_PREV;
    if (inputGo)
      _context.keyDown &= INPUT_GO;
    if (inputBack)
      _context.KeyDown &= INPUT_BACK;
      
    if (_menu)
      _menu->process();
  }
  
  void init(int x, int y, int labelWidth, int fieldWidth)
  {
    _context.currentX = x;
    _context.currentY = y;
    _context.labelWidth = labelWidth;
    _context.fieldWidth = fieldWidth;
  }
  
  void button(const char* label)
  {
    
    currentY += lineSpacing;
  }
}
