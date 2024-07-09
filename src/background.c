/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:28:02 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/09 21:38:15 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_background(t_cube *cube, int floor[3], int ceiling[3])
{
	int i;
	int j;
	int color[2];
	t_data *bg;

	bg = cube->bg;
	i = -1;
	color[0] = floor[0] * 256 + floor[1] * 16 + floor[2] + 0x55000000;
	color[1] = ceiling[0] * 256 + ceiling[1] * 16 + floor[2] + 0x55000000;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				my_mlx_pixel_put(bg, j, i, color[1]);
			else
				my_mlx_pixel_put(bg, j, i, color[0]);
		}
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->bg->img, 0, 0);
}

void make_background(t_cube *cube)
{
	cube->bg->img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	cube->bg->addr = mlx_get_data_addr(cube->bg->img, &cube->bg->bits_per_pixel,
		&cube->bg->line_length, &cube->bg->endian);
	draw_background(cube, cube->lvl->floor, cube->lvl->ceil);
}