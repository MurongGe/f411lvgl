//
// Created by ShunX on 2023/7/6.
//

#include "lcd_io.h"
#include <stdio.h>


uint8_t lcdbuffer[1024] __ALIGNED(4);
/* spi send a byte */
static __IO uint8_t dma_cplt = 1;
#define DMA_TIMEOUT 0xffff00

void LCD_Writ_Bus(uint8_t dat)
{
  LCD_CS_LOW;
#ifdef USE_HAL_INTFC
  HAL_SPI_Transmit(&LCD_SPI_INTERFACE, &dat, 1, 1000);
#else
  uint8_t i;
  for (i = 0; i < 8; i++) {
    LCD_SCL_LOW;
    if (dat & 0x80) {
      LCD_SDA_HIGH;
    } else {
      LCD_SDA_LOW;
    }
    LCD_SCL_HIGH;
    dat <<= 1;
  }
#endif
  LCD_CS_HIGH;
}

void LCD_WR_DATAS(uint16_t sizeof16, uint8_t *buff)
{
  uint32_t dma_timeout = DMA_TIMEOUT;
#ifdef USE_HAL_INTFC
  LCD_CS_LOW;
#ifdef USE_SPI_DMA_TRANS
  dma_cplt = 0;
  HAL_SPI_Transmit_DMA(&LCD_SPI_INTERFACE, buff, sizeof16 * 2);
  while (dma_cplt == 0) {
    dma_timeout--;
    if (dma_timeout == 0) {
      printf("dma trans timeout\r\n");
    }
  }
#else
    HAL_SPI_Transmit(&LCD_SPI_INTERFACE, buff, sizeof16 * 2, 1000);
#endif

  LCD_CS_HIGH;
#else
  uint8_t i;
  for (i = 0; i < poxs; i++) {
    LCD_Writ_Bus(lcdbuffer[i * 2]);
    LCD_Writ_Bus(lcdbuffer[2 * i + 1]);
  }
#endif
}

/* LCD Write byte DATA */
void LCD_WR_DATA8(uint8_t dat)
{
  LCD_Writ_Bus(dat);
}

/* LCD Write 2bytes DATA */
void LCD_WR_DATA16(uint16_t dat)
{
  LCD_Writ_Bus(dat >> 8);
  LCD_Writ_Bus(dat);
}

/* LCD Write CMD byte */
void LCD_WR_REG(uint8_t cmd)
{
  LCD_DC_LOW;
  LCD_Writ_Bus(cmd);
  LCD_DC_HIGH;
}

/* lcd spi dma trans complete callback */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == LCD_SPI_INTERFACE.Instance) {
    dma_cplt = 1;
  }
}