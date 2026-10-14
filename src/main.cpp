#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <../include/MonthView.h>
#include <Fonts/FreeMonoBold9pt7b.h>


GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> display(GxEPD2_750_GDEY075T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW075T7 800x480, EK79655 (GD7965)
MonthView view;

void setup(){
   
  display.init(115200, true, 10, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse  
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK); 
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE); 
    view.draw(display, 30,10,2026);
  }
  while (display.nextPage());

  
  display.powerOff();
}

void loop(){}