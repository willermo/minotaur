/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_maze_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:28:41 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 19:42:35 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
insert_cell(t_point coords) {
    t_cell *cell;

    cell = (t_cell *) malloc(sizeof(t_cell));
    cell->coords = coords;
    cell->neighbours = cl_init_list();
    cell->color = WHITE;
    cell->parent = NULL;
    cell->distance = -1;
    cell->sprite_type = NONE;
    cl_insert_begin(game->lair, cell);
}

static void
init_lair(void) {
    game->lair = cl_init_list();
    // populating adjacency list
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (strchr("0PE", game->map->grid[i][j]))
                insert_cell((t_point){j, i});
}

static void
build_lair() {
    init_lair();
    cl_foreach(game->lair, add_neighbours);
    setup_free_cells();
    setup_food();
    setup_traps();
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
