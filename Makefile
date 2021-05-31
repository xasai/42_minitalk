##########################################################################################
NAME := minitalk 

VPATH := ./src
OBJPATH := ./obj
BINPATH := ./bin/
OBJDIR := $(subst $(VPATH), $(OBJPATH), $(shell find $(VPATH) -type d))

SERVER := $(BINPATH)server
SERVER_SRC := ./src/server/server.c	./src/server/main.c	./src/server/auxillary.c
SERVER_OBJ := $(subst $(VPATH), $(OBJPATH), $(SERVER_SRC:.c=.o))

CLIENT := $(BINPATH)client
CLIENT_SRC := ./src/client/request.c ./src/client/main.c ./src/client/send_data.c ./src/client/auxillary.c
CLIENT_OBJ := $(subst $(VPATH), $(OBJPATH), $(CLIENT_SRC:.c=.o))
###########################################################################################
BONUS_CLIENT := $(BINPATH)bonus/client
BONUS_CLIENT_SRC := ./src/bonus/client/request_bonus.c ./src/bonus/client/auxillary_bonus.c\
					./src/bonus/client/main_bonus.c ./src/bonus/client/send_data_bonus.c
BONUS_CLIENT_OBJ := $(subst $(VPATH), $(OBJPATH), $(BONUS_CLIENT_SRC:.c=.o))

BONUS_SERVER := $(BINPATH)bonus/server
BONUS_SERVER_SRC := ./src/bonus/server/server_bonus.c ./src/bonus/server/auxillary_bonus.c\
					./src/bonus/server/main_bonus.c
BONUS_SERVER_OBJ := $(subst $(VPATH), $(OBJPATH), $(BONUS_SERVER_SRC:.c=.o))
BONUS_HEADER := include/bonus/minitalk_bonus.h include/bonus/miniclient_bonus.h\
				include/bonus/miniserver_bonus.h
############################################################################################
CC := gcc#	 											  #_____    _____    _____ 
														#/ ____|  / ____|  / ____
INC := -Iinclude -Iinclude/bonus#						#| |  __  | |      | |     
														#| | |_ | | |      | |     
														#| |__| | | |____  | |____ 
														 #\_____|  \____|  \_____|
CFLAGS := -O3 -Wall -Wextra -Werror
HEADER := include/minitalk.h include/miniclient.h include/miniserver.h
############################################################################################

all: $(NAME)

bonus:	$(OBJPATH) $(BINPATH) $(BONUS_HEADER) $(BONUS_CLIENT) $(BONUS_SERVER) 

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
	@mkdir -p $(BINPATH) $(BINPATH)/bonus

clean:
	@echo -n "\e[0;31m- "
	rm -rf $(OBJPATH)
	@echo -n "\e[0m"

fclean: clean
	@echo -n "\e[0;31m- "
	rm -rf $(BINPATH) 
	@echo -n "\e[0m"

re: fclean all

.PHONY: test re fclean clean all

$(BONUS_CLIENT): $(BONUS_CLIENT_OBJ) 
	$(CC) $(CFLAGS) $(INC) $(BONUS_CLIENT_OBJ) -o $(BONUS_CLIENT)
	@echo "\n\e[0;32m$(SERVER) [Compiled +++] \e[0m\n"

$(BONUS_SERVER): $(BONUS_SERVER_OBJ)
	$(CC) $(CFLAGS) $(INC) $(BONUS_SERVER_OBJ) -o $(BONUS_SERVER)
	@echo "\n\e[0;32m$(SERVER) [Compiled +++] \e[0m\n"
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

