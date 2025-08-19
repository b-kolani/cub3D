#include "../../includes/cub3d_bonus.h"

// Projeter et rendre un sprite
int project_and_render_sprite(t_game *game, t_sprite *sprite)
{
    t_player    player;
    double      invDet;
    int         type;
    int         frame;
    t_img       *texture;
    int         y;
    int         d;
    int         color;
    int         stripe; // Ceci représenté la colonne du sprite à dessiner
    // puisque'on déssine chaque pixel colonne par colonne

    type = sprite->type;
    frame = sprite->anim_index;
    player = game->config.player;

    // Calculer la position relative sprite joueur
    // Cela reveint à calculer les coordonnées du vecteur
    // joueur -> sprite
    sprite->dx = sprite->x - player.pos.x;
    sprite->dy = sprite->y - player.pos.y;
    // Inverse du déterminant (projection caméra)
    invDet = 1.0 / (player.plane.x * player.dir.y - 
        player.dir.x * player.plane.y);
    // Transformation vers caméra
    sprite->transform_x = invDet * (player.dir.y * sprite->dx - player.dir.x * sprite->dy);
    sprite->transform_y = invDet * (-player.plane.y * sprite->dx + player.plane.x * sprite->dy);
    // Coordonnée écran horizontale du sprite
    // Ceci représente la position du centre du sprite à l'écran; calculée via la projection
    sprite->sprite_screen_x = (int)((WIDTH / 2) * (1 + sprite->transform_x / sprite->transform_y));
    
    // Hauteur/largeur projectées
    // La hauteur et la largeur ont la même taille
    // en 3D on considère les sprites étant des carrés
    // Calcul de la hauteur on utilise transform_y qui 
    // représente la position en 3D et aussi la profondeur 
    // de la visison du sprite par le joueur
    // Ici on utilise HEIGHT dans les deux cas car HEIGHT sert d'échelle
    // de représentation du sprite basée sur sa distance par rapport au joueur
    if (sprite->type == 2)
        sprite->sprite_height = fabs(HEIGHT / sprite->transform_y / 4);
    else
        sprite->sprite_height = fabs(HEIGHT / sprite->transform_y);
    // Position verticale du sprite: où commence verticalement le sprite
    // et où prend il fin verticalement. HEIGHT / 2 représente le centre
    // vertical de l'écran où dessiner le sprite, sprite->sprite_height / 2
    // représente la moitié de la hauteur (taille) du sprite à projeter
    // draw_start_y = milieu - moitié de la hauteur; le haut du sprite
    // draw_end_y = milieu + moitié de la hauteur; le bas du sprite
    // Cela place la hauteur du sprite à l'horizon (ligne centrale de l'écran), ce 
    // qui donne l'illusion qu'il est débout sur le sol.
    // Pour éviter le débordement donc des valeurs hors de l'écran on utilise fmax et fmin()
    // Calcul des bornes Y
    // sprite->draw_start_y = fmax(0, -(sprite->sprite_height / 2) + (HEIGHT / 2));
    sprite->draw_start_y = fmax(0, -(sprite->sprite_height / 2) + (HEIGHT / 2));
    // sprite->draw_end_y = fmin(HEIGHT - 1, (sprite->sprite_height / 2) + (HEIGHT / 2));
    sprite->draw_end_y = fmin(HEIGHT - 1, (sprite->sprite_height / 2) + (HEIGHT / 2));
    // sprite->draw_end_y = HEIGHT - 1;
    // Calcul de la largeur
    // Ceci est pour centrer le sprite autour de sprite_screen_x
    // Le calcul de draw_start_x et draw_end_x centre le sprite horizontalement autour 
    // de sa projection
    if (sprite->type == 2)
        sprite->sprite_width = fabs(HEIGHT / sprite->transform_y / 4);
    else
        sprite->sprite_width = fabs(HEIGHT / sprite->transform_y);
        // sprite->sprite_width = abs(HEIGHT * 3);
    // draw_start_x et draw_end_x représente la position horizontale du sprite projetée
    // Calcul des bornes X
    // Où commence le sprite dessiné horizontalement et où se termine t-il horizontalement
    sprite->draw_start_x = fmax(0, -sprite->sprite_width / 2 + sprite->sprite_screen_x);
    sprite->draw_end_x = fmin(WIDTH - 1, sprite->sprite_width / 2 + sprite->sprite_screen_x);

    // Trouver la bonne texture à l'aide du type et de la texture
    // Texture actuelle selon l'animation
    texture = &game->sprite_textures[type][frame];

    // On déssine chaque colonne(stripe) du sprite de gauche à droite
    // Dessiner pixel par pixel de la texture
    // Boucle de balayage horizontal du sprite
    // Cette condition évite de dessiner:
    // 1. Des sprites derrière la caméra (transformy > 0)
    // 2. Des colonnes hors de l'écran, (stripe dans [0, WIDTH])
    // 3. Des sprites cachés derrière un mur (z_buffer[stripe]) contient la distance au mur)

    // Parcourir les colonnes(stripes) du sprite à l'écran
    stripe = sprite->draw_start_x;
    while (stripe < sprite->draw_end_x)
    {
        if (sprite->transform_y > 0 && stripe >= 0 && stripe < WIDTH 
        && sprite->transform_y < game->config.z_buffer[stripe])
        {
            // Calcul de la colonne dans la texture
            texture->tex_x = (int)((stripe - (-sprite->sprite_width / 2 + sprite->sprite_screen_x)) 
                * texture->width / sprite->sprite_width);
            // Éviter les débordements
            if (texture->tex_x < 0)
                texture->tex_x = 0;
            else if (texture->tex_x >= texture->width)
                texture->tex_x = texture->width - 1;
            // parcourir verticalement chaque pixel de cette colonne
            y = sprite->draw_start_y;
            while (y < sprite->draw_end_y)
            {
                // Calcul de d comme offset vertical relatif
                d = (y - sprite->draw_start_y);
                texture->tex_y = (d * texture->height) / sprite->sprite_height;
                if (texture->tex_y < 0)
                    texture->tex_y = 0;
                else if (texture->tex_y >= texture->height)
                    texture->tex_y = texture->height - 1;
                color = get_texture_pixels(texture, texture->tex_x, texture->tex_y);
                // Éviter les pixels transparents
                if ((color & 0x00FFFFFF) != 0)
                    put_pixel(&game->mlx.screen, stripe, y, color);
                y++;
            }
        }
        stripe++;
    }
    return (0);
}

