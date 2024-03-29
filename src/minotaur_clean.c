/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:35:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 20:09:51 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_items(void) {
    cl_dismiss_list(game->collectibles->food);
    free(game->collectibles->food);
    cl_dismiss_list(game->collectibles->traps);
    free(game->collectibles->traps);
    cl_dismiss_list(game->collectibles->active_traps);
    free(game->collectibles->active_traps);
    cl_dismiss_list(game->collectibles->free_cells);
    free(game->collectibles->free_cells);
}

static void
free_data_structures_memory(void) {
    // cl_destroy_list(&game->lair);
    free(game->components);
    free(game->collectibles);
    free(game->sprites);
    for (int i = 0; i < ROWS; i++)
        free(game->map->grid[i]);
    free(game->map->grid);
    free(game->minotaur);
    free(game->player);
    free(game->map);
    free(game);
}

void
clean_game(void) {
    destroy_items();
    free_data_structures_memory();
}
