/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:21 by doriani           #+#    #+#             */
/*   Updated: 2024/02/01 23:49:03 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_game *game;

static void
setup_maze() {
    char **maze = game->map->grid;

    initializeMaze(maze);
    // Entry point (bottom line)
    maze[ROWS - 1][1] = 'P';

    // Exit point (upper line)
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

    // Print the maze
    if (VERBOSE)
        printMaze(maze);
}

static void
init_player(void) {
    game->map->player->x = 1;
    game->map->player->y = ROWS - 1;
    game->map->player->health = PLAYER_START_HP_POINTS;
}

static void
init_map(void) {
    game->map->width = COLS;
    game->map->height = ROWS;
    game->map->grid = (char **) malloc(sizeof(char *) * ROWS);
    for (int i = 0; i < ROWS; i++)
        game->map->grid[i] = (char *) malloc(sizeof(char) * COLS);
}

static void
init_game(void) {
    ft_printf(TY_BLUE_B "Initializing minotaur\n" TY_RESET);
    game = (t_game *) malloc(sizeof(t_game));
    game->map = (t_map *) malloc(sizeof(t_map));
    game->map->player = (t_player *) malloc(sizeof(t_player));
    init_map();
    init_player();
}

static void
clean_game(void) {
    ft_printf(TY_BLUE_B "Cleaning minotaur\n" TY_RESET);
    for (int i = 0; i < ROWS; i++)
        free(game->map->grid[i]);
    free(game->map->grid);
    free(game->map->player);
    free(game->map);
    free(game);
}

static void
start_game(void) {
    setup_maze();
    init_graphics();
    render_gamescreen();
    init_hooks();
    mlx_loop(game->display.mlx);
}

int
main() {
    srand(time(NULL));
    init_game();
    start_game();
    clean_game();
    ft_printf(TY_BLUE_B "\nExiting minotaur\n" TY_RESET);
    return (0);
}
