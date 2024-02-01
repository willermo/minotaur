/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_common.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:03:26 by doriani           #+#    #+#             */
/*   Updated: 2024/02/01 20:48:35 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
init_graphics(void) {
    init_system(&game->display, SCREEN_W, SCREEN_H, SCREEN_TITLE);
    game->screen = create_image(&game->display, SCREEN_W, SCREEN_H);
    game->header = create_image(&game->display, HEADER_W, HEADER_H);
    game->scene = create_image(&game->display, SCENE_W, SCENE_H);
    game->footer = create_image(&game->display, FOOTER_W, FOOTER_H);
    game->refresh = NULL;
    game->gamescene = MAIN;
}

void
init_hooks(void) {
    mlx_hook(game->display.win, KeyPress, KeyPressMask, keypress, game);
    mlx_hook(game->display.win, DestroyNotify, StructureNotifyMask, x_click,
             &game->display);
    mlx_hook(game->display.win, MotionNotify, PointerMotionMask, mouse_hook,
             game);
}

void
destroy_mlx(void) {
    destroy_image(&game->display, game->screen);
    free(game->screen);
    destroy_image(&game->display, game->header);
    free(game->header);
    destroy_image(&game->display, game->scene);
    free(game->scene);
    destroy_image(&game->display, game->footer);
    free(game->footer);
    mlx_clear_window(game->display.mlx, game->display.win);
    mlx_destroy_window(game->display.mlx, game->display.win);
    mlx_destroy_display(game->display.mlx);
    free(game->display.mlx);
}
