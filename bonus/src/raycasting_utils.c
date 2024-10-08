/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:54:19 by lvodak            #+#    #+#             */
/*   Updated: 2024/08/31 17:29:44 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	pick_texture(t_drawdata *dr, t_rcdata dt, t_cube *cube, int door_text)
{
	t_door	*door;

	door = NULL;
	if (!door_text && cube->lvl->c_maps[(int)(dt.dest.y - dt.p_dest.y)]
			[(int)(dt.dest.x - dt.p_dest.x)] != 'D')
		(*dr).texture = cube->texture[dt.side];
	else if (!door_text && cube->lvl->c_maps[(int)(dt.dest.y - dt.p_dest.y)]
			[(int)(dt.dest.x - dt.p_dest.x)] == 'D')
		(*dr).texture = cube->door_texture[0];
	else
	{
		door = find_door(cube, dt.d_dest.x, dt.d_dest.y);
		if (door)
		{
			if (door->open == 0 || door->open == 30)
				door->on_going = 0;
			(*dr).texture = cube->door_texture[door->open / 10];
			if (door->on_going)
				door->open += door->on_going;
		}
	}
}

void	set_dda_ray_delta(t_rcdata *data, t_player player, int x)
{
	(*data).p_dest = (t_point){0};
	(*data).door = 0;
	(*data).camerx = 2 * x / ((double)WIN_WIDTH) - 1;
	(*data).ray_dir.x = player.dir.x + data->plane.x * (data->camerx);
	(*data).ray_dir.y = player.dir.y + data->plane.y * (data->camerx);
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

void	check_hit_target(t_rcdata *dt, char **map)
{
	if (map[(int)dt->dest.y][(int)dt->dest.x] == '1'
		|| map[(int)dt->dest.y][(int)dt->dest.x] == ' '
		|| map[(int)dt->dest.y][(int)dt->dest.x] == '.'
		|| (map[(int)dt->dest.y][(int)dt->dest.x] == '2'
		&& (dt->hit == 2 || dt->hit == 5)))
		(*dt).hit = 1;
	else if (map[(int)dt->dest.y][(int)dt->dest.x] == 'D')
	{
		if (dt->hit != 3)
		{
			calculate_perp_wall_dist(dt, 2);
			(*dt).d_side = dt->side;
			(*dt).d_dest = (t_point){dt->dest.x, dt->dest.y};
			(*dt).door = 1;
		}
		(*dt).hit = 3;
	}
}

void	calculate_wall_dist(t_rcdata *dt, char **map)
{
	while (dt->hit != 1)
	{
		if (dt->side_dist.x < dt->side_dist.y)
		{
			(*dt).side_dist.x += dt->delta_dist.x;
			(*dt).dest.x += dt->step.x;
			if ((dt->step.x > 0))
				(*dt).side = 2;
			else
				(*dt).side = 0;
		}
		else if (dt->side_dist.x >= dt->side_dist.y)
		{
			(*dt).side_dist.y += dt->delta_dist.y;
			(*dt).dest.y += dt->step.y;
			if (dt->step.y > 0)
				(*dt).side = 3;
			else
				(*dt).side = 1;
		}
		check_hit_target(dt, map);
		update_mirror(dt, map);
	}
	dt->dest = (t_point){dt->dest.x + dt->p_dest.x, dt->dest.y + dt->p_dest.y};
}
