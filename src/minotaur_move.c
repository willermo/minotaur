/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:55:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/10 21:48:23 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_cell *
find_nearest_cell(t_cell *start, t_cell *end) {
    t_cell *nearest;

    if (start == end)
        return (start);
    explore_maze(start);
    if (!end->parent)
        return (NULL);
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
    if (!nearest) {
        // TODO
        // minotaur is disconnected from player
        // define triggers and events
        printf("minotaur is disconnected from player\n");
        return;
    }
    game->minotaur->coords = nearest->coords;
    if (get_player_cell() == get_minotaur_cell())
        minotaur_enters_player_cell();
    if (is_trap_active_cell(nearest))
        minotaur_enters_active_trap_cell(nearest);
    render_gamescreen();
}
