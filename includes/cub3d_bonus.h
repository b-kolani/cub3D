#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "unistd.h"
# include "stdio.h"
# include "../../minilibx_opengl_20191021/mlx.h"
# include "fcntl.h"
# include "stdlib.h"
# include "string.h"
# include "stdbool.h"
# include "stdint.h"
# include "math.h"
# include "sys/time.h"

# define BUFFER_SIZE 42

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

# define FOV (M_PI / 3)

# define HEIGHT 720
# define WIDTH 1280

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_texture;

typedef struct s_fov
{
	int     x;
	int		y;
	double	dx;
	double	dy;
	int		px;
	int		py;
	double	player_angle;
	int		intersection;
	double	start_angle;
	double	end_angle;
	double	step;
	int		map_x;
	int		map_y;
	double range;
}	t_fov;

typedef struct	s_sprite {
	// char	item;
	int		type; // 2, 3 etc.
	double	x;
	double	y;
	double	dx; // Position ralative x sprite -> joueur 
	double	dy; // Position ralative y sprite -> joueur 
	int		anim_index; // Frame d'animation actuelle
	double	anim_timer; // Temps écoulé depuis la dernière frame
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
	bool		active; // optionnel: pour désactivé le sprite si ramassé
	bool		is_open;
}	t_sprite;

typedef struct	s_item {
	t_sprite	sprite;
	bool		active; // optionnel: pour désactivé le sprite si ramassé
}	t_item;


// STRUCT FOR A VERTICAL LINE WHEN A RAY TOUCH A WALL
typedef struct s_draw {
	int	draw_start;
	int	draw_end;
	int	line_height;
	int	color; // A remplacer par texture apres et a utiliser
}	t_draw;

typedef struct s_vector {
	double	x; // Valeur de sur l'axe x 
	double	y;
}	t_vector;

typedef struct s_player {
	t_vector	pos;
	t_vector	dir; // direction du regard du joueur selon sa position 
	t_vector	plane; // Plan de la camera
}	t_player;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_img {
	void	*img_ptr; // Image créee en mémoire avec mlx_new_image
	char	*img_data_addr; // Pointeur vers les donnees de l'img en memoire img_data_addr
	int		bits_per_pixel; // Nombre de bits par pixel
	int		line_length; // Nombre d'octets par ligne
	int		endian; // ordere des octets (endiannas)
	int		width;
	int		height;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	// int		tex_dir;
}	t_img;

// STRUCT POUR LES PORTES
typedef struct	s_door {
	int			type;
	double		x;
	double		y;
	int			anim_index;
	int			state; // 0 fermée, 1 ouverte, 2 fermée, 3 ouverte
	float 		door_offset; // Ceci représente l'état d'une porte on utilise 
	// float pour une ouverture fluide ou progressive; avec un int on a une ouverture
	// brusque et ce n'est pas le comportement voulu
	t_img		tex;
	t_vector	dir;
	// int			pos_on_mini_map;
	bool		is_open;
	int			current_frame;
	float 		anim_timer; // Temps écoulé pour l'animation
	int			side_hit;
}	t_door;

typedef	struct s_config {
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	int				floor_color;
	int				ceil_color;
	t_map			map;
	t_player		player; // Joueur
	int 			floor_found;
	int				ceil_found;
	double			delta_time;
	struct timeval	prev_time;
	// Sprites
	t_sprite		*sprites;
	int				sprites_count;
	// Portes
	t_door			*doors;
	int				doors_count;
	// Z-buffer pour affichage correct des sprites (optionnel mais recommandé)
	// Eviter d'afficher les sprites derrières ou cachés par des murs
	double			*z_buffer;
}	t_config;


typedef	struct s_mlx {
	void	*mlx_ptr; // pointeur mlx global (le contexte) cree lors de la connexion avec le serveur grahique x11
	void	*win_ptr; // Fenetre (mlx window)
	t_img	screen; // L'image principale dans laquelle dessiner
}	t_mlx;

