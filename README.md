# Synapse RTD-DO8 Tool

 Dependancies :

```# apt-get install sqlite3 libsqlite3-dev libmodbus5 libmodbus-dev```

Compile as below or use 'make all'

```gcc log.c -o log -lsqlite3 -lmodbus```


```

Synapse RTU-DI8 Reader - v1.0

./rtu-do8 [-h|j|c] [-a] [-b] [-p] [-o] [-s] [-f] [-n] [-1] [-2] [-3] [-4] [-5] [-6] [-7] [-8] [-m] [-w] [-d]

Syntax :

-h = Human readable output (default)
-j = JSON readable output
-c = Comma delimited minimal output

-a = Set Modbus device address (1-255)  default=1
-b = Set serial baud rate (9600/14400/19200/38400/57600)  default=19200
-p = Set serial interface to use e.g. /dev/ttyS0  default=/dev/ttyUSB0

-o = Output channel to set (1|2|3|4|5|6|7|8)
-s = Set logic on/off state (0|1)
-f = Set period of pulse frequency output  e.g. 100 = 10Hz  or  0 = off
-n = Select number of pulses for fixed pulse count output

-1 = Set Channel 1 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-2 = Set Channel 2 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-3 = Set Channel 3 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-4 = Set Channel 4 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-5 = Set Channel 5 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-6 = Set Channel 6 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-7 = Set Channel 7 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level
-8 = Set Channel 8 mode register (1=Logic Level|2=Pulse Freq Continuous|3=Pulse Freq Num Pulses) - default=Logic Level

-m = Set value for RTU Baud Rate register (1=9600/2=14400/3=19200/4=38400/5=57600)

-w = Confirm writing configured setting registers to RTU NVRAM

-d = debug mode

Examples :
Set output channel 3 to on                                                 :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 1
Set output channel 3 to off                                                :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 3 -s 0

Set output channel 1 to pulse frequency 10Hz (free running )               :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 100
Set output channel 1 to pulse frequency 0Hz (off)                          :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 0

Set output channel 1 to pulse frequency 10Hz for 50 pulses only )          :  ./rtu-do8 -a 1 -b 19200 -p /dev/ttyS0 -o 1 -f 100 -n 50

Reconfigure RTU channel 1 into pulse frequency output mode                 :  ./rtu-do8 -a 3 -p /dev/ttyS0 -1 2 -w

```
