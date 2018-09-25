// Counts for how long the machine has been running

#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "lcd.h"

#define keypadDirectionRegisterR DDRC
#define keypadPortControlR PORTC
#define keypadPortValueR PINC
#define keypad_R_0 0
#define keypad_R_1 1
#define keypad_R_2 2
#define keypad_R_3 3

#define keypadDirectionRegisterC DDRC
#define keypadPortControlC PORTC
#define keypadPortValueC PINC
#define keypad_C_0 7
#define keypad_C_1 6
#define keypad_C_2 5
#define keypad_C_3 4

/*
#define ctrl PORTB // We are using port D
#define en 2       // enable signal pin 2
#define rw 1       // read/write signal pin 1
#define rs 0       // register select signal pin 0


void lcd_command(unsigned char cmd);
void lcd_init(void);
void lcd_data(unsigned char data);
void lcdCommand(char);
void lcdData(char);
void lcd_print(unsigned char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_update_time(void);
*/

void keypadScan(void);

int main(void)

{

      

        int key=0;//allocating integer to reset the LCD once it reaches its display limit

        int keypressed=0;//integer for storing matrix value


        LCD4_Init();  // initialization of LCD function
        LCD4_Clear();
        _delay_ms(30);

        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
        LCD4_Write_String("Press 2 key"); // Print the text
        LCD4_Set_Cursor(2, 1);         // Go to the location 1,2 of lcd

      

     

        DDRC=0xF0;//taking column pins as input and row pins as output

        _delay_ms(1);

        PORTC=0x0F;// powering the row ins

        _delay_ms(1);



        while(1)

        {
       
      

        if (PINC!=0b11110000)//in any of column pins goes high execute the loop

        {
                
                //LCD4_Write_Float(PINC);
                //key++;
                       // _delay_ms(5);

                        keypressed = PINC;//taking the column value into integer

                        DDRC ^=0b11111111;//making rows as inputs and columns as ouput

                        _delay_ms(1);

                        PORTC ^= 0b11111111;//powering columns

                        _delay_ms(1);



                        keypressed |=PINC;//taking row value and OR ing it to column value
                //LCD4_Write_Int(keypressed);
                       

                        if (keypressed==119)

                        {

                                        LCD4_Write_String("1");//if row1 and column1 is high show “1”

                                                        key++;

                        }

                        if (keypressed==183)

                        {

                                        LCD4_Write_String("4");// if row1 and column2 is high show “4”

                                                        key++;

                        }

                        if (keypressed==215)

                        {

                                        LCD4_Write_String("7");// if row1 and column3 is high show “7”

                                                        key++;

                        }

                        if (keypressed==231)

                        {

                                        LCD4_Write_String("*");//if row1 and column4 is high show “*”

                                                        key++;

                        }    



                        if (keypressed==123)

                        {

                                        LCD4_Write_String("2");// if row2 and column1 is high show “2”

                                        key++;

                        }

                        if (keypressed==187)

                        {

                                        LCD4_Write_String("5");// if row2 and column2 is high show “5”

                                        key++;

                        }

                        if (keypressed==219)

                        {

                                        LCD4_Write_String("8");// if row2 and column3 is high show “8”

                                        key++;

                        }

                        if (keypressed==235)

                        {

                                        LCD4_Write_String("0");// if row2 and column4 is high show “0”

                                        key++;

                        }

                       

                       

                       

                        if (keypressed==125)                                   

                        {

                                        LCD4_Write_String("3");

                                        key++;

                        }

                        if (keypressed==189)

                        {

                                        LCD4_Write_String("6");

                                        key++;

                        }

                        if (keypressed==221)

                        {

                                        LCD4_Write_String("9");

                                        key++;

                        }

                        if (keypressed==237)

                        {

                                        LCD4_Write_String("#");

                                        key++;

                        }

                       

                       

                       

                        if (keypressed==126)

                        {

                                        LCD4_Write_String("A");

                                        key++;

                        }

                        if (keypressed==190)

                        {

                                        LCD4_Write_String("B");

                                        key++;

                        }

                        if (keypressed==222)

                        {

                                        LCD4_Write_String("C");

                                        key++;

                        }

                        if (keypressed==238)

                        {

                                        LCD4_Write_String("D");

                                        key++;

                        }

                        keypressed=0;//after showing integer erasing the row column memory

                        DDRC ^=0b11111111;//shifting input and power port

                        _delay_ms(1);

                        PORTC ^= 0b11111111;//powering row pins of keypad

                        _delay_ms(220);

                       

        }

        if (key==16)//if 16 characters are shown on LCD

        {
                          LCD4_Clear();
                        _delay_ms(30);

                        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
                        LCD4_Write_String("Press 2 key"); // Print the text
                        LCD4_Set_Cursor(2, 1);         // Go to the location 1,2 of lcd



                      

                        key=0;

        }

        }



}

