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
trigger_suitable_events(t_cell *landing_cell) {
    if (is_minotaur_cell(landing_cell))
        player_enters_minotaur_cell(landing_cell);
    if (is_food_cell(landing_cell))
        player_enters_food_cell(landing_cell);
    if (is_trap_cell(landing_cell))
        player_enters_trap_cell(landing_cell);
    if (is_exit_cell(landing_cell))
        player_enters_exit_cell(landing_cell);
    if (is_player_dead())
        player_dies();
}

static void
update_position(t_cell *from, t_cell *to) {
    game->player->coords = to->coords;
    game->player->health -= MOVEMENT_COST;
    trigger_suitable_events(to);
    sprintf(game->footer_text, "Player moved from (%d, %d) to (%d, %d)",
            from->coords.y, from->coords.x, to->coords.y, to->coords.x);
    render_gamescreen();
    if (game->gamescene == GAME && !is_player_dead())
        minotaur_move();
}

void
set_trap() {
    if (!game->player->has_trap)
        return;
    player_sets_trap();
    sprintf(game->footer_text, "Trap set at (%d, %d)", game->player->coords.x,
            game->player->coords.y);
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
