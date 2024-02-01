/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:10:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/01 20:15:47 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

// Function to initialize the maze with walls
void
initializeMaze(char **maze) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = '1';   // Initialize all cells as walls
        }
    }
}

// Function to print the maze
void
printMaze(char **maze) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

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
        int randIndex = rand() % 4;
        int temp = order[i];
        order[i] = order[randIndex];
        order[randIndex] = temp;
    }

    // Iterate over all directions
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[order[i]][0];
        int newCol = col + directions[order[i]][1];
        // Check if the new cell is within the bounds of the maze
        if (newRow > 0 && newRow < ROWS - 1 && newCol > 0 &&
            newCol < COLS - 1) {
            // Check if the new cell is a wall
            if (maze[newRow][newCol] == '1') {
                // Carve a path in the cell between the current cell and the new
                // cell
                maze[row + directions[order[i]][0] / 2]
                    [col + directions[order[i]][1] / 2] = '0';
                // Recursively call the function on the new cell
                generateMaze(maze, newRow, newCol);
            }
        }
    }
}
