/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:09:05 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 18:40:15 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

// static int
// get_pixel(t_image *img, t_point pos) {
//     int color;
//     char *pixel;
//     int i;

//     i = img->bits_per_pixel - 8;
//     pixel = img->addr +
//             (pos.y * img->line_length + pos.x * (img->bits_per_pixel / 8));
//     color = 0;
//     while (i >= 0) {
//         color = (color << 8) + *pixel;
//         pixel++;
//         i -= 8;
//     }
//     return (color);
//     return (*(int *) pixel);
// }

void
apply_sprite_to_image(t_image *img, t_image *sprite, t_point pos) {
    int row;
    int col;
    t_point pixel;

    row = 0;
    while (row < sprite->height) {
        col = 0;
        while (col < sprite->width) {
            pixel = (t_point){pos.x + col, pos.y + row};
            if (pixel.x >= 0 && pixel.x < img->width && pixel.y >= 0 &&
                pixel.y < img->height) {
                draw_pixel(img, pixel, get_pixel_color(sprite, col, row));
            }
            col++;
        }
        row++;
    }
}