/*
int main() {
 // DDRD = 0xFF; // Setting DDRD to output // setting for port D
  LCD4_Init();  // initialization of LCD function
  LCD4_Clear();
  _delay_ms(30);

  LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
  LCD4_Write_String("Press a key"); // Print the text
  LCD4_Set_Cursor(1, 2);         // Go to the location 1,2 of lcd

  // Keypad initialization
  keypadDirectionRegisterR = (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3);
  keypadDirectionRegisterC = (0<<keypad_C_0) | (0<<keypad_C_1) | (0<<keypad_C_2) | (0<<keypad_C_3);

  keypadPortControlR = (0<<keypad_R_0) | (0<<keypad_R_1) | (0<<keypad_R_2) | (0<<keypad_R_3);
  keypadPortControlC = (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
  
  while (1) {
      //LCD4_Clear();
      LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
      LCD4_Write_String("Press a key"); // Print the text
      LCD4_Set_Cursor(2, 1);         
      keypadScan();
      _delay_ms(500);
    
    /*
     DDRD = 0xff;                       // setting DDR of PORT B

        //LED on
        PORTD = 0x80;            // PC0 = High = LED attached on PC0 is ON
        _delay_ms(500);                // wait 500 milliseconds

        //LED off
        PORTD = 0x00;            // PC0 = Low = LED attached on PC0 is OFF
        _delay_ms(500);                // wait 500 milliseconds
 /*       */
 /* };

  return 0;
}
*/
void keypadScan(){
  
  // Store value for column
  uint8_t keyPressCodeC = keypadPortValueC;
  
      keypadDirectionRegisterC ^= (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
      keypadDirectionRegisterR ^= (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3); 
  
      keypadPortControlC ^= (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
      keypadPortControlR ^= (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3);
      
      _delay_ms(50);
  
      // Store value for row
      int temp = keypadPortValueR;
      uint8_t keyPressCodeR = temp << 4;
  
      // Add value for column and row
      uint8_t keyPressCode = keyPressCodeC | keyPressCodeR;
      LCD4_Write_Float(keyPressCode);
  
      uint8_t blinkDuration = 0;
  
      // Comparison and resultant action
  
      // Column one

      if(keyPressCode == 0b11101110){
        LCD4_Write_String("a");
      }
      if(keyPressCode == 0b11011110){
        LCD4_Write_String("b");
      }
      if(keyPressCode == 0b10111110){
        LCD4_Write_String("c");
      }
      if(keyPressCode == 0b01111110){
        LCD4_Write_String("d");
      }
  
      // Column two
      if(keyPressCode == 0b11101101){
        LCD4_Write_String("e");
      }
      if(keyPressCode == 0b11011101){
        LCD4_Write_String("f");
      }
      if(keyPressCode == 0b10111101){
        LCD4_Write_String("g");;
      }
      if(keyPressCode == 0b01111101){
        LCD4_Write_String("h");
      }
  
      // Column three
      if(keyPressCode == 0b11101011){
        LCD4_Write_String("i");
      }
      if(keyPressCode == 0b11011011){
        LCD4_Write_String("j");;
      }
      if(keyPressCode == 0b10111011){
        LCD4_Write_String("k");
      }
      if(keyPressCode == 0b01111011){
        LCD4_Write_String("l");
      }
  
      // Column four
      if(keyPressCode == 0b11100111){
        LCD4_Write_String("m");
      }
      if(keyPressCode == 0b11010111){
        LCD4_Write_String("n");
      }
      if(keyPressCode == 0b10110111){
        LCD4_Write_String("o");
      }
      if(keyPressCode == 0b01110111){
        LCD4_Write_String("p");
      }
  
}
/*
// Function moving to a given position on the LCD screen
void lcd_gotoxy(unsigned char x, unsigned char y) {
  unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
  lcdCommand(firstCharAdr[y - 1] + x - 1);
  _delay_ms(0.1);
}

void lcd_init(void) {
  lcdCommand(0x02); // To initialize LCD in 4-bit mode.
  _delay_ms(1);
  lcdCommand(0x28); // To initialize LCD in 2 lines, 5X7 dots and 4bit mode.
  _delay_ms(1);
  lcdCommand(0x01); // Clear LCD
  _delay_ms(1);
  lcdCommand(0x0E); // Turn on cursor ON
  _delay_ms(1);
  lcdCommand(0x80); // —8 go to first line and –0 is for 0th position
  _delay_ms(1);
  return;
}

void lcdCommand(char cmd_value) {
  char cmd_value1;
  cmd_value1 = cmd_value & 0xF0;          // Mask lower nibble
                                          // because PD4-PD7 pins are used.
  lcd_command(cmd_value1);                // Send to LCD
  cmd_value1 = ((cmd_value << 4) & 0xF0); // Shift 4-bit and mask
  lcd_command(cmd_value1);                // Send to LCD
}

void lcdData(char data_value) {
  char data_value1;
  data_value1 = data_value & 0xF0;          // Mask lower nibble
  lcd_data(data_value1);                    // because PD4-PD7 pins are used.
  data_value1 = ((data_value << 4) & 0xF0); // Shift 4-bit and mask
  lcd_data(data_value1);                    // Send to LCD
}

void lcd_command(unsigned char cmd) {
  ctrl = cmd;
  ctrl &= ~(1 << rs); // RS = 0 for command
  ctrl &= ~(1 << rw); // RW = 0 for write
  ctrl |= (1 << en);  // EN = 1 for High to Low pulse
  _delay_ms(1);
  ctrl &= ~(1 << en); // EN = 0 for High to Low pulse
  _delay_ms(40);
  return;
}

void lcd_data(unsigned char data) {
  ctrl = data;
  ctrl |= (1 << rs);  // RS = 1 for data
  ctrl &= ~(1 << rw); // RW = 0 for write
  ctrl |= (1 << en);  // EN = 1 for High to Low pulse
  _delay_ms(1);
  ctrl &= ~(1 << en); // EN = 0 for High to Low Pulse
  _delay_ms(40);
  return;
}

void lcd_print(
    unsigned char *str) { // store address value of the string in pointer *str
  int i = 0;
  while (str[i] !=
         '\0') {     // loop will go on till the NULL character in the string
    lcdData(str[i]); // sending data on LCD byte by byte
    i++;
  }
  return;
}
*/
