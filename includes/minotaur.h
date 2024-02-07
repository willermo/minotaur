/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur.h                                            :+:      :+:    :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:05 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:21:29 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINOTAUR_h
#define MINOTAUR_h

#include "libft.h"
#include "minotaur_params.h"
#include "mlx.h"
#include "mlx_utils.h"
#include "typography.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_W         720
#define SCREEN_H         1280
#define HEADER_W         720
#define HEADER_H         200
#define HEADER_OFFSET_W  0
#define HEADER_OFFSET_H  0
#define SCENE_W          720
#define SCENE_H          1000
#define SCENE_OFFSET_W   0
#define SCENE_OFFSET_H   200
#define FOOTER_W         720
#define FOOTER_H         80
#define FOOTER_OFFSET_W  0
#define FOOTER_OFFSET_H  1200
#define FOOTER_TEXT_X    30
#define FOOTER_TEXT_Y    1230
#define ROWS             50
#define COLS             36
#define CELL_SIZE        SCENE_W / COLS
#define SPRITES_SIZE     18
#define HP_OFFSET_X      295
#define HP_OFFSET_Y      39
#define STATS_BAR_LENGTH 400
#define STATS_BAR_HEIGHT 50

typedef enum e_component { SCREEN, HEADER, SCENE, FOOTER } t_component;

typedef enum e_gamescene { MAIN, INSTRUCTIONS, GAME, WIN, LOSE } t_gamescene;

typedef enum e_movement { UP, DOWN, LEFT, RIGHT } t_movement;

typedef enum e_cell_color { WHITE, GRAY, BLACK } t_cell_color;

typedef enum e_sprite_type { NONE, FOOD, TRAP, ACTIVE_TRAP } t_sprite_type;

typedef struct s_player {
    t_point coords;
    int health;
    int has_trap;
} t_player;

typedef struct s_minotaur {
    t_point coords;
    int is_trapped;
} t_minotaur;

typedef struct s_map {
    char **grid;
    size_t width;
    size_t height;
    t_point start_pos;
    t_point end_pos;
} t_map;

typedef struct s_cell t_cell;   // forward declaration

typedef struct s_cell {
    t_point coords;
    t_cl_list *neighbours;
    t_sprite_type sprite_type;
    // metadata for pathfinding
    t_cell_color color;
    int distance;
    t_cell *parent;
} t_cell;

typedef struct s_sprites {
    t_image *food;
    t_image *trap;
    t_image *active_trap;
    t_image *player;
    t_image *minotaur;
} t_sprites;

typedef struct s_collectibles {
    t_cl_list *free_cells;
    t_cl_list *food;
    t_cl_list *traps;
    t_cl_list *active_traps;
} t_collectibles;

typedef struct s_components {
    t_image *screen;
    t_image *header;
    t_image *scene;
    t_image *footer;
    t_image *refresh;
} t_components;

// typedef struct s_characters {
//     t_player *player;
//     t_minotaur *minotaur;
// } t_characters;

typedef struct s_game {
    t_display display;
    t_map *map;
    t_sprites *sprites;
    t_collectibles *collectibles;
    t_components *components;
    t_cl_list *lair;
    t_player *player;
    t_minotaur *minotaur;
    char *footer_text;
    t_gamescene gamescene;
} t_game;

extern t_game *game;

// UTILS SECTION
// defined in minotaur_debug.c
void print_maze(char **maze);
void print_cell(void *cell);
void print_neighbours(void *cell);
// defined in minotaur_helpers.c
t_cell *get_cell_from_coords(t_point coord);
t_cell *get_player_cell();
t_cell *get_minotaur_cell();
t_cell *get_enter_cell();
t_cell *get_exit_cell();
int is_enter_cell(t_cell *cell);
int is_exit_cell(t_cell *cell);
int is_food_cell(t_cell *cell);
int is_trap_cell(t_cell *cell);
int is_trap_active_cell(t_cell *cell);
int is_free_cell(t_cell *cell);
int is_player_cell(t_cell *cell);
int is_minotaur_cell(t_cell *cell);
int is_walkable_cell(t_point coords);
int is_valid_coords(t_point coords);
char **clone_grid(char **grid);
int compare_lair_cells(void *cell1, void *cell2);
int compare_coords(void *coord1, void *coord2);

// defined in minotaur_utils.c

// MAIN ROUTINE SECTION
// defined in minotaur_init.c
void init_game(void);
// defined in minotaur_start.c
void start_game(void);
// defined in minotaur_end.c
void end_game(void);
// defined in minotaur_clean.c
void clean_game(void);

// MAZE MANAGEMENT SECTION
// defined in minotaur_maze_setup.c
void init_lair();
void refresh_lair();
// defined in minotaur_maze_setup_neighbours.c
void add_neighbours(void *cell);
// defined in minotaur_maze_setup_items.c
void setup_free_cells();
void setup_food();
void setup_traps();
// defined in minotaur_maze_unset.c
void destroy_lair();
// defined in minotaur_maze_algorithms.c
void generate_maze(char **maze, int row, int col);
void explore_maze(t_cell *start);
t_cell *find_nearest_cell(t_cell *start, t_cell *end);

// MLX SECTION
// defined in hooks.c
int keypress(int ks);
int x_click(void);
int mouse_hook(int x, int y);
// defined in minotaur_render.c
void refresh(t_component component, t_point coords);
void render_gamescreen(void);
// defined in minotaur_render_draw_collectibles.c
void draw_food(t_image *board);
void draw_traps(t_image *board);
void draw_active_traps(t_image *board);
void draw_collectibles(t_image *board);
void draw_player(t_image *board);
void draw_minotaur(t_image *board);

// GAMEPLAY SECTION
// defined in actions.c
void set_trap(void);
void move(t_movement direction);
// defined in minotaur_mino.c
t_cell *get_nearest_to_player_cell();
t_point get_nearest_to_player_cell_coordinate();
void minotaur_move();
// defined in events.c
void player_enters_food_cell(t_cell *cell);
void player_enters_trap_cell(t_cell *cell);
void player_enters_minotaur_cell(t_cell *cell);
void player_enters_exit_cell(t_cell *cell);
void minotaur_enters_active_trap_celll(t_cell *cell);
#endif
