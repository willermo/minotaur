/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:35:26 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 18:08:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void *
game_routine() {
    enum turn { PLAYER, MINOTAUR };
    t_cell *player;
    t_cell *minotaur;
    t_cell *nearest;

    enum turn current_turn = PLAYER;
    game->player->has_played = 0;
    game->is_running = 1;
    while (game->is_running) {
        while (current_turn == PLAYER) {
            // player routine
            if (game->player->has_played) {
                current_turn = MINOTAUR;
                game->player->has_played = 0;
            }
        };
        // minotaur routine
        while (current_turn == MINOTAUR) {
            if (game->minotaur->is_trapped) {
                game->minotaur->is_trapped--;
                current_turn = PLAYER;
                break;
            }
            // set positions
            player = get_cell_from_coords(
                (t_point){game->player->x, game->player->y});
            minotaur = get_cell_from_coords(
                (t_point){game->minotaur->x, game->minotaur->y});
            // finds nearest cell to player
            nearest = find_nearest_cell(minotaur, player);
            // moves minotaur to nearest cell
            game->minotaur->x = nearest->coords.x;
            game->minotaur->y = nearest->coords.y;
            render_gamescreen();
            current_turn = PLAYER;
        }
    }
    return (NULL);
}
