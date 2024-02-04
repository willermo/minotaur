/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:48:11 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 10:39:21 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static int
keypress_main(int ks) {
    if (ks == 0xFF1B) {
        mlx_loop_end(game->display.mlx);
        return (0);
    }
    if (ks == 0x31)
        game->gamescene = GAME;
    if (ks == 0x32)
        game->gamescene = INSTRUCTIONS;
    render_gamescreen();
    return (0);
}

static int
keypress_other(int ks) {
    if (ks == 0x77 || ks == 0x57)
        move(UP);
    if (ks == 0x61 || ks == 0x41)
        move(LEFT);
    if (ks == 0x73 || ks == 0x53)
        move(DOWN);
    if (ks == 0x64 || ks == 0x44)
        move(RIGHT);
    if (ks == 0xFF0D && game->player->has_trap)
        set_trap();
    return (0);
}

int
keypress(int ks) {
    if (game->gamescene == MAIN)
        return (keypress_main(ks));
    if (ks == 0xFF1B) {
        game->gamescene = MAIN;
        render_gamescreen();
        return (0);
    }
    if (game->gamescene == GAME)
        return (keypress_other(ks));
    return (0);
}

int
x_click() {
    mlx_loop_end(game->display.mlx);
    return (0);
}

int
mouse_hook(int x, int y) {
    (void) x;
    (void) y;
    return (0);
}
