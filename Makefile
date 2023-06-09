CC = g++
CFLAGS += -mavx2 -DREP_NUM=10000 -O1
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

all: v1 v2

v1: obj/v1.o obj/bmp.o obj/main.o
	$(CC) -o v1 obj/v1.o obj/bmp.o obj/main.o $(SFMLFLAGS)

v2: obj/v2.o obj/bmp.o obj/main.o
	$(CC) -o v2 obj/v2.o obj/bmp.o obj/main.o $(SFMLFLAGS)

obj/bmp.o: src/bmp.cpp
	$(CC) -o obj/bmp.o src/bmp.cpp -c $(CFLAGS)

obj/main.o: src/main.cpp
	$(CC) -o obj/main.o src/main.cpp -c $(CFLAGS)

obj/v1.o: src/v1.cpp
	$(CC) -o obj/v1.o src/v1.cpp -c $(CFLAGS)

obj/v2.o: src/v2.cpp
	$(CC) -o obj/v2.o src/v2.cpp -c $(CFLAGS)


blend: obj/blend.o obj/bmp.o
	$(CC) -o blend obj/blend.o obj/bmp.o

obj/blend.o: src/blend.cpp
	$(CC) -o obj/blend.o src/blend.cpp -c $(CFLAGS)


clean:
	rm obj/*.o -f
	clear
	
.PHONY: clean