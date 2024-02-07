/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/07 23:30:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
draw_stats() {
    int j;
    int size[2];

    j = 0;
    size[0] = STATS_BAR_LENGTH / PLAYER_MAX_HP_POINTS;
    size[1] = STATS_BAR_HEIGHT;
    while (j <= PLAYER_MAX_HP_POINTS) {
        if (game->player->health >= j)
            draw_rectangle(game->components->refresh,
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_FULL_COLOR, size);
        else
            draw_rectangle(game->components->refresh,
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_EMPTY_COLOR, size);
        j++;
    }
}

static void
draw_board(t_image *img) {
    int i;
    int j;

    i = 0;
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (game->map->grid[i][j] == '1')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            WALL_CELL_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == 'P')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            START_POSITION_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == 'E')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            END_POSITION_COLOR, CELL_SIZE);
            else if (game->map->grid[i][j] == '0')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            FREE_CELL_COLOR, CELL_SIZE);
            j++;
        }
        i++;
    }
}

static void
draw_footer(t_image *img) {
    if (game->gamescene == INSTRUCTIONS)
        draw_background(img, INSTRUCTIONS_FOOTER_BACKGROUND, 0, 0);
    else
        draw_background(img, STANDARD_FOOTER_BACKGROUND, 0, 0);
}

static void
setup_refresh(t_component comp, t_image ***ptr) {
    switch (comp) {
    case SCREEN:
        *ptr = &game->components->screen;
        game->components->refresh =
            create_image(&game->display, SCREEN_W, SCREEN_H);
        draw_background(game->components->refresh, 0x0000FF, 0, 0);
        break;
    case HEADER:
        *ptr = &game->components->header;
        if (game->gamescene != GAME) {
            game->components->refresh =
                load_xpm_image(&game->display, XPM_HEADER);
        } else {
            if (game->player->has_trap)
                game->components->refresh =
                    load_xpm_image(&game->display, XPM_STATS_TRAP);
            else
                game->components->refresh =
                    load_xpm_image(&game->display, XPM_STATS_NOTRAP);
            draw_stats(game);
        }
        break;
    case SCENE:
        *ptr = &game->components->scene;
        if (game->gamescene == MAIN)
            game->components->refresh =
                load_xpm_image(&game->display, XPM_MAIN_SCENE);
        else if (game->gamescene == INSTRUCTIONS)
            game->components->refresh =
                load_xpm_image(&game->display, XPM_INSTRUCTIONS);
        else if (game->gamescene == WIN)
            game->components->refresh = load_xpm_image(&game->display, XPM_WIN);
        else if (game->gamescene == LOSE)
            game->components->refresh =
                load_xpm_image(&game->display, XPM_LOSE);
        else if (game->gamescene == GAME) {
            game->components->refresh =
                create_image(&game->display, SCENE_W, SCENE_H);
            draw_board(game->components->refresh);
            draw_collectibles(game->components->refresh);
            if (game->minotaur->is_trapped) {
                draw_minotaurs(game->components->refresh);
                draw_player(game->components->refresh);
            } else {
                draw_player(game->components->refresh);
                draw_minotaur(game->components->refresh);
            }
        }
        break;
    case FOOTER:
        *ptr = &game->components->footer;
        if (game->gamescene == MAIN) {
            game->components->refresh =
                load_xpm_image(&game->display, XPM_FOOTER);
        } else if (game->gamescene == WIN) {
            game->components->refresh =
                load_xpm_image(&game->display, XPM_FOOTER_WIN);
        } else if (game->gamescene == LOSE) {
            game->components->refresh =
                load_xpm_image(&game->display, XPM_FOOTER_LOSE);
        } else {
            game->components->refresh =
                create_image(&game->display, FOOTER_W, FOOTER_H);
            draw_footer(game->components->refresh);
        }
        break;
    }
}

void
refresh(t_component component, t_point coords) {
    t_image **ptr;

    setup_refresh(component, &ptr);
    add_image(&game->display, game->components->refresh, coords);
    if (*ptr) {
        destroy_image(&game->display, *ptr);
        free(*ptr);
    }
    *ptr = game->components->refresh;
    game->components->refresh = NULL;
    if (game->gamescene == GAME && component == FOOTER && game->footer_text)
        mlx_string_put(game->display.mlx, game->display.win, FOOTER_TEXT_X,
                       FOOTER_TEXT_Y, FOOTER_TEXT_COLOR, game->footer_text);
}

void
render_gamescreen(void) {
    refresh(HEADER, (t_point){HEADER_OFFSET_W, HEADER_OFFSET_H});
    refresh(SCENE, (t_point){SCENE_OFFSET_W, SCENE_OFFSET_H});
    refresh(FOOTER, (t_point){FOOTER_OFFSET_W, FOOTER_OFFSET_H});
}
