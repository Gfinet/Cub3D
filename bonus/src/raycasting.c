/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:08:02 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/17 18:49:09 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	calculate_perp_wall_dist(t_rcdata *data, int mirr)
{
	if (!mirr)
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
	else
	{
		if (data->side == 0)
			(*data).m_perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
		else if (data->side == 2)
			(*data).m_perp_wall_dist = (data->side_dist.x - data->delta_dist.x);
		else if (data->side == 1)
			(*data).m_perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
		else if (data->side == 3)
			(*data).m_perp_wall_dist = (data->side_dist.y - data->delta_dist.y);
	}
}

static double	fix_texture_pos(t_rcdata dt, t_player pl)
{
	double	fix_x;
	double	garb;

	fix_x = 0;
	if (dt.side == 0 || dt.side == 2)
		fix_x = modf(pl.pos.y, &garb);
	else
		fix_x = modf(pl.pos.x, &garb);
	if ((pl.prev_pos.y != pl.pos.y) && (dt.side == 0 || dt.side == 2))
		fix_x = modf(pl.pos.y, &garb);
	else if ((pl.prev_pos.x != pl.pos.x) && (dt.side == 1 || dt.side == 3))
		fix_x = modf(pl.pos.x, &garb);
	else if ((pl.prev_pos.x != pl.pos.x) && (dt.side == 0 || dt.side == 2))
		fix_x = modf(pl.pos.y, &garb);
	else if ((pl.prev_pos.y != pl.pos.y) && (dt.side == 1 || dt.side == 3))
		fix_x = modf(pl.pos.x, &garb);
	return (fix_x);
}

static void	get_base_info_draw(t_drawdata *dr, t_rcdata dt, t_player player,
		t_cube *cube)
{
	double	fix_x;

	fix_x = fix_texture_pos(dt, player);
	(*dr).line_height = (int)(WIN_HEIGHT / dt.perp_wall_dist);
	(*dr).pitch = 100;
	(*dr).draw_start = -dr->line_height / 2 + WIN_HEIGHT / 2 + dr->pitch;
	if (dr->draw_start < 0)
		(*dr).draw_start = 0;
	(*dr).draw_end = dr->line_height / 2 + WIN_HEIGHT / 2 + dr->pitch;
	if (dr->draw_end >= WIN_HEIGHT)
		(*dr).draw_end = WIN_HEIGHT - 1;
	(*dr).tex_num = dt.side;
	if (dt.side == 0 || dt.side == 2)
		(*dr).wall_x = (int)player.pos.x + dt.perp_wall_dist * dt.ray_dir.y;
	else if (dt.side == 1 || dt.side == 3)
		(*dr).wall_x = (int)player.pos.y + dt.perp_wall_dist * dt.ray_dir.x;
	(*dr).wall_x += fix_x;
	(*dr).wall_x -= floor((dr->wall_x));
	(*dr).tex_x = (int)((dr->wall_x) * (double)(cube->texture[dt.side].width));
	if ((dt.side == 0 || dt.side == 2) && dt.ray_dir.x > 0)
		(*dr).tex_x = cube->texture[dt.side].width - dr->tex_x - 1;
	if ((dt.side == 1 || dt.side == 3) && dt.ray_dir.y < 0)
		(*dr).tex_x = cube->texture[dt.side].width - dr->tex_x - 1;
	(*dr).step_f = 1.0 * cube->texture[dt.side].height / dr->line_height;
}

static void	draw_xwall(t_data *screen, t_drawdata *dt, t_cube *c, int x)
{
	int				y;
	unsigned int	col;

	dt->tex_pos = (dt->draw_start - dt->pitch - WIN_HEIGHT / 2 + dt->line_height
			/ 2) * dt->step_f;
	y = -1;
	col = c->lvl->floor[0] * 65536 + c->lvl->floor[1] * 256 + c->lvl->floor[2];
	if (dt->draw_start > WIN_HEIGHT)
		dt->draw_start = 0;
	while (++y < dt->draw_start)
		my_mlx_pixel_put(screen, x, y, col);
	y = dt->draw_start - 1;
	while (++y < dt->draw_end)
	{
		(*dt).tex_y = (int)dt->tex_pos & (c->texture[dt->tex_num].height - 1);
		dt->tex_pos += dt->step_f;
		col = *((unsigned int *)c->texture[dt->tex_num].addr +(int)
				((c->texture[dt->tex_num].height * dt->tex_y + dt->tex_x)));
		if (dt->mirr)
			col += 0x33000000;
		my_mlx_pixel_put(screen, x, y, col);
	}
	col = c->lvl->ceil[0] * 65536 + c->lvl->ceil[1] * 256 + c->lvl->ceil[2];
	while (++y <= WIN_HEIGHT)
		my_mlx_pixel_put(screen, x, y - 1, col);
}

void	rcdda(t_cube *cb, char **map, t_player player)
{
	t_rcdata	data;
	t_drawdata	drawdata;
	int			x;

	data.plane = (t_point){-1 * (0.66 * player.dir.y), (0.66 * player.dir.x)};
	x = -1;
	while (++x < WIN_WIDTH)
	{
		drawdata.mirr = 0;
		data.p_dest = (t_point){0};
		set_dda_ray_delta(&data, player, x);
		set_side_dist_and_step(player, &data);
		calculate_wall_dist(&data, map);
		if (data.p_dest.x && !drawdata.mirr)
			drawdata.mirr = 1;
		calculate_perp_wall_dist(&data, 0);
		get_base_info_draw(&drawdata, data, player, cb);
		draw_xwall(cb->screen, &drawdata, cb, x);
		if (drawdata.mirr)
			draw_mirr_frame(cb->screen, drawdata, x, data);
	}
	cb->screen->addr = mlx_get_data_addr(cb->screen->img,
			&cb->screen->bits_per_pixel, &cb->screen->line_length,
			&cb->screen->endian);
	mlx_put_image_to_window(cb->mlx, cb->win, cb->screen->img, 0, 0);
}
