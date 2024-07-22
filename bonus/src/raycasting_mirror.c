/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_mirror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:12:10 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/22 17:10:16 by lvodak           ###   ########.fr       */
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

void	draw_door(t_data *screen, int x, t_rcdata data, t_cube *c)
{
	unsigned int	col;
	t_drawdata		dt;

	dt.line_height = (int)(WIN_HEIGHT / data.d_perp_wall_dist);
	dt.draw_start = -dt.line_height / 2 + WIN_HEIGHT / 2 + 100;
	dt.draw_end = dt.line_height / 2 + WIN_HEIGHT / 2 + 100;
	data.side = data.d_side;
	pick_texture(&dt, data, c, 1);
	if (dt.draw_start < 0)
		(dt).draw_start = 0;
	if (dt.draw_end >= WIN_HEIGHT)
		(dt).draw_end = WIN_HEIGHT - 1;
	if (data.d_side == 0 || data.d_side == 2)
		(dt).wall_x = (int)c->player->pos.x + data.d_perp_wall_dist * data.ray_dir.y;
	else if (data.d_side == 1 || data.d_side == 3)
		(dt).wall_x = (int)c->player->pos.y + data.d_perp_wall_dist * data.ray_dir.x;
	(dt).wall_x += fix_texture_pos(data, *c->player);;
	(dt).wall_x -= floor((dt.wall_x));
	(dt).tex_x = (int)((dt.wall_x) * (double)(dt.texture.width));
	if ((data.d_side == 0 || data.d_side == 2) && data.ray_dir.x > 0)
		(dt).tex_x = dt.texture.width - dt.tex_x - 1;
	if ((data.d_side == 1 || data.d_side == 3) && data.ray_dir.y < 0)
		(dt).tex_x = dt.texture.width - dt.tex_x - 1;
	(dt).step_f = 1.0 * dt.texture.height / dt.line_height;
	dt.tex_pos = (dt.draw_start - 100 - WIN_HEIGHT / 2 + dt.line_height
			/ 2) * dt.step_f;
	while (++dt.draw_start < dt.draw_end)
	{
		(dt).tex_y = (int)dt.tex_pos & (dt.texture.height - 1);
		dt.tex_pos += dt.step_f;
		col = *((unsigned int *)dt.texture.addr +(int)
				((dt.texture.height * dt.tex_y + dt.tex_x)));
		// printf("%x\n", col);
		if (col)
			my_mlx_pixel_put(screen, x, dt.draw_start, col);
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
