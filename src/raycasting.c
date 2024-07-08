/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:08:02 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/08 22:47:32 by lvodak           ###   ########.fr       */
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
	if (fabs(pl.dir.x) > fabs(pl.dir.y) && (dt.side == 0 || dt.side == 2))
		fix_x = fabs(pl.pos.y - (int)pl.pos.y);
	else if (fabs(pl.dir.x) < fabs(pl.dir.y))
		fix_x = fabs(pl.pos.x - (int)pl.pos.x);
	if ((pl.prev_pos.y != pl.pos.y) && (dt.side == 0 || dt.side == 2))
		fix_x = fabs(pl.pos.y - (int)pl.pos.y);
	else if ((pl.prev_pos.x != pl.pos.x) && (dt.side == 1 || dt.side == 3))
		fix_x = fabs(pl.pos.x - (int)pl.pos.x);
	else if ((pl.prev_pos.x != pl.pos.x) && (dt.side == 0 || dt.side == 2))
		fix_x = fabs(pl.pos.y - (int)pl.pos.y);
	else if ((pl.prev_pos.y != pl.pos.y) && (dt.side == 1 || dt.side == 3))
		fix_x = fabs(pl.pos.x - (int)pl.pos.x);
	// printf("%f == fix\n", fix_x);
	return (fix_x);
}

// void jump_update(t_drawdata *drw, t_cube *cube)
// {
// 	if (!cube->player->jump)
// 		return ;
// 	if (cube->player->jump < 0.5)
// 	{
// 		printf("jump == %f\n", fabs(cube->player->jump - 1) * 2 * JUMP_HEIGHT);
// 		(*drw).draw_start -= fabs(cube->player->jump - 1) * 2 * JUMP_HEIGHT;
// 		(*drw).draw_end -= fabs(cube->player->jump - 1) * 2 * JUMP_HEIGHT;
// 	}
// 	else
// 	{
// 		printf("jump == %f\n", fabs(cube->player->jump) * 2 * JUMP_HEIGHT);
// 		(*drw).draw_start += cube->player->jump * 2 *JUMP_HEIGHT;
// 		(*drw).draw_end  += cube->player->jump * 2 *JUMP_HEIGHT;
// 	}
// 	if (drw->draw_start < 0)
// 		(*drw).draw_start = 0;
// 	if (drw->draw_end >= WIN_HEIGHT)
// 		(*drw).draw_end = WIN_HEIGHT - 1;
// }

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
	// jump_update(drw, cube);
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
	y = -1;
	color = c->lvl->floor[0] * 65536 + c->lvl->floor[1] * 256 + c->lvl->floor[2];
	if (dt->draw_start > WIN_HEIGHT)
		dt->draw_start = 0;
	while (++y < dt->draw_start)
		my_mlx_pixel_put(screen, x, y, color);
	y = dt->draw_start - 1;
	while (++y < dt->draw_end)
	{
		(*dt).tex_y = (int)tex_pos & (c->texture[dt->tex_num].height - 1);
		tex_pos += dt->step_f;
		color = *((unsigned int *)c->texture[dt->tex_num].addr +(int)
				((c->texture[dt->tex_num].height * dt->tex_y + dt->tex_x)));
		my_mlx_pixel_put(screen, x, y, color);
	}
	y -= 1;
	color = c->lvl->ceiling[0] * 65536 + c->lvl->ceiling[1] * 256 + c->lvl->ceiling[2];
	while (++y < WIN_HEIGHT - 1)
		my_mlx_pixel_put(screen, x, y, color);
}

void	rcdda(t_cube *cube, char **map, t_player player)
{
	t_rcdata	data;
	t_drawdata	drawdata;
	int			x;

	data.plane.x = -(float)(0.66 * player.dir.y);
	data.plane.y = (float)(0.66 * player.dir.x);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		set_dda_ray_delta(&data, player, x);
		set_side_dist_and_step(player, &data);
		calculate_wall_dist(&data, map);
		calculate_perp_wall_dist(&data);
		get_base_info_draw(&drawdata, data, player, cube);
		drawdata.tex_num = data.side;
		draw_xwall(cube->screen, &drawdata, cube, x);
	}
	cube->screen->addr = mlx_get_data_addr(cube->screen->img, &cube->screen->bits_per_pixel, &cube->screen->line_length, &cube->screen->endian);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->screen->img, 0, 0);
}
