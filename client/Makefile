SRC += char_array.c cleanup.c client.c client_passive.c client_read.c cmd_get.c cmd_ls.c cmd_other.c cmd_put.c core.c exec.c sockets.c strings.c utils.c
OBJ := $(SRC:.c=.o)

CFLAGS += -g -Wall -Werror -Wextra
LDFLAGS += -g

client: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f client

re: fclean client
