
CC				:= gcc
RM				:= rm -f
CFLAGS		?= -g -Wall -O2 -fsanitize=address
LDFLAGS		?=
C_FILES		?= $(shell ls -t | grep "\.c" | head -n 1)
OBJ_FILES	:= $(patsubst %.c,%.o,$(C_FILES))
TARGET		:= main

build: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

$(OBJ_FILES): clean $(C_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(C_FILES)

.PHONY: clean
clean:
	$(RM) $(TARGET) *.o

