# ITo Iur LCD Module 74HC595

Esta biblioteca permite ao Arduino trabalhar com módulos LCD (mais de 1) usando a biblioteca IToOutputModule595 baseados no 74HC595 usando apenas 1 porta de saída.

Para mais informações, exemplos e circuitos desta biblioteca, por favor, nos visite no
[Project ITo Output Module 74HC595 @ labirito.com](http://www.labirito.com/projetos/itooutputmodule74595 "Labirito projects")

Muito obrigado ao Rui Viana que desenvolveu, testou e refinou esta biblioteca.

## Como usar esta biblioteca?

```cpp
// esta biblioteca depende da biblioteca abaixo
#include "IToOutputModule595.h"
#include "IToIurLcdModule595.h"

const int numero_de_modulos = 1;
IToOutputModule595 outs(numero_de_modulos, 2);
IToIurLcdModule595 lcd0(0); // LCD utilizara modulo 0

setup() {
  outs.ResetAll(); // desliga todas as saidas
  lcd0.begin();
}

loop() {
}
```

## Esquemas elétricos

O circuito abaixo deve ser 
[![Circuito de expansão com 74HC595 que usa 1 porta do arduino](http://i.imgur.com/b1QZOXZ.png)](http://www.labirito.com/projetos/itooutputmodule74595)


[![Veja o LCD contando tempo](https://lh5.googleusercontent.com/-GjHtiAUi2Gk/V6Os9YWtp-I/AAAAAAAACNg/TYu0XMB35ZMz4DZKOL9ZbFZzre4Z7S2lwCL0B/w796-h597-no/2016-08-04.jpg)]

[![2 LCDs rodando ao mesmo tempo](https://lh5.googleusercontent.com/-0-acNRu_C_M/V6FPS8eIZTI/AAAAAAAACMY/llGJefWlrekSO_atE9_Mh0SbuI9LTIkwACL0B/w796-h597-no/2016-08-02.jpg)]


## License

**Copyright (c) 2010 Labirito. All right reserved.**

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
