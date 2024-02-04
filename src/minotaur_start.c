/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:03:26 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 17:45:27 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
init_graphics(void) {
    game->screen = NULL;
    game->header = NULL;
    game->scene = NULL;
    game->footer = NULL;
    game->refresh = NULL;
    game->player_image = NULL;
    game->minotaur_image = NULL;
    game->footer_text = NULL;
}

static void
init_hooks(void) {
    mlx_hook(game->display.win, KeyPress, KeyPressMask, keypress, game);
    mlx_hook(game->display.win, DestroyNotify, StructureNotifyMask, x_click,
             &game->display);
    mlx_hook(game->display.win, MotionNotify, PointerMotionMask, mouse_hook,
             game);
}

void
start_game(void) {
    init_system(&game->display, SCREEN_W, SCREEN_H, SCREEN_TITLE);
    init_graphics();
    init_hooks();
    game->gamescene = MAIN;
    render_gamescreen();
    pthread_create(&game->game_routine, NULL, game_routine, NULL);
    mlx_loop(game->display.mlx);
    pthread_join(game->game_routine, NULL);
}
