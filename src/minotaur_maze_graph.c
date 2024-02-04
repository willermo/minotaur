/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:53:56 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 19:28:27 by doriani          ###   ########.fr       */
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

static void
add_neighbours(void *cell) {
    t_cell *c = (t_cell *) cell;
    add_neighbour(c, get_neighbour((t_point){c->coords.x - 1, c->coords.y}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x + 1, c->coords.y}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x, c->coords.y - 1}));
    add_neighbour(c, get_neighbour((t_point){c->coords.x, c->coords.y + 1}));
    print_neighbours(c);
}

static void
insert_cell(t_point coords) {
    t_cell *cell;

    cell = (t_cell *) malloc(sizeof(t_cell));
    cell->coords.x = coords.x;
    cell->coords.y = coords.y;
    cell->neighbours = cl_init_list();
    cell->color = WHITE;
    cell->parent = NULL;
    cell->distance = -1;
    cl_insert_begin(game->lair, cell);
}

void
reset_cell_metadata(void *cell) {
    t_cell *c = (t_cell *) cell;

    c->color = WHITE;
    c->parent = NULL;
    c->distance = -1;
}

void
build_lair() {
    // creating adjacency list
    game->lair = cl_init_list();
    // populating adjacency list
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (strchr("0PE", game->map->grid[i][j]))
                insert_cell((t_point){j, i});
    if (DEBUG)
        cl_foreach(game->lair, print_cell);
    //  adding neighbours to each cell
    cl_foreach(game->lair, add_neighbours);
}
