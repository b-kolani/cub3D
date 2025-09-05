#include "../includes/cub3d_bonus.h"

int	main(int ac, const char **av)
{
	t_game	*game;

	if (ac != 2)
		return (print_err("Usage: ./cub3D <map>.cub\n"));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_err("game allocation failed\n"));
	game->gc = malloc(sizeof(t_gc));
	if (!game->gc)
		return (print_err("Allocation of gc failed\n"));
	game->gc->head = NULL;
	if (parse_cub3d_map(&game->config, game->gc, av[1]))
	{
		gc_free(game);
		return (-1);
	}
	if (rendering(game))
	{
		gc_free(game);
		return (-1);
	}
	gc_free(game);
	return (0);
}
