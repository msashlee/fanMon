# fanMon
*arduinoFanMon*

A program used to monitor CPU fan speed using an Arduino.

*Tested on*

Arduino Uno - Circuit Diagram can be found in main repository folder.

*Setup*

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