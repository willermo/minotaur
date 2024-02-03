/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_algorithms.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 20:09:33 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

// Recursive backtracking algorithm to generate the maze
void
generateMaze(char **maze, int row, int col) {
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
                generateMaze(maze, next_row, next_col);
            }
        }
    }
}