typedef struct s_ray {
	t_vector	ray_dir; // Direction du rayon lance depuis la position du joueur
	int			map_x;	// indice x donc la colonne (la case) sur la carte ou se trouve le rayon
	int			map_y;  // indice y donc de la ligne de la case sur la carte ou se trouve le rayon
	t_vector	side_dist; // Distance actuelle du rayon au prochain bord en x ou y
	t_vector	delta_dist; // Distance actuelle que le rayon doit parcourir pour traverser une case en x ou y
	double		perp_wall_dist; // Distance reelle perpendiculaire du joueur au mur; elle est 
	//utilisee pour calculer la hauteur reelle du mur vertical a dessiner
	int			step_x; // Sens dans lequel on avance dans la grille -1 a gauche 1 a droite
	int			step_y; // Sens dans lequel on avance dans la grille -1 vers le bas 1 vers le haut
	int			hit; // Indique si le rayon a touche un mur 0 pour non et 1 pour oui
	int			side; // Quel cote du mur a ete touche 0 pour le cote X (vertical: Est ou Ouest) et 1 pour le cote Y (horizontal: Haut ou Bas)
	t_draw		column;
	int			texture_id; // Ceci vaut 0 ou 1 ou 2 ou 3 dû au nombre de textures disponibles.
	int			text_type;
	int			door_x;
	int			door_y;
	t_door		*door_hit;
}	t_ray;

// FOR KEYS POUR MEMORISER LES TOUCHES PRESSES 
// CAR mlx NE CAPTE QU"UN SEUL CLIC 
// DONC POUR AVOIR UNE CLIQUE CONTINU
typedef struct s_keys {
	int	w;
	int a;
	int s;
	int d;
	int	left;
	int	right;
	int	enter;
}	t_keys;

// MEMORY MANAGEMENT FUNCTIONS AND GARBAGE COLLECTOR
// TYPE DEFINITION
typedef struct s_gc_node {
	void			*ptr;
	struct s_gc_node *next;
}	t_gc_node;

typedef struct s_gc {
	t_gc_node	*head;
}	t_gc;

typedef	struct s_game {
	t_config	config; // Contient les infos parsees
	t_mlx		mlx; 	// Graphismes mlx
	t_gc		*gc;
	t_img		textures[4]; // Tableau de 4 textures N, S, E, W
	t_img		door_textures[2];
	t_img 		sprite_textures[SPRITE_TYPE_COUNT][MAX_FRAMES_PER_SPRITE];
	int			sprites_frames_count[SPRITE_TYPE_COUNT];
	t_keys		keys;
	double		move_speed;
	double		rot_speed;
	int			last_x; // Dernière Position horizontale de la souris 
	// Pour la rotation par le mouvement de la souris
	// int			center_x;
	// int			center_y;
	int			g_mouse_lock; // Pour capturer le curseur dans le fenêtre 
	// C'est à dire activer/désactiver la capture de la souris
	// Pour pouvoir sortir de la fenêtre et interagir avec d'autres 
	// éléments extérieurs et revenir dans la fenêtre de jeu
	t_door		*door_in_front_of_player;
	t_fov		mini_map_fov;
}	t_game;

// MEMORY MANAGEMENT
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free(t_game *game);

// UTILS FUNCTIONS
int		print_err(const char *err_msg);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*get_next_line(int fd, t_gc *gc);
char	*ft_strjoin(char *s1, char *s2, t_gc *gc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s, t_gc *gc);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *str);
int 	ft_isspace(const char c);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t len);
void	*ft_memset(void *b, int c, size_t len);

// PARSING UTILS FUNCTIONS
int		parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len);
void    free_split_alloc(char **arr);
int 	is_color_line(const char *line);
int 	is_color_integer(char *color, int *rgb_int, t_gc *gc);
int 	is_path_line(const char *line);
int		is_map_config_line(const char *line);
int		is_map_desc_line(const char *line);
int		is_empty_line(const char *line);
// int 	d_fill(t_config *config, char **tmp_map, int x, int y);
int		flood_fill(t_config *config, char **tmp_map, int x, int y);
int 	flood_fill_space(t_config *config, char **tmp_map, int x, int y);
void    set_player_x_pos(t_config *config, char *pos_line);
void	set_player_orientation(t_player *player, char *pos_line);

