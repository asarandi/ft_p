NAME		=	ft_p
SERVER		=	server/server
CLIENT		=	client/client
LIBFT		=	libft/libft.a

all: server client

###############################################################

server: $(LIBFT) $(SERVER)

server/server:
	make -C server/

server_clean:
	make clean -C server/

server_fclean:
	make fclean -C server/

###############################################################

client: $(LIBFT) $(CLIENT)

client/client:
	make -C client/

client_clean:
	make clean -C client/

client_fclean:
	make fclean -C client/

###############################################################

libft/libft.a:
	make -C libft/

libft_clean:
	make clean -C libft/

libft_fclean:
	make fclean -C libft/

###############################################################

clean: server_clean client_clean libft_clean

fclean: clean server_fclean client_fclean libft_fclean

re: fclean all
