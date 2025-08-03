#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "unistd.h"
# include "stdio.h"
# include "../../minilibx_opengl_20191021/mlx.h"
// # include "X11/X.h"
# include "fcntl.h"
# include "stdlib.h"
# include "string.h"
# include "stdbool.h"
# include "stdint.h"
# include "math.h"
# include "sys/time.h"

# define BUFFER_SIZE 42

// Pour les portes et sprites
// # define MAX_SPRITES 64
// # define MAX_DOORS 32
# define ENEMY_TYPE 0
# define DOOR_TYPE 1
# define ITEM_TYPE 2
# define SPRITE_TYPE_COUNT 3
# define ENEMY_FRAMES 8
# define ITEM_FRAMES 7
# define DOOR_FRAMES 1
# define MAX_FRAMES_PER_SPRITE 30

// Pour le rendu
# define HEIGHT 720
# define WIDTH 1280

typedef enum e_texture { NORTH, SOUTH, WEST, EAST }	t_texture;

// STRUCT POUR LES SPRITES
typedef struct	s_sprite {
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
	bool	active; // optionnel: pour désactivé le sprite si ramassé
}	t_sprite;

// STRUCT POUR LES PORTES
typedef struct	s_door {
	int		type;
	double	x;
	double	y;
	double	transform_x;
	double	transform_y;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	// double	anim_timer; // Pour l'animation d'ouverture des portes.
	bool	is_open;
}	t_door;

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
	t_img 		sprite_textures[SPRITE_TYPE_COUNT][MAX_FRAMES_PER_SPRITE];
	int			sprites_frames_count[SPRITE_TYPE_COUNT];
	t_keys		keys;
	double		move_speed;
	double		rot_speed;
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
int 	flood_fill(t_config *config, char **tmp_map, int x, int y);
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

// RAYCASTING FUNCTIONS
int		raycasting(t_game *game);
// int 	render_frame(t_game *game);
void	perform_dda(t_ray *ray, t_config *config);
void	init_dda(t_ray *ray, t_config *config);
void	compute_projection(t_ray *ray);
int		draw_column(t_ray *ray, t_game *game, int x);
// void    cast_single_ray(t_game *game, int x);

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
int close_window(t_game *game);

// LOAD TEXTURES FUNCTION
void    load_wall_all_tex(t_game *game);
void    load_all_sprites_tex(t_game *game);

#endif