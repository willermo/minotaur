/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:28:57 by doriani           #+#    #+#             */
/*   Updated: 2024/02/06 12:53:56 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

void
print_maze(char **maze) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

void
print_cell(void *cell) {
    t_cell *c = (t_cell *) cell;

    printf("Cell: (%d, %d)\n", c->coords.x, c->coords.y);
}

void
print_neighbours(void *cell) {
    t_cell *c = (t_cell *) cell;
    t_cl_list *node;

    printf("Cell: (%d, %d)\n", c->coords.x, c->coords.y);
    node = c->neighbours->next;
    while (node->data) {
        t_cell *neighbour = (t_cell *) node->data;
        printf("Neighbour: (%d, %d)\n", neighbour->coords.x,
               neighbour->coords.y);
        node = node->next;
    }
}
