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

void
move(t_movement direction) {

    switch (direction) {
    case UP:
        if (game->map->grid[game->map->player->y - 1][game->map->player->x] ==
            '0')
            game->map->player->y--;
        break;
    case DOWN:
        if (game->map->grid[game->map->player->y + 1][game->map->player->x] ==
            '0')
            game->map->player->y++;
        break;
    case LEFT:
        if (game->map->grid[game->map->player->y][game->map->player->x - 1] ==
            '0')
            game->map->player->x--;
        break;
    case RIGHT:
        if (game->map->grid[game->map->player->y][game->map->player->x + 1] ==
            '0')
            game->map->player->x++;
        break;
    }
    // refresh(slp, SCENE, (t_point){0, C3D_HEIGHT / 4});
}

void
set_trap() {
    // refresh(slp, SCENE, (t_point){0, C3D_HEIGHT / 4});
}
