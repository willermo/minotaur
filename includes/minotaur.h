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

typedef enum e_component { SCREEN, HEADER, SCENE, FOOTER } t_component;

typedef enum e_gamescene { MAIN, INSTRUCTIONS, GAME, WIN, LOSE } t_gamescene;

typedef enum e_movement { UP, DOWN, LEFT, RIGHT } t_movement;

typedef struct s_player {
    int x;
    int y;
    int health;
    int has_trap;
} t_player;

typedef struct s_minotaur {
    int x;
    int y;
    int is_trapped;
} t_minotaur;

typedef struct s_map {
    char **grid;
    size_t width;
    size_t height;
    int start_pos[2];
    int end_pos[2];
    t_player *player;
    t_minotaur *minotaur;
    t_cl_list *collectibles;
    t_cl_list *traps;
    t_cl_list *active_traps;
    t_cl_list *free_cells;
} t_map;

typedef struct s_game {
    t_display display;
    t_image *screen;
    t_image *header;
    t_image *scene;
    t_image *footer;
    t_image *refresh;
    t_image *player_image;
    t_image *minotaur_image;
    t_cl_list *collectibles_images;
    t_cl_list *traps_images;
    t_cl_list *active_traps_images;
    char *footer_text;
    t_map *map;
    t_gamescene gamescene;
} t_game;

extern t_game *game;

// UTILS SECTION
// defined in minotaur_helpers.c
char **clone_grid(char **grid);
int compare_cells(void *cell1, void *cell2);
int is_starting_cell(int col, int row);
int is_exit_cell(int col, int row);
t_point *is_food_cell(int col, int row);
t_point *is_trap_cell(int col, int row);
t_point *is_trap_active_cell(int col, int row);
// defined in minotaur_utils.c
void printMaze(char **maze);
void destroy_collectibles();
void destroy_traps();
void destroy_active_traps();

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
// defined in maze.c
void printMaze(char **maze);
void generateMaze(char **maze, int row, int col);

// MLX SECTION
// defined in hooks.c
int keypress(int ks);
int x_click(void);
int mouse_hook(int x, int y);
// defined in minotaur_render.c
void refresh(t_component component, t_point coords);
void render_gamescreen(void);

// GAMEPLAY SECTION
// defined in actions.c
void set_trap(void);
void move(t_movement direction);

#endif
