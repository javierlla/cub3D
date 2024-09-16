# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 17:25:33 by jllarena          #+#    #+#              #
#    Updated: 2024/09/16 14:31:41 by jllarena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP

NAME            = cub3D
CC              = gcc
RM              = rm -rf
FLAGS           = -Wall -Wextra -Werror -Ilibft -Imlx -g3 -fsanitize=address

# FILES AND PATH

HEADER_SRCS = cub3d.h
HEADER_DIR  = includes/
HEADER      = $(addprefix $(HEADER_DIR), $(HEADER_SRCS))


MPATH_SRCS  = main.c \
			  open_window.c \
			  player.c \
			  put_walls_map.c \
			  read.cub.file.c \
			  render.c \
			  utils_mlx.c \
			  player_double_position.c \
			  

MPATH_DIR   = mandatory/
MPATH       = $(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M       = $(MPATH:.c=.o)


all:        lib $(NAME)

$(NAME):    $(OBJ_M)
		    @$(CC) $(FLAGS) $(OBJ_M) -lm -Llibft -lft -Lmlx -lmlx -lX11 -lXext -o $(NAME)


$(OBJ_M): %.o: %.c $(HEADER) Makefile
		    @$(CC) $(FLAGS) -c $< -o $@

bonus:      lib $(OBJ_B)
			@$(CC) $(FLAGS) $(OBJ_B) -lm -Llibft -lft -Lmlx -lmlx -lX11 -lXext -o $(NAME)

clean:
	        @$(RM) $(OBJ_M)
			@$(RM) $(OBJ_B)
	        $(MAKE) -C libft clean
			$(MAKE) -C mlx clean

fclean:	    clean
		    @$(RM) $(NAME)

re:         fclean all

lib:
	        $(MAKE) -C libft
			$(MAKE) -C mlx

.PHONY: all clean fclean re lib
