##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC				= g++ -g3

UTILS_PATH		= src/Utils
KITCHEN_PATH	= src/Kitchen
IPC_PATH		= src/IPC

SRC				= src/main.cpp \
				src/Pizza.cpp \
				src/Status.cpp \
				src/Reception/Reception.cpp \
				$(UTILS_PATH)/Fork.cpp \
				$(UTILS_PATH)/String.cpp \
				$(UTILS_PATH)/AError.cpp \
				$(UTILS_PATH)/Errors/Convert.cpp \
				$(UTILS_PATH)/Errors/Fork.cpp \
				$(KITCHEN_PATH)/Kitchen.cpp \
				$(KITCHEN_PATH)/Chief.cpp \
				$(IPC_PATH)/SocketClient.cpp \
				$(IPC_PATH)/SocketServer.cpp

OBJ			= $(SRC:.cpp=.o)

BIN 		= plazza

INCLUDES	= -Isrc -Isrc/Utils/ -Isrc/IPC/
CPPFLAGS	= -W -Wall -Wextra $(INCLUDES)

all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lpthread

clean:
	$(RM) *~
	$(RM) #*#
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BIN)

re: fclean all
