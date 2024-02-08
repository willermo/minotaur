/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:58:07 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 11:32:52 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_utils.h"
#include <stdlib.h>

void
init_system(t_display *display, int width, int height, char *title) {
    display->mlx = mlx_init();
    display->win = mlx_new_window(display->mlx, width, height, title);
}

void
shutdown_system(t_display *display) {
    mlx_clear_window(display->mlx, display->win);
    mlx_destroy_window(display->mlx, display->win);
    mlx_destroy_display(display->mlx);
    free(display->mlx);
}

int
get_endianness(void) {
    int i;
    char *str;

    i = 1;
    str = (char *) &i;
    if (*str)
        return (LE);
    else
        return (BE);
}
