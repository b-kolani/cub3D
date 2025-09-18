/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:20:36 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/18 18:15:33 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "unistd.h"
# include "stdio.h"
# include "../../minilibx_opengl_20191021/mlx.h"
# include "fcntl.h"
# include "stdlib.h"
# include "stdbool.h"
# include "math.h"
# include "sys/time.h"

# define BUFFER_SIZE 42
# define MINIMAP_RADIUS 100
# define MINIMAP_SCALE 10
# define WALL_TYPE 0
# define DOOR_TYPE 1
# define ITEM_TYPE 2
# define SPRITE_TYPE_COUNT 3
# define ENEMY_FRAMES 8
# define ITEM_FRAMES 12
# define DOOR_FRAMES 2
# define MAX_FRAMES_PER_SPRITE 30
# define CELL_SIZE 10
# define ITEM_CELL_SIZE 5
# define PLAYER_CELL_SIZE 5
# define DOOR_CELL_SIZE 5
# define START_PIXEL_X 1
# define START_PIXEL_Y 1
# define FOV 1.047197551
# define HEIGHT 720
# define WIDTH 1280

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_texture;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_is_last
{
	int	c_color_flag;
	int	f_color_flag;
	int	no_path_flag;
	int	so_path_flag;
	int	we_path_flag;
	int	ea_path_flag;
}	t_is_last;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	color;
}	t_line;

typedef struct s_sprite
{
	int		type;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		anim_index;
	double	anim_timer;
	double	distance;
	double	transform_x;
	double	transform_y;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		sprite_screen_x;
	bool	active;
	bool	is_open;
}	t_sprite;

typedef struct s_iter_state
{
	int	i;
	int	map_started;
	int	f_map_line;
	int	l_map_line;
}	t_iter_state;

typedef struct s_item
{
	t_sprite	sprite;
	bool		active;
}	t_item;

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

typedef struct s_door
{
	int			type;
	double		x;
	double		y;
	int			anim_index;
	int			state;
	float		door_offset;
	t_img		tex;
	t_vector	dir;
	bool		is_open;
	int			current_frame;
	float		anim_timer;
	int			side_hit;
}	t_door;

typedef struct s_mini_map
{
	double		dx;
	double		dy;
	int			center_x;
	int			center_y;
	int			screen_x;
	int			screen_y;
	t_door		*door;
	t_sprite	*item;
}	t_mini_map;

typedef struct s_config
{
	t_is_last		last_map;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	int				floor_color;
	int				ceil_color;
	t_map			map;
	t_player		player;
	int				floor_found;
	int				ceil_found;
	double			delta_time;
	struct timeval	prev_time;
	t_sprite		*sprites;
	int				sprites_count;
	t_door			*doors;
	int				doors_count;
	double			*z_buffer;
}	t_config;

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
	int			text_type;
	int			door_x;
	int			door_y;
	t_door		*door_hit;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	enter;
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
	t_img		door_textures[2];
	t_img		sprite_textures[SPRITE_TYPE_COUNT][MAX_FRAMES_PER_SPRITE];
	int			sprites_frames_count[SPRITE_TYPE_COUNT];
	t_keys		keys;
	double		move_speed;
	double		rot_speed;
	int			last_x;
	int			g_mouse_lock;
	t_door		*door_in_front_of_player;
}	t_game;

typedef struct s_queue
{
	t_point	*data;
	int		max_size;
	int		front;
	int		back;
}	t_queue;

typedef struct s_parse_ctx
{
	t_config		*config;
	t_gc			*gc;
	char			**lines;
	t_iter_state	*state;
	size_t			*map_len;
}	t_parse_ctx;

typedef struct s_bfs_args
{
	t_gc		*gc;
	t_config	*config;
	char		**tmp_map;
}	t_bfs_args;

// MEMORY UTILS FUNCTIONS
void		*gc_malloc(t_gc *gc, size_t size);
void		gc_free(t_game *game);
void		clean_exit_and_exit(t_game *game, int status);

// UTILS FUNCTIONS
void		gc_free_all(t_gc *gc);
int			print_err(const char *err_msg);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *str, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*get_next_line(int fd, t_gc *gc);
char		*ft_strjoin(char *s1, char *s2, t_gc *gc);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s, t_gc *gc);
char		**ft_split(t_gc *gc, char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_atoi(const char *str);
int			ft_isspace(const char c);
char		*ft_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t len);
void		*ft_memset(void *b, int c, size_t len);

// PARSING UTILS FUNCTIONS
int			count_comma(const char *line);
int			is_last(t_parse_ctx *context);
int			is_door_valide(char **grid, int x, int y);
int			is_hidden(const char *path);
int			parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len);
int			is_color_line(const char *line);
int			is_color_integer(char *color, int *rgb_int, t_gc *gc);
int			is_path_line(const char *line);
int			is_map_config_line(const char *line, t_gc *gc);
int			is_map_desc_line(const char *line);
int			is_empty_line(const char *line);
int			d_fill(t_config *config, char **tmp_map, int x, int y);
int			flood_fill_space(t_config *config, char **tmp_map, int x, int y);
void		set_player_x_pos(t_config *config, char *pos_line);
void		set_player_orientation(t_player *player, char *pos_line);
t_door		*get_door_in_front_helper(t_config *config, int idx);
char		*ft_strtrim(char const *s1, char const *set, t_gc *gc);

