# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image ` -g
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image` -pthread

all: Snake

SRC = grille.c serpent.c liste_section.c interface.c main.c
OBJ = ${SRC:.c=.o}
EXE = Snake

Snake: ${OBJ}
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -o $@
$(OBJ) $(MAIN_OBJ): %.o: %.c $(HEADERS)

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
