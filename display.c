// --- display.c ---
#include "display.h"

// LCD Pin Definitions (Example: D12-D8 for RS, E, D4-D7)
#define LCD_RS  PB4 // D12
#define LCD_E   PB5 // D13
// NOTE: Actual D4-D7 pins must be defined and used for 4-bit mode.

void LCD_command(uint8_t cmd) {
    // Placeholder for LCD_write(cmd, 0); 
}

void LCD_data(uint8_t data) {
    // Placeholder for LCD_write(data, 1);
}

void LCD_Init(void) {
    // 1. Set all LCD pins as outputs
    DDRB |= (1<<LCD_RS) | (1<<LCD_E);
    // ...DDRD |= (1<<LCD_D4) | ...
    
    _delay_ms(20); 
    
    // 2. Initialization Sequence (4-bit mode commands)
    LCD_command(0x33);
    LCD_command(0x32);
    LCD_command(0x28); // Function set
    LCD_command(0x0C); // Display ON
    LCD_command(0x01); // Clear Display
    _delay_ms(2);
}

void LCD_Update_Status(const char *line1, const char *line2) {
    // 1. Clear display and set cursor (command 0x80)
    
    // 2. Loop through line1 chars and call LCD_data()
    
    // 3. Set cursor for line 2 (command 0xC0)
    
    // 4. Loop through line2 chars and call LCD_data()
}