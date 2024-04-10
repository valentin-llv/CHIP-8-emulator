CC = gcc

SOURCES = src\main.c src\startup\startup.c src\memory\memory.c src\events\events.c src\cpu\cpu.c src\screen\screen.c src\utils\utils.c
OBJS = ${SOURCES:.c=.o}

all: build run

build: ${OBJS}
	@${CC} -o dist/programm.exe ${OBJS} -Llib/SDL2/ -lSDL2

%.o: %.c
	@${CC} -c $< -o $@ -Ilib/SDL2/include/

run: dist/programm.exe
	@./dist/programm.exe

clean:
	@del ${OBJS}