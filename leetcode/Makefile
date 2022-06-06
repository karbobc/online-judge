
CC				:= gcc
RM				:= rm -f
CFLAGS		?=
LDFLAGS		?=
C_FILES		?=
OBJ_FILES	:= $(patsubst %.c,%.o,$(C_FILES))
TARGET		:= main

build:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(C_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

clean:
	$(RM) $(TARGET) *.o

