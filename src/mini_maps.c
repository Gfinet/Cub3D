/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:05:21 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 16:18:03 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_border(int x, int y)
{
	if (x == 0 || y == 0 || x - 1 == 0 || y - 1 == 0)
		return (1);
	else if (x + 1 == WIN_HEIGHT / 5 || y + 1 == WIN_WIDTH / 5)
		return (1);
	else if (x + 2 == WIN_HEIGHT / 5 || y + 2 == WIN_WIDTH / 5)
		return (1);
	else
		return (0);
}

void	draw_background(t_cube *cube, t_maps *lvl)
{
	int		i;
	int		j;
	t_data	*im;

	i = -1;
	im = &lvl->mini.maps;
	im->img = mlx_new_image(cube->mlx,
			WIN_WIDTH / 5, WIN_HEIGHT / 5);
	im->addr = mlx_get_data_addr(im->img,
			&im->bits_per_pixel, &im->line_length, &im->endian);
	while (++i < WIN_HEIGHT / 5)
	{
		j = -1;
		while (++j < WIN_WIDTH / 5)
		{
			if (is_border(i, j))
				my_mlx_pixel_put(im, j, i, 0x00FFFFFF);
			else
				my_mlx_pixel_put(im, j, i, 0x000000FF);
		}
	}
}

int	*get_ind(int i[2], int w_h[2], t_maps *lvl)
{
	int	bf;
	int	af;
	int	coef[2];

	coef[0] = WIN_HEIGHT / 5 / lvl->mini.height;
	coef[1] = WIN_WIDTH / 5 / lvl->mini.witdh;
	af = 1;
	bf = 0;
	while (!(bf * coef[0] <= i[0] && i[0] < af * coef[0]))
	{
		bf++;
		af++;
	}
	w_h[0] = bf;
	af = 1;
	bf = 0;
	while (!(bf * coef[1] <= i[1] && i[1] < af * coef[1]))
	{
		bf++;
		af++;
	}
	w_h[1] = bf;
	return (w_h);
}

void	draw_maps(t_maps *lvl)
{
	int	i[2];
	int	w_h[2];

	i[0] = -1;
	while (++i[0] < WIN_HEIGHT / 5)
	{
		i[1] = -1;
		while (++i[1] < WIN_WIDTH / 5)
		{
			get_ind(i, w_h, lvl);
			if (w_h[0] < lvl->mini.height - 2)
			{
				if (w_h[1] < lvl->max_len)
					draw_mini_pixel(lvl, w_h, i);
			}
		}
	}
}

int	make_mini(t_cube *cube, t_maps *lvl)
{
	lvl->mini.witdh = lvl->max_len + 1;
	lvl->mini.height = lvl->m_height + 2;
	draw_background(cube, lvl);
	draw_maps(lvl);
	return (1);
}
