/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_setup_items.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:25:23 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 23:21:48 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
setup_free_cells() {
    t_point *cell;
    t_cl_list *node;

    cl_delete_list(game->collectibles->free_cells);
    node = game->lair->next;
    while (node->data) {
        if (((t_cell *) node->data)->sprite_type == NONE)
            cl_insert_end(game->collectibles->free_cells, node->data);
        node = node->next;
    }
}

void
setup_food() {
    int free_cells_count;
    t_cl_list *node;
    t_cell *cell;

    free_cells_count = cl_size(game->collectibles->free_cells);
    for (int i = 0; i < COLLECTIBLES; i++) {
        node = cl_remove_node_by_position(game->collectibles->free_cells,
                                          rand() % free_cells_count--);
        ((t_cell *) node->data)->sprite_type = FOOD;
        cl_add_node_end(game->collectibles->food, node);
    }
}

void
setup_traps() {
    int free_cells_count;
    t_cl_list *node;
    t_cell *cell;

    free_cells_count = cl_size(game->collectibles->free_cells);
    for (int i = 0; i < TRAPS; i++) {
        node = cl_remove_node_by_position(game->collectibles->free_cells,
                                          rand() % free_cells_count--);
        ((t_cell *) node->data)->sprite_type = TRAP;
        cl_add_node_end(game->collectibles->traps, node);
    }
}
