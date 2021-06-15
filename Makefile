##########################################################################################
NAME := minitalk 

VPATH := ./src
OBJPATH := ./obj
BINPATH := ./bin/
OBJDIR := $(subst $(VPATH), $(OBJPATH), $(shell find $(VPATH) -type d))

SERVER := $(BINPATH)server
SERVER_SRC := $(shell find ./src/server -name *.c)
SERVER_OBJ := $(subst $(VPATH), $(OBJPATH), $(SERVER_SRC:.c=.o))
SERVER_HEADERS := include/miniserver.h include/minitalk.h

CLIENT := $(BINPATH)client
CLIENT_SRC := $(shell find ./src/client -name *.c)
CLIENT_OBJ := $(subst $(VPATH), $(OBJPATH), $(CLIENT_SRC:.c=.o))
CLIENT_HEADERS := include/miniclient.h include/minitalk.h
############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
														#/ ____|  / ____|  / ____
INC := -Iinclude#										#| |  __  | |      | |     
														#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
CFLAGS := -O3 -Wall -Wextra -Werror 
############################################################################################

all: $(NAME)

$(NAME): $(OBJPATH) $(BINPATH) $(SERVER) $(CLIENT) 

$(CLIENT): $(CLIENT_OBJ) 
	$(CC) $(CFLAGS) $(INC) $(CLIENT_OBJ) -o $(CLIENT)
	@echo "\n\033[0;32m========>$(CLIENT) [Compiled +++] \033[0m\n"

$(SERVER): $(SERVER_OBJ) 
	$(CC) $(CFLAGS) $(INC) $(SERVER_OBJ) -o $(SERVER)
	@echo "\n\033[0;32m========>$(SERVER) [Compiled +++] \033[0m\n"

$(OBJPATH)/%.o: %.c $(SERVER_HEADERS) $(CLIENT_HEADERS) 
	@echo -n "\033[0;32m+"
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	@echo "\033[0m"

$(OBJPATH):
	@mkdir -p $(OBJDIR)

$(BINPATH):
	@mkdir -p $(BINPATH)

clean:
	@echo -n "\033[0;31m- "
	rm -rf $(OBJPATH)
	@echo  "\033[0m"

fclean: clean
	@echo -n "\033[0;31m- "
	rm -rf $(SERVER) $(CLIENT) $(BINPATH) 
	@echo "\033[0m"

re: fclean all

.PHONY: bonus test re fclean clean all

bonus: all

############################################################################################
echo:
	@echo $(OBJPATH) 
	@echo $(BINPATH) 
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)

val: $(NAME)
	valgrind --leak-check=full ./$(NAME)

debug: $(NAME)
	gdb	./$(NAME)
############################################################################################
