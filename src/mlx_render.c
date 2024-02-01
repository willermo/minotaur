/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/01 18:51:19 by doriani          ###   ########.fr       */
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

static void
draw_stats() {
    int j;
    int size[2];

    j = 0;
    size[0] = STATS_BAR_LENGTH / PLAYER_MAX_HP_POINTS;
    size[1] = STATS_BAR_HEIGHT;
    while (j <= PLAYER_MAX_HP_POINTS) {
        if (game->player->health >= j)
            draw_rectangle(game->refresh,
                           (t_point){STATS_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_FULL_COLOR, size);
        else
            draw_rectangle(game->refresh,
                           (t_point){STATS_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_EMPTY_COLOR, size);
        j++;
    }
}

static void
draw_scene(t_image *img, int size[2]) {
    int i;
    int j;

    i = 0;
    while (i < size[1]) {
        j = 0;
        while (j < size[0]) {
            if (game->map->grid[i][j] == '1')
                draw_rectangle(img, (t_point){j, i}, 0x000000, (int[2]){1, 1});
            else if (game->map->grid[i][j] == 'P')
                draw_rectangle(img, (t_point){j, i}, 0x00FF00, (int[2]){1, 1});
            else if (game->map->grid[i][j] == 'E')
                draw_rectangle(img, (t_point){j, i}, 0xFF0000, (int[2]){1, 1});
            j++;
        }
        i++;
    }
}

static void
draw_footer(t_image *img, int size[2]) {
    draw_background(img, 0x000000, size[0], size[1]);
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
        if (game->gamescene != GAME)
            game->refresh = load_xpm_image(&game->display, XPM_HEADER);
        else {
            game->refresh = load_xpm_image(&game->display, XPM_PLAYERSTATS);
            draw_stats(game);
        }
        break;
    case SCENE:
        *ptr = &game->screen;
        if (game->gamescene == MAIN)

            game->refresh = load_xpm_image(&game->display, XPM_MAIN_SCENE);
        else if (game->gamescene == INSTRUCTIONS)
            game->refresh = load_xpm_image(&game->display, XPM_WIP);
        else {
            game->refresh = create_image(&game->display, SCENE_W, SCENE_H);
            draw_scene(game->refresh, (int[2]){SCENE_W, SCENE_H});
        }
        break;
    case FOOTER:
        *ptr = &game->footer;
        if (game->gamescene == MAIN)

            game->refresh = load_xpm_image(&game->display, XPM_FOOTER);
        else {
            game->refresh = create_image(&game->display, FOOTER_W, FOOTER_H);
            draw_footer(game->refresh, (int[2]){FOOTER_W, FOOTER_H});
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
}

void
render_gamescreen(void) {
    refresh(HEADER, (t_point){0, 0});
    refresh(SCENE, (t_point){0, 200});
    refresh(FOOTER, (t_point){0, 1200});
}
