/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_mino.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:55:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 00:09:06 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_point *
get_nearest_cell_to_player() {
    char **grid = clone_grid(game->map->grid);
    // todo: implement this function
    for (int i = 0; i < ROWS; i++)
        free(grid[i]);
    free(grid);
    return NULL;
}
