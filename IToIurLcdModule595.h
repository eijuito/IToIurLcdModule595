/*
   Nome do Aquivo:   IToIurLcdModule595.h
   Descrição:        Library to enable LCD using IToOutputModule595
   Data criada:      2016-08-06
   Versao do Aquivo: 2016-08-10
   Dependências:     IToOutputModule595
   Escrito por:      Celso Eiju Ito - eijuito@gmail.com
   	   	   	   	   	 Rui Lopes Viana - ruianaiv@gmail.com
   MCU:              ATMEGA 328P 16 MHz
   Board:            Arduino Uno/Mega/Mini
   Compilador        GCC para Arduino
   IDE:              Eclipse Mars CDT 8.8.1 com plugin Arduino C++ Jantje Baeyens 3.0.0
   Hardware:         Arduino UNO
   Colaboradores:    Rui Viana - ruianaiv@gmail.com
                     Natalia Ayako Takano - natalia.takano@gmail.com
   Uso:              Generico
   Diagrams:         http://github.com/eijuito/IToOutputModule595
                     http://www.labirito.com/projetos/itooutputmodule74595
                             +--\__/--+
                     DB5[ ]1 |        | 16[ ]+V
                     DB6[ ]2 |        | 15[ ]DB5
                     DB7[ ]3 |        | 14[ ]DAT
                     ENA[ ]4 |        | 13[ ]GND
                     RW [ ]5 |        | 12[ ]LTC
                     RS [ ]6 |        | 11[ ]CLK
                     ---[ ]7 |        | 10[ ]+V
                     GND[ ]1 |        | 9 [ ]OUT
                             +--------+
   Copyright ®       2016 Celso Eiju Ito eijuito@gmail.com (www.itosa.com.br)
                     Este programa e de propriedade do Celso Eiju Ito eijuito@gmail.com
                     E vedada a copia total ou parcial por pessoas nao autorizadas
                     Nao e permitida a comercializacao ou locacao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   REVISIONS: (latest entry first)
   2016-08-10 Tests with 1 and 2 LCDs and updated code
   2016-08-06 Primeira versao
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   NEXT STEPS: (priority first)
   Review
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef ITOIURLCDMODULE595_H_
#define ITOIURLCDMODULE595_H_
#define ITOIURLCDMODULE595_VERSION "IToOutputModule595 v0.1.0"

#include "Print.h"
#include "IToOutputModule595.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define LCD_PIN_DB4       0x01 // Pino 15 do 74HC595 ligado no DB4 do modulo LCD
#define LCD_PIN_DB5       0x02 // Pino 1 do 74HC595 ligado no DB5 do modulo LCD
#define LCD_PIN_DB6       0x04 // Pino 2 do 74HC595 ligado no DB6 do modulo LCD
#define LCD_PIN_DB7       0x08 // Pino 3 do 74HC595 ligado no DB7 do modulo LCD
#define LCD_PIN_RS        0x10 // Pino 6 do 74HC595 ligado no RS(4) do modulo LCD - LOW:command  HIGH:data
#define LCD_PIN_READWRITE 0x20 // Pino 5 do 74HC595 ligado no RW(5) do modulo - LCD LOW:write HIGH:read
#define LCD_PIN_ENABLE    0x40 // Pino 4 do 74HC595 ligado no ENA(6) do modulo LCD - LOW:Desabilitado HIGH:habilitado

class IToIurLcdModule595 : public Print {
public:
	IToIurLcdModule595(IToOutputModule595* outs, uint8_t module = 0);
	virtual ~IToIurLcdModule595();
	bool begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
	void clear();
	void home();
	void setCursor(uint8_t cols, uint8_t rows);

	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();

	void createChar(uint8_t location, uint8_t charmap[]);
	void command(uint8_t value);
	size_t write(uint8_t value);
	using Print::write;

private:
	void send(uint8_t value, uint8_t mode);
	void pulseEnable();
	void setRowOffsets(int row1, int row2, int row3, int row4);
	void write4bits(uint8_t value);

	uint8_t _module = -1;
	IToOutputModule595* _outs;

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;

	uint8_t _numlines;
	uint8_t _row_offsets[4];
};

#endif /* ITOIURLCDMODULE595_H_ */
