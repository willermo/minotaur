/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minotaur_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:21 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 21:16:00 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minotaur.h"

t_game *game;

static int
validate_command(int argc, char **argv) {
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "random"))) {
        ft_printf("Usage: ./minotaur [random]\n");
        exit(1);
    }
    return (argc == 2);
}

static void
logger(char *msg) {
    if (VERBOSE)
        ft_printf(TY_BLUE_B "%s\n" TY_RESET, msg);
}

int
main(int argc, char **argv) {
    int random = validate_command(argc, argv);
    srand(time(NULL));

    logger("Initializing minotaur");
    init_game(random);
    logger("Starting minotaur");
    start_game();
    logger("Closing minotaur");
    end_game();
    logger("Cleaning minotaur");
    clean_game();
    logger("Exiting minotaur");
    return (0);
}
