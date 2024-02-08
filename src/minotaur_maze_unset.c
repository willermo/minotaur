/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:30:07 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 11:44:00 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
clear_neighbours(void *cell) {
    cl_dismiss_list(((t_cell *) cell)->neighbours);
}

static void
clear_cell(void *cell) {
    free(((t_cell *) cell)->neighbours);
}

void
destroy_lair() {
    cl_foreach(game->lair, clear_neighbours);
    cl_foreach(game->lair, clear_cell);
    cl_destroy_list(&game->lair);
}
