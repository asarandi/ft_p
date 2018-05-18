NAME		=	ft_p
SERVER_SRC	+=	server.c whitespace.c
SERVER_OBJ	=	$(addprefix obj/, $(SERVER_SRC:.c=.o))
CLIENT_SRC	+=	client.c
CLIENT_OBJ	=	$(addprefix obj/, $(CLIENT_SRC:.c=.o))
CC			=	gcc
CFLAGS		+=	-g -Wextra -Wall -Werror
INC			=	-I libft/inc -I inc/
LIB			=	-L libft/ -lft
LIBFT		=	libft/libft.a
FT_LS		=	ft_ls/ft_ls

all: server client

server: $(SERVER_OBJ) | $(LIBFT) $(FT_LS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

client: $(CLIENT_OBJ) | $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

libft/libft.a:
	make -C libft/

ft_ls/ft_ls:
	make -C ft_ls/

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf server client

again: rmobj rmbin all

clean: rmobj
	make clean -C ft_ls/
	make clean -C libft/

fclean: clean rmbin
	make fclean -C ft_ls/
	make fclean -C libft/

re: fclean all
