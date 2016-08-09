/*
 * IToIurLcdModule595.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: Administrator
 */

#include "IToIurLcdModule595.h"

IToIurLcdModule595::IToIurLcdModule595(IToOutputModule595 &outs, uint8_t module) {
	_module = module;
	_outs = outs;
}

IToIurLcdModule595::~IToIurLcdModule595() {
}

void IToIurLcdModule595::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
	  delay(15);                                    // Tempo de power on

	  outs.SetModule(0, _module);                     // Zera saida do 595

	  write595(3, _module);                           // Envia Hex 3  Interface 8 bits long ??
	  delayMicroseconds(4500);                      // wait min 4.1ms
	  write595(3, _module);                           // Envia Hex 3  Interface 8 bits long ??
	  delayMicroseconds(40);                        // wait min 40 us
	  write595(3, _module);                           // Envia Hex 3  Interface 8 bits long ??
	  delayMicroseconds(40);                        // wait min 40 us
	  write595(2, _module);                           // Envia Hex 2  Interface 4 bits long
	  delayMicroseconds(40);                        // wait min 40 us

	  // 28
	  write595(LCD_FUNCTIONSET, _module);
	  write595(LCD_2LINE, _module);                   // Envia Hex 8  display de 2 linhas
	  delayMicroseconds(60);                        // wait min 60 us

	  // 08
	  write595(0, _module);                           // Envia Hex 0
	  write595(LCD_DISPLAYCONTROL, _module);                           // Envia Hex 8  ativa display
	  delayMicroseconds(60);

	  // 0C
	  write595(0, _module);                           // Envia Hex 0
	  write595(LCD_2LINE | LCD_DISPLAYON | LCD_CURSOROFF, _module);   // Envia Hex 2 linlhas  cursor off Lcd on

	  // 01
	  write595(0, _module);                           // Envia Hex 0
	  write595(LCD_CLEARDISPLAY, _module);            // Envia Hex 1  clear LCD
	  delay(3);                                     // wait min 3ms
}

void write595(uint8_t cmd, uint8_t module) {
	;
}
