/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:16:37 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 13:56:49 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
destroy_components(void) {
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

static void
destroy_sprites(void) {
    destroy_image(&game->display, game->sprites->food);
    destroy_image(&game->display, game->sprites->trap);
    destroy_image(&game->display, game->sprites->active_trap);
    destroy_image(&game->display, game->sprites->player);
    destroy_image(&game->display, game->sprites->minotaur);
}

static void
destroy_graphics(void) {
    destroy_components();
    destroy_sprites();
}

void
end_game(void) {
    destroy_graphics();
    destroy_lair();
    shutdown_system(&game->display);
}
