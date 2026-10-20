#include <Adafruit_GFX.h>
#include <../include/MonthView.h>
#include <string>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <ctime>


static const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char* days[7] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};


void MonthView::draw(Adafruit_GFX& view){

  time_t now = time(0); 
  struct tm* localTime = localtime(&now);

  this->color = 0x0000;
  this->width = view.width();
  this->height = view.height();
  this->currentDay = localTime->tm_mday;
  this->currentMonth = localTime->tm_mon + 1;
  this->currentYear = localTime->tm_year + 1900;
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((currentYear % 4 == 0 && currentYear % 100 != 0) || (currentYear % 400 == 0)) {
        daysInMonth[1] = 29; // Adjust for leap year
    }
  this->totalDays = daysInMonth[currentMonth-1];
  this->heightOfHeader = (height / 5) + 40;
  
  drawHeader(view);
  drawColumns(view);
  drawRows(view);
  drawDays(view);
  
}

 void MonthView::drawHeader(Adafruit_GFX& view){
  uint16_t columnWidth = width / 7;
  view.drawRoundRect(0, 0, width, height, 10, color);
  view.fillRect(0, height / 5, width, 10, color);
  view.setCursor(40, (height/5) + 30);
  for(int counter = 1; counter <= 7; counter++){
    view.print(days[counter-1]);
    view.setCursor(40 + (counter * columnWidth), view.getCursorY());

  }   
  view.drawLine(0, heightOfHeader, width, heightOfHeader, color);
  view.setCursor(20, (height/5) - 20); 
  view.setFont(&FreeSansBold24pt7b);
  view.print(months[currentMonth - 1]);
  view.print(". ");
  view.print(currentDay);
  view.print(" ");
  view.print(currentYear);
  
}

void MonthView::drawColumns(Adafruit_GFX& view){
  uint16_t columnWidth = width / 7;
  for(int counter = 1; counter < 8; counter++){
    view.drawLine(columnWidth * counter, (height / 5), columnWidth * counter, height, color);
  }
}

void MonthView::drawRows(Adafruit_GFX& view){
  uint16_t rowHeight = (height - (heightOfHeader)) / 6;
  for(int counter = 1; counter < 6; counter++){
    view.drawLine(0, (heightOfHeader) + rowHeight * counter, width, (heightOfHeader) + rowHeight * counter, color);
  }
}

void MonthView::drawDays(Adafruit_GFX& view){

  uint16_t columnWidth = width / 7;
  uint16_t rowHeight = (height - (heightOfHeader)) / 6;
  struct tm firstDay = {};
  firstDay.tm_year = currentYear - 1900;
  firstDay.tm_mon = currentMonth-1;
  firstDay.tm_mday = 1;
  mktime(&firstDay); 
  int startWeekday = firstDay.tm_wday; 
  int increment = 0;
 
  view.setCursor(view.getCursorX(), heightOfHeader + 20);
  view.setFont(&FreeMonoBold9pt7b);

  int currentWeekday = startWeekday;
  for(int day = 1; day <= totalDays; day++){ 
    view.setCursor(50 + (currentWeekday * columnWidth), view.getCursorY());
    view.print(day);
    currentWeekday++;
    if(currentWeekday > 6){
      view.setCursor(50, view.getCursorY() + rowHeight);
      currentWeekday = 0;
      continue;
    }
    view.setCursor(view.getCursorX() + columnWidth, view.getCursorY());
    
  }
}
