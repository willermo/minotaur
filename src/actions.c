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

static void
update_position(t_cell *from, t_cell *to) {
    game->player->coords = to->coords;
    game->player->health -= MOVEMENT_COST;
    if (is_exit_cell(to)) {
        game->gamescene = WIN;
        render_gamescreen();
        return;
    }
    if (is_minotaur_cell(to)) {
        player_enters_minotaur_cell(to);
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
    sprintf(game->footer_text, "Player moved from (%d, %d) to (%d, %d)",
            from->coords.y, from->coords.x, to->coords.y, to->coords.x);
    render_gamescreen();
    minotaur_move();
}

void
set_trap() {
    if (game->player->has_trap)
        player_sets_trap();
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
