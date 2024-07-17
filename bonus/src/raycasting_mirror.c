/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_mirror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:12:10 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/17 18:49:57 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	draw_mirr_frame(t_data *screen, t_drawdata dt, int x, t_rcdata data)
{
	static int	ds[2];
	static int	de[2];
	int			*tab;
	int			i;

	ds[1] = dt.draw_start;
	de[1] = dt.draw_end;
	dt.line_height = (int)(WIN_HEIGHT / data.m_perp_wall_dist);
	ds[0] = -dt.line_height / 2 + WIN_HEIGHT / 2 + 100;
	de[0] = dt.line_height / 2 + WIN_HEIGHT / 2 + 100;
	ds[0] = ds[0] * (ds[0] > 0) + (WIN_HEIGHT - 1) * (ds[0] >= WIN_HEIGHT);
	de[0] = (de[0] * (de[0] < WIN_HEIGHT)) + ((WIN_HEIGHT - 1) * (de[0]
				>= WIN_HEIGHT));
	tab = (int [8]){ds[0], ds[0] + 1, ds[0] + 2, ds[1], de[1], de[0],
		de[0] - 1, de[0] - 2};
	i = -1;
	while (++i < 8)
	{
		if (i == 4 || i == 3)
			my_mlx_pixel_put(screen, x, tab[i], 0x55C0C0C0);
		else
			my_mlx_pixel_put(screen, x, tab[i], 0x55808080);
	}
}

void	update_mirror(t_rcdata *data, char **map)
{
	if (map[(int)data->dest.y][(int)data->dest.x] != '2')
		return ;
	if (data->hit != 2)
	{
		(*data).p_dest = (t_point){data->dest.x, data->dest.y};
		(*data).side_dist_m = (t_point){data->side_dist.x, data->side_dist.y};
		calculate_perp_wall_dist(data, 1);
	}
	else
		return ;
	(*data).hit = 2;
	(*data).step.x *= (1 - (data->side == 0 || data->side == 2) * 2);
	(*data).step.y *= (1 - (data->side == 1 || data->side == 3) * 2);
}
