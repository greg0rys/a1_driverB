CC = g++
CPPFLAGS = -g -Wall -std=c++17
DEPS = main.h ChickenYard.h Player.h Bone.h DLL.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

app: main.o ChickenYard.o Player.o Bone.o Game.o Field.o DLL.o
	$(CC) -o app Bone.o ChickenYard.o Player.o DLL.o main.o

.PHONY: clean

clean:
	$(info -- cleaning up --)
	rm -f app
	rm -f *.o
