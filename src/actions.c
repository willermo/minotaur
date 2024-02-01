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
update_position(int old_col, int old_row, int new_col, int new_row) {
    game->map->grid[old_row][old_col] = '0';
    game->map->grid[new_row][new_col] = 'P';
    game->map->player->x = new_col;
    game->map->player->y = new_row;
    printf("Player moved from (%d, %d) to (%d, %d)\n", old_col, old_row,
           new_col, new_row);
    refresh(SCENE, (t_point){0, 200});
}

void
move(t_movement direction) {
    char **grid = game->map->grid;
    int col = game->map->player->x;
    int row = game->map->player->y;

    switch (direction) {
    case UP:
        if (row > 0 && strchr("0E", grid[row - 1][col]))
            update_position(col, row, col, row - 1);
        break;
    case DOWN:
        if (row < ROWS - 1 && strchr("0E", grid[row + 1][col]))
            update_position(col, row, col, row + 1);
        break;
    case LEFT:
        if (col > 0 && strchr("0E", grid[row][col - 1]))
            update_position(col, row, col - 1, row);
        break;
    case RIGHT:
        if (col < COLS - 1 && strchr("0E", grid[row][col + 1]))
            update_position(col, row, col + 1, row);
        break;
    }
}

void
set_trap() {
    // refresh(slp, SCENE, (t_point){0, C3D_HEIGHT / 4});
}
