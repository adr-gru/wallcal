#include <Adafruit_GFX.h>
#include <../include/MonthView.h>
#include <string>

void drawColumns(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color);
void drawRows(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color);
void drawHeader(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color, uint16_t day, uint16_t month, uint16_t year);

static const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char* days[7] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};

void MonthView::draw(Adafruit_GFX& view, uint16_t day, uint16_t month, uint16_t year){

  uint16_t color = 0x0000;
  uint16_t width = view.width();
  uint16_t height = view.height();
  uint16_t currentDay = day;
  uint16_t currentMonth = month;
  uint16_t currentYear = year;

  
  
  drawHeader(view, width, height, color, currentDay, currentMonth, currentYear);
  drawColumns(view, width, height, color);
  drawRows(view, width, height, color);
  
}

 void drawHeader(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color, uint16_t day, uint16_t month, uint16_t year){
  view.drawRoundRect(0, 0, width, height, 10, color);
  view.fillRect(0, height / 5, width, 10, color);
  view.setCursor(30, (height/5) + 30);
  for(int counter = 0; counter < 7; counter++){
    view.print(days[counter]);
    view.setCursor(view.getCursorX() + 80, (height/5) + 30);
  }   
  view.drawLine(0, (height / 5) + 40, width, (height / 5) + 40, color);
  view.setCursor(20, (height/5) - 30);
  view.setTextSize(4);
  view.print(months[month - 1]);
  view.print(day);

}

void drawColumns(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color){
  for(int counter = 1; counter < 8; counter++){
    uint16_t columnWidth = width / 7;
    view.drawLine(columnWidth * counter, (height / 5), columnWidth * counter, height, color);
  }
}

void drawRows(Adafruit_GFX& view, uint16_t width, uint16_t height, uint16_t color){
  for(int counter = 1; counter < 6; counter++){
    uint16_t rowHeight = (height - ((height / 5) + 40)) / 6;
    view.drawLine(0, ((height / 5) + 40) + rowHeight * counter, width, ((height / 5) + 40) + rowHeight * counter, color);
  }
}