// PARSING FUNCTIONS
int			is_valid(char *str);
int			validate_config(t_config *config, t_gc *gc);
int			validate_map(t_config *config, t_gc *gc, size_t map_len);
void		fetch_map_desc_lines(t_config *config, char **lines, t_gc *gc);
int			parse_cub3d_map(t_config *config, t_gc *gc, const char *filename);
int			parse_elements(t_config *config, t_gc *gc,
				char **lines, size_t *map_len);
int			ft_check_set(char c, char const *set);
int			check_for_an_empty_space_in(char **rgb);
void		init_values_to_iterate_on_line(int *i, int *map_started,
				int *first_map_line, int *last_map_line);
void		handle_vals_to_check_for_empty_line(int *i, int *map_started,
				int *first_map_line, int *last_map_line);
int			my_access(char *path);
int			flood_fill_space_bfs(t_bfs_args *args, int x, int y);
int			check_first_last_rows(t_map map, int i);
int			check_middle_rows(t_map map, int i, t_gc *gc);
int			check_player_count(char **tmp_map, int *player_count, int i);
size_t		find_max_width(t_config *config);
int			check_rgb_string(char *tmp);
void		init_vars(int *front, int *back);
void		set_plane(t_player *player, double x, double y);
int			get_element_path(const char *line, t_config *config, t_gc *gc);
int			parse_color(const char *line, t_config *config,
				char conf_type, t_gc *gc);
int			fill_sprites_and_doors_arrays(t_config *config, t_gc *gc);
int			handle_config_line_err(t_config *config, t_gc *gc, char *line,
				int map_started);
void		set_player_details(t_config *config, char **tmp_map, int i);
int			handle_config_line(t_config *config, t_gc *gc, char *line);
int			add_sprite(t_config *config, double x, double y, t_gc *gc);
int			add_door(t_config *config, int x, int y, t_gc *gc);
char		*clean_path(const char *line, t_gc *gc);

// RENDER FUNCTIONS
int			rendering(t_game *game);
int			init_mlx(t_mlx *mlx_);

// RENDER UTILS FUNCTIONS 
void		open_door(t_game *game);
int			draw_background(t_game *game);
int			put_pixel(t_img *img, int x, int y, int color);
int			get_texture_pixels(t_img *tex, int x, int y);
int			draw_mini_map(t_game *game, t_img screen);
void		calculate_dist_camera_to_sprite(t_config *config);
void		sort_sprites_by_distance(t_sprite *sprites, int count);
void		update_sprites_animation(t_game *game);
void		update_all_doors(t_config *config);
void		render_all_sprites(t_game *game);
t_sprite	*detect_item_(t_config *config, int x, int y);
int			is_item_active(t_config *config, int x, int y);
int			project_and_render_sprite(t_game *game, t_sprite *sprite);
int			draw_square(t_img *img, int x, int y, int color);
int			draw_filled_circle(t_img *img, int cx, int cy, int r);
int			draw_line_loop(t_img *img, t_line *ln);
int			draw_line(t_img *img, t_line *ln);
int			draw_line_(t_game *game, int center_x, int center_y);
int			draw_item_cell(t_game *game, t_mini_map *m_map, int x, int y);
int			draw_door_cell(t_game *game, t_mini_map *m_map, int x, int y);
int			process_line(t_parse_ctx *context);

// RAYCASTING FUNCTIONS
int			raycasting(t_game *game);
void		perform_dda(t_ray *ray, t_config *config);
void		init_dda(t_ray *ray, t_config *config);
void		compute_projection(t_ray *ray);
int			draw_column(t_ray *ray, t_game *game, int x);
int			dda_hit_door(t_config *config, t_ray *ray);
void		get_x_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex);
void		get_y_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex);
void		init_text_helper(t_config *config, t_ray *ray, double *wall_x);
int			draw_col_helper(t_game *game, t_ray *ray, t_img *texture, int x);
int			apply_shadow(int color, double distance, int side);

// PLAYER AND ENEMYS MOVEMENTS AND EVENTS
int			update_player(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		strafe_left(t_game *game);
void		strafe_right(t_game *game);
int			mouse_move_handler(int x, int y, t_game *game);
int			mouse_click_handler(int button, int x, int y, t_game *game);
void		handle_x_movement(t_game *game, double next_x);
void		handle_y_movement(t_game *game, double next_y);
void		detect_item(t_config *config, int x, int y);
int			find_player_position(t_config *config, char **tmp_map);

// ROTATE CAMERA
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);

// CLOSE GAME
int			close_window(t_game *game);

// LOAD TEXTURES FUNCTION
void		load_wall_all_tex(t_game *game);
void		load_all_sprites_tex(t_game *game);
void		load_door_all_text(t_game *game);

// DOORS UTILS
t_door		*find_door(t_config *config, int map_x, int map_y);
t_door		*get_door_in_front_of_player(t_config *config);

#endif