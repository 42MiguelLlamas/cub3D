# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 17:20:49 by mllamas-          #+#    #+#              #
#    Updated: 2023/12/28 15:22:56 by mllamas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS =	main.c						\
		aux.c						\
		memory_handle.c				\
		gnl/get_next_line.c			\
		gnl/get_next_line_utils.c	\
		parse/check_map.c			\
		parse/fill_map.c			\
		parse/check_map_utils.c		\
		parse/init_data.c			\
		
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CC = cc
LIBFT = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

clean:
	rm -f $(OBJS)
	make -C libft/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
#-Imlx -lmlx -framework OpenGL -framework AppKit 