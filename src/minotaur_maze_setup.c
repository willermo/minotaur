/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:28:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 20:30:13 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
update_free_cells() {
    t_point *cell;

    cl_delete_list(game->map->free_cells);
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (game->map->grid[i][j] == '0' && !is_starting_cell(j, i) &&
                !is_exit_cell(j, i) && is_food_cell(j, i) == NULL &&
                is_trap_cell(j, i) == NULL) {
                cell = (t_point *) malloc(sizeof(t_point));
                cell->x = j;
                cell->y = i;
                cl_insert_end(game->map->free_cells, cell);
            }
}

static void
setup_food() {
    int free_cells_count;

    update_free_cells();
    free_cells_count = cl_size(game->map->free_cells);
    for (int i = 0; i < COLLECTIBLES; i++)
        cl_add_node_end(
            game->map->collectibles,
            cl_remove_node_by_position(game->map->free_cells,
                                       rand() % free_cells_count--));
}

static void
setup_traps() {
    int free_cells_count;

    update_free_cells();
    free_cells_count = cl_size(game->map->free_cells);
    for (int i = 0; i < TRAPS; i++)
        cl_add_node_end(game->map->traps, cl_remove_node_by_position(
                                              game->map->free_cells,
                                              rand() % free_cells_count--));
}

static void
initializeMaze(char **maze) {
    // Initializes all cells as walls
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = '1';
        }
    }
}

static void
setup_maze() {
    char **maze = game->map->grid;

    // Mark the entry and exit points
    maze[ROWS - 1][1] = 'P';
    maze[0][COLS - 2] = 'E';
    // Generate the maze starting from the entry point
    generateMaze(maze, ROWS - 1, 1);
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
init_lair() {
    initializeMaze(game->map->grid);
    setup_maze();
    if (VERBOSE)
        printMaze(game->map->grid);
    setup_food();
    setup_traps();
}

void
refresh_lair() {}
