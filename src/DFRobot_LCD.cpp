/*!
 * @file DFRobot_LCD.cpp
 * @brief Define the subclass of DFRobot_GDL display library, the realization of the screen
 *
 * @copyright Copyright (c) 2010 DFRobot Co. Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [Arya] (xue.peng@dfrobot.com)
 * @version V1.0
 * @date 2019-12-23
 * @https: //github.com/DFRobot/DFRobot_GDL
 */
#include "Arduino.h"
#include "DFRobot_Type.h"
#include "DFRobot_GDL.h"
#include "Interface/DFRobot_IF.h"
#include "Drivers/DFRobot_LCDType.h"

GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x240_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x204_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_R240x204_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x320_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R80x160_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_R80x160_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R128x160_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_R128x160_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ILI9488_R320x480_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ILI9488_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7365P_R320x480_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7365P_initCmd, IF_COM_HW_SPI);
GDL_IF_PB_DEV(gdl_Dev_SSD1306_R128x32_HW_IIC, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_SSD1306_initCmd, IF_COM_HW_IIC);
GDL_IF_PB_DEV(gdl_Dev_ILI9341_R240x320_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ILI9341_initCmd, IF_COM_HW_SPI);

GDL_IF_PB_DEV(gdl_Dev_ST7789_R172x320_HW_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_HW_SPI);


DFRobot_ILI9341_240x320_HW_SPI::DFRobot_ILI9341_240x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ILI9341_R240x320_HW_SPI, 240, 320, dc, cs, rst, bl, pspi){
  setDriverICResolution(ILI9341_IC_WIDTH, ILI9341_IC_HEIGHT);
  madctlReg.madctl = ILI9341_MADCTL;
  madctlReg.args.value = ILI9341_MADCTL_RGB;
  invertOffCmd = ILI9341_INVOFF;
  invertOnCmd = ILI9341_INVON;
}
DFRobot_ILI9341_240x320_HW_SPI::~DFRobot_ILI9341_240x320_HW_SPI(){}
void DFRobot_ILI9341_240x320_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ILI9341_240x320_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq, fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ILI9341_240x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ILI9341_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ILI9341_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ILI9341_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ILI9341_240x320_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7789_240x240_HW_SPI::DFRobot_ST7789_240x240_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x240_HW_SPI, 240, 240, dc, cs, rst, bl,pspi){
  setDriverICResolution(ST7789_IC_WIDTH, ST7789_IC_HEIGHT);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x240_HW_SPI::~DFRobot_ST7789_240x240_HW_SPI(){}

void DFRobot_ST7789_240x240_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ST7789_240x240_HW_SPI::begin(devInterfaceInit fun, uint32_t freq){
  gdlInit(freq, fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_240x240_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x240_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}


DFRobot_ST7789_172x320_HW_SPI::DFRobot_ST7789_172x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7789_R172x320_HW_SPI, 172, 320, dc, cs, rst, bl,pspi){
  setDriverICResolution(172, 320);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_172x320_HW_SPI::~DFRobot_ST7789_172x320_HW_SPI(){}

void DFRobot_ST7789_172x320_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq, fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_172x320_HW_SPI::begin(uint32_t freq){
  begin(NULL, freq);
}
void DFRobot_ST7789_172x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  switch(rotation){
      case 0:
      case 2:
            _xStart = 34;
            _yStart = 0;
            break;
      case 1:
      case 3:
            _xStart = 0;
            _yStart = 34;
            break;
  }
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_172x320_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}


DFRobot_ST7789_240x204_HW_SPI::DFRobot_ST7789_240x204_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x204_HW_SPI, 240, 204, dc, cs, rst, bl,pspi){
  setDriverICResolution(240, 204);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x204_HW_SPI::~DFRobot_ST7789_240x204_HW_SPI(){}
void DFRobot_ST7789_240x204_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ST7789_240x204_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq, fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}

