NAME		=	ft_p
SERVER		=	server/server
CLIENT		=	client/client

all: server client

###############################################################

server: $(SERVER)

server/server:
	make -C server/
	ln -s server/server ftp_server

server_clean:
	make clean -C server/

server_fclean:
	make fclean -C server/
	rm -f ftp_server

###############################################################

client: $(CLIENT)

client/client:
	make -C client/
	ln -s client/client ftp_client

client_clean:
	make clean -C client/

client_fclean:
	make fclean -C client/
	rm -f ftp_client

###############################################################

clean: server_clean client_clean

fclean: clean server_fclean client_fclean

re: fclean all

norminette:
	norminette server/src
	norminette server/inc
	norminette client/src
	norminette client/inc

norme: norminette

norm: norminette

