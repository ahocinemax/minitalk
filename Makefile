SERVER   = server
CLIENT   = client
HEADER	 = includes/minitalk.h
CC	     = gcc
FLAGS    = -Wall -Werror -Wextra
LIBFT	 = libft/libft.a

all : $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT) : 
	@make -C libft

$(SERVER) : srcs/server.c $(HEADER)
	@$(CC) $(FLAGS) srcs/server.c $(LIBFT) -o $@
	@printf "\e[38;5;226m./$@ successfully build🥑\e[0m\n"

$(CLIENT) : srcs/client.c $(HEADER)
	@$(CC) $(FLAGS) srcs/client.c $(LIBFT) -o $@
	@printf "\e[38;5;46m./$@ successfully build🥝\e[0m\n"


clean :
	@make clean -C libft
	@rm -f *.o
	@printf "\e[38;5;206m.o files deleted🚽\e[0m\n"

fclean: clean
	@make fclean -C libft
	@rm -f $(SERVER) $(CLIENT)
	@printf "\e[38;5;200mBinaries deleted🗑\e[0m\n"

re: fclean all