void DFRobot_ST7789_240x204_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x204_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7789_240x320_HW_SPI::DFRobot_ST7789_240x320_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x320_HW_SPI, 240, 320, dc, cs, rst, bl,pspi){
  setDriverICResolution(ST7789_IC_WIDTH, ST7789_IC_HEIGHT);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x320_HW_SPI::~DFRobot_ST7789_240x320_HW_SPI(){}
void DFRobot_ST7789_240x320_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ST7789_240x320_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq, fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_240x320_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x320_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}
DFRobot_ST7735_80x160_HW_SPI::DFRobot_ST7735_80x160_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R80x160_HW_SPI, ST7735S_R80x160_IC_WIDTH, ST7735S_R80x160_IC_HEIGHT, dc, cs, rst, bl,pspi){
  setDriverICResolution(ST7735S_R80x160_IC_WIDTH, ST7735S_R80x160_IC_HEIGHT);
  madctlReg.madctl = ST7735S_MADCTL;
  madctlReg.args.value = ST7735S_R80x160_MADCTL_RGB;
  invertOffCmd = ST7735S_INVOFF;
  invertOnCmd = ST7735S_INVON;
}
DFRobot_ST7735_80x160_HW_SPI::~DFRobot_ST7735_80x160_HW_SPI(){}
void DFRobot_ST7735_80x160_HW_SPI::begin(uint32_t freq)
{
  begin(NULL,freq);
}
void DFRobot_ST7735_80x160_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq,fun);
  initDisplay();
  setRotation(1);
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7735_80x160_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) ;
  //Serial.println(rotation);
  switch(rotation){
      case 0:
      case 2:
            _xStart = 24;
            _yStart = 0;
            break;
      case 1:
      case 3:
            _xStart = 0;
            _yStart = 24;
            break;
  }
 // Serial.println(_xStart);
 // Serial.println(_yStart);
  sendCommand(ST7735S_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7735S_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7735S_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7735_80x160_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}


DFRobot_ST7735_128x160_HW_SPI::DFRobot_ST7735_128x160_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R128x160_HW_SPI, ST7735S_R128x160_IC_WIDTH, ST7735S_R128x160_IC_HEIGHT, dc, cs, rst, bl,pspi){
  setDriverICResolution(ST7735S_R128x160_IC_WIDTH, ST7735S_R128x160_IC_HEIGHT);
  madctlReg.madctl = ST7735S_MADCTL;
  madctlReg.args.value = ST7735S_R128x160_MADCTL_RGB;
  invertOffCmd = ST7735S_INVOFF;
  invertOnCmd = ST7735S_INVON;
}
DFRobot_ST7735_128x160_HW_SPI::~DFRobot_ST7735_128x160_HW_SPI(){}
void DFRobot_ST7735_128x160_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ST7735_128x160_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq,fun);
  initDisplay();
  setRotation(1);
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7735_128x160_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) ;
  //Serial.println(rotation);
  switch(rotation){
      case 0:
      case 2:
            _xStart = 2;
            _yStart = 1;
            break;
      case 1:
      case 3:
            _xStart = 1;
            _yStart = 2;
            break;
  }
 // Serial.println(_xStart);
 // Serial.println(_yStart);
  sendCommand(ST7735S_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7735S_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7735S_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7735_128x160_HW_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}


DFRobot_ILI9488_320x480_HW_SPI::DFRobot_ILI9488_320x480_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ILI9488_R320x480_HW_SPI, 320, 480, dc, cs, rst, bl,pspi){
  setDriverICResolution(ILI9488_IC_WIDTH, ILI9488_IC_HEIGHT);
  madctlReg.madctl = ILI9488_MADCTL;
  madctlReg.args.value = ILI9488_MADCTL_RGB;
  invertOffCmd = ILI9488_INVOFF;
  invertOnCmd = ILI9488_INVON;
}
DFRobot_ILI9488_320x480_HW_SPI::~DFRobot_ILI9488_320x480_HW_SPI(){}
void DFRobot_ILI9488_320x480_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ILI9488_320x480_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq,fun);
  initDisplay();
  setColorMode(COLOR_MODE_RGB666);
}
void DFRobot_ILI9488_320x480_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ILI9488_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ILI9488_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ILI9488_RAMWR);
  //sendColor(rgb666, 3, (uint32_t)w*h);
}
void DFRobot_ILI9488_320x480_HW_SPI::pushColor(uint8_t *color,uint32_t len){
  uint8_t rgb666[3];
  uint16_t col = color[1]<<8 | color[0];
  rgb565ToRGB666(rgb666, col);
  sendColor(rgb666, 3, (uint32_t)len);
}

