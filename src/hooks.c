/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:48:11 by doriani           #+#    #+#             */
/*   Updated: 2024/02/10 09:50:51 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static int
keypress_main(int ks) {
    if (ks == 0xFF1B)   // ESC
        return (mlx_loop_end(game->display.mlx), 0);
    if (ks == 0x31)   // 1
        game->gamescene = GAME;
    if (ks == 0x32)   // 2
        game->gamescene = INSTRUCTIONS;
    render_gamescreen();
    return (0);
}

static int
keypress_instruction(int ks) {
    if (ks == 0xFF1B) {   // ESC
        game->gamescene = MAIN;
        render_gamescreen();
        return (0);
    }
    return (0);
}

static int
keypress_gamescene(int ks) {
    if (ks == 0xFF1B) {   // ESC
        game->gamescene = MAIN;
        render_gamescreen();
        return (0);
    }
    if (ks == 0x77 || ks == 0x57)   // W
        move(UP);
    if (ks == 0x61 || ks == 0x41)   // A
        move(LEFT);
    if (ks == 0x73 || ks == 0x53)   // S
        move(DOWN);
    if (ks == 0x64 || ks == 0x44)   // D
        move(RIGHT);
    if (ks == 0xFF0D)   // ENTER
        set_trap();
    return (0);
}

static int
keypress_endgame(int ks) {
    if (ks == 0xFF1B)   // ESC
        return (mlx_loop_end(game->display.mlx), 0);
    return (0);
}

int
keypress(int ks) {
    if (game->gamescene == MAIN)
        return (keypress_main(ks));
    if (game->gamescene == INSTRUCTIONS)
        return (keypress_instruction(ks));
    if (game->gamescene == GAME)
        return (keypress_gamescene(ks));
    if (game->gamescene == WIN || game->gamescene == LOSE)
        return (keypress_endgame(ks));
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
