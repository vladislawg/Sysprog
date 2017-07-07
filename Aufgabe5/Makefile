BIN = Prog
SRC = \
	main.c \
	utils.c \
	BankierAlog.c \
	deadlock_avoidance.c

CC	 = gcc
CFLAGS   = -g -Wall -std=c99

RM     = rm -f

OBJS = $(SRC:%.c=%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

# pull in dependencies for .o files
-include $(OBJS:.o=.d)


clean:
	$(RM) $(BIN) $(OBJS) *.d

.PHONY: clean debug run