// Appelle project_and_render_sprite pour chaque sprite
void    render_all_sprites(t_game *game)
{
    t_sprite    *sprites;
    int         sprites_count;
    int         i;

    i = -1;
    sprites = game->config.sprites;
    sprites_count = game->config.sprites_count;
    while (++i < sprites_count)
    {
        // if (sprites[i].type != ENEMY_TYPE)
        // {
        if (sprites[i].active && sprites[i].type == ITEM_TYPE)
            project_and_render_sprite(game, &sprites[i]);
        // }
    }
}

// Calculer la distance caméra à chaque sprite
// La distance est en fait la norme du vecteur
// caméra à un sprite
void   calculate_dist_camera_to_sprite(t_config *config)
{
    int     i;
    double  dx; // x pour le nouveau vecteur
    double  dy; // y pour le nouveau vecteur

    i = -1;
    while (++i < config->sprites_count)
    {
        dx = config->sprites[i].x - config->player.pos.x;
        dy = config->sprites[i].y - config->player.pos.y;
        config->sprites[i].distance = dx * dx + dy * dy; // Ici la distance n'est rien
        // d'autre que la norme mais ici pas besoin de la racine 
        // carrée; car ici on aura besoin juste de la distance dans la fonction 
        // sort pour le tri; peu importe si on utilise la racine carrée
        // en plus la racine carrée (sqrt) est coûteuse
        // Donc ici la distane calculée ici est au carrée pour éviter l'
        // utilisation du temps du CPU inutilement
        // Dans sort la comparaison de ces distances se fera dans le même 
        // ordre ou mêmes proportions comme avec les distances réelles.
    }
}

void    sort_sprites_by_distance(t_sprite *sprites, int count)
{
    t_sprite    tmp;
    int         i;
    int         j;

    i = -1;
    while (++i < count - 1)
    {
        j = i + 1;
        while (j < count)
        {
            if (sprites[i].distance < sprites[j].distance)
            {
                tmp = sprites[i];
                sprites[i] = sprites[j];
                sprites[j] = tmp;
            }
            j++; 
        }
    }
}

// Update sprites frames
void    update_sprites_animation(t_game *game)
{
    double      anim_speed;
    t_sprite    *sprites;
    int         count;
    int         i;

    // anim_speed est le nombre de secondes ou le temps 
    // qu'on attend entre deux frames d'animation du sprite.
    anim_speed = 0.1; 
    sprites = game->config.sprites;
    count = game->config.sprites_count;
    i = -1;
    while (++i < count)
    {
        // anim_timer est le temps écoulé depuis la dernière frame
        // Elle sert pour avancer l'animation des sprites
        if (sprites[i].type == ITEM_TYPE 
            && sprites[i].active)
        {
            sprites[i].anim_timer += game->config.delta_time;
            if (sprites[i].anim_timer > anim_speed)
            {
                sprites[i].anim_timer = 0;
                sprites[i].anim_index++;
                if (sprites[i].anim_index >= game->sprites_frames_count[sprites[i].type])
                    sprites[i].anim_index = 0;
            }
        }
    }
}

