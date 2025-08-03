#include "../includes/cub3d.h"

void    *gc_malloc(t_gc *gc, size_t size)
{
    void        *ptr;
    t_gc_node   *gc_node;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    gc_node = malloc(sizeof(t_gc_node));
    if (!gc_node)
    {
        free(ptr);
        return (NULL);
    }
    gc_node->ptr = ptr;
    gc_node->next = gc->head;
    gc->head = gc_node;
    return ptr;
}

void    gc_free(t_game *game)
{
    t_gc_node    *tmp;

    if (!game->gc)
        return ;
    while (game->gc->head)
    {
        tmp = game->gc->head->next;
        free(game->gc->head->ptr);
        free(game->gc->head);
        game->gc->head = tmp;
    }
    free(game->gc);
    free(game);
}
