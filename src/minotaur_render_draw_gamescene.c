/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_render_draw_gamescene.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:16:11 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 11:21:52 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
draw_board(t_image *img) {
    int i;
    int j;

    i = 0;
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (game->map->grid[i][j] == '1')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            WALL_CELL_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == 'P')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            START_POSITION_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == 'E')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            END_POSITION_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == '0')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            FREE_CELL_COLOR, CELL_SIZE);
            j++;
        }
        i++;
    }
}

void
draw_gamescene(t_image *img) {
    draw_board(img);
    draw_collectibles(img);
    if (game->minotaur->is_trapped) {
        draw_minotaur(img);
        draw_player(img);
    } else {
        draw_player(img);
        draw_minotaur(img);
    }
}
