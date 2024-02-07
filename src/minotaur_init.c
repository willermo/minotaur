/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:17:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 22:31:44 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
init_items() {
    game->collectibles->free_cells = cl_init_list();
    game->collectibles->food = cl_init_list();
    game->collectibles->traps = cl_init_list();
    game->collectibles->active_traps = cl_init_list();
}

static void
init_sprites() {
    game->sprites->food =
        load_xpm_image(game->display.mlx, "./assets/sprites/food.xpm");
    game->sprites->trap =
        load_xpm_image(game->display.mlx, "./assets/sprites/trap.xpm");
    game->sprites->active_trap =
        load_xpm_image(game->display.mlx, "./assets/sprites/active_trap.xpm");
    game->sprites->player =
        load_xpm_image(game->display.mlx, "./assets/sprites/player.xpm");
    game->sprites->minotaur =
        load_xpm_image(game->display.mlx, "./assets/sprites/minotaur.xpm");
}

static void
allocate_data_structures_memory(void) {
    game = (t_game *) malloc(sizeof(t_game));
    game->map = (t_map *) malloc(sizeof(t_map));
    game->player = (t_player *) malloc(sizeof(t_player));
    game->minotaur = (t_minotaur *) malloc(sizeof(t_minotaur));
    game->map->grid = (char **) malloc(sizeof(char *) * ROWS);
    for (int i = 0; i < ROWS; i++)
        game->map->grid[i] = (char *) malloc(sizeof(char) * COLS);
    game->sprites = (t_sprites *) malloc(sizeof(t_sprites));
    game->collectibles = (t_collectibles *) malloc(sizeof(t_collectibles));
    game->components = (t_components *) malloc(sizeof(t_components));
}

static void
init_map_parameters(void) {
    // set dimensions
    game->map->width = COLS;
    game->map->height = ROWS;
    // set enter and exit positions
    game->map->start_pos.x = 1;
    game->map->start_pos.y = ROWS - 1;
    game->map->end_pos.x = COLS - 2;
    game->map->end_pos.y = 0;
    // set player parameters
    game->player->coords.x = game->map->start_pos.x;
    game->player->coords.y = game->map->start_pos.y;
    game->player->health = PLAYER_START_HP_POINTS;
    game->player->has_trap = 1;
    // set minotaur parameters
    game->minotaur->coords.x = game->map->end_pos.x;
    game->minotaur->coords.y = game->map->end_pos.y;
    game->minotaur->is_trapped = 0;
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
    setup_lair();
}