DFRobot_ST7365P_320x480_HW_SPI::DFRobot_ST7365P_320x480_HW_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl, SPIClass *pspi)
  :DFRobot_GDL(&gdl_Dev_ST7365P_R320x480_HW_SPI, 320, 480, dc, cs, rst, bl,pspi){
  setDriverICResolution(ST7365P_IC_WIDTH, ST7365P_IC_HEIGHT);
  madctlReg.madctl = ST7365P_MADCTL;
  madctlReg.args.value = ST7365P_MADCTL_RGB;
  invertOffCmd = ST7365P_INVOFF;
  invertOnCmd = ST7365P_INVON;
}
DFRobot_ST7365P_320x480_HW_SPI::~DFRobot_ST7365P_320x480_HW_SPI(){}
void DFRobot_ST7365P_320x480_HW_SPI::begin(uint32_t freq)
{
  begin(NULL, freq);
}
void DFRobot_ST7365P_320x480_HW_SPI::begin(devInterfaceInit fun, uint32_t freq)
{
  gdlInit(freq,fun);
  initDisplay();
  invertDisplay(1);
  setColorMode(COLOR_MODE_RGB666);
}
void DFRobot_ST7365P_320x480_HW_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7365P_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7365P_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7365P_RAMWR);
  //sendColor(rgb666, 3, (uint32_t)w*h);
}
void DFRobot_ST7365P_320x480_HW_SPI::pushColor(uint8_t *color,uint32_t len){
  uint8_t rgb666[3];
  uint16_t col = color[1]<<8 | color[0];
  rgb565ToRGB666(rgb666, col);
  sendColor(rgb666, 3, (uint32_t)len);
}
void DFRobot_ST7365P_320x480_HW_SPI::setRotation(uint8_t r){
  if(madctlReg.madctl == 0) return;
  if(madctlReg.madctl == 0xA0){
      rotation = r&1;
      switch(rotation){
          case 0:
                sendCommand(madctlReg.madctl);
                sendCommand(madctlReg.args.value);
                break;
          case 1:
                sendCommand(madctlReg.madctl | 1);
                sendCommand(madctlReg.args.value | 8);
                break;
      }
  }else{
        rotation = r&3;
        uint8_t temp = madctlReg.args.value;
        switch(rotation){
            case 0:
                _width = WIDTH;
                _height = HEIGHT;
                _xStart = 0;
                _yStart = 0;
                break;
            case 1:
                madctlReg.args.mv = 1;
                madctlReg.args.mx = 0; //The ST7365P screen has been horizontally mirrored.
                _width = HEIGHT;
                _height = WIDTH;
                _xStart = 0;
                _yStart = 0;
                break;
            case 2:
			
                madctlReg.args.my = 1;
                madctlReg.args.mx = 0; //The ST7365P screen has been horizontally mirrored.
                _width = WIDTH;
                _height = HEIGHT;
                _xStart = 0;
                _yStart = _icHeight - HEIGHT;
                break;
            default:
                madctlReg.args.mv = 1;
                madctlReg.args.my = 1;
                _width = HEIGHT;
                _height = WIDTH;
                _xStart = _icHeight - HEIGHT;
                _yStart = 0;
                break;
        }
        sendCommand(madctlReg.madctl, &madctlReg.args.value, 1,true);
        madctlReg.args.value = temp;
  }
}

DFRobot_SSD1306_128x32_HW_IIC::DFRobot_SSD1306_128x32_HW_IIC(uint8_t addr, uint8_t rst, uint8_t bl, TwoWire *pwire)
  :DFRobot_GDL(&gdl_Dev_SSD1306_R128x32_HW_IIC, 128, 32, addr, rst, bl,pwire){
  invertOffCmd = SSD1306_INVOFF;
  invertOnCmd = SSD1306_INVON;
  madctlReg.madctl = SSD1306_REMAP;
  madctlReg.args.value = SSD1306_SCANDIR;
}

