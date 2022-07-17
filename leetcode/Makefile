
CC				:= gcc
RM				:= rm -f
CFLAGS		?=
LDFLAGS		?=
C_FILES		?= $(shell ls -t | grep "\.c" | head -n 1)
OBJ_FILES	:= $(patsubst %.c,%.o,$(C_FILES))
TARGET		:= main

build: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

$(OBJ_FILES): clean $(C_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(C_FILES)

.PHONY: clean
clean:
	$(RM) $(TARGET) *.o

