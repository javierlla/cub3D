# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 17:25:33 by jllarena          #+#    #+#              #
#    Updated: 2024/11/15 18:26:40 by jllarena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP

NAME            = cub3D
CC              = gcc
RM              = rm -rf
FLAGS           = -Wall -Wextra -Werror -Ilibft -Imlx  -g3 -fsanitize=address

# FILES AND PATH

HEADER_SRCS = cub3d.h
HEADER_DIR  = includes/
HEADER      = $(addprefix $(HEADER_DIR), $(HEADER_SRCS))


MPATH_SRCS  = 0_main.c \
				gnl1.c \
				gnl2.c \
				read_cub_file_1.c \
				read_cub_file_2.c \
				read_cub_file_3.c \
				read_cub_file_4.c \
				read_cub_file_utils.c \
				read_cub_file_utils_2.c \
				read_cub_file_utils_3.c \
				read_cub_file_utils_4.c \
				read_cub_file_utils_80.c \
				init_1.c \
				init_2.c \
				init_3.c \
				init_aux.c \
				moves_1.c \
				moves_2.c \
				moves_3.c \
				moves_4.c \
				99_utils.c \
				open_window.c \
				parse_utils_1.c \
				parse_utils_2.c \
				parse_utils_3.c \
				parse_utils_4.c \
				raycast_1.c \
				raycast_2.c \
				raycast_3.c \
				raycast_4.c \
				render_1.c \
				render_2.c \
				render_3.c \
				textures_1.c\
				textures_2.c\
				validate_borders.c\
				validate_borders_2.c\
				
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
