/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:28:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/06 21:04:37 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static int
cell_is_free(int i, int j) {
    if (game->map->grid[i][j] != '0')
        return (0);
    if (is_starting_cell(j, i))
        return (0);
    if (is_exit_cell(j, i))
        return (0);
    if (is_food_cell(j, i))
        return (0);
    if (is_trap_cell(j, i))
        return (0);
    return (1);
}

static void
initialize_maze() {
    char **maze = game->map->grid;

    // Initializes all cells as walls
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            maze[i][j] = '1';
    // Mark the entry and exit points
    maze[ROWS - 1][1] = 'P';
    maze[0][COLS - 2] = 'E';
    // Generate the maze starting from the entry point
    generate_maze(maze, ROWS - 1, 1);
    // Ensure a path from the entry to the exit
    for (int i = 1; i < COLS - 1; i++) {
        if (maze[0][i] == '0') {
            maze[0][i] = '1';
            break;
        }
    }
    maze[1][COLS - 2] = '0';
}

void
setup_lair() {
    initialize_maze();
    if (VERBOSE)
        print_maze(game->map->grid);
    build_lair();
}

void
refresh_lair() {}
