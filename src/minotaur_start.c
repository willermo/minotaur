/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:03:26 by doriani           #+#    #+#             */
/*   Updated: 2024/02/10 14:13:29 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
init_sprites() {
    game->sprites->food = load_xpm_image(&game->display, XPM_FOOD);
    rescale_image(&game->display, game->sprites->food, SPRITES_SIZE,
                  SPRITES_SIZE, BICUBIC);
    game->sprites->trap = load_xpm_image(&game->display, XPM_TRAP_COLLECTIBLE);
    rescale_image(&game->display, game->sprites->trap, SPRITES_SIZE,
                  SPRITES_SIZE, BICUBIC);
    game->sprites->active_trap =
        load_xpm_image(&game->display, XPM_TRAP_ACTIVE);
    rescale_image(&game->display, game->sprites->active_trap, SPRITES_SIZE,
                  SPRITES_SIZE, BICUBIC);
    game->sprites->player = load_xpm_image(&game->display, XPM_EXPLORER);
    rescale_image(&game->display, game->sprites->player, SPRITES_SIZE,
                  SPRITES_SIZE, BICUBIC);
    game->sprites->minotaur = load_xpm_image(&game->display, XPM_MINOTAUR);
    rescale_image(&game->display, game->sprites->minotaur, SPRITES_SIZE,
                  SPRITES_SIZE, BICUBIC);
}

static void
init_components() {
    game->components->screen = NULL;
    game->components->header = NULL;
    game->components->scene = NULL;
    game->components->footer = NULL;
}

static void
init_graphics(void) {
    init_components();
    init_sprites();
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
    mlx_loop(game->display.mlx);
}
