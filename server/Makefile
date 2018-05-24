NAME		=	ftp_server

SERVER_SRC	=	cleanup.c \
				cmd_list.c \
				cmd_retr.c \
				cmd_stor.c \
				dele_size_help_type_quit.c \
				file_op.c \
				incoming.c \
				main.c \
				parse_init_accept.c \
				pasv_user_pass_syst_port.c \
				pwd_cwd_cdup_mkd_rmd.c \
				sendtext_usage_random_ipmatch.c \
				signals.c \
				sockets.c \
				string_op.c \
				worker.c

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
