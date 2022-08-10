# Synapse RTD-DO8 Tool

 Dependancies :

```# apt-get install libmodbus5 libmodbus-dev```

Compile as below or use 'make all'

```gcc rtu-do8.c -o rtu-do8 -lmodbus  ```


```
Synapse RTU-DO8 tool - v1.1

./rtu-do8 [-h|j|c] [-a] [-b] [-p] [-o] [-s] [-m] [-w] [-d]

Syntax :

-h = Human readable output (default)
-j = JSON readable output
-c = Comma delimited minimal output

-a = Set Modbus device address (1-255)  default=1
-b = Set serial baud rate (9600/14400/19200/38400/57600)  default=19200
-p = Set serial interface to use e.g. /dev/ttyS0  default=/dev/ttyUSB0

-o = Output channel to set (1|2|3|4|5|6|7|8)
-s = Set logic on/off state (0|1)

-m = Set value for RTU Baud Rate register (1=9600/2=14400/3=19200/4=38400/5=57600)

-w = Confirm writing configured setting registers to RTU NVRAM

-d = debug mode

Examples :
Set output channel 3 to on       :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 1
Set output channel 3 to off      :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 0

```
