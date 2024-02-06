/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:53:56 by doriani           #+#    #+#             */
/*   Updated: 2024/02/06 21:23:32 by doriani          ###   ########.fr       */
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
    cell->sprite = NONE;
    cell->sprite_image = NULL;
    cl_insert_begin(game->lair, cell);
}

static void
setup_food() {
    int free_cells_count;
    t_cl_list *node;
    t_cell *cell;

    free_cells_count = cl_size(game->map->free_cells);
    for (int i = 0; i < COLLECTIBLES; i++) {
        node = cl_remove_node_by_position(game->map->free_cells,
                                          rand() % free_cells_count--);
        ((t_cell *) node->data)->sprite = FOOD;
        ((t_cell *) node->data)->sprite_image =
            load_xpm_image(&game->display, XPM_FOOD);
        cl_add_node_end(game->map->collectibles, node);
        add_image(&game->display, ((t_cell *) node->data)->sprite_image,
                  (t_point){((t_cell *) node->data)->coords.x * CELL_SIZE + 2,
                            ((t_cell *) node->data)->coords.y * CELL_SIZE +
                                HEADER_H + 2});
    }
}

static void
setup_traps() {
    int free_cells_count;
    t_cl_list *node;
    t_cell *cell;

    free_cells_count = cl_size(game->map->free_cells);
    for (int i = 0; i < TRAPS; i++) {
        node = cl_remove_node_by_position(game->map->free_cells,
                                          rand() % free_cells_count--);
        ((t_cell *) node->data)->sprite = TRAP;
        ((t_cell *) node->data)->sprite_image =
            load_xpm_image(&game->display, XPM_TRAP_COLLECTIBLE);
        cl_add_node_end(game->map->traps, node);
        add_image(&game->display, ((t_cell *) node->data)->sprite_image,
                  (t_point){((t_cell *) node->data)->coords.x * CELL_SIZE + 2,
                            ((t_cell *) node->data)->coords.y * CELL_SIZE +
                                HEADER_H + 2});
    }
}

static void
setup_player() {
    t_cell *cell;

    cell = (t_cell *) get_cell_from_coords(
        (t_point){game->map->start_pos[0], game->map->start_pos[1]});
    cell->sprite = PLAYER;
    cell->sprite_image = load_xpm_image(&game->display, XPM_EXPLORER);
    add_image(&game->display, cell->sprite_image,
              (t_point){cell->coords.x * CELL_SIZE + 2,
                        cell->coords.y * CELL_SIZE + HEADER_H + 2});
}

static void
setup_minotaur() {
    t_cell *cell;

    cell = (t_cell *) get_cell_from_coords(
        (t_point){game->map->end_pos[0], game->map->end_pos[1]});
    cell->sprite = MINO;
    cell->sprite_image = load_xpm_image(&game->display, XPM_MINOTAUR);
    add_image(&game->display, cell->sprite_image,
              (t_point){cell->coords.x * CELL_SIZE + 2,
                        cell->coords.y * CELL_SIZE + HEADER_H + 2});
}

static void
init_lair(void) {
    game->lair = cl_init_list();

    // creating adjacency list
    game->lair = cl_init_list();
    // populating adjacency list
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (strchr("0PE", game->map->grid[i][j]))
                insert_cell((t_point){j, i});
}

void
reset_cell_metadata(void *cell) {
    t_cell *c = (t_cell *) cell;

    c->color = WHITE;
    c->parent = NULL;
    c->distance = -1;
}

static void
update_free_cells() {
    t_point *cell;
    t_cl_list *node;

    cl_delete_list(game->map->free_cells);
    node = game->lair->next;
    while (node->data) {
        if (((t_cell *) node->data)->sprite == NONE)
            cl_insert_end(game->map->free_cells, node->data);
        node = node->next;
    }
}

void
build_lair() {
    init_lair();
    //  adding neighbours to each cell
    cl_foreach(game->lair, add_neighbours);
    update_free_cells();
    setup_food();
    setup_traps();
    setup_player();
    setup_minotaur();
}

static void
clear_neighbours(void *cell) {
    t_cell *c = (t_cell *) cell;

    // cl_foreach(c->neighbours, free);
    while (cl_size(c->neighbours)) {
        free(cl_remove_begin(c->neighbours));
    }
}

static void
clear_cell(void *cell) {
    free(((t_cell *) cell)->neighbours);
}

void
destroy_lair() {
    cl_foreach(game->lair, clear_neighbours);
    cl_foreach(game->lair, clear_cell);
    cl_destroy_list(&game->lair);
}
