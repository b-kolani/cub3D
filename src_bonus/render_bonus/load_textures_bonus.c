#include "../../includes/cub3d_bonus.h"

static t_img   load_texture(t_game *game, char *file)
{
    t_img   tex;

    tex.img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr, 
        file, &tex.width, &tex.height);
    if (!tex.img_ptr)
    {
        gc_free(game);
        exit(-1);
    }
    tex.img_data_addr = mlx_get_data_addr(tex.img_ptr, &tex.bits_per_pixel,
        &tex.line_length, &tex.endian);
    if (!tex.img_data_addr)
    {
        gc_free(game);
        exit(-1);
    }
    return (tex);
}

void    load_wall_all_tex(t_game *game)
{
    game->textures[NORTH] = load_texture(game, game->config.no);
    game->textures[SOUTH] = load_texture(game, game->config.so);
    game->textures[WEST] = load_texture(game, game->config.we);
    game->textures[EAST] = load_texture(game, game->config.ea);
}

void    load_door_all_text(t_game *game)
{
    // int     i;
    // t_door  *doors;
    // int     doors_count;

    // doors = game->config.doors;
    // doors_count = game->config.doors_count;
    // i = -1;
    // while (++i < doors_count)
    // {
    //     if (!doors[i].is_open)
    //         doors[i].tex = load_texture(game, "sprites/door_closed.xpm");
    //     else
    //         doors[i].tex = load_texture(game, "sprites/door_opened.xpm");
    // }
    game->door_textures[0] = load_texture(game, "sprites/door.xpm");
    game->door_textures[1] = load_texture(game, "sprites/door.xpm");
}

static void load_item_sprites(t_game *game, int type, char *files_paths[], int frames_count)
{
    int i;

    i = -1;
    while (++i < frames_count)
    {
        game->sprite_textures[type][i].img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
            files_paths[i], &game->sprite_textures[type][i].width,
            &game->sprite_textures[type][i].height);
        if (!game->sprite_textures[type][i].img_ptr)
        {
            gc_free(game);
            exit(-1);
        }
        game->sprite_textures[type][i].img_data_addr = mlx_get_data_addr(game->sprite_textures[type][i].img_ptr,
            &game->sprite_textures[type][i].bits_per_pixel, &game->sprite_textures[type][i].line_length,
            &game->sprite_textures[type][i].endian);
        if (!game->sprite_textures[type][i].img_data_addr)
        {
            gc_free(game);
            exit(-1);
        }
    }
    game->sprites_frames_count[type] = frames_count;
}

// static void load_door_sprites(t_game *game, int type, char **files, int frames_count)
// {
//     int i;

//     i = -1;
//     while (++i < frames_count)
//     {
//         game->sprite_textures[type][i].img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
//             files[i], &game->sprite_textures[type][i].width, &game->sprite_textures[type][i].height);
//         if (!game->sprite_textures[type][i].img_ptr)
//         {
//             gc_free(game);
//             exit(-1);
//         }
//         game->sprite_textures[type][i].img_data_addr = mlx_get_data_addr(
//             game->sprite_textures[type][i].img_ptr, &game->sprite_textures[type][i].bits_per_pixel,
//             &game->sprite_textures[type][i].line_length, 
//             &game->sprite_textures[type][i].endian);
//         if (!game->sprite_textures[type][i].img_data_addr)
//         {
//             gc_free(game);
//             exit(-1);
//         }
//     }
//     game->sprites_frames_count[type] = frames_count;
//     // printf("%d\n", game->config.doors_count);
//     // while (++i < game->config.doors_count)
//     //     printf("%c\n", game->config.doors->type);
// }

void    load_all_sprites_tex(t_game *game)
{
    // char    *enemy_sprites[ENEMY_FRAMES] = {
    //     "sprites/sonic_0.xpm",
    //     "sprites/sonic_1.xpm",
    //     "sprites/sonic_2.xpm",
    //     "sprites/sonic_3.xpm",
    //     "sprites/sonic_4.xpm",
    //     "sprites/sonic_5.xpm",
    //     "sprites/sonic_6.xpm",
    //     "sprites/sonic_7.xpm"
    // };
    char    *item_sprites[ITEM_FRAMES] = {
        "sprites/1.xpm",
        "sprites/2.xpm",
        "sprites/3.xpm",
        "sprites/4.xpm",
        "sprites/5.xpm",
        "sprites/6.xpm",
        "sprites/7.xpm",
        "sprites/8.xpm",
        "sprites/9.xpm",
        "sprites/10.xpm",
        "sprites/11.xpm",
        "sprites/12.xpm"
    };
    // char    *door_sprites[DOOR_FRAMES] = {
    //     "sprites/door_closed.xpm",
    //     "sprites/door_opened.xpm",
    // };
    // load_item_sprites(game, ENEMY_TYPE, enemy_sprites, ENEMY_FRAMES);
    load_item_sprites(game, ITEM_TYPE, item_sprites, ITEM_FRAMES);
    // load_door_sprites(game, DOOR_TYPE, door_sprites, DOOR_FRAMES);
    // int i = -1;
    // while (++i < 3)
    //     printf("Frames per sprites: %d\n", game->sprites_frames_count[i]);
}
