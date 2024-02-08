/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_params.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:33:49 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 21:22:12 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINOTAUR_PARAMS_H
#define MINOTAUR_PARAMS_H

#define VERBOSE                        1
#define DEBUG                          0
#define SCREEN_TITLE                   "Minotaur's Lair"
#define PLAYER_MAX_HP_POINTS           100
#define PLAYER_START_HP_POINTS         100
#define MOVEMENT_COST                  1
#define FOOD_RESTORE                   20
#define COLLECTIBLES                   50
#define TRAPS                          10
#define TRAP_PENALTY                   5
#define MINOTAUR_DAMAGE                200
#define FOOTER_TEXT_COLOR              0x000000
#define FOOTER_TEXT_BACKGROUND         0xFAFAFA
#define STANDARD_FOOTER_BACKGROUND     0xFAFAFA
#define INSTRUCTIONS_FOOTER_BACKGROUND 0xB84B19
#define FREE_CELL_COLOR                0xb9ccb1
#define WALL_CELL_COLOR                0x3b3b3b
#define START_POSITION_COLOR           0xFF0000
#define END_POSITION_COLOR             0x00FF00
#define HP_FULL_COLOR                  0Xd60000
#define HP_EMPTY_COLOR                 0x5c0000
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
#define XPM_EXPLORER                   "./assets/sprites/explorer.xpm"
#define XPM_MINOTAUR                   "./assets/sprites/minotaur.xpm"
#endif