DFRobot_SSD1306_128x32_HW_IIC::~DFRobot_SSD1306_128x32_HW_IIC(){
  
}

void DFRobot_SSD1306_128x32_HW_IIC::begin(uint32_t freq){
  begin(NULL, freq);
}

void DFRobot_SSD1306_128x32_HW_IIC::begin(devInterfaceInit fun, uint32_t freq){
  gdlInit(freq, fun);
  _lcd.buffer = (uint8_t *)malloc(128*64/8);
  memset(_lcd.buffer,0xff,128*64/8);
  initDisplay();//Init display
  setColorMode(COLOR_MODE_SINGLE);
}

void DFRobot_SSD1306_128x32_HW_IIC::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h){
	/*
  //if((x + w ) > _width || (y + h) > _height) return;
  if(x == 0 && y == 0 && w == (uint16_t)_width && h == (uint16_t)_height){
      color ? memset(_lcd.buffer, 0xFF, _width*_height/8) : memset(_lcd.buffer, 0x00, _width*_height/8);
  }else{
      uint16_t index = 0, bi = 0;
      for(uint16_t i = x; i < x+w; i++){
          for(uint16_t j = y; j < y+h; j++){
              index = ((j/8)*128) + i;
              bi = j % 8;
              _lcd.buffer[index] = (color ? _lcd.buffer[index] | (1 << bi) : _lcd.buffer[index] & ~(1 << bi));
          }
      }
  }
  */
  x=x;y=y;w=w;h=h;
  sendCommand(SSD1306_COLSET);
  sendCommand(SSD1306_STARTCOL);
  sendCommand(SSD1306_ENDCOL);
  sendCommand(SSD1306_PAGESET);
  sendCommand(SSD1306_STARTPAGE);
  sendCommand(SSD1306_ENDPAGE);
}
void DFRobot_SSD1306_128x32_HW_IIC::pushColor(uint8_t *color,uint32_t len){
     /*?*/
     color=color;len=len;
}

#ifdef ARDUINO_SAM_ZERO
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x240_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x204_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_R240x204_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R240x320_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R80x160_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_R80x160_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7735S_R128x160_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7735S_R128x160_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ILI9488_R320x480_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ILI9488_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7365P_R320x480_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7365P_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ILI9341_R240x320_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ILI9341_initCmd, IF_COM_DMA_SPI);
GDL_IF_PB_DEV(gdl_Dev_ST7789_R172x320_DMA_SPI, DEV_TYPE_SCREEN, (uint8_t *)DFRobot_ST7789_initCmd, IF_COM_DMA_SPI);

