/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/02/04 23:39:15 by doriani          ###   ########.fr       */
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
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_FULL_COLOR, size);
        else
            draw_rectangle(game->refresh,
                           (t_point){HP_OFFSET_X + j * size[0], HP_OFFSET_Y},
                           HP_EMPTY_COLOR, size);
        j++;
    }
}

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
draw_collectibles() {
    t_cl_list *node;
    t_point *cell;
    t_image *collectible_image;

    destroy_collectibles();
    node = game->map->collectibles->next;
    while (node->data) {
        cell = (t_point *) node->data;
        collectible_image = load_xpm_image(&game->display, XPM_FOOD);
        add_image(&game->display, collectible_image,
                  (t_point){cell->x * CELL_SIZE + 2,
                            cell->y * CELL_SIZE + HEADER_H + 2});
        cl_insert_end(game->collectibles_images, collectible_image);
        node = node->next;
    }
}

static void
draw_traps() {
    t_cl_list *node;
    t_point *cell;
    t_image *trap_image;

    destroy_traps();
    node = game->map->traps->next;
    while (node->data) {
        cell = (t_point *) node->data;
        trap_image = load_xpm_image(&game->display, XPM_TRAP_COLLECTIBLE);
        add_image(&game->display, trap_image,
                  (t_point){cell->x * CELL_SIZE + 2,
                            cell->y * CELL_SIZE + HEADER_H + 2});
        cl_insert_end(game->traps_images, trap_image);
        node = node->next;
    }
}

static void
draw_active_traps() {
    t_cl_list *node;
    t_point *cell;
    t_image *trap_image;

    destroy_active_traps();
    node = game->map->active_traps->next;
    while (node->data) {
        cell = (t_point *) node->data;
        trap_image = load_xpm_image(&game->display, XPM_TRAP_ACTIVE);
        add_image(&game->display, trap_image,
                  (t_point){cell->x * CELL_SIZE + 2,
                            cell->y * CELL_SIZE + HEADER_H + 2});
        cl_insert_end(game->active_traps_images, trap_image);
        node = node->next;
    }
}

static void
draw_player() {
    t_image *img;

    img = load_xpm_image(&game->display, XMP_EXPLORER);
    add_image(&game->display, img,
              (t_point){game->player->x * CELL_SIZE + 2,
                        game->player->y * CELL_SIZE + HEADER_H + 2});
    if (game->player_image) {
        destroy_image(&game->display, game->player_image);
        free(game->player_image);
    }
    game->player_image = img;
}

static void
draw_minotaur() {
    t_image *img;

    img = load_xpm_image(&game->display, XPM_MINOTAUR);
    add_image(&game->display, img,
              (t_point){game->minotaur->x * CELL_SIZE + 2,
                        game->minotaur->y * CELL_SIZE + HEADER_H + 2});
    if (game->minotaur_image) {
        destroy_image(&game->display, game->minotaur_image);
        free(game->minotaur_image);
    }
    game->minotaur_image = img;
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
            if (game->player->has_trap)
                game->refresh = load_xpm_image(&game->display, XPM_STATS_TRAP);
            else
                game->refresh =
                    load_xpm_image(&game->display, XPM_STATS_NOTRAP);
            draw_stats(game);
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
        else if (game->gamescene == LOSE)
            game->refresh = load_xpm_image(&game->display, XPM_LOSE);
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
    if (*ptr) {
        destroy_image(&game->display, *ptr);
        free(*ptr);
    }
    *ptr = game->refresh;
    game->refresh = NULL;
    if (game->gamescene == GAME && component == FOOTER && game->footer_text)
        mlx_string_put(game->display.mlx, game->display.win, FOOTER_TEXT_X,
                       FOOTER_TEXT_Y, FOOTER_TEXT_COLOR, game->footer_text);
}

void
render_gamescreen(void) {
    refresh(HEADER, (t_point){HEADER_OFFSET_W, HEADER_OFFSET_H});
    refresh(SCENE, (t_point){SCENE_OFFSET_W, SCENE_OFFSET_H});
    refresh(FOOTER, (t_point){FOOTER_OFFSET_W, FOOTER_OFFSET_H});
    if (game->gamescene == GAME) {
        draw_collectibles();
        draw_traps();
        draw_active_traps();
        if (game->minotaur->is_trapped) {
            draw_minotaur();
            draw_player();
        } else {
            draw_player();
            draw_minotaur();
        }
    }
}