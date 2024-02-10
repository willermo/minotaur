/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_images_scaling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:40:03 by doriani           #+#    #+#             */
/*   Updated: 2024/02/10 12:35:37 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include <stdlib.h>
#define EPSILON 0.0001f

static float
cubic_interpolate(float v[4], float x) {
    return v[1] + 0.5 * x *
                      (v[2] - v[0] +
                       2.0 * x *
                           (2.0 * v[0] - 5.0 * v[1] + 4.0 * v[2] - v[3] +
                            x * (3.0 * (v[1] - v[2]) + v[3] - v[0])));
}

static float
bicubic_interpolate(float pixels[4][4], float x, float y) {
    float arr[4];
    arr[0] = cubic_interpolate(pixels[0], y);
    arr[1] = cubic_interpolate(pixels[1], y);
    arr[2] = cubic_interpolate(pixels[2], y);
    arr[3] = cubic_interpolate(pixels[3], y);
    return cubic_interpolate(arr, x);
}

void
interpolate_pixels_bicubic(t_image *src, t_image *dst, int x, int y) {
    float src_x = ((float) x * src->width) / dst->width;
    float src_y = ((float) y * src->height) / dst->height;
    int x1 = (int) src_x;
    int y1 = (int) src_y;
    //  Bicubic interpolation requires 16 pixels, so we need to get the pixels
    //  around (x1, y1)
    float pixels[4][4];
    for (int dy = -1; dy <= 2; ++dy) {
        for (int dx = -1; dx <= 2; ++dx) {
            int x = x1 + dx;
            int y = y1 + dy;
            // Clamp x and y to the image bounds
            x = x < 0 ? 0 : x >= src->width ? src->width - 1 : x;
            y = y < 0 ? 0 : y >= src->height ? src->height - 1 : y;
            pixels[dy + 1][dx + 1] =
                *(int *) (src->addr + (y * src->line_length + x * 4));
        }
    }

    int interpolated = bicubic_interpolate(pixels, src_x - x1, src_y - y1);

    *(int *) (dst->addr + (y * dst->line_length + x * 4)) = interpolated;
}

void
interpolate_pixels_bilinear(t_image *src, t_image *dst, int x, int y) {
    float src_x = ((float) x * src->width) / dst->width;
    float src_y = ((float) y * src->height) / dst->height;
    int x1 = (int) src_x;
    int y1 = (int) src_y;
    int x2 = x1 + 1 < src->width ? x1 + 1 : x1;
    int y2 = y1 + 1 < src->height ? y1 + 1 : y1;

    int q11 = *(int *) (src->addr + (y1 * src->line_length + x1 * 4));
    int q12 = *(int *) (src->addr + (y2 * src->line_length + x1 * 4));
    int q21 = *(int *) (src->addr + (y1 * src->line_length + x2 * 4));
    int q22 = *(int *) (src->addr + (y2 * src->line_length + x2 * 4));

    float r1 = ((x2 - src_x) * q11 + (src_x - x1) * q21) / (x2 - x1);
    float r2 = ((x2 - src_x) * q12 + (src_x - x1) * q22) / (x2 - x1);

    int interpolated =
        (int) ((y2 - src_y + EPSILON) * r1 + (src_y - y1 + EPSILON) * r2) /
        (y2 - y1 + 2 * EPSILON);

    *(int *) (dst->addr + (y * dst->line_length + x * 4)) = interpolated;
}

void
interpolate_pixels_nearest_neighbour(t_image *src, t_image *dst, int x, int y) {
    int src_x;
    int src_y;
    int dst_x;
    int dst_y;

    src_x = (x * src->width) / dst->width;
    src_y = (y * src->height) / dst->height;
    dst_x = x;
    dst_y = y;
    *(int *) (dst->addr + (dst_y * dst->line_length + dst_x * 4)) =
        *(int *) (src->addr + (src_y * src->line_length + src_x * 4));
}

void
rescale_image(t_display *display, t_image *image, int width, int height,
              t_rescale_algorithm method) {
    t_image *rescaled;

    if (image->width == width && image->height == height)
        return;
    rescaled = create_image(display, width, height);
    for (int y = 0; y < rescaled->height; y++)
        for (int x = 0; x < rescaled->width; x++)
            switch (method) {
            case NEAREST_NEIGHBOUR:
                interpolate_pixels_nearest_neighbour(image, rescaled, x, y);
                break;
            case BILINEAR:
                interpolate_pixels_bilinear(image, rescaled, x, y);
                break;
            case BICUBIC:
                interpolate_pixels_bicubic(image, rescaled, x, y);
                break;
            }
    destroy_image(display, image);
    substitute_images(image, rescaled);
    free(rescaled);
}
