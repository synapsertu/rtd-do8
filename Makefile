all: rtu

rtu: 
	gcc rtu-do8.c -o rtu-do8 -lmodbus  

clean:
	rm -rf *.o rtu-do8
