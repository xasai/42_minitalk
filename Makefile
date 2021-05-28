##########################################################################################
NAME := bin/server bin/client

VPATH := ./src
OBJPATH := ./obj
BIN_DIR := ./bin/
OBJDIR := $(subst $(VPATH), $(OBJPATH), $(shell find $(VPATH) -type d))
INC := -Iinclude/

SERVER := server
SERVER_PATH := $(VPATH)/$(SERVER)
SERVER_SRC := $(shell find $(SERVER_PATH) -name *.c)
SERVER_OBJ := $(subst $(VPATH), $(OBJPATH), $(SERVER_SRC:.c=.o))

CLIENT := client
CLIENT_PATH := $(VPATH)/$(CLIENT)
CLIENT_SRC := $(shell find $(CLIENT_PATH) -name *.c)
CLIENT_OBJ := $(subst $(VPATH), $(OBJPATH), $(CLIENT_SRC:.c=.o))

############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
CFLAGS := -g3 -Wall -Wextra -Werror --std=c99# 			#/ ____|  / ____|  / ____|
														#| |  __  | |      | |     
														#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
############################################################################################

all: $(NAME)

$(NAME): $(OBJPATH) $(SERVER_OBJ) $(CLIENT_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INC) $(CLIENT_OBJ) -o bin/$(CLIENT)
	@echo "\n\e[0;32mbin/$(CLIENT) [Compiled +++] \e[0m\n"
	$(CC) $(CFLAGS) $(INC) $(SERVER_OBJ) -o bin/$(SERVER)
	@echo "\n\e[0;32mbin/$(SERVER) [Compiled +++] \e[0m\n"

$(OBJPATH)/%.o: %.c
	@echo -n "\e[0;32m"
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	@echo -n "\e[0m"

$(OBJPATH):
	@mkdir -p $(OBJDIR)

clean:
	@echo -n "\e[0;31m"
	rm -rf $(OBJPATH)
	@echo -n "\e[0m"

fclean: clean
	@echo -n "\e[0;31m"
	rm -rf $(BIN_DIR) 
	@echo -n "\e[0m"

re: fclean all

.PHONY: test re fclean clean all

############################################################################################
echo:
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)

est: $(NAME) 
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################
