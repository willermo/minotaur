/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_mino.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:55:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/06 14:02:52 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_cell *
find_nearest_cell(t_cell *start, t_cell *end) {
    t_cell *nearest;

    explore_maze(start);
    nearest = end;
    while (nearest->parent != start)
        nearest = nearest->parent;
    return (nearest);
}

static int
minotaur_walked_on_active_trap(int col, int row) {
    t_point *cell;

    cell = is_trap_active_cell(col, row);
    if (cell != NULL) {
        cl_add_node_end(game->map->free_cells,
                        cl_remove_node_by_data(game->map->active_traps, cell,
                                               compare_map_cells));
        free(cell);
        return (1);
    }
    return 0;
}

void
minotaur_move() {
    t_cell *player;
    t_cell *minotaur;
    t_cell *nearest;

    if (game->minotaur->is_trapped) {
        game->minotaur->is_trapped--;
        return;
    }

    // set positions
    player = get_cell_from_coords((t_point){game->player->x, game->player->y});
    minotaur =
        get_cell_from_coords((t_point){game->minotaur->x, game->minotaur->y});
    // finds nearest cell to player
    nearest = find_nearest_cell(minotaur, player);
    // moves minotaur to nearest cell
    game->minotaur->x = nearest->coords.x;
    game->minotaur->y = nearest->coords.y;
    if (nearest == player) {
        game->gamescene = LOSE;
        render_gamescreen();
        return;
    }
    if (minotaur_walked_on_active_trap(game->minotaur->x, game->minotaur->y))
        game->minotaur->is_trapped = TRAP_PENALTY;
    render_gamescreen();
}
