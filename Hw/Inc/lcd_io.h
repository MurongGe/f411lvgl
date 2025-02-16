//
// Created by ShunX on 2023/7/6.
//

#ifndef TFT169_LCD_IO_H
#define TFT169_LCD_IO_H

#include "main.h"
#include "spi.h"

/* if use hal lib spi */
#define USE_HAL_INTFC
#define USE_SPI_DMA_TRANS

/* lcd delay */
#define lcd_delay HAL_Delay

#ifndef USE_HAL_INTFC
/* lcd spi soft */
#define LCD_SCL_LOW HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_RESET)
#define LCD_SCL_HIGH HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_SET)
#define LCD_SDA_LOW HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_RESET)
#define LCD_SDA_HIGH HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_SET)
#else
/* lcd spi hardware by hal lib */
#define LCD_SPI_INTERFACE hspi1
#endif

/* lcd other lines option */
#define LCD_CS_LOW 		HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_HIGH 	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_DC_LOW 		HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_HIGH 	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)
#define LCD_RES_LOW 	HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET)
#define LCD_RES_HIGH 	HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)
#define LCD_BLK_LOW 	HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET)
#define LCD_BLK_HIGH 	HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET)


void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA16(uint16_t dat);
void LCD_WR_REG(uint8_t cmd);
void LCD_WR_DATAS(uint16_t sizeof16, uint8_t* buff);

extern uint8_t lcdbuffer[1024];

#endif //TFT169_LCD_IO_H
