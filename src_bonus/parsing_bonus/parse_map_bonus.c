#include "../../includes/cub3d_bonus.h"

// Lecture du fichier .cub
static char **read_map_file_lines(const char *filename, t_gc *gc)
{
    int fd;
    char    **lines;
    char    *line;
    int     i;

    fd = open(filename, O_RDONLY, 0644);
    if (fd == -1)
        return (NULL);
    lines = gc_malloc(gc, sizeof(char *) * 2048);
    if (!lines)
        return (NULL);
    line = NULL;
    i = -1;
    while ((line = get_next_line(fd, gc)) && i < 2047)
        lines[++i] = ft_strdup(line, gc);
    lines[++i] = NULL;
    close(fd);
    return (lines);
}

int    add_sprite(t_config *config, double x, double y, int type)
{
    t_sprite    *new_arr;
    int         i;

    // Créer un nouveau tableau et faire l'allocation
    new_arr = malloc(sizeof(t_sprite) * (config->sprites_count + 1));
    if (!new_arr)
        return (print_err("new_arr allocation failed\n"));
    // Si l'ancien tableau avait un contenu
    // le copier dans le nouveau
    i = -1;
    while (++i < config->sprites_count)
        new_arr[i] = config->sprites[i];
    // Ajouter le nouveau sprite
    // new_arr[config->sprites_count].item = '3';
    new_arr[config->sprites_count].x = x + 0.5;
    new_arr[config->sprites_count].y = y + 0.5;
    new_arr[config->sprites_count].type = type;
    // if (type == ITEM_TYPE)
    new_arr[config->sprites_count].active = true;
    // else if (type == DOOR_TYPE)
    //     new_arr[config->sprites_count].is_open = false;
    new_arr[config->sprites_count].anim_index = 0; // Frame courant du sprite
    // Libérer l'ancien tableau avant de
    // lui assigner le nouveau;
    if (config->sprites)
        free(config->sprites);
    // Affecter le nouveau tableau à l'ancien
    config->sprites = new_arr;
    config->sprites_count++;
    return (0);
}

int    add_door(t_config *config, int x, int y)
{
    t_door  *new_arr;
    int     i;

    new_arr = malloc(sizeof(t_door) * (config->doors_count + 1));
    if (!new_arr)
        return (print_err("new_arr allocation failed\n"));
    i = -1;
    while (++i < config->doors_count)
        new_arr[i] = config->doors[i];
    // new_arr[config->doors_count].door = '4';
    new_arr[config->doors_count].x = x + 0.5;
    new_arr[config->doors_count].y = y + 0.5;
    new_arr[config->doors_count].anim_timer = 0;
    new_arr[config->doors_count].is_open = false;
    new_arr[config->doors_count].type = DOOR_TYPE;
    new_arr[config->doors_count].door_offset = 0.0;
    new_arr[config->doors_count].state = 0;
    new_arr[config->doors_count].side_hit = 0;
    // new_arr[config->doors_count].dir.x = 0;
    // new_arr[config->doors_count].dir.y = 0;
    // if (new_arr[config->doors_count].x - config->player.pos.x > 0)
    //     new_arr[config->doors_count].dir.x = 1;
    // else if (new_arr[config->doors_count].x - config->player.pos.x < 0)
    //     new_arr[config->doors_count].dir.x = -1;
    // if (new_arr[config->doors_count].y - config->player.pos.y > 0)
    //     new_arr[config->doors_count].dir.y = 1;
    // else if (new_arr[config->doors_count].y - config->player.pos.y < 0)
    //     new_arr[config->doors_count].dir.y = -1;
    if (config->doors)
        free(config->doors);
    config->doors = new_arr;
    config->doors_count++;
    return (0);
}

int    fill_sprites_and_doors_arrays(t_config *config)
{
    int i;
    int j;

    i = -1;
    while (config->map.grid[++i])
    {
        j = -1;
        while (config->map.grid[i][++j])
        {
            // if (config->map.grid[i][j] == '2')
            // {
            //     if (add_sprite(config, j, i, ENEMY_TYPE))
            //         return (-1);
            // }
            if (config->map.grid[i][j] == '3')
            {
                if (add_sprite(config, j, i, ITEM_TYPE))
                    return (-1);
            }
            else if (config->map.grid[i][j] == '4')
            {
                // if (add_sprite(config, j, i, DOOR_TYPE))
                //     return (-1);
                if (add_door(config, j, i))
                    return (-1);
            }
        }
    }
    return (0);
}

// Fonction principale du parsing
int	parse_cub3d_map(t_config *config, t_gc *gc, const char *filename)
{
    char    **lines;
    size_t  map_desc_len;

    map_desc_len = 0;
    config->sprites = NULL;
    config->sprites_count = 0;
    config->doors = NULL;
    config->doors_count = 0;
    if (ft_strncmp(filename + (ft_strlen(filename) - 4), ".cub", 4))
        return (print_err("File error: invalid file; need .cub extension file\n"));
    lines = read_map_file_lines(filename, gc);
    if (!lines)
        return (print_err("Map error: Failed when getting map lines!\n"));
    if (parse_elements(config, gc, lines, &map_desc_len)
        || validate_config(config, gc) 
        || validate_map(config, gc, map_desc_len))
        return (-1);
    config->map.grid[(int)config->player.pos.y][(int)config->player.pos.x] = '0';
    // config->sprites = gc_malloc(gc, config->sprites_count * sizeof(t_sprite) + 1);
    // if (!config->sprites)
    //     return (print_err("Sprites array allocation failed\n"));
    // config->doors = gc_malloc(gc, config->doors_count * sizeof(t_door) + 1);
    // if (!config->doors)
    //     return (print_err("Doors array allocation failed\n"));
    if (fill_sprites_and_doors_arrays(config))
        return (-1);
    // int i = -1;
    // while (++i < config->sprites_count)
    //     printf("Sprite: %d\n", config->sprites[i].type);
    // i = -1;
    // while (++i < config->doors_count)
    //     printf("Door: x: %d, y: %d\n", config->doors[i].x, config->doors[i].y);
    // int i = -1;
    // while (++i < config->doors_count)
    //     printf("Player dir: x:%f, y:%f - Door dir: x:%f, y:%f\n", 
    //     config->player.dir.x, config->player.dir.y, 
    //     config->doors[i].dir.x, config->doors[i].dir.y);
    
    return (0);
}
