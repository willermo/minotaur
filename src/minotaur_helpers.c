/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:03:29 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 19:14:05 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_cell *
get_cell_from_coords(t_point coord) {
    t_cell cell;

    cell.coords.x = coord.x;
    cell.coords.y = coord.y;
    return (cl_get_node_by_data(game->lair, &cell, compare_lair_cells)->data);
}

int
is_walkable_cell(t_point coords) {
    return (is_valid_coords(coords) &&
            strchr("0PE", game->map->grid[coords.y][coords.x]) != NULL);
}

int
is_valid_coords(t_point coords) {
    return (coords.x >= 0 && coords.x < COLS && coords.y >= 0 &&
            coords.y < ROWS);
}

char **
clone_grid(char **grid) {
    char **clone;

    clone = (char **) malloc(ROWS * sizeof(char *));
    for (int i = 0; i < ROWS; i++) {
        clone[i] = (char *) malloc(COLS * sizeof(char));
        for (int j = 0; j < COLS; j++)
            clone[i][j] = grid[i][j];
    }
    return (clone);
}

int
compare_lair_cells(void *cell1, void *cell2) {
    t_cell *c1 = (t_cell *) cell1;
    t_cell *c2 = (t_cell *) cell2;

    if (c1->coords.x == c2->coords.x && c1->coords.y == c2->coords.y)
        return (0);
    return (1);
}

int
compare_map_cells(void *cell1, void *cell2) {
    t_point *c1 = (t_point *) cell1;
    t_point *c2 = (t_point *) cell2;

    if (c1->x == c2->x && c1->y == c2->y)
        return (0);
    return (1);
}

int
is_starting_cell(int col, int row) {
    return (col == game->map->start_pos[0] && row == game->map->start_pos[1]);
}

int
is_exit_cell(int col, int row) {
    return (col == game->map->end_pos[0] && row == game->map->end_pos[1]);
}

t_point *
is_food_cell(int col, int row) {
    t_point *cell;
    t_cl_list *collectible;

    collectible = game->map->collectibles->next;
    while (collectible->data != NULL) {
        cell = (t_point *) collectible->data;
        if (cell->x == col && cell->y == row)
            return (cell);
        collectible = collectible->next;
    }
    return (NULL);
}

t_point *
is_trap_cell(int col, int row) {
    t_point *cell;
    t_cl_list *trap;

    trap = game->map->traps->next;
    while (trap->data != NULL) {
        cell = (t_point *) trap->data;
        if (cell->x == col && cell->y == row)
            return (cell);
        trap = trap->next;
    }
    return (NULL);
}

t_point *
is_trap_active_cell(int col, int row) {
    t_point *cell;
    t_cl_list *trap;

    trap = game->map->active_traps->next;
    while (trap->data != NULL) {
        cell = (t_point *) trap->data;
        if (cell->x == col && cell->y == row)
            return (cell);
        trap = trap->next;
    }
    return (NULL);
}
