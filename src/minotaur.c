/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:21 by doriani           #+#    #+#             */
/*   Updated: 2024/02/02 23:22:09 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_game *game;

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
setup_collectibles() {
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
init_minotaur(void) {
    game->map->minotaur->x = game->map->end_pos[0];
    game->map->minotaur->y = game->map->end_pos[1];
    game->map->minotaur->is_trapped = 0;
}

static void
init_player(void) {
    game->map->player->x = game->map->start_pos[0];
    game->map->player->y = game->map->start_pos[1];
    game->map->player->health = PLAYER_START_HP_POINTS;
    game->map->player->has_trap = 1;
}

static void
init_map(void) {
    game->map->width = COLS;
    game->map->height = ROWS;
    game->map->grid = (char **) malloc(sizeof(char *) * ROWS);
    for (int i = 0; i < ROWS; i++)
        game->map->grid[i] = (char *) malloc(sizeof(char) * COLS);
    game->map->start_pos[0] = 1;
    game->map->start_pos[1] = ROWS - 1;
    game->map->end_pos[0] = COLS - 2;
    game->map->end_pos[1] = 0;
    game->map->collectibles = cl_init_list();
    game->map->traps = cl_init_list();
    game->map->active_traps = cl_init_list();
    game->map->free_cells = cl_init_list();
}

static void
init_game(void) {
    ft_printf(TY_BLUE_B "Initializing minotaur\n" TY_RESET);
    game = (t_game *) malloc(sizeof(t_game));
    game->map = (t_map *) malloc(sizeof(t_map));
    game->map->player = (t_player *) malloc(sizeof(t_player));
    game->map->minotaur = (t_minotaur *) malloc(sizeof(t_minotaur));
    init_map();
    init_player();
    init_minotaur();
    game->footer_text = NULL;
    game->collectibles_images = cl_init_list();
    game->traps_images = cl_init_list();
    game->active_traps_images = cl_init_list();
    game->player_image = NULL;
    game->minotaur_image = NULL;
}

static void
clean_game(void) {
    ft_printf(TY_BLUE_B "Cleaning minotaur\n" TY_RESET);
    for (int i = 0; i < ROWS; i++)
        free(game->map->grid[i]);
    free(game->map->grid);
    free(game->map->player);
    free(game->map->minotaur);
    cl_destroy_list(&game->map->collectibles);
    cl_destroy_list(&game->map->traps);
    cl_destroy_list(&game->map->active_traps);
    cl_destroy_list(&game->map->free_cells);
    free(game->map);
    if (game->player_image)
        free(game->player_image);
    if (game->minotaur_image)
        free(game->minotaur_image);
    free(game);
}

static void
start_game(void) {
    setup_maze();
    setup_collectibles();
    setup_traps();
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
