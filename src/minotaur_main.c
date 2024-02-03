/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:21 by doriani           #+#    #+#             */
/*   Updated: 2024/02/03 21:01:42 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_game *game;

static void
logger(char *msg) {
    if (VERBOSE)
        ft_printf(TY_BLUE_B "%s\n" TY_RESET, msg);
}

int
main() {
    srand(time(NULL));

    logger("Initializing minotaur");
    init_game();
    logger("Starting minotaur");
    start_game();
    logger("Closing minotaur");
    end_game();
    logger("Cleaning minotaur");
    clean_game();
    logger("Exiting minotaur");
    return (0);
}
