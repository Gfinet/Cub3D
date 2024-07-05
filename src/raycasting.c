/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:08:02 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/05 23:53:30 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_base_rcdda(t_cube *cube, t_data *screen, t_rcdata *data,
	t_player player)
{
	(*screen).img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	(*screen).addr = mlx_get_data_addr((*screen).img, &(*screen).bits_per_pixel,
			&(*screen).line_length, &(*screen).endian);
	(*data).plane.x = -(float)(0.66 * player.dir.y);
	(*data).plane.y = (float)(0.66 * player.dir.x);
}

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

void	calculate_perp_wall_dist(t_rcdata *data)
{
	if (data->side == 0)
		(*data).perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
	else if (data->side == 2)
		(*data).perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
	else if (data->side == 1)
		(*data).perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
	else if (data->side == 3)
		(*data).perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
}

double	fix_texture_pos(t_rcdata dt, t_player pl)
{
	double	fix_x;

	fix_x = 0;
	if (fabs(pl.dir.x) < fabs(pl.dir.y) && (dt.side == 0 || dt.side == 2))
		fix_x = fabs(pl.pos.y - (int)pl.pos.y);
	else if (fabs(pl.dir.x) < fabs(pl.dir.y) && (dt.side == 1 || dt.side == 3))
		fix_x = fabs(pl.pos.x - (int)pl.pos.x);
	if ((pl.prev_pos.x != pl.pos.x) && (dt.side == 1 || dt.side == 3))
		fix_x = fabs(pl.pos.x - (int)pl.pos.x);
	else if ((pl.prev_pos.y != pl.pos.y) && (dt.side == 0 || dt.side == 2))
		fix_x = fabs(pl.pos.y - (int)pl.pos.y);
	return (fix_x);
}

void	get_base_info_draw(t_drawdata *drw, t_rcdata dt, t_player player,
		t_cube *cube)
{
	double fix_x;

	fix_x = fix_texture_pos(dt, player);
	(*drw).line_height = (int)(WIN_HEIGHT / dt.perp_wall_dist);
	(*drw).pitch = 100;
	(*drw).draw_start = -drw->line_height / 2 + WIN_HEIGHT / 2 + drw->pitch;
	if (drw->draw_start < 0)
		(*drw).draw_start = 0;
	(*drw).draw_end = drw->line_height / 2 + WIN_HEIGHT / 2 + drw->pitch;
	if (drw->draw_end >= WIN_HEIGHT)
		(*drw).draw_end = WIN_HEIGHT - 1;
	(*drw).tex_num = dt.side;
	if (dt.side == 0 || dt.side == 2)
		(*drw).wall_x = (int)player.pos.x + dt.perp_wall_dist * dt.ray_dir.y;
	else if (dt.side == 1 || dt.side == 3)
		(*drw).wall_x = (int)player.pos.y + dt.perp_wall_dist * dt.ray_dir.x;
	(*drw).wall_x += fix_x;
	(*drw).wall_x -= floor((drw->wall_x));
	(*drw).tex_x = (int)((drw->wall_x) * (double)(cube->texture[dt.side].width));
	if ((dt.side == 0 || dt.side == 2) && dt.ray_dir.x > 0)
		(*drw).tex_x = cube->texture[dt.side].width - drw->tex_x - 1;
	if ((dt.side == 1 || dt.side == 3) && dt.ray_dir.y < 0)
		(*drw).tex_x = cube->texture[dt.side].width - drw->tex_x - 1;
	(*drw).step_f = 1.0 * cube->texture[dt.side].height / drw->line_height;
}

void	draw_xwall(t_data *screen, t_drawdata *dt, t_cube *c, int x)
{
	int				y;
	unsigned int	color;
	double			tex_pos;

	tex_pos = (dt->draw_start - dt->pitch - WIN_HEIGHT / 2 + dt->line_height
			/ 2) * dt->step_f;
	y = dt->draw_start - 1;
	while (++y < dt->draw_end)
	{
		(*dt).tex_y = (int)tex_pos & (c->texture[dt->tex_num].height - 1);
		tex_pos += dt->step_f;
		color = *((unsigned int *)c->texture[dt->tex_num].addr +(int)
				((c->texture[dt->tex_num].height * dt->tex_y + dt->tex_x)));
		my_mlx_pixel_put(screen, x, y, color);
	}
}

void	rcdda(t_cube *cube, char **map, t_player player)
{
	t_data		screen;
	t_rcdata	data;
	t_drawdata	drawdata;
	int			x;

	set_base_rcdda(cube, &screen, &data, player);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		set_dda_ray_delta(&data, player, x);
		set_side_dist_and_step(player, &data);
		calculate_wall_dist(&data, map);
		calculate_perp_wall_dist(&data);
		get_base_info_draw(&drawdata, data, player, cube);
		drawdata.tex_num = data.side;
		draw_xwall(&screen, &drawdata, cube, x);
	}
	screen.addr = mlx_get_data_addr(screen.img, &screen.bits_per_pixel, &screen.line_length, &screen.endian);
	mlx_put_image_to_window(cube->mlx, cube->win, screen.img, 0, 0);
	// if (cube->screen)
	// 	mlx_destroy_image(cube->mlx, cube->screen->img);
	(*cube).screen = &screen;
}
