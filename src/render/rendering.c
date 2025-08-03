#include "../../includes/cub3d.h"

int game_loop(t_game *game)
{
    // update_player_pos
    if (update_player(game))
        return (-1);
    if (draw_background(game))
        return (-1);
    if (raycasting(game))
        return (-1);
    // clear image pour un nouveau rendu
    // mlx_clear_window()
    // if (render_frame(game))
    //     return (-1);
    
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.screen.img_ptr,
        0, 0);
    return (0);
}

int close_window(t_game *game)
{
    printf("Window closed: exiting...\n");
    if (game->mlx.screen.img_ptr)
        mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.screen.img_ptr);
    if (game->mlx.mlx_ptr)
        mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
    gc_free(game);
    exit(0);
}

int rendering(t_game *game)
{
    if (init_mlx(&game->mlx))
        return (-1);
    // Creer une nouvelle image en memoire et dessiner ou ecrire pixel par pixel
    game->mlx.screen.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
    if (!game->mlx.screen.img_ptr)
        return (print_err("mlx error: Failed to create mlx image\n"));
    // Recuperer l'adresse de notre image en memoire qui pointe vers le premier pixel 
    // dans le tableau des donnees brutes de notre image en memoire et d'autres
    // donnees comme la longueur de chaque ligne du tableau en memoire
    // le nombre de bits pour chaque pixel, comme chaque octets est stocke (endianness:
    // est ce du plus significatif au moins significatif ou le contraire)
    game->mlx.screen.img_data_addr = mlx_get_data_addr(game->mlx.screen.img_ptr, 
        &game->mlx.screen.bits_per_pixel, &game->mlx.screen.line_length, 
        &game->mlx.screen.endian);
    if (!game->mlx.screen.img_data_addr)
        return (print_err("mlx error: Failed to get image address\n"));
    // if (access(game->config.no, F_OK) == 0)
    //     printf("Ok!: %s\n", game->config.no);
    // else
    //     printf("Wrong!: %s\n", game->config.no);
    game->textures[NORTH] = load_texture(game, game->config.no);
    game->textures[SOUTH] = load_texture(game, game->config.so);
    game->textures[EAST] = load_texture(game, game->config.ea);
    game->textures[WEST] = load_texture(game, game->config.we);
    // ft_memset(game->mlx.screen.img_data_addr, 0, WIDTH * HEIGHT * 4);
    // Ensuite commencer par dessiner dans notre image en memoire 
    // avec une fonction personnalisee que nous allons appeler 
    // put_pixel(). mlx a une telle fonction mais cette fonction 
    // ecrit directement dans la fenetre sans passer par une image tampon
    // donc tres lent si dessiner pixel par pixel. On utilise a des fins de 
    // de simples tests et petits dessins.
    // Avec notre fonction personnalisee on dessine d'abord dans une image tampon
    // donc un dessin performant; rendu complet (ex: raycasting); tres rapide;
    // puis affichage en bloc
    // printf("Img addr: %p\n", game->mlx.screen.img_data_addr);
    // printf("bbp: %d\n", game->mlx.screen.bits_per_pixel);
    // printf("Line size: %d\n", game->mlx.screen.line_length);
    // printf("Endianness: %d\n", game->mlx.screen.endian);
    // if (put_pixel(&game->mlx.screen, 0, 0, 0x00FF0000))
    //     return (-1);
    mlx_hook(game->mlx.win_ptr, 2, 1L<<0, key_press, game);
    mlx_hook(game->mlx.win_ptr, 3, 1L<<1, key_release, game);
    mlx_hook(game->mlx.win_ptr, 17, 0L, close_window, game);
    // if (game_loop(game))
    //     return (-1);
    // Coller l'image sur la fenetre la position du pixel dessine
    // est determiner par la combinaison des x de put_pixel et 
    // mlx_put_img_to_window et pareil pour y
    mlx_loop_hook(game->mlx.mlx_ptr, game_loop, game);
    mlx_loop(game->mlx.mlx_ptr);
    return (0);
}
