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

#define VERBOSE                        1
#define SCREEN_TITLE                   "Minotaur's Labyrinth"
#define SCREEN_W                       720
#define SCREEN_H                       1280
#define HEADER_W                       720
#define HEADER_H                       200
#define SCENE_W                        720
#define SCENE_H                        1000
#define FOOTER_W                       720
#define FOOTER_H                       80
#define ROWS                           50
#define COLS                           36
#define CELL_SIZE                      SCENE_W / COLS
#define PLAYER_MAX_HP_POINTS           100
#define PLAYER_START_HP_POINTS         100
#define HP_FULL_COLOR                  0Xd60000
#define HP_EMPTY_COLOR                 0x5c0000
#define HP_OFFSET_X                    295
#define HP_OFFSET_Y                    39
#define COLLECTIBLES                   50
#define TRAPS                          10
#define STATS_BAR_LENGTH               400
#define STATS_BAR_HEIGHT               50
#define STANDARD_FOOTER_BACKGROUND     0xFAFAFA
#define INSTRUCTIONS_FOOTER_BACKGROUND 0xB84B19
#define FREE_CELL_COLOR                0xb9ccb1
#define WALL_CELL_COLOR                0x3b3b3b
#define START_POSITION_COLOR           0x00FF00
#define END_POSITION_COLOR             0xFF0000
#define XPM_HEADER                     "./assets/images/header.xpm"
#define XPM_MAIN_SCENE                 "./assets/images/main_scene.xpm"
#define XPM_INSTRUCTIONS               "./assets/images/instructions.xpm"
#define XPM_FOOTER                     "./assets/images/footer.xpm"
#define XPM_FOOTER_WIN                 "./assets/images/footer_win.xpm"
#define XPM_FOOTER_LOSE                "./assets/images/footer_lose.xpm"
#define XPM_WIN                        "./assets/images/win.xpm"
#define XPM_LOSE                       "./assets/images/lose.xpm"
#define XPM_STATS_TRAP                 "./assets/images/stats_trap.xpm"
#define XPM_STATS_NOTRAP               "./assets/images/stats_notrap.xpm"
#define XPM_WIP                        "./assets/images/wip.xpm"
#define XPM_TRAP_COLLECTIBLE           "./assets/sprites/trap_collectible.xpm"
#define XPM_TRAP_ACTIVE                "./assets/sprites/trap_active.xpm"
#define XPM_FOOD                       "./assets/sprites/food.xpm"
#define XMP_EXPLORER                   "./assets/sprites/explorer.xpm"
#define XPM_MINOTAUR                   "./assets/sprites/minotaur.xpm"

typedef enum e_component { SCREEN, HEADER, SCENE, FOOTER } t_component;

typedef enum e_gamescene { MAIN, INSTRUCTIONS, GAME, WIN, LOSE } t_gamescene;

typedef enum e_movement { UP, DOWN, LEFT, RIGHT } t_movement;

typedef struct s_player {
    int x;
    int y;
    int health;
    int have_trap;
} t_player;

typedef struct s_map {
    char **grid;
    size_t width;
    size_t height;
    t_player *player;
    int start_pos[2];
    int end_pos[2];
    t_cl_list *collectibles;
    t_cl_list *traps;
} t_map;

typedef struct s_game {
    t_display display;
    t_image *screen;
    t_image *header;
    t_image *scene;
    t_image *footer;
    t_image *refresh;
    t_map *map;
    t_player *player;
    t_gamescene gamescene;
    char *footer_text;
} t_game;

extern t_game *game;

// ROUTINE SECTION
// maze.c
void initializeMaze(char **maze);
void printMaze(char **maze);
void generateMaze(char **maze, int row, int col);
// MLX SECTION
// defined in mlx_common.c
void init_graphics(void);
// defined in mlx_linux_hooks.c
int keypress(int ks);
int x_click(void);
int mouse_hook(int x, int y);
// defined in minotaur_actions_move.c
void move(t_movement direction);
void set_trap(void);
// defined in mlx_common.c
void init_graphics(void);
void init_hooks(void);
void destroy_mlx(void);
// defined in mlx_render.c
void refresh(t_component component, t_point coords);
void render_gamescreen(void);

#endif
