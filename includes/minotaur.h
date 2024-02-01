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
#include <time.h>
#include <unistd.h>

#define VERBOSE                1
#define SCREEN_TITLE           "Minotaur's Labyrinth"
#define SCREEN_W               720
#define SCREEN_H               1280
#define HEADER_W               720
#define HEADER_H               200
#define SCENE_W                720
#define SCENE_H                1000
#define FOOTER_W               720
#define FOOTER_H               80
#define ROWS                   50
#define COLS                   36
#define CELL_SIZE              SCENE_W / COLS
#define PLAYER_MAX_HP_POINTS   100
#define PLAYER_START_HP_POINTS 100
#define HP_FULL_COLOR          0Xd60000
#define HP_EMPTY_COLOR         0x5c0000
#define MANA_FULL_COLOR        0x011bfa
#define MANA_EMPTY_COLOR       0x00095c
#define STATS_OFFSET_X         310
#define HP_OFFSET_Y            55
#define MANA_OFFSET_Y          120
#define STATS_BAR_LENGTH       200
#define STATS_BAR_HEIGHT       25
#define XPM_HEADER             "./assets/images/header.xpm"
#define XPM_MAIN_SCENE         "./assets/images/main_scene.xpm"
#define XPM_FOOTER             "./assets/images/footer.xpm"
#define XPM_WIP                "./assets/images/wip.xpm"
#define XPM_WIN                "./assets/images/win.xpm"
#define XPM_PLAYERSTATS        "./assets/images/playerstats.xpm"

typedef enum e_component { SCREEN, HEADER, SCENE, FOOTER } t_component;

typedef enum e_gamescene { MAIN, INSTRUCTIONS, GAME, WIN, LOSE } t_gamescene;

typedef enum e_movement { UP, DOWN, LEFT, RIGHT } t_movement;

typedef struct s_player {
    int x;
    int y;
    int health;
} t_player;

typedef struct s_map {
    char **grid;
    size_t width;
    size_t height;
    t_player *player;
    int start_pos[2];
    int end_pos[2];
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
