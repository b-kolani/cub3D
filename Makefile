NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBMLX = -L../minilibx_opengl_20191021 -I../minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit


HEADER = includes/cub3d.h
HEADER_BONUS = includes/cub3D_bonus.h 

SRCS = src/cub3d.c utils/error.c utils/ft_strlen.c \
	 	src/parsing/parse_map.c utils/ft_strjoin.c \
		src/events/events.c \
		utils/get_next_line.c utils/ft_strchr.c \
		utils/ft_strnstr.c utils/ft_strncmp.c \
		utils/ft_split.c utils/ft_strdup.c \
		utils/ft_strlcpy.c utils/ft_atoi.c \
		utils/ft_isspace.c src/memory_management.c \
		src/parsing/parse_elements.c src/parsing/check_map.c \
		utils/ft_substr.c utils/ft_calloc.c \
		utils/ft_bzero.c utils/ft_memset.c \
		src/parsing/validate_config.c src/parsing/validate_map.c \
		src/parsing/parse_elements_utils.c src/parsing/flood_fill.c \
		src/render/rendering.c src/init/init_mlx.c src/render/render_utils.c \
		src/render/raycasting.c src/render/raycasting_utils.c \
		src/player/movement.c src/player/movement_utils.c \
		src/player/rotate_camera.c src/render/load_textures.c

SRCS_BONUS = src_bonus/cub3d_bonus.c utils/error.c utils/ft_strlen.c \
	 	src_bonus/parsing_bonus/parse_map_bonus.c utils/ft_strjoin.c \
		src_bonus/events_bonus/events_bonus.c \
		utils/get_next_line.c utils/ft_strchr.c \
		utils/ft_strnstr.c utils/ft_strncmp.c \
		utils/ft_split.c utils/ft_strdup.c \
		utils/ft_strlcpy.c utils/ft_atoi.c \
		utils/ft_isspace.c src_bonus/memory_management_bonus.c \
		src_bonus/parsing_bonus/parse_elements_bonus.c \
		src_bonus/parsing_bonus/check_map_bonus.c \
		utils/ft_substr.c utils/ft_calloc.c \
		utils/ft_bzero.c utils/ft_memset.c \
		src_bonus/parsing_bonus/validate_config_bonus.c \
		src_bonus/parsing_bonus/validate_map_bonus.c \
		src_bonus/parsing_bonus/parse_elements_utils_bonus.c \
		src_bonus/parsing_bonus/flood_fill_bonus.c \
		src_bonus/render_bonus/rendering_bonus.c \
		src_bonus/init_bonus/init_mlx_bonus.c \
		src_bonus/render_bonus/render_utils_bonus.c \
		src_bonus/render_bonus/raycasting_bonus.c \
		src_bonus/render_bonus/raycasting_utils_bonus.c \
		src_bonus/player_bonus/movement_bonus.c \
		src_bonus/player_bonus/movement_utils_bonus.c \
		src_bonus/player_bonus/rotate_camera_bonus.c \
		src_bonus/render_bonus/load_textures_bonus.c \
		src_bonus/events_bonus/events_bonus_utils.c \
		src_bonus/render_bonus/raycasting_utils_0_bonus.c \
		src_bonus/render_bonus/render_utils_bonus_0.c \
		src_bonus/render_bonus/raycasting_utils_bonus_0.c \
		src_bonus/render_bonus/rendering_utils_bonus_.c \
		src_bonus/render_bonus/rendering_utils_bonus__.c \
		src_bonus/render_bonus/rendering_utils_bonus___.c \
		src_bonus/render_bonus/rendering_utils_bonus____.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBMLX) $^ -o $(NAME) 

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(LIBMLX) $(OBJS_BONUS) -o $@ 

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all re clean fclean bonus