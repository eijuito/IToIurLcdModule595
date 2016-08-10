/*
 * IToIurLcdModule595.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: Administrator
 */

#include "IToIurLcdModule595.h"

IToIurLcdModule595::IToIurLcdModule595(IToOutputModule595* outs, uint8_t module) {
	if(module < outs->NumModules()) {
		_outs = outs;
		_module = module;
		_displayfunction = LCD_1LINE;
		_displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
		_displaymode = LCD_ENTRYRIGHT | LCD_ENTRYSHIFTINCREMENT;
		_numlines = 1;
	}
}

IToIurLcdModule595::~IToIurLcdModule595() {
}

bool IToIurLcdModule595::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
	if(rows == 2) _displayfunction |= LCD_2LINE;
	if(_module < 0) return false; // retorna false se houver erro ex.: _module > max modulos
	_outs->SetModule(0, _module); // Zera saida do 595
	_numlines = rows;
	setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);
	// for some 1 line displays you can select a 10 pixel high font
	if ((charsize != LCD_5x8DOTS) && (rows == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}
	delay(15);                    // Tempo de power on
	write4bits(3);                // Envia Hex 3  Interface 8 bits long ??
	delayMicroseconds(4500);      // wait min 4.1ms
	write4bits(3);                // Envia Hex 3  Interface 8 bits long ??
	delayMicroseconds(40);        // wait min 40 us
	write4bits(3);                // Envia Hex 3  Interface 8 bits long ??
	delayMicroseconds(40);        // wait min 40 us
	write4bits(2);                // Envia Hex 2  Interface 4 bits long
	delayMicroseconds(40);        // wait min 40 us

	// 28
	write4bits(LCD_FUNCTIONSET);
	write4bits(LCD_2LINE);        // Envia Hex 8  display de 2 linhas
	delayMicroseconds(60);        // wait min 60 us

	// 08
	write4bits(0);                // Envia Hex 0
	write4bits(LCD_DISPLAYCONTROL);  // Envia Hex 8  ativa display
	delayMicroseconds(60);

	// 0C
	write4bits(0);                // Envia Hex 0
	write4bits(LCD_2LINE | LCD_DISPLAYON | LCD_CURSOROFF); // Envia Hex 2 linhas cursor off Lcd on

	// 01
	write4bits(0);                // Envia Hex 0
	write4bits(LCD_CLEARDISPLAY); // Envia Hex 1  clear LCD
	delay(3);                     // wait min 3ms

	return true;
}

void IToIurLcdModule595::clear() {
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void IToIurLcdModule595::home() {
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

// **** private: ****



void IToIurLcdModule595::setCursor(uint8_t col, uint8_t row) {
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
void IToIurLcdModule595::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void IToIurLcdModule595::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void IToIurLcdModule595::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void IToIurLcdModule595::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void IToIurLcdModule595::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void IToIurLcdModule595::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void IToIurLcdModule595::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void IToIurLcdModule595::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void IToIurLcdModule595::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void IToIurLcdModule595::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void IToIurLcdModule595::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void IToIurLcdModule595::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void IToIurLcdModule595::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void IToIurLcdModule595::command(uint8_t value) {
  send(value, LOW);
}

inline size_t IToIurLcdModule595::write(uint8_t value) {
  send(value, HIGH);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

/**
 * mode command ou character LOW: command.  HIGH: character.
 */
void IToIurLcdModule595::send(uint8_t value, uint8_t mode) {
	_outs->SetOutput(LCD_PIN_RS, mode, _module);
	_outs->SetOutput(LCD_PIN_READWRITE, LOW, _module);
	write4bits(value >> 4);
	write4bits(value);
}

void IToIurLcdModule595::pulseEnable() {
	_outs->SetOutput(LCD_PIN_ENABLE, LOW, _module);
	_outs->SetOutput(LCD_PIN_ENABLE, HIGH, _module); // enable pulse must be >450ns
	_outs->SetOutput(LCD_PIN_ENABLE, LOW, _module);
	delayMicroseconds(37);   // commands need > 37us to settle
}

void IToIurLcdModule595::setRowOffsets(int row0, int row1, int row2, int row3) {
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

void IToIurLcdModule595::write4bits(uint8_t value) {
	cli();
	_outs->SetOutput(LCD_PIN_DB4, (value) & 0x01);
	_outs->SetOutput(LCD_PIN_DB5, (value >> 1) & 0x01);
	_outs->SetOutput(LCD_PIN_DB6, (value >> 2) & 0x01);
	_outs->SetOutput(LCD_PIN_DB7, (value >> 3) & 0x01);
	pulseEnable();                      // Pulsa ENABLE
	sei();
}
