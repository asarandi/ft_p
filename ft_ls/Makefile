# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 20:09:21 by asarandi          #+#    #+#              #
#    Updated: 2018/05/18 10:26:43 by asarandi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
CC		= gcc
CFLAGS	= -O2 -Wall -Werror -Wextra

C_FILES	=	build_list.c \
			clear_structs.c \
			columns.c \
			columns_util.c \
			compare_files1.c \
			compare_files2.c \
			compare_files3.c \
			dir_util.c \
			display.c \
			extattr.c \
			list_dir.c \
			listdir_norme.c \
			main.c \
			merge_sort.c \
			options.c \
			parse_options.c \
			print.c \
			symbol_type.c \
			symlink.c \
			time.c \
			widths.c

O_FILES	= $(C_FILES:%.c=%.o)
SRC		= $(addprefix src/,$(C_FILES))
OBJ		= $(addprefix obj/,$(O_FILES))
LIB		= -L ../libft/ -lft
INC		= -I ../libft/inc/ -I inc/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf $(NAME)

again: rmobj rmbin all

clean: rmobj

fclean: clean rmbin

re: fclean all
