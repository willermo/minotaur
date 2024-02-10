/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:03:29 by doriani           #+#    #+#             */
/*   Updated: 2024/02/10 09:48:22 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_cell *
get_cell_from_coords(t_point coord) {
    t_cell cell;
    t_cl_list *node;

    cell.coords = coord;
    if ((node = cl_get_node_by_data(game->lair, &cell, compare_lair_cells)))
        return ((t_cell *) node->data);
    return (NULL);
}

t_cell *
get_player_cell() {
    return (get_cell_from_coords(game->player->coords));
}

t_cell *
get_minotaur_cell() {
    return (get_cell_from_coords(game->minotaur->coords));
}

t_cell *
get_enter_cell() {
    return (get_cell_from_coords(game->map->start_pos));
}

t_cell *
get_exit_cell() {
    return (get_cell_from_coords(game->map->end_pos));
}

int
is_enter_cell(t_cell *cell) {
    return (cell == get_enter_cell());
}

int
is_exit_cell(t_cell *cell) {
    return (cell == get_exit_cell());
}

int
is_food_cell(t_cell *cell) {
    t_cl_list *food = game->collectibles->food->next;

    while (food->data != NULL) {
        if (cell == (t_cell *) food->data)
            return (1);
        food = food->next;
    }
    return (0);
}

int
is_trap_cell(t_cell *cell) {
    t_cl_list *trap = game->collectibles->traps->next;

    while (trap->data != NULL) {
        if (cell == (t_cell *) trap->data)
            return (1);
        trap = trap->next;
    }
    return (0);
}

int
is_trap_active_cell(t_cell *cell) {
    t_cl_list *trap = game->collectibles->active_traps->next;

    while (trap->data != NULL) {
        if (cell == (t_cell *) trap->data)
            return (1);
        trap = trap->next;
    }
    return (0);
}

int
is_free_cell(t_cell *cell) {
    t_cl_list *free = game->collectibles->free_cells->next;

    while (free->data != NULL) {
        if (cell == (t_cell *) free->data)
            return (1);
        free = free->next;
    }
    return (0);
}

int
is_player_cell(t_cell *cell) {
    return (cell == get_player_cell());
}

int
is_minotaur_cell(t_cell *cell) {
    return (cell == get_minotaur_cell());
}

int
is_walkable_cell(t_point coords) {
    return (cl_get_node_position(game->lair, &coords, compare_lair_cells));
}

int
is_valid_coords(t_point coords) {
    return (coords.x >= 0 && coords.x < COLS && coords.y >= 0 &&
            coords.y < ROWS);
}

int
is_player_dead() {
    return (game->player->health <= 0);
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
compare_coords(void *coord1, void *coord2) {
    t_point *c1 = (t_point *) coord1;
    t_point *c2 = (t_point *) coord2;

    if (c1->x == c2->x && c1->y == c2->y)
        return (0);
    return (1);
}
