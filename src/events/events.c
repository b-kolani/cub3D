#include "../../includes/cub3d.h"

int key_press(int keycode, t_game *game)
{
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
    return (0);
}
