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
		memory_handle.c				\
		gnl/get_next_line.c			\
		gnl/get_next_line_utils.c	\
		parse/check_map.c			\
		parse/fill_map.c			\
		parse/check_map_utils.c		\
		parse/init_data.c			\
		parse/check_imgs.c			\
		carlos.c					\
		distances/angles_from_180.c	\
		distances/angles_til_180.c	\
		distances/moves.c			\
		draw/draw.c					\
		draw/draw_utils.c
		
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
LIBFT = libft/libft.a
MLX = minilibx/libmlx.a
MLX_FLAGS = -Lminilibx -lmlx -lX11 -lXext -lm

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

$(MLX):
	make -C minilibx/

clean:
	rm -f $(OBJS)
	make -C libft/ fclean
	make -C minilibx/ clean

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)