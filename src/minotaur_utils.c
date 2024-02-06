/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:05:33 by doriani           #+#    #+#             */
/*   Updated: 2024/02/06 12:53:58 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
destroy_collectibles() {
    t_cl_list *node;
    t_image *collectible_image;

    node = game->collectibles_images->next;
    while (node->data) {
        collectible_image = (t_image *) node->data;
        destroy_image(&game->display, collectible_image);
        node = node->next;
    }
    cl_delete_list(game->collectibles_images);
}

void
destroy_traps() {
    t_cl_list *node;
    t_image *trap_image;

    node = game->traps_images->next;
    while (node->data) {
        trap_image = (t_image *) node->data;
        destroy_image(&game->display, trap_image);
        node = node->next;
    }
    cl_delete_list(game->traps_images);
}

void
destroy_active_traps() {
    t_cl_list *node;
    t_image *trap_image;

    node = game->active_traps_images->next;
    while (node->data) {
        trap_image = (t_image *) node->data;
        destroy_image(&game->display, trap_image);
        node = node->next;
    }
    cl_delete_list(game->active_traps_images);
}
