/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slp_actions_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:33:22 by doriani           #+#    #+#             */
/*   Updated: 2024/01/23 13:37:04 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

// static int
// player_eats_food(int col, int row) {
//     t_point *cell;

//     if ((cell = is_food_cell(col, row))) {
//         cl_add_node_end(game->map->free_cells,
//                         cl_remove_node_by_data(game->map->collectibles, cell,
//                                                compare_map_cells));
//         return (1);
//     }
//     return 0;
// }

static void
player_enters_food_cell(t_cell *cell) {
    cl_add_node_end(game->map->free_cells,
                    cl_remove_node_by_data(game->map->collectibles,
                                           &cell->coords, compare_map_cells));
    destroy_image(&game->display, cell->sprite_image);
    cell->sprite = NONE;
    cell->sprite_image = NULL;
}

// static int
// player_gets_trap(int col, int row) {
//     t_point *cell;

//     if ((cell = is_trap_cell(col, row))) {
//         cl_add_node_end(
//             game->map->free_cells,
//             cl_remove_node_by_data(game->map->traps, cell,
//             compare_map_cells));
//         return (1);
//     }
//     return 0;
// }

static void
player_enters_trap_cell(t_cell *cell) {
    if (game->player->has_trap)
        return;
    cl_add_node_end(game->map->free_cells,
                    cl_remove_node_by_data(game->map->traps, &cell->coords,
                                           compare_map_cells));
    destroy_image(&game->display, cell->sprite_image);
    cell->sprite = NONE;
    cell->sprite_image = NULL;
    game->player->has_trap++;
}

void
set_trap() {
    char str[100];
    t_point cell;

    cell.x = game->player->x;
    cell.y = game->player->y;

    cl_add_node_end(game->map->active_traps,
                    cl_remove_node_by_data(game->map->free_cells, &cell,
                                           compare_map_cells));

    game->player->has_trap = 0;
    sprintf(str, "Trap set at (%d, %d)", game->player->x, game->player->y);
    if (game->footer_text)
        free(game->footer_text);
    game->footer_text = strdup(str);
    render_gamescreen();
    minotaur_move();
}

static int
player_hit_minotaur() {
    return (game->player->x == game->minotaur->x &&
            game->player->y == game->minotaur->y);
}

static void
player_enters_minotaur_cell(t_cell *to) {
    // todo
    if (game->minotaur->is_trapped)
        return;
    game->gamescene = LOSE;
    render_gamescreen();
}

static void
update_position(int old_col, int old_row, int new_col, int new_row) {
    char str[100];
    if (is_exit_cell(new_col, new_row)) {
        game->gamescene = WIN;
        render_gamescreen();
        return;
    }
    game->player->x = new_col;
    game->player->y = new_row;
    if (!game->minotaur->is_trapped && player_hit_minotaur()) {
        game->gamescene = LOSE;
        render_gamescreen();
        return;
    }
    sprintf(str, "Player moved from (%d, %d) to (%d, %d)", old_col, old_row,
            new_col, new_row);
    if (game->footer_text)
        free(game->footer_text);
    game->footer_text = strdup(str);
    game->player->health -= MOVEMENT_COST;
    if (game->player->has_trap == 0 && player_gets_trap(new_col, new_row))
        game->player->has_trap = 1;
    if (player_eats_food(new_col, new_row))
        game->player->health =
            ft_min(game->player->health + FOOD_RESTORE, PLAYER_MAX_HP_POINTS);
    if (!game->player->has_trap && player_gets_trap(new_col, new_row))
        game->player->has_trap = 1;
    if (game->player->health <= 0)
        game->gamescene = LOSE;
    render_gamescreen();
    minotaur_move();
}

void
move(t_movement direction) {
    t_cell *from;
    t_cell *to;

    from = get_cell_from_coords((t_point){game->player->x, game->player->y});
    switch (direction) {
    case UP:
        to = get_cell_from_coords(
            (t_point){game->player->x, game->player->y - 1});
        break;
    case DOWN:
        to = get_cell_from_coords(
            (t_point){game->player->x, game->player->y + 1});
        break;
    case LEFT:
        to = get_cell_from_coords(
            (t_point){game->player->x - 1, game->player->y});
        break;
    case RIGHT:
        to = get_cell_from_coords(
            (t_point){game->player->x + 1, game->player->y});
        break;
    }
    if (!to)
        return;
    switch (to->sprite) {
    case FOOD:
        player_enters_food_cell(to);
        break;
    case TRAP:
        player_enters_food_cell(to);
        break;
    case MINO:
        // todo mino routine
        break;
    }
    update_position(from->coords.x, from->coords.y, to->coords.x, to->coords.y);
}

// void
// move(t_movement direction) {
//     char **grid = game->map->grid;
//     int col = game->player->x;
//     int row = game->player->y;

//     switch (direction) {
//     case UP:
//         if (row > 0 && strchr("0EP", grid[row - 1][col]))
//             update_position(col, row, col, row - 1);
//         break;
//     case DOWN:
//         if (row < ROWS - 1 && strchr("0EP", grid[row + 1][col]))
//             update_position(col, row, col, row + 1);
//         break;
//     case LEFT:
//         if (col > 0 && strchr("0EP", grid[row][col - 1]))
//             update_position(col, row, col - 1, row);
//         break;
//     case RIGHT:
//         if (col < COLS - 1 && strchr("0EP", grid[row][col + 1]))
//             update_position(col, row, col + 1, row);
//         break;
//     }
// }
