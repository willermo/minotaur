/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_mino.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:55:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 17:15:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_cell *
get_nearest_to_player_cell() {
    t_cell *start;
    t_cell *end;
    t_point coord;

    coord.x = game->minotaur->x;
    coord.y = game->minotaur->y;
    start = get_cell_from_coords(coord);
    coord.x = game->player->x;
    coord.y = game->player->y;
    end = get_cell_from_coords(coord);
    return (find_nearest_cell(start, end));
}

t_point
get_nearest_to_player_cell_coordinate() {
    return (get_nearest_to_player_cell()->coords);
}
