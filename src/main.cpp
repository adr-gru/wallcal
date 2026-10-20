#include <Arduino.h>
#include <driver/gpio.h>
#include <GxEPD2_BW.h>
#include <../include/MonthView.h>
#include <Fonts/FreeMonoBold9pt7b.h>


GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> display(GxEPD2_750_GDEY075T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW075T7 800x480, EK79655 (GD7965)
MonthView view;

void setup(){

  // SPI wiring rings at full speed and garbles the image: slow the clock and soften SCK/MOSI edges
  display.epd2.selectSPI(SPI, SPISettings(1000000, MSBFIRST, SPI_MODE0));
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse  
  gpio_set_drive_capability(GPIO_NUM_18, GPIO_DRIVE_CAP_0); // SCK
  gpio_set_drive_capability(GPIO_NUM_23, GPIO_DRIVE_CAP_0); // MOSI
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK); 
  display.setFullWindow();
  display.firstPage();

  struct tm date = {};      // zeroed, so no garbage fields
  date.tm_year = 2026 - 1900;
  date.tm_mon  = 9;
  date.tm_mday = 19;

  time_t timeInSecs = mktime(&date);
  struct timeval currentTime;
  currentTime.tv_sec = timeInSecs;
  currentTime.tv_usec = 0;

  settimeofday(&currentTime, NULL);
  do
  {
    display.fillScreen(GxEPD_WHITE); 
    view.draw(display);
  }
  while (display.nextPage());

  
  display.powerOff();
}

void loop(){}