DFRobot_ST7789_240x240_DMA_SPI::DFRobot_ST7789_240x240_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x240_DMA_SPI, 240, 240, dc, cs, rst, bl){
  setDriverICResolution(ST7789_IC_WIDTH, ST7789_IC_HEIGHT);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x240_DMA_SPI::~DFRobot_ST7789_240x240_DMA_SPI(){}
void DFRobot_ST7789_240x240_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_240x240_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x240_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7789_240x204_DMA_SPI::DFRobot_ST7789_240x204_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x204_DMA_SPI, 240, 204, dc, cs, rst, bl){
  setDriverICResolution(240, 204);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x204_DMA_SPI::~DFRobot_ST7789_240x204_DMA_SPI(){}
void DFRobot_ST7789_240x204_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_240x204_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x204_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7789_172x320_DMA_SPI::DFRobot_ST7789_172x320_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R172x320_DMA_SPI, 172, 320, dc, cs, rst, bl){
  setDriverICResolution(172, 320);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_172x320_DMA_SPI::~DFRobot_ST7789_172x320_DMA_SPI(){}
void DFRobot_ST7789_172x320_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_172x320_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  _xStart = 32;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_172x320_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7735_80x160_DMA_SPI::DFRobot_ST7735_80x160_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R80x160_DMA_SPI, ST7735S_R80x160_IC_WIDTH, ST7735S_R80x160_IC_HEIGHT, dc, cs, rst, bl){
  setDriverICResolution(ST7735S_R80x160_IC_WIDTH, ST7735S_R80x160_IC_HEIGHT);
  madctlReg.madctl = ST7735S_MADCTL;
  madctlReg.args.value = ST7735S_R80x160_MADCTL_RGB;
  invertOffCmd = ST7735S_INVOFF;
  invertOnCmd = ST7735S_INVON;
}
DFRobot_ST7735_80x160_DMA_SPI::~DFRobot_ST7735_80x160_DMA_SPI(){}
void DFRobot_ST7735_80x160_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
   setRotation(1);
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7735_80x160_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  
  switch(rotation){
      case 0:
      case 2:
            _xStart = 24;
            _yStart = 0;
            break;
      case 1:
      case 3:
            _xStart = 0;
            _yStart = 24;
            break;
  }
  
  sendCommand(ST7735S_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7735S_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7735S_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7735_80x160_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7735_128x160_DMA_SPI::DFRobot_ST7735_128x160_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7735S_R128x160_DMA_SPI, ST7735S_R128x160_IC_WIDTH, ST7735S_R128x160_IC_HEIGHT, dc, cs, rst, bl){
  setDriverICResolution(ST7735S_R128x160_IC_WIDTH, ST7735S_R128x160_IC_HEIGHT);
  madctlReg.madctl = ST7735S_MADCTL;
  madctlReg.args.value = ST7735S_R128x160_MADCTL_RGB;
  invertOffCmd = ST7735S_INVOFF;
  invertOnCmd = ST7735S_INVON;

}
DFRobot_ST7735_128x160_DMA_SPI::~DFRobot_ST7735_128x160_DMA_SPI(){}
void DFRobot_ST7735_128x160_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setRotation(1);
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7735_128x160_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  
  switch(rotation){
      case 0:
      case 2:
            _xStart = 2;
            _yStart = 1;
            break;
      case 1:
      case 3:
            _xStart = 1;
            _yStart = 2;
            break;
  }
  
  sendCommand(ST7735S_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7735S_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7735S_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7735_128x160_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}

DFRobot_ST7789_240x320_DMA_SPI::DFRobot_ST7789_240x320_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7789_R240x320_DMA_SPI, 240, 320, dc, cs, rst, bl){
  setDriverICResolution(ST7789_IC_WIDTH, ST7789_IC_HEIGHT);
  madctlReg.madctl = ST7789_MADCTL;
  madctlReg.args.value = ST7789_MADCTL_RGB;
  invertOffCmd = ST7789_INVOFF;
  invertOnCmd = ST7789_INVON;
}
DFRobot_ST7789_240x320_DMA_SPI::~DFRobot_ST7789_240x320_DMA_SPI(){}
void DFRobot_ST7789_240x320_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ST7789_240x320_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ST7789_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ST7789_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ST7789_RAMWR);
  //sendColor(color, (uint32_t)w*h);
}
void DFRobot_ST7789_240x320_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}
DFRobot_ILI9488_320x480_DMA_SPI::DFRobot_ILI9488_320x480_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ILI9488_R320x480_DMA_SPI, 320, 480, dc, cs, rst, bl){
  setDriverICResolution(ILI9488_IC_WIDTH, ILI9488_IC_HEIGHT);
  madctlReg.madctl = ILI9488_MADCTL;
  madctlReg.args.value = ILI9488_MADCTL_RGB;
  invertOffCmd = ILI9488_INVOFF;
  invertOnCmd = ILI9488_INVON;
}
DFRobot_ILI9488_320x480_DMA_SPI::~DFRobot_ILI9488_320x480_DMA_SPI(){}
void DFRobot_ILI9488_320x480_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB666);
  
}
void DFRobot_ILI9488_320x480_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(0x2A);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(0x2B);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(0x2C);
}


void DFRobot_ILI9488_320x480_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
  uint8_t rgb666[3];
  uint16_t col = color[1]<<8 | color[0];
  rgb565ToRGB666(rgb666, col);
  sendColor(rgb666, sizeof(rgb666), (uint32_t)len);
}


