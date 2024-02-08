/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:48:49 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 20:00:49 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
player_sets_trap() {
    t_cell *cell = get_player_cell();
    if (cell->sprite_type == NONE) {
        cell->sprite_type = ACTIVE_TRAP;
        cl_add_node_end(game->collectibles->active_traps,
                        cl_remove_node_by_data(game->collectibles->free_cells,
                                               cell, compare_lair_cells));
        game->player->has_trap--;
        sprintf(game->footer_text, "Trap set at (%d, %d)",
                game->player->coords.x, game->player->coords.y);
        render_gamescreen();
        minotaur_move();
    }
}

void
player_enters_food_cell(t_cell *cell) {
    cell->sprite_type = NONE;
    cl_add_node_end(game->collectibles->free_cells,
                    cl_remove_node_by_data(game->collectibles->food, cell,
                                           compare_lair_cells));
    game->player->health =
        ft_min(game->player->health + FOOD_RESTORE, PLAYER_MAX_HP_POINTS);
}

void
player_enters_trap_cell(t_cell *cell) {
    if (game->player->has_trap)
        return;
    cell->sprite_type = NONE;
    game->player->has_trap++;
    cl_add_node_end(game->collectibles->free_cells,
                    cl_remove_node_by_data(game->collectibles->traps, cell,
                                           compare_lair_cells));
}

void
player_enters_minotaur_cell(t_cell *cell) {
    (void) cell;
    if (game->minotaur->is_trapped)
        return;
    game->player->health -= MINOTAUR_DAMAGE;
}

void
player_enters_exit_cell(t_cell *cell) {
    (void) cell;
    game->gamescene = WIN;
    render_gamescreen();
}

void
minotaur_enters_player_cell() {
    game->gamescene = LOSE;
    render_gamescreen();
}

void
minotaur_enters_active_trap_cell(t_cell *cell) {
    game->minotaur->is_trapped = TRAP_PENALTY;
    cell->sprite_type = NONE;
    cl_add_node_end(game->collectibles->free_cells,
                    cl_remove_node_by_data(game->collectibles->active_traps,
                                           cell, compare_lair_cells));
}
