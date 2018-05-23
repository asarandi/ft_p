NAME		=	ftp_client

CLIENT_SRC	=	char_array.c \
				cleanup.c \
				client.c \
				client_passive.c \
				client_read.c \
				cmd_get.c \
				cmd_ls.c \
				cmd_other.c \
				cmd_put.c \
				core.c \
				exec.c \
				sockets.c \
				strings.c \
				utils.c

CLIENT_OBJ	=	$(addprefix obj/, $(CLIENT_SRC:.c=.o))

CC			=	gcc
CFLAGS		=	-g -Wextra -Wall -Werror -Wno-unused-result
INC			=	-I ../libft/inc -I inc/
LIBFT		=	../libft/libft.a

all: client

client: $(CLIENT_OBJ) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf client

again: rmobj rmbin all

clean: rmobj

fclean: clean rmbin

re: fclean all
