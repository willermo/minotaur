/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_setup_neighbours.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:22:40 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 19:23:10 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
add_neighbour(t_cell *cell, t_cell *neighbour) {
    if (neighbour &&
        !cl_get_node_by_data(cell->neighbours, neighbour, compare_lair_cells))
        cl_insert_begin(cell->neighbours, neighbour);
}

static t_cell *
get_neighbour(t_point coords) {
    t_cell cell;
    t_cell *neighbour;

    if (!is_walkable_cell(coords))
        return (NULL);
    cell.coords = (t_point){coords.x, coords.y};
    neighbour =
        (t_cell *) (cl_get_node_by_data(game->lair, &cell, compare_lair_cells)
                        ->data);
    return (neighbour);
}

void
add_neighbours(void *cell) {
    t_cell *c = (t_cell *) cell;
    add_neighbour(c, get_neighbour((t_point){c->coords.x - 1, c->coords.y}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x + 1, c->coords.y}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x, c->coords.y - 1}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x, c->coords.y + 1}));
}
