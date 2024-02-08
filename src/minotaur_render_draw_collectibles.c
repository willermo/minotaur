/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_render_draw_collectibles.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:03:28 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 16:33:57 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static t_point
offset_coords(t_point coords) {
    t_point offset;

    offset.x = coords.x * CELL_SIZE + (CELL_SIZE - SPRITES_SIZE) / 2;
    offset.y = coords.y * CELL_SIZE + HEADER_H + (CELL_SIZE - SPRITES_SIZE) / 2;
    return (offset);
}

void
draw_food(t_image *board) {
    t_cl_list *node;
    t_point start;

    node = game->collectibles->food->next;
    while (node->data) {
        start = offset_coords(((t_cell *) node->data)->coords);
        apply_sprite_to_image(board, game->sprites->food, start);
        node = node->next;
    }
}

void
draw_traps(t_image *board) {
    t_cl_list *node;
    t_point start;

    node = game->collectibles->traps->next;
    while (node->data) {
        start = offset_coords(((t_cell *) node->data)->coords);
        apply_sprite_to_image(board, game->sprites->trap, start);
        node = node->next;
    }
}

void
draw_active_traps(t_image *board) {
    t_cl_list *node;
    t_point start;

    node = game->collectibles->active_traps->next;
    while (node->data) {
        start = offset_coords(((t_cell *) node->data)->coords);
        apply_sprite_to_image(board, game->sprites->active_trap, start);
        node = node->next;
    }
}

void
draw_collectibles(t_image *board) {
    draw_food(board);
    draw_traps(board);
    draw_active_traps(board);
}

void
draw_player(t_image *board) {
    t_point start;

    start = offset_coords(game->player->coords);
    apply_sprite_to_image(board, game->sprites->player, start);
}

void
draw_minotaur(t_image *board) {
    t_point start;

    start = offset_coords(game->minotaur->coords);
    apply_sprite_to_image(board, game->sprites->minotaur, start);
}
