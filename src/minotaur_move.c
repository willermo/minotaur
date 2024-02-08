/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:55:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 12:19:44 by doriani          ###   ########.fr       */
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

void
minotaur_move() {
    t_cell *nearest;

    if (game->minotaur->is_trapped) {
        game->minotaur->is_trapped--;
        return;
    }
    nearest = find_nearest_cell(get_minotaur_cell(), get_player_cell());
    game->minotaur->coords = nearest->coords;
    if (get_player_cell() == get_minotaur_cell())
        return (minotaur_enters_player_cell());
    if (is_trap_active_cell(nearest))
        minotaur_enters_active_trap_cell(nearest);
    render_gamescreen();
}