DFRobot_ST7365P_320x480_DMA_SPI::DFRobot_ST7365P_320x480_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ST7365P_R320x480_DMA_SPI, 320, 480, dc, cs, rst, bl){
  setDriverICResolution(ST7365P_IC_WIDTH, ST7365P_IC_HEIGHT);
  madctlReg.madctl = ST7365P_MADCTL;
  madctlReg.args.value = ST7365P_MADCTL_RGB;
  invertOffCmd = ST7365P_INVOFF;
  invertOnCmd = ST7365P_INVON;
}
DFRobot_ST7365P_320x480_DMA_SPI::~DFRobot_ST7365P_320x480_DMA_SPI(){}
void DFRobot_ST7365P_320x480_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB666);
  invertDisplay(1);
}
void DFRobot_ST7365P_320x480_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(0x2A);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(0x2B);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(0x2C);
}


void DFRobot_ST7365P_320x480_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
  uint8_t rgb666[3];
  uint16_t col = color[1]<<8 | color[0];
  rgb565ToRGB666(rgb666, col);
  sendColor(rgb666, sizeof(rgb666), (uint32_t)len);
}

void DFRobot_ST7365P_320x480_DMA_SPI::setRotation(uint8_t r){
  if(madctlReg.madctl == 0) return;
  if(madctlReg.madctl == 0xA0){
      rotation = r&1;
      switch(rotation){
          case 0:
                sendCommand(madctlReg.madctl);
                sendCommand(madctlReg.args.value);
                break;
          case 1:
                sendCommand(madctlReg.madctl | 1);
                sendCommand(madctlReg.args.value | 8);
                break;
      }
  }else{
        rotation = r&3;
        uint8_t temp = madctlReg.args.value;
        switch(rotation){
            case 0:
                _width = WIDTH;
                _height = HEIGHT;
                _xStart = 0;
                _yStart = 0;
                break;
            case 1:
                madctlReg.args.mv = 1;
                madctlReg.args.mx = 0;
                _width = HEIGHT;
                _height = WIDTH;
                _xStart = 0;
                _yStart = 0;
                break;
            case 2:
			
                madctlReg.args.my = 1;
                madctlReg.args.mx = 0;
                _width = WIDTH;
                _height = HEIGHT;
                _xStart = 0;
                _yStart = _icHeight - HEIGHT;
                break;
            default:
                madctlReg.args.mv = 1;
                madctlReg.args.my = 1;
                _width = HEIGHT;
                _height = WIDTH;
                _xStart = _icHeight - HEIGHT;
                _yStart = 0;
                break;
        }
        sendCommand(madctlReg.madctl, &madctlReg.args.value, 1,true);
        madctlReg.args.value = temp;
  }
}
DFRobot_ILI9341_240x320_DMA_SPI::DFRobot_ILI9341_240x320_DMA_SPI(uint8_t dc, uint8_t cs, uint8_t rst, uint8_t bl)
  :DFRobot_GDL(&gdl_Dev_ILI9341_R240x320_DMA_SPI, 240, 320, dc, cs, rst, bl){
  setDriverICResolution(ILI9341_IC_WIDTH, ILI9341_IC_HEIGHT);
  madctlReg.madctl = ILI9341_MADCTL;
  madctlReg.args.value = ILI9341_MADCTL_RGB;
  invertOffCmd = ILI9341_INVOFF;
  invertOnCmd = ILI9341_INVON;
}
DFRobot_ILI9341_240x320_DMA_SPI::~DFRobot_ILI9341_240x320_DMA_SPI(){}
void DFRobot_ILI9341_240x320_DMA_SPI::begin(uint32_t freq)
{
  gdlInit(freq);
  initDisplay();
  setColorMode(COLOR_MODE_RGB565);
}
void DFRobot_ILI9341_240x320_DMA_SPI::setDisplayArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if((x + w ) > _width || (y + h) > _height) return;
  sendCommand(ILI9341_COLSET);
  sendData16(_xStart + x);
  sendData16(_xStart + x + w -1);
  sendCommand(ILI9341_RAWSET);
  sendData16(_yStart + y);
  sendData16(_yStart + y + h -1);
  sendCommand(ILI9341_RAMWR);
}
void DFRobot_ILI9341_240x320_DMA_SPI::pushColor(uint8_t *color,uint32_t len){
     uint16_t col = color[1]<<8 | color[0];
     sendColor(col, len);
}
#endif//end M0
