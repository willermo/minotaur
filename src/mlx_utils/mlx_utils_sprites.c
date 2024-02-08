/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:09:05 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 17:10:58 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static unsigned int
get_pixel(t_image *img, t_point pos) {
    unsigned int color;
    char *pixel;
    int i;

    i = img->bits_per_pixel - 8;
    pixel = img->addr +
            (pos.y * img->line_length + pos.x * (img->bits_per_pixel / 8));
    color = 0;
    while (i >= 0) {
        color = (color << 8) + (unsigned char) *pixel;
        pixel++;
        i -= 8;
    }
    return (color);
}

void
apply_sprite_to_image(t_image *img, t_image *sprite, t_point pos) {
    int row;
    int col;
    int x;
    int y;

    row = 0;
    while (row < sprite->height) {
        col = 0;
        while (col < sprite->width) {
            x = pos.x + col;
            y = pos.y + row;
            if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
                draw_pixel(img, (t_point){x, y},
                           get_pixel(sprite, (t_point){col, row}));
            }
            col++;
        }
        row++;
    }
}
