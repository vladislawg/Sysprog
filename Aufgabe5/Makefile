BIN = Prog
SRC = \
	main.c \
	utils.c

ARCH = $(shell getconf LONG_BIT)

#SDL_CFLAGS_32 = $(shell libsdl_32/bin/sdl-config --cflags)
#SDL_LFLAGS_32 = $(shell libsdl_32/bin/sdl-config --static-libs)

CC	 = gcc
CFLAGS   = -g -Wall -std=c99

RM     = rm -f

OBJS = $(SRC:%.c=%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

# pull in dependencies for .o files
-include $(OBJS:.o=.d)

run: $(BIN)
	./$(BIN)

clean:
	$(RM) $(BIN) $(OBJS) *.d

.PHONY: clean debug run
