# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 13:36:16 by akuzmenk          #+#    #+#              #
#    Updated: 2024/01/15 17:52:09 by tfinni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
INC		:= ./includes
FLAGS	:= -Wall -Wextra -Werror
LIB_DIR	:= ./libft
LIBFT	:= $(LIB_DIR)/libft.a

SRCS	:= \
		src/main.c \
		src/utils.c \
		src/free.c \
		src/key_hook.c \
		src/key_hook_move.c \
		\
		src/raycaster/dda_algorithm.c \
		src/raycaster/ray_caster.c \
		src/raycaster/ray_caster_utils.c \
		\
		src/map_validation/check.c \
		src/map_validation/color.c \
		src/map_validation/create_map.c \
		src/map_validation/init.c \
		src/map_validation/list.c \
		src/map_validation/map_utils.c \
		src/map_validation/map.c \
		src/map_validation/surrounds.c \
		src/map_validation/textures.c \
		src/map_validation/textures_utils.c \
		\
		src/draw/create_textures.c \
		src/draw/draw_image.c \
		src/draw/draw_player.c \
		src/draw/draw_walls.c

B_SRCS	:= \
		bonus/free.c \
		bonus/image.c \
		bonus/key_hook.c \
		bonus/main.c \
		bonus/minimap.c \
		\
		src/utils.c \
		src/key_hook_move.c \
		\
		src/raycaster/dda_algorithm.c \
		src/raycaster/ray_caster.c \
		src/raycaster/ray_caster_utils.c \
		\
		src/map_validation/check.c \
		src/map_validation/color.c \
		src/map_validation/create_map.c \
		src/map_validation/init.c \
		src/map_validation/list.c \
		src/map_validation/map_utils.c \
		src/map_validation/map.c \
		src/map_validation/surrounds.c \
		src/map_validation/textures.c \
		src/map_validation/textures_utils.c \
		\
		src/draw/create_textures.c \
		src/draw/draw_image.c \
		src/draw/draw_player.c \
		src/draw/draw_walls.c 
		
OBJS	:= $(SRCS:.c=.o)

B_OBJS	:= $(B_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIB_DIR)
	cc $(FLAGS) $(OBJS) -o $(NAME) -L. -lmlx -framework OpenGL -framework AppKit -L. $(LIBFT)
#	cc $(FLAGS) $(OBJS) -o $(NAME) -L./minilibx_linux/ -lmlx_Linux -lX11 -lXext -lm $(LIBFT)	

bonus: $(B_OBJS)
	make -sC $(LIB_DIR)
	cc $(FLAGS) $(B_OBJS) -o $(NAME) -L. -lmlx -framework OpenGL -framework AppKit -L. $(LIBFT)
#	cc $(FLAGS) $(B_OBJS) -o $(NAME) -L./minilibx_linux/ -lmlx_Linux -lX11 -lXext -lm $(LIBFT)	

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	make clean -sC $(LIB_DIR)
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	make fclean -sC $(LIB_DIR)
	rm -f $(NAME) $(B_NAME)

re: fclean all
