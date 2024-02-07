/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:16:37 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 22:40:50 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_graphics(void) {
    destroy_image(&game->display, game->components->header);
    free(game->components->header);
    game->components->header = NULL;
    destroy_image(&game->display, game->components->scene);
    free(game->components->scene);
    game->components->scene = NULL;
    destroy_image(&game->display, game->components->footer);
    free(game->components->footer);
    game->components->footer = NULL;
}

void
end_game(void) {
    destroy_graphics();
    destroy_lair();
    mlx_clear_window(game->display.mlx, game->display.win);
    mlx_destroy_window(game->display.mlx, game->display.win);
    mlx_destroy_display(game->display.mlx);
    free(game->display.mlx);
}
