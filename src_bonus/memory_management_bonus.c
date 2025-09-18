/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:22:09 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/13 22:41:12 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*tmp;

	if (!gc)
		return ;
	while (gc->head)
	{
		tmp = gc->head->next;
		free(gc->head->ptr);
		free(gc->head);
		gc->head = tmp;
	}
	free(gc);
}

static void	err_handler(t_gc *gc, const char *msg, int flag)
{
	if (flag)
		gc_free_all(gc);
	print_err(msg);
	exit(EXIT_FAILURE);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*gc_node;

	if (!gc || size == 0)
		err_handler(gc, "Error: invalid GC or size\n", 0);
	ptr = malloc(size);
	if (!ptr)
		err_handler(gc, "Error: memory allocation failed\n", 1);
	gc_node = malloc(sizeof(t_gc_node));
	if (!gc_node)
	{
		free(ptr);
		err_handler(gc, "Error: GC node allocation failed\n", 1);
	}
	gc_node->ptr = ptr;
	gc_node->next = gc->head;
	gc->head = gc_node;
	return (ptr);
}

void	gc_free(t_game *game)
{
	if (!game || !game->gc)
		return ;
	gc_free_all(game->gc);
	free(game);
}