// PARSING FUNCTIONS
int 	validate_config(t_config *config, t_gc *gc);
int		validate_map(t_config *config, t_gc *gc, size_t map_len);
void    fetch_map_desc_lines(t_config *config, char **lines, t_gc *gc);
int		parse_cub3d_map(t_config *config, t_gc *gc, const char *filename);
int 	parse_elements(t_config *config, t_gc *gc, char **lines, size_t *map_len);

// RENDER FUNCTIONS
int 	rendering(t_game *game);
int		init_mlx(t_mlx *mlx_);
// int		render_frame(t_game *game);

// RENDER UTILS FUNCTIONS 
int		draw_background(t_game *game);
int		put_pixel(t_img *img, int x, int y, int color);
int		get_texture_pixels(t_img* tex, int x, int y);
int		draw_mini_map(t_game *game);
int		draw_opened_door_side_x(t_game *game, int color, int pixel_x, int pixel_y);
int		draw_opened_door_side_y(t_game *game, int color, int pixel_x, int pixel_y);
int		draw_closed_door_side_x(t_game *game, int color, int pixel_x,int pixel_y);
int		draw_closed_door_side_y(t_game *game, int color, int pixel_x,int pixel_y);
void	calculate_dist_camera_to_sprite(t_config *config);
void	sort_sprites_by_distance(t_sprite *sprites, int count);
void	update_sprites_animation(t_game *game);
void	update_all_doors(t_config *config);
void	render_all_sprites(t_game *game);
int		draw_map_wall_cell(t_img *screen, int map_x, int map_y, int color);
int		is_item_active(t_config *config, int x, int y);
int		draw_map_item_cell(t_game *game, int map_x, int map_y, int color);
int		draw_map_door_cell(t_game *game, int map_x, int map_y, int color);
int		draw_player_on_the_map(t_game *game, int color);
int		project_and_render_sprite(t_game *game, t_sprite *sprite);

// RAYCASTING FUNCTIONS
int		raycasting(t_game *game);
// int 	render_frame(t_game *game);
void	perform_dda(t_ray *ray, t_config *config);
void	init_dda(t_ray *ray, t_config *config);
void	compute_projection(t_ray *ray);
int		draw_column(t_ray *ray, t_game *game, int x);
int		dda_hit_door(t_config *config, t_ray *ray);
void	get_x_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex);
void	get_y_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex);
void    init_text_helper(t_config *config, t_ray *ray, double *wall_x);
int		draw_col_helper(t_game *game, t_ray *ray, t_img *texture, int x);
t_img	*get_dir_texture(t_ray *ray, t_img *textures);
t_img	*get_door_dir_text(t_ray *ray, t_door *door, t_img *textures);
int		initialize_texture(t_ray *ray, t_img *texture, t_config *config);
int		apply_shadow(int color, double distance, int side);
void	init_fov(t_game *game, t_fov **fov);

// PLAYER AND ENEMYS MOVEMENTS AND EVENTS
int		update_player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
int 	mouse_move_handler(int x, int y, t_game *game);
int 	mouse_click_handler(int button, int x, int y, t_game *game);
// void	move_enemies(t_game *game);
void	handle_x_movement(t_game *game, double next_x);
void	handle_y_movement(t_game *game, double next_y);
void	detect_item(t_config *config, int x, int y);
// void	update_enemy_position(t_game *game, t_sprite *enemy);

// ROTATE CAMERA
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
// void    mouse_rotate_left(t_game *game, int rot_speed);
// void    mouse_rotate_right(t_game *game, int rot_speed);

// CLOSE GAME
int close_window(t_game *game);

// LOAD TEXTURES FUNCTION
void    load_wall_all_tex(t_game *game);
void    load_all_sprites_tex(t_game *game);
void    load_door_all_text(t_game *game);

// DOORS UTILS
t_door *find_door(t_config *config, int map_x, int map_y);
t_door  *get_door_in_front_of_player(t_config *config);
t_door	*get_door_in_front_helper(t_config *config, int idx);
void	open_door(t_game *game);

#endif