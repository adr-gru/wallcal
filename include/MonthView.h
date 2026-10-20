#pragma once
#include <Adafruit_GFX.h>

class MonthView{
 
  public:
  uint16_t color;
  uint16_t width;
  uint16_t height;
  uint16_t currentDay;
  uint16_t currentMonth;
  uint16_t currentYear;
  uint16_t heightOfHeader;
  uint16_t totalDays;

  void draw(Adafruit_GFX& view);

  private:
    void drawColumns(Adafruit_GFX& view);
    void drawRows(Adafruit_GFX& view);
    void drawHeader(Adafruit_GFX& view);
    void drawDays(Adafruit_GFX& view);


};