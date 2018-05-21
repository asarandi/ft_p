NAME		=	ftp_server

SERVER_SRC	=	char_array.c \
				file_op.c \
				server.c \
				server_cmds_1.c \
				server_cmds_2.c \
				server_cmds_3.c \
				server_cmds_4.c \
				server_cmds_5.c \
				server_core.c \
				server_incoming.c \
				server_sockets.c \
				server_utils.c \
				whitespace.c

SERVER_OBJ	=	$(addprefix obj/, $(SERVER_SRC:.c=.o))

CC			=	gcc
CFLAGS		=	-O2 -Wextra -Wall -Werror -Wno-unused-result
INC			=	-I ../libft/inc -I inc/
LIBFT		=	../libft/libft.a

all: server

server: $(SERVER_OBJ) | $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf server

again: rmobj rmbin all

clean: rmobj

fclean: clean rmbin

re: fclean all
