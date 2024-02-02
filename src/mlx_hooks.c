/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:48:11 by doriani           #+#    #+#             */
/*   Updated: 2024/02/02 21:49:05 by doriani          ###   ########.fr       */
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
    if (ks == 0xFF0D)
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
    return (keypress_other(ks));
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
