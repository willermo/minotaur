/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:17:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 22:33:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
init_items() {
    game->map->collectibles = cl_init_list();
    game->map->traps = cl_init_list();
    game->map->active_traps = cl_init_list();
    game->map->free_cells = cl_init_list();
}

static void
init_sprites() {
    game->collectibles_images = cl_init_list();
    game->traps_images = cl_init_list();
    game->active_traps_images = cl_init_list();
}

static void
allocate_data_structures_memory(void) {
    game = (t_game *) malloc(sizeof(t_game));
    game->map = (t_map *) malloc(sizeof(t_map));
    game->map->player = (t_player *) malloc(sizeof(t_player));
    game->map->minotaur = (t_minotaur *) malloc(sizeof(t_minotaur));
    game->map->grid = (char **) malloc(sizeof(char *) * ROWS);
    for (int i = 0; i < ROWS; i++)
        game->map->grid[i] = (char *) malloc(sizeof(char) * COLS);
}

static void
init_map_parameters(void) {
    // set dimensions
    game->map->width = COLS;
    game->map->height = ROWS;
    // set enter and exit positions
    game->map->start_pos[0] = 1;
    game->map->start_pos[1] = ROWS - 1;
    game->map->end_pos[0] = COLS - 2;
    game->map->end_pos[1] = 0;
    // set player parameters
    game->map->player->x = game->map->start_pos[0];
    game->map->player->y = game->map->start_pos[1];
    game->map->player->health = PLAYER_START_HP_POINTS;
    game->map->player->has_trap = 1;
    // set minotaur parameters
    game->map->minotaur->x = game->map->end_pos[0];
    game->map->minotaur->y = game->map->end_pos[1];
    game->map->minotaur->is_trapped = 0;
}

static void
init_game_structures(void) {
    allocate_data_structures_memory();
    init_items();
    init_sprites();
    init_map_parameters();
}

void
init_game(void) {
    init_game_structures();
    init_lair();
}
