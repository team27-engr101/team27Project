DIR = C:\Users\disab\Desktop\101project3\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1
CFLAGS = -I ${DIR}\include 
LFLAGS = -L ${DIR}\lib 
LIBS = -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
robot: robot.o 
	g++ $(LFLAGS) -o robot robot.o ${LIBS} 
robot.o: robot.cpp 
	g++  -c $(CFLAGS) robot.cpp 


