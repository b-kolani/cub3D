/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:04 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/18 18:15:40 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "unistd.h"
# include "stdio.h"
# include "../../minilibx_opengl_20191021/mlx.h"
# include "fcntl.h"
# include "stdlib.h"
# include "math.h"

# define BUFFER_SIZE 42
# define HEIGHT 720
# define WIDTH 1280

typedef struct s_is_last
{
	int	c_color_flag;
	int	f_color_flag;
	int	no_path_flag;
	int	so_path_flag;
	int	we_path_flag;
	int	ea_path_flag;
}	t_is_last;

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_texture;

typedef struct s_iter_state
{
	int	i;
	int	map_started;
	int	f_map_line;
	int	l_map_line;
}	t_iter_state;

typedef struct s_draw
{
	int	draw_start;
	int	draw_end;
	int	line_height;
	int	color;
}	t_draw;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	t_is_last	last_map;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			floor_color;
	int			ceil_color;
	t_map		map;
	t_player	player;
	int			floor_found;
	int			ceil_found;
}	t_config;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_queue
{
	t_point	*data;
	int		max_size;
	int		front;
	int		back;
}	t_queue;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_data_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	screen;
}	t_mlx;

typedef struct s_ray
{
	t_vector	ray_dir;
	int			map_x;
	int			map_y;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	t_draw		column;
	int			texture_id;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

typedef struct s_game
{
	t_config	config;
	t_mlx		mlx;
	t_gc		*gc;
	t_img		textures[4];
	t_keys		keys;
	double		move_speed;
	double		rot_speed;
}	t_game;

typedef struct s_bfs_args
{
	t_gc		*gc;
	t_config	*config;
	char		**tmp_map;
}	t_bfs_args;

typedef struct s_parse_ctx
{
	t_config		*config;
	t_gc			*gc;
	char			**lines;
	t_iter_state	*state;
	size_t			*map_len;
}	t_parse_ctx;

// MEMORY MANAGEMENT
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free(t_game *game);

// UTILS FUNCTIONS
int		count_comma(const char *line);
int		is_last(t_parse_ctx *context);
int		print_err(const char *err_msg);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*get_next_line(int fd, t_gc *gc);
char	*ft_strjoin(char *s1, char *s2, t_gc *gc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s, t_gc *gc);
char	**ft_split(t_gc *gc, char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *str);
int		ft_isspace(const char c);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t len);
void	init_vars(int *front, int *back);
void	*ft_memset(void *b, int c, size_t len);
int		normalized(char **config_map, char **tmp, t_gc *gc, size_t max_len);
void	init_values_to_iterate_on_line(int *i, int *map_started,
			int *first_map_line, int *last_map_line);
void	handle_vals_to_check_for_empty_line(int *i, int *map_started,
			int *first_map_line, int *last_map_line);
int		set_config(t_config *config, t_gc *gc, size_t map_len);
int		my_access(char *path);
void	set_plane(t_player *player, double x, double y);
int		ft_check_set(char c, char const *set);
int		get_element_path(const char *line, t_config *config, t_gc *gc);
int		check_for_an_empty_space_in(char **rgb);
int		handle_config_line_err(t_config *config,
			t_gc *gc, char *line, int map_started);
int		parse_color(const char *line,
			t_config *config, char conf_type, t_gc *gc);

// PARSING UTILS FUNCTIONS
int		is_hidden(const char *path);
int		parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len);
int		is_color_line(const char *line);
int		is_color_integer(char *color, int *rgb_int, t_gc *gc);
int		is_path_line(const char *line);
int		is_map_config_line(const char *line, t_gc *gc);
int		is_map_desc_line(const char *line);
int		is_empty_line(const char *line);
int		flood_fill_space_bfs(t_bfs_args *args, int x, int y);
void	set_direction(t_player *player, char dir);
void	set_player_x_pos(t_config *config, char *pos_line);
void	set_player_orientation(t_player *player, char *pos_line);
int		handle_config_line(t_config *config, t_gc *gc, char *line);
char	*clean_path(const char *line, t_gc *gc);
int		process_line(t_parse_ctx *context);
char	*ft_strtrim(char const *s1, char const *set, t_gc *gc);

// PARSING FUNCTIONS
int		is_valid(char *str);
int		validate_config(t_config *config, t_gc *gc);
int		validate_map(t_config *config, t_gc *gc, size_t map_len);
void	fetch_map_desc_lines(char **grid, char **lines, t_gc *gc);
int		parse_cub3d_map(t_config *config, t_gc *gc, const char *filename);
int		parse_elements(t_config *config,
			t_gc *gc, char **lines, size_t *map_len);
size_t	find_max_width(t_config *config);
int		check_player_count(char **tmp_map, int *player_count, int i);
int		check_first_last_rows(t_map map, int i);
int		check_middle_rows(t_map map, int i, t_gc *gc);

// RENDER FUNCTIONS
int		rendering(t_game *game);
int		ft_init_mlx(t_mlx *mlx);

// RENDER UTILS FUNCTIONS 
int		draw_background(t_game *game);
int		put_pixel(t_img *img, int x, int y, int color);
int		get_texture_pixels(t_img *tex, int x, int y);
int		initialize_texture(t_ray *ray, t_img *texture, t_config *config);

// RAYCASTING FUNCTIONS
int		raycasting(t_game *game);
void	perform_dda(t_ray *ray, t_config *config);
void	init_dda(t_ray *ray, t_config *config);
void	compute_projection(t_ray *ray);
int		draw_column(t_ray *ray, t_game *game, int x);
int		draw_col_checker(t_game *game, t_img *texture, t_ray *ray);

// PLAYER MOVEMENTS
int		update_player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);

// ROTATE CAMERA
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// CLOSE GAME
int		close_window(t_game *game);

// LOAD TEXTURES FUNCTION
t_img	load_texture(t_game *game, char *file);

#endif