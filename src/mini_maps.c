/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:05:21 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/01 22:50:32 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void get_width_height(t_maps *lvl)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (i < lvl->m_height)
	{
		if (ft_strlen(lvl->maps[i]) > (size_t)max)
			max = ft_strlen(lvl->maps[i]);
		i++;
	}
	lvl->mini.witdh = max + 2;
	lvl->mini.height = lvl->m_height + 2;
}

void draw_background(t_cube *cube, t_maps *lvl)
{
	int i;
	int j;
	int color;
	t_data *im;

	color = (lvl->floor[0] << 16) + (lvl->floor[1] << 8) + lvl->floor[2];

	i = -1;
	im = &lvl->mini.m_maps;
	get_width_height(lvl);
	printf("%p %p \n", im, &lvl->mini.m_maps);
	im->img = mlx_new_image(cube->mlx,
		lvl->mini.witdh * WIN_WIDTH / 10,lvl->mini.height * WIN_HEIGHT / 10);
	im->addr = mlx_get_data_addr(im->img,
		&im->bits_per_pixel, &im->line_length, &im->endian);
	while (++i < WIN_HEIGHT / 5)
	{
		j = -1;
		while (++j < WIN_WIDTH / 5)
			my_mlx_pixel_put(im, j, i, color);
	}
}

void draw_maps(t_cube *cube, t_maps *lvl)
{
	
}

int make_mini(t_cube *cube, t_maps *lvl)
{
	draw_background(cube, lvl);
	draw_maps(cube, lvl);
	mlx_put_image_to_window(cube->mlx, cube->win, lvl->mini.m_maps.img, 0, 0);
	return (1);
}
