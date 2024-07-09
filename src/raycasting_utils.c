/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:54:19 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/09 21:54:58 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_dda_ray_delta(t_rcdata *data, t_player player, int x)
{
	(*data).cameraX = 2 * x / ((double)WIN_WIDTH) - 1;
	(*data).ray_dir.x = player.dir.x + data->plane.x * (data->cameraX);
	(*data).ray_dir.y = player.dir.y + data->plane.y * (data->cameraX);
	if (data->ray_dir.x)
		(*data).delta_dist.x = fabs(1 / data->ray_dir.x);
	else
		(*data).delta_dist.x = 1e30;
	if (data->ray_dir.y)
		(*data).delta_dist.y = fabs(1 / data->ray_dir.y);
	else
		(*data).delta_dist.x = 1e30;
	(*data).dest = (t_point){(int)player.pos.x, (int)player.pos.y};
}

void	set_side_dist_and_step(t_player p, t_rcdata *dt)
{
	if (dt->ray_dir.x < 0)
	{
		(*dt).step.x = -1;
		(*dt).side_dist.x = (p.pos.x - dt->dest.x) * dt->delta_dist.x;
	}
	else
	{
		(*dt).step.x = 1;
		(*dt).side_dist.x = (dt->dest.x + 1.0 - p.pos.x) * dt->delta_dist.x;
	}
	if (dt->ray_dir.y < 0)
	{
		(*dt).step.y = -1;
		(*dt).side_dist.y = (p.pos.y - dt->dest.y) * dt->delta_dist.y;
	}
	else
	{
		(*dt).step.y = 1;
		(*dt).side_dist.y = (dt->dest.y + 1.0 - p.pos.y) * dt->delta_dist.y;
	}
	(*dt).hit = 0;
}

void	calculate_wall_dist(t_rcdata *data, char **map)
{
	while (data->hit == 0)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			(*data).side_dist.x += data->delta_dist.x;
			(*data).dest.x += data->step.x;
			if (data->step.x > 0)
				(*data).side = 2;
			else
				(*data).side = 0;
		}
		else
		{
			(*data).side_dist.y += data->delta_dist.y;
			(*data).dest.y += data->step.y;
			if (data->step.y > 0)
				(*data).side = 3;
			else
				(*data).side = 1;
		}
		if (map[(int)data->dest.y][(int)data->dest.x] == '1')
			(*data).hit = 1;
	}
}
