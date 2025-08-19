#include "../../includes/cub3d_bonus.h"

t_door  *get_door_in_front_of_player(t_config *config)
{
    int i;
    t_door  *doors;
    t_vector *player_pos;

    i = -1;
    doors = config->doors;
    player_pos = &config->player.pos;
    while (++i < config->doors_count)
    {
        if (((int)player_pos->y + 1 <= config->map.height - 1) 
            && config->map.grid[(int)player_pos->y + 1][(int)player_pos->x] == '4'
            && (int)player_pos->x == (int)doors[i].x
            && (int)(player_pos->y + 1) == (int)doors[i].y)
            return (&doors[i]);
        else if (((int)player_pos->y - 1 >= 0) 
            && config->map.grid[(int)player_pos->y - 1][(int)player_pos->x] == '4'
            && (int)player_pos->x == (int)doors[i].x
            && (int)(player_pos->y - 1) == (int)doors[i].y)
            return (&doors[i]);
        else if (((int)player_pos->x + 1 <= config->map.width - 1) 
            && config->map.grid[(int)player_pos->y][(int)player_pos->x + 1] == '4'
            && (int)(player_pos->x + 1) == (int)doors[i].x
            && (int)player_pos->y == (int)doors[i].y)
            return (&doors[i]);
        else if (((int)player_pos->x - 1 >= 0) 
            && config->map.grid[(int)player_pos->y][(int)player_pos->x - 1] == '4'
            && (int)(player_pos->x - 1) == (int)doors[i].x
            && (int)player_pos->y == (int)doors[i].y)
            return (&doors[i]);
    }
    return (NULL);
}

int key_press(int keycode, t_game *game)
{
    t_door  *door;

    if (keycode == 119 || keycode == 13)
        game->keys.w = 1; // W KEY
    else if (keycode == 97 || keycode == 0)
        game->keys.a = 1; // A KEY
    else if (keycode == 115 || keycode == 1)
        game->keys.s = 1; // S KEY
    else if (keycode == 100 || keycode == 2)
        game->keys.d = 1; // D KEY
    else if (keycode == 65361 || keycode == 123)
        game->keys.left = 1; // LEFT ARROW KEY
    else if (keycode == 65363 || keycode == 124)
        game->keys.right = 1; // RIGHT ARROW KEY
    else if (keycode == 76)
    {
        // game->keys.enter = 1; // ENTER KEY
        door = get_door_in_front_of_player(&game->config);
        if (door)
        {
            if (!door->is_open && door->door_offset == 0.0)
                door->is_open = true;
            else if (door->is_open && door->door_offset == 1.0)
                door->is_open = false;
        }
    }
    else if (keycode == 65307 || keycode == 53)
        close_window(game);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == 119 || keycode == 13)
        game->keys.w = 0; // W KEY
    else if (keycode == 97 || keycode == 0)
        game->keys.a = 0; // A KEY
    else if (keycode == 115 || keycode == 1)
        game->keys.s = 0; // S KEY
    else if (keycode == 100 || keycode == 2)
        game->keys.d = 0; // D KEY
    else if (keycode == 65361 || keycode == 123)
        game->keys.left = 0; // LEFT ARROW KEY
    else if (keycode == 65363 || keycode == 124)
        game->keys.right = 0; // RIGHT ARROW KEY
    else if (keycode == 76)
        game->keys.right = 0;
    return (0);
}

// Cette fonction gère le mouvement de la souris
int mouse_move_handler(int x, int y, t_game *game)
{
    (void)y;
    int         center_x;
    int         delta_x;

    if (game->g_mouse_lock == 0)
        return (0);
    center_x = WIDTH / 2;
    if (x == center_x)
        return (0);
    delta_x = x - center_x;
    if (delta_x > 0)
        rotate_right(game);
    else
        rotate_left(game);
    mlx_mouse_move(game->mlx.win_ptr, center_x, HEIGHT / 2);
    return (0);
}

// Cette fonction active/désactive la capture du curseur
int mouse_click_handler(int button, int x, int y, t_game *game)
{
    (void)x;
    if (button == 1) {
        if (y >= 2)
            game->g_mouse_lock = !game->g_mouse_lock;
    }
    if (game->g_mouse_lock)
        mlx_mouse_hide();
    else
        mlx_mouse_show();
    return (0);
}
