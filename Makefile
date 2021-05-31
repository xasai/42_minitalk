##########################################################################################
NAME := minitalk 

VPATH := ./src
OBJPATH := ./obj
INPATH := ./bin/
OBJDIR := $(subst $(VPATH), $(OBJPATH), $(shell find $(VPATH) -type d))

SERVER := $(BINPATH)server
SERVER_SRC := $(shell find ./src/server -name *.c)
SERVER_OBJ := $(subst $(VPATH), $(OBJPATH), $(SERVER_SRC:.c=.o))

CLIENT := $(BINPATH)client
CLIENT_SRC := $(shell find ./src/client -name *.c)
CLIENT_OBJ := $(subst $(VPATH), $(OBJPATH), $(CLIENT_SRC:.c=.o))

############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
														#/ ____|  / ____|  / ____
INC := -Iinclude#										#| |  __  | |      | |     
														#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
CFLAGS := -O3 -Wall -Wextra -Werror -fsanitize=address #std=gnu99#
############################################################################################

all: $(NAME)

$(NAME): $(OBJPATH) $(BINPATH) $(SERVER) $(CLIENT) 

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(INC) $(CLIENT_OBJ) -o $(CLIENT)
	@echo "\n\e[0;32m$(CLIENT) [Compiled +++] \e[0m\n"

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(INC) $(SERVER_OBJ) -o $(SERVER)
	@echo "\n\e[0;32m$(SERVER) [Compiled +++] \e[0m\n"

$(OBJPATH)/%.o: %.c
	@echo -n "\e[0;32m+ "
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	@echo "\e[0m"

$(OBJPATH):
	@mkdir -p $(OBJDIR)

$(BINPATH):
	@mkdir -p $(BINPATH)

clean:
	@echo -n "\e[0;31m- "
	rm -rf $(OBJPATH)
	@echo -n "\e[0m"

fclean: clean
	@echo -n "\e[0;31m- "
	rm -rf $(SERVER) $(CLIENT) $(BINPATH) 
	@echo -n "\e[0m"

re: fclean all

.PHONY: test re fclean clean all

############################################################################################
echo:
	@echo $(OBJPATH) 
	@echo $(BINPATH) 
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)

test: $(NAME) 
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################
