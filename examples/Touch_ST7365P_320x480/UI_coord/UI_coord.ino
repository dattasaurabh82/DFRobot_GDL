/*!
 * @file UI_coord.ino
 * @brief Coordinate system control, users can customize the coordinate data in the coordinate system to draw polyline graph
 * @n The demo supports Mega2560, FireBeetle-ESP32, FireBeetle-M0
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2019-12-6
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_GDL
*/


#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"
/*M0*/
#if defined ARDUINO_SAM_ZERO
#define TFT_DC    7
#define TFT_CS    5
#define TFT_RST   6
#define TFT_BL    9
#define TOUCH_RST 10
#define TOUCH_INT 2
#define TOUCH_CS A3
/*ESP32 and ESP8266*/
#elif defined(ESP32)
#define TFT_DC    D2     
#define TFT_CS    D6      
#define TFT_RST   D3    
#define TFT_BL    D13   
#define TOUCH_RST D10
#define TOUCH_INT D11
/* AVR series mainboard */
#else
#define TFT_DC    34
#define TFT_CS    36
#define TFT_RST   35
#define TFT_BL    33
#define TOUCH_RST 31
#define TOUCH_INT 32
#endif

/**
   @brief Constructor  When the touch uses the gt series chip, you can call this constructor
*/

//If you are using the Firebeetle 2 ESP32-E (N16R2) board and connecting the screen through the GDI interface with the address set to 0x14, and other card addresses are set to 0x5D.
DFRobot_Touch_GT911_IPS touch(0X5D,TOUCH_RST,TOUCH_INT);
 
/**
   @brief Constructor When the screen uses hardware SPI communication, the driver IC is ST7365P, and the screen resolution is 320x480, this constructor can be called
   @param dc Command/data line pin for SPI communication
   @param cs Chip select pin for SPI communication
   @param rst Reset pin of the screen
*/
DFRobot_ST7365P_320x480_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);
/* M0 mainboard DMA transfer */
//DFRobot_ST7365P_320x480_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST,/*bl=*/TFT_BL);
 
/**
   @brief Constructor
   @param gdl Screen object
   @param touch Touch object
*/
DFRobot_UI ui(&screen, NULL);

int16_t point3[15][2] ={{0,50},{10,55},{15,65},{20,70},{63,75},{70,80},{80,90},{100,100},{110,110},{112,112},{150,120},{210,130},{230,130},{240,150},{300,190}};
void setup()
{
  
  Serial.begin(9600);
  //Initialize UI
  ui.begin();


  //Create a coordinate 
  DFRobot_UI::sCoordinate_t &coord = ui.creatCoordinate();
  coord.setPoint(point3,15,COLOR_RGB565_RED);
  ui.draw(&coord);

}


void loop()
{
  //Refresh 
  ui.refresh();
}
