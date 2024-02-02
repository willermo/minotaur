/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/02 12:06:39 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
draw_background(t_image *img, t_rgba color, int random, int progressive) {
    int i;
    int j;

    i = 0;
    while (i < img->height) {
        j = 0;
        while (j < img->width) {
            if (random)
                draw_pixel(img, (t_point){j++, i}, get_random_color());
            else if (progressive)
                draw_pixel(img, (t_point){j++, i}, color++ % 0xFFFFFF);
            else
                draw_pixel(img, (t_point){j++, i}, color);
        }
        i++;
    }
}

// static void
// draw_stats() {
//     int j;
//     int size[2];

//     j = 0;
//     size[0] = STATS_BAR_LENGTH / PLAYER_MAX_HP_POINTS;
//     size[1] = STATS_BAR_HEIGHT;
//     while (j <= PLAYER_MAX_HP_POINTS) {
//         if (game->player->health >= j)
//             draw_rectangle(game->refresh,
//                            (t_point){STATS_OFFSET_X + j * size[0],
//                            HP_OFFSET_Y}, HP_FULL_COLOR, size);
//         else
//             draw_rectangle(game->refresh,
//                            (t_point){STATS_OFFSET_X + j * size[0],
//                            HP_OFFSET_Y}, HP_EMPTY_COLOR, size);
//         j++;
//     }
// }

static void
draw_scene(t_image *img) {
    int i;
    int j;

    i = 0;
    while (i < ROWS) {
        j = 0;
        while (j < COLS) {
            if (game->map->grid[i][j] == '1')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            0x000000, CELL_SIZE);
            else if (game->map->grid[i][j] == 'P')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            0x00FF00, CELL_SIZE);
            else if (game->map->grid[i][j] == 'E')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            0xFF0000, CELL_SIZE);
            else if (game->map->grid[i][j] == '0')
                draw_square(img, (t_point){j * CELL_SIZE, i * CELL_SIZE},
                            0xFFFFFF, CELL_SIZE);
            j++;
        }
        i++;
    }
}

static void
draw_footer(t_image *img) {
    if (game->gamescene == INSTRUCTIONS)
        draw_background(img, 0xB84B19, 0, 0);
    else
        draw_background(img, 0xFAFAFA, 0, 0);
}

static void
setup_refresh(t_component comp, t_image ***ptr) {
    switch (comp) {
    case SCREEN:
        *ptr = &game->screen;
        game->refresh = create_image(&game->display, SCREEN_W, SCREEN_H);
        draw_background(game->refresh, 0x0000FF, 0, 0);
        break;
    case HEADER:
        *ptr = &game->header;
        if (game->gamescene != GAME) {
            game->refresh = load_xpm_image(&game->display, XPM_HEADER);
        } else {
            game->refresh = load_xpm_image(&game->display, XPM_PLAYERSTATS);
            // draw_stats(game);
        }
        break;
    case SCENE:
        *ptr = &game->scene;
        if (game->gamescene == MAIN)
            game->refresh = load_xpm_image(&game->display, XPM_MAIN_SCENE);
        else if (game->gamescene == INSTRUCTIONS)
            game->refresh = load_xpm_image(&game->display, XPM_INSTRUCTIONS);
        else if (game->gamescene == WIN)
            game->refresh = load_xpm_image(&game->display, XPM_WIN);
        else {
            game->refresh = create_image(&game->display, SCENE_W, SCENE_H);
            draw_scene(game->refresh);
        }
        break;
    case FOOTER:
        *ptr = &game->footer;
        if (game->gamescene == MAIN) {
            game->refresh = load_xpm_image(&game->display, XPM_FOOTER);
        } else if (game->gamescene == WIN) {
            game->refresh = load_xpm_image(&game->display, XPM_FOOTER_WIN);
        } else if (game->gamescene == LOSE) {
            game->refresh = load_xpm_image(&game->display, XPM_FOOTER_LOSE);
        } else {
            game->refresh = create_image(&game->display, FOOTER_W, FOOTER_H);
            draw_footer(game->refresh);
        }
        break;
    }
}

void
refresh(t_component component, t_point coords) {
    t_image **ptr;

    setup_refresh(component, &ptr);
    add_image(&game->display, game->refresh, coords);
    destroy_image(&game->display, *ptr);
    free(*ptr);
    *ptr = game->refresh;
    game->refresh = NULL;
    if (game->gamescene == GAME && component == FOOTER && game->footer_text)
        mlx_string_put(game->display.mlx, game->display.win, 30, 1230, 0x000000,
                       game->footer_text);
}

void
render_gamescreen(void) {
    refresh(HEADER, (t_point){0, 0});
    refresh(SCENE, (t_point){0, 200});
    refresh(FOOTER, (t_point){0, 1200});
}
