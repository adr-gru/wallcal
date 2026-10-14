#include <Adafruit_GFX.h>
#include <../include/MonthView.h>

void MonthView::draw(Adafruit_GFX& view, int day, int month, int year){

  uint16_t color = 0x0000;
  uint16_t width = view.width();
  uint16_t height = view.height();
  
  Uint16_t barHeight = ((height / 5) + 40);

  view.drawRoundRect(0, 0, width, height, 10, color);
  view.fillRect(0, height / 5, width, 10, color);
  view.drawLine(0, (height / 5) + 40, width, (height / 5) + 40, color);

  for(int counter = 1; counter < 8; counter++){
    uint16_t columnWidth = width / 7;
    view.drawLine(columnWidth * counter, (height / 5), columnWidth * counter, height, color);
  }
  for(int counter = 1; counter < 6; counter++){
    uint16_t rowHeight = (height - ((height / 5) + 40)) / 6;
    view.drawLine(0, ((height / 5) + 40) + rowHeight * counter, width, ((height / 5) + 40) + rowHeight * counter, color);
  }
}