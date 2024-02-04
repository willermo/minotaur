/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_algorithms.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 22:57:11 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

// Recursive backtracking algorithm to generate the maze
void
generate_maze(char **maze, int row, int col) {
    // Stop the recursion when it reaches the 'E' cell
    if (maze[row][col] == 'E') {
        return;
    }
    // Mark the current cell as a free path
    if (!strchr("PE", maze[row][col]))
        maze[row][col] = '0';

    // Define possible directions (up, down, left, right)
    int directions[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
    int order[4] = {0, 1, 2, 3};

    for (int i = 0; i < 4; i++) {
        int rand_index = rand() % 4;
        int temp = order[i];
        order[i] = order[rand_index];
        order[rand_index] = temp;
    }

    // Iterate over all directions
    for (int i = 0; i < 4; i++) {
        int next_row = row + directions[order[i]][0];
        int next_col = col + directions[order[i]][1];
        // Check if the next cell is within the bounds of the maze
        if (next_row > 0 && next_row < ROWS - 1 && next_col > 0 &&
            next_col < COLS - 1) {
            // Check if the next cell is a wall
            if (maze[next_row][next_col] == '1') {
                // Carve a path in the cell between the current cell and the
                // next cell
                maze[row + directions[order[i]][0] / 2]
                    [col + directions[order[i]][1] / 2] = '0';
                // Recursively call the function on the next cell
                generate_maze(maze, next_row, next_col);
            }
        }
    }
}

static void
visit_neighbours(t_cell *source, t_cl_list *queue) {
    t_cl_list *neighbour;
    t_cell *cell;

    neighbour = source->neighbours->next;
    while (neighbour->data && (cell = (t_cell *) neighbour->data)) {
        if (cell->color == WHITE) {
            cell->color = GRAY;
            cell->parent = source;
            cell->distance = cell->parent->distance + 1;
            cl_insert_begin(queue, cell);
        }
        neighbour = neighbour->next;
    }
    source->color = BLACK;
}

// BFS algorithm to find the shortest path from the start to the end of the maze
void
explore_maze(t_cell *start) {
    t_cl_list *queue;
    t_cell *cell;

    // resets metadata for each cell
    cl_foreach(game->lair, reset_cell_metadata);
    start->color = GRAY;
    start->distance = 0;
    start->parent = NULL;
    queue = cl_init_list();
    cl_insert_begin(queue, start);
    while (cl_size(queue) > 0) {
        cell = (t_cell *) cl_remove_end(queue)->data;
        visit_neighbours(cell, queue);
    }
}
