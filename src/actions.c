/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slp_actions_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:33:22 by doriani           #+#    #+#             */
/*   Updated: 2024/01/23 13:37:04 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

// static int
// player_eats_food(int col, int row) {
//     t_point *cell;

//     if ((cell = is_food_cell(col, row))) {
//         cl_add_node_end(game->map->free_cells,
//                         cl_remove_node_by_data(game->map->collectibles, cell,
//                                                compare_map_cells));
//         return (1);
//     }
//     return 0;
// }

// static void
// player_enters_food_cell(t_cell *cell) {
//     cl_add_node_end(game->collectibles->free_cells,
//                     cl_remove_node_by_data(game->collectibles->food, cell,
//                                            compare_lair_cells));
//     cell->sprite_type = NONE;
// }

// static int
// player_gets_trap(int col, int row) {
//     t_point *cell;

//     if ((cell = is_trap_cell(col, row))) {
//         cl_add_node_end(
//             game->map->free_cells,
//             cl_remove_node_by_data(game->map->traps, cell,
//             compare_map_cells));
//         return (1);
//     }
//     return 0;
// }

static void
player_enters_minotaur_cell(t_cell *to) {
    // todo
    if (game->minotaur->is_trapped)
        return;
    game->gamescene = LOSE;
    render_gamescreen();
}

static void
update_position(t_cell *from, t_cell *to) {
    char str[100];

    game->player->coords = to->coords;
    game->player->health -= MOVEMENT_COST;
    if (is_exit_cell(to)) {
        game->gamescene = WIN;
        render_gamescreen();
        return;
    }
    if (is_minotaur_cell(to && !game->minotaur->is_trapped)) {
        game->gamescene = LOSE;
        render_gamescreen();
        return;
    }
    if (game->player->health <= 0) {
        game->gamescene = LOSE;
        render_gamescreen();
        return;
    }
    if (is_food_cell(to)) {
        player_enters_food_cell(to);
    }
    if (is_trap_cell(to)) {
        player_enters_trap_cell(to);
    }
    sprintf(str, "Player moved from (%d, %d) to (%d, %d)", from->coords.y,
            from->coords.x, to->coords.y, to->coords.x);
    if (game->footer_text)
        free(game->footer_text);
    game->footer_text = strdup(str);
    render_gamescreen();
    minotaur_move();
}

void
move(t_movement direction) {
    t_cell *from;
    t_cell *to;

    from = get_cell_from_coords(game->player->coords);
    switch (direction) {
    case UP:
        to = get_cell_from_coords(
            (t_point){game->player->coords.x, game->player->coords.y - 1});
        break;
    case DOWN:
        to = get_cell_from_coords(
            (t_point){game->player->coords.x, game->player->coords.y + 1});
        break;
    case LEFT:
        to = get_cell_from_coords(
            (t_point){game->player->coords.x - 1, game->player->coords.y});
        break;
    case RIGHT:
        to = get_cell_from_coords(
            (t_point){game->player->coords.x + 1, game->player->coords.y});
        break;
    }
    if (!to)
        return;
    // todo: catch and bind events
    update_position(from, to);
}
