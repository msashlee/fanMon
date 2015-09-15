# fanMon
##arduinoFanMon

*CURRENTLY VERY ALPHA! WORKING OUT BUGS USE WITH CARE & DONT EXPECT IT TO WORK!*

A program used to monitor CPU fan speed using an Arduino.

##License

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

##Tested on

Arduino Uno 

##Schematic

fanMonV1.pdf - Original UNO hook up schematic can be found in main repository folder. Note that JP1, JP2, JP3 are Arduino UNO I/O blocks.

##Setup

Set number of fans & LCD Width/Height:
```C++
#define LCDHEIGHT 2
#define LCDWIDTH 16
#define fanC 3
```

Edit the following line as such: {index, Hall Sensor type, Trigger Pin}, adding entries for proper quantity of fans.

Hall Type|ID #
---------|---------
Monopole | 0
Bi pole  | 1
Quad Pole| 2

```C++
fandef fans[fanC]={{0,2,13},{1,2,12},{2,2,11}};
```

Edit the following line to adjust LCD display pin out as needed.
```C++
LiquidCrystal lcd( 7, 6, 5, 4, 3, 2);
```