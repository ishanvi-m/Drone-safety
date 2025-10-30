// --- display.h ---
#ifndef DISPLAY_H
#define DISPLAY_H
#include <avr/io.h>
#include <util/delay.h>

#ifdef __cplusplus
extern "C" {
#endif

void LCD_Init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_Update_Status(const char *line1, const char *line2);

#ifdef __cplusplus
}
#endif

#endif