/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:35:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 22:32:48 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_sprites(void) {
    destroy_image(&game->display, game->sprites->food);
    destroy_image(&game->display, game->sprites->trap);
    destroy_image(&game->display, game->sprites->active_trap);
    destroy_image(&game->display, game->sprites->player);
    destroy_image(&game->display, game->sprites->minotaur);
    if (game->footer_text) {
        free(game->footer_text);
        game->footer_text = NULL;
    }
}

static void
destroy_items(void) {
    cl_destroy_list(&game->collectibles->food);
    cl_destroy_list(&game->collectibles->traps);
    cl_destroy_list(&game->collectibles->active_traps);
    cl_destroy_list(&game->collectibles->free_cells);
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
    destroy_sprites();
    destroy_items();
    free_data_structures_memory();
}
