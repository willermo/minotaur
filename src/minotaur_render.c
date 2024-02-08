/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 20:24:59 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

static void
draw_stats(t_image **refresh) {
    int j;
    int size[2];

    j = 0;
    size[0] = STATS_BAR_LENGTH / PLAYER_MAX_HP_POINTS;
    size[1] = STATS_BAR_HEIGHT;
    while (j <= PLAYER_MAX_HP_POINTS) {
        if (game->player->health >= j)
            draw_rectangle(*refresh,
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_FULL_COLOR, size);
        else
            draw_rectangle(*refresh,
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_EMPTY_COLOR, size);
        j++;
    }
}

static void
draw_footer(t_image *img) {
    if (game->gamescene == INSTRUCTIONS)
        return (draw_background(img, INSTRUCTIONS_FOOTER_BACKGROUND, 0, 0));
    draw_background(img, FOOTER_TEXT_BACKGROUND, 0, 0);
}

static void
setup_refresh(t_component comp, t_image ***ptr, t_image **refresh) {
    switch (comp) {
    case SCREEN:
        *ptr = &game->components->screen;
        *refresh = create_image(&game->display, SCREEN_W, SCREEN_H);
        draw_background(*refresh, 0x0000FF, 0, 0);
        break;
    case HEADER:
        *ptr = &game->components->header;
        if (game->gamescene != GAME) {
            *refresh = load_xpm_image(&game->display, XPM_HEADER);
        } else {
            if (game->player->has_trap)
                *refresh = load_xpm_image(&game->display, XPM_STATS_TRAP);
            else
                *refresh = load_xpm_image(&game->display, XPM_STATS_NOTRAP);
            draw_stats(refresh);
        }
        break;
    case SCENE:
        *ptr = &game->components->scene;
        if (game->gamescene == MAIN)
            *refresh = load_xpm_image(&game->display, XPM_MAIN_SCENE);
        else if (game->gamescene == INSTRUCTIONS)
            *refresh = load_xpm_image(&game->display, XPM_INSTRUCTIONS);
        else if (game->gamescene == WIN)
            *refresh = load_xpm_image(&game->display, XPM_WIN);
        else if (game->gamescene == LOSE)
            *refresh = load_xpm_image(&game->display, XPM_LOSE);
        else if (game->gamescene == GAME) {
            *refresh = create_image(&game->display, SCENE_W, SCENE_H);
            draw_gamescene(*refresh);
        }
        break;
    case FOOTER:
        *ptr = &game->components->footer;
        if (game->gamescene == MAIN)
            *refresh = load_xpm_image(&game->display, XPM_FOOTER);
        else if (game->gamescene == WIN)
            *refresh = load_xpm_image(&game->display, XPM_FOOTER_WIN);
        else if (game->gamescene == LOSE)
            *refresh = load_xpm_image(&game->display, XPM_FOOTER_LOSE);
        else {
            *refresh = create_image(&game->display, FOOTER_W, FOOTER_H);
            draw_footer(*refresh);
        }
        break;
    }
}

void
refresh(t_component component, t_point coords) {
    t_image **ptr;
    t_image *refresh;

    setup_refresh(component, &ptr, &refresh);
    add_image(&game->display, refresh, coords);
    if (*ptr) {
        destroy_image(&game->display, *ptr);
        free(*ptr);
    }
    *ptr = refresh;
}

void
render_gamescreen(void) {
    refresh(HEADER, (t_point){HEADER_OFFSET_W, HEADER_OFFSET_H});
    refresh(SCENE, (t_point){SCENE_OFFSET_W, SCENE_OFFSET_H});
    refresh(FOOTER, (t_point){FOOTER_OFFSET_W, FOOTER_OFFSET_H});
    if (game->gamescene == GAME && strlen(game->footer_text))
        mlx_string_put(game->display.mlx, game->display.win, FOOTER_TEXT_X,
                       FOOTER_TEXT_Y, FOOTER_TEXT_COLOR, game->footer_text);
}
