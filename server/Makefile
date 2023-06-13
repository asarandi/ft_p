SRC += cleanup.c cmd_list.c cmd_retr.c cmd_stor.c dele_size_help_type_quit.c file_op.c incoming.c main.c parse_init_accept.c pasv_user_pass_syst_port.c pwd_cwd_cdup_mkd_rmd.c sendtext_usage_random_ipmatch.c signals.c sockets.c string_op.c worker.c
OBJ := $(SRC:.c=.o)

CFLAGS += -Wall -Werror -Wextra
LDFLAGS +=

server: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f server

re: fclean server
