/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:35:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 22:46:41 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_sprites(void) {
    cl_destroy_list(&game->collectibles_images);
    cl_destroy_list(&game->traps_images);
    cl_destroy_list(&game->active_traps_images);
    if (game->footer_text) {
        free(game->footer_text);
        game->footer_text = NULL;
    }
}

static void
destroy_items(void) {
    cl_destroy_list(&game->map->collectibles);
    cl_destroy_list(&game->map->traps);
    cl_destroy_list(&game->map->active_traps);
    cl_destroy_list(&game->map->free_cells);
}

static void
free_data_structures_memory(void) {
    for (int i = 0; i < ROWS; i++)
        free(game->map->grid[i]);
    free(game->map->grid);
    free(game->map->minotaur);
    free(game->map->player);
    free(game->map);
    free(game);
}

void
clean_game(void) {
    destroy_sprites();
    destroy_items();
    free_data_structures_memory();
}