void update_door_anim(t_door *door, double delta_time)
{
    double speed;

    // Vitesse d'ouverture/fermeture en unités par seconde
    // Ici 1.0 unité/seconde: en 1 seconde la porte passera de 0.0(fermée)
    // à 1.0(complètement ouverte)
    // Comme door_offset varie de 0.0 à 1.0; ça fait une animation fluide
    speed = 1.0; // unité/seconde
    // Si la porte doit s'ouvrir on augmente door_offset en multipliant 
    // le temps écoulé depuis la dernière frame (dela_time) à speed
    // la vitesse de changement de frames (plus )
    // Sinon si la porte doit se fermer on diminue door_offset 
    if (door->is_open && door->door_offset < 1.0)
        door->door_offset += delta_time * speed;
    else if (!door->is_open && door->door_offset > 0.0)
        door->door_offset -= delta_time * speed;
    // Ce garde fou ou cette sentinelle est là pour éviter 
    // des débordements.
    if (door->door_offset < 0.0)
        door->door_offset = 0.0;
    else if (door->door_offset > 1.0)
        door->door_offset = 1.0;
}

void    update_all_doors(t_config *config)
{
    int i;

    i = -1;
    while (++i < config->doors_count)
        update_door_anim(&config->doors[i], config->delta_time);
    // i = -1;
    // while (++i < config->doors_count)
    // {
    //     if (config->doors[i].is_open)
    //         config->map.grid[(int)config->doors[i].y][(int)config->doors[i].x] = '0';
    //     else
    //         config->map.grid[(int)config->doors[i].y][(int)config->doors[i].x] = '4';
    // }
}

int game_loop(t_game *game)
{
    struct timeval  curr_time;
    double          seconds;
    double          micros;

    // Calculer delat_time en secondes
    gettimeofday(&curr_time, NULL);
    seconds = (curr_time.tv_sec - game->config.prev_time.tv_sec);
    micros = (curr_time.tv_usec - game->config.prev_time.tv_usec) / 1e6;
    game->config.delta_time = seconds + micros;
    // Mettre à jour le temps précédent
    game->config.prev_time = curr_time;
    // Appeler update doors après update player; car le mouvement du joueur
    // modifie l'état des portes;
    // update_all_doors(&game->config);
    // update_player_pos
    if (update_player(game))
        return (-1);
    if (draw_background(game))
        return (-1);
    if (raycasting(game))
        return (-1);
    // Calculer la distance joueur - sprite
    calculate_dist_camera_to_sprite(&game->config);
    // int i = -1;
    // while (game->config.z_buffer[++i])
    //     printf("z_buffer %d:%f\n", i, game->config.z_buffer[i]);
    // Tri des sprites par distance
    sort_sprites_by_distance(game->config.sprites, game->config.sprites_count);
    // clear image pour un nouveau rendu
    // mlx_clear_window()
    // if (render_frame(game))
    //     return (-1);
    // Update sprites frames (animation)
    // move_enemies(game);
    update_sprites_animation(game);
    update_all_doors(&game->config);
    // Rendre les sprites ici
    render_all_sprites(game);
    // Draw mini map ici
    if (draw_mini_map(game))
    {
        gc_free(game);
        exit(-1);
    }
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
    // Créer une nouvelle image en mémoire et déssiner ou écrire pixel par pixel
    game->mlx.screen.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
    if (!game->mlx.screen.img_ptr)
        return (print_err("mlx error: Failed to create mlx image\n"));
    // Récupérer l'adresse de notre image en mémoire qui pointe vers le premier pixel 
    // dans le tableau des données brutes de notre image en mémoire et d'autres
    // données comme la longueur de chaque ligne du tableau en mémoire
    // le nombre de bits pour chaque pixel, comment chaque octet est stocké (endianness:
    // est ce du plus significatif au moins significatif ou le contraire)
    game->mlx.screen.img_data_addr = mlx_get_data_addr(game->mlx.screen.img_ptr, 
        &game->mlx.screen.bits_per_pixel, &game->mlx.screen.line_length, 
        &game->mlx.screen.endian);
    if (!game->mlx.screen.img_data_addr)
        return (print_err("mlx error: Failed to get image address\n"));
    game->config.z_buffer = gc_malloc(game->gc, sizeof(double) * WIDTH);
    if (!game->config.z_buffer)
        return (print_err("z_buffer allocation failed\n"));
    // if (access(game->config.no, F_OK) == 0)
    //     printf("Ok!: %s\n", game->config.no);
    // else
    //     printf("Wrong!: %s\n", game->config.no);
    load_wall_all_tex(game);
    load_door_all_text(game);
    load_all_sprites_tex(game);
    // Initialiser prev_time une fois ici qui sert à mémoriser 
    // le temps ou l'heure de la dernière frame on le comparera
    // à l'heure ou au temps actuelle pour calculer delta_time
    if (gettimeofday(&game->config.prev_time, NULL))
        return (print_err("Time error\n"));
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
    game->g_mouse_lock = 0;
    mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
    mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
    // game->last_x = -1;
    // game->center_x = WIDTH / 2;
    // game->center_y = HEIGHT / 2;
    mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move_handler, game);
    mlx_mouse_hook(game->mlx.win_ptr, mouse_click_handler, game);
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
