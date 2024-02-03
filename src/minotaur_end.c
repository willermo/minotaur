/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:16:37 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 22:44:17 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_graphics(void) {
    destroy_image(&game->display, game->header);
    free(game->header);
    game->header = NULL;
    destroy_image(&game->display, game->scene);
    free(game->scene);
    game->scene = NULL;
    destroy_image(&game->display, game->footer);
    free(game->footer);
    game->footer = NULL;
    destroy_image(&game->display, game->player_image);
    free(game->player_image);
    game->player_image = NULL;
    destroy_image(&game->display, game->minotaur_image);
    free(game->minotaur_image);
    game->minotaur_image = NULL;
    destroy_collectibles();
    destroy_traps();
    destroy_active_traps();
}

void
end_game(void) {
    destroy_graphics();
    mlx_clear_window(game->display.mlx, game->display.win);
    mlx_destroy_window(game->display.mlx, game->display.win);
    mlx_destroy_display(game->display.mlx);
    free(game->display.mlx);
}
