/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:08:02 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/03 23:27:22 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_data*	rcdda(t_cube *cube, char **map, t_player player)
{
	t_data			*screen = 0;
	t_point			delta_dist;
	t_point			side_dist;
	t_point			ray_dir;
	t_point			step;
	t_point			plane;
	t_point			dest;
	double			cameraX;
	double			perp_wall_dist;
	int				x;
	int				y;
	int				hit = 0;
	int				side = 0;
	int				line_height = 0;
	int				pitch = 0;
	int				draw_start = 0;
	int				draw_end = 0;
	double			wall_x = 0;
	double			step_f = 0;
	int				tex_num = 0;
	int				tex_x = 0;
	int				tex_y = 0;
	double			tex_pos = 0;
	double			tex_width;
	double			tex_height;
	unsigned int	color = 0;

	screen = malloc(sizeof(t_data));
	screen->img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	screen->addr = mlx_get_data_addr(screen->img, &screen->bits_per_pixel, &screen->line_length, &screen->endian);
	plane.x = -0.66 * player.dir.y;
	plane.y = -0.66 * player.dir.x;
	x = -1;
	tex_height = 128;
	tex_width = 128;
	while (++x < WIN_WIDTH)
	{
		cameraX = 2 * x / ((double)WIN_WIDTH) - 1;
		ray_dir.x = player.dir.x + plane.x * (cameraX);
    	ray_dir.y = player.dir.y + plane.y * (cameraX);
		if (ray_dir.x)
			delta_dist.x = fabs(1 / ray_dir.x);
		else
			delta_dist.x = 1e30;
		if (ray_dir.y)
			delta_dist.y = fabs(1 / ray_dir.y);
		else
			delta_dist.x = 1e30;
		dest = (t_point){(int)player.pos.x, (int)player.pos.y};
		if(ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (player.pos.x - dest.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (dest.x + 1.0 - player.pos.x) * delta_dist.x;
		}
		if(ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (player.pos.y - dest.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (dest.y + 1.0 - player.pos.y) * delta_dist.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if(side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				dest.x += step.x;
				if (step.x > 0)
					side = 2;
				else
					side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				dest.y += step.y;
				if (step.y > 0)
					side = 3;
				else
					side = 1;
			}
			if(map[(int)dest.y][(int)dest.x] == '1')
				hit = 1;
		}
		if(side == 0 || side == 2)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		pitch = 100;
		draw_start = -line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if(draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		tex_num = side;
		if(side == 0 || side == 2)
			wall_x = player.pos.x + perp_wall_dist * ray_dir.y;
		else
			wall_x = player.pos.y + perp_wall_dist * ray_dir.x;
		// else if (side == 2)
		// 	wall_x = player.pos.x - perp_wall_dist * ray_dir.y;
		// else if (side == 3)
		// 	wall_x = player.pos.y - perp_wall_dist * ray_dir.x;
		wall_x -= floor((wall_x));
		tex_x = (int)(wall_x * (cube->texture[side].width));
		if((side == 0 || side == 2) && ray_dir.x > 0)
			tex_x = cube->texture[side].width - tex_x - 1;
		if((side == 1 || side == 3) && ray_dir.y < 0)
			tex_x = cube->texture[side].width - tex_x - 1;
		step_f = 1 * cube->texture[side].height / line_height;
		tex_pos = (draw_start - pitch - WIN_HEIGHT / 2 + line_height / 2) * (step_f);
		y = draw_start - 1;
		while(++y < draw_end)
		{
			tex_y = (int)tex_pos & (int)(cube->texture[side].height - 1);
			tex_pos += step_f;
			//printf("tex pos == %f; stepf == %f\n", tex_pos, step_f);
			color = *((unsigned int*)cube->texture[side].addr+(int)((((cube->texture[side].height) * tex_y + tex_x))));
			// if(side == 0)
			// 	color = *((unsigned int*)cube->texture[side].addr+(int)((((tex_height) * tex_y + tex_x))));
			my_mlx_pixel_put(screen, x, y, color);
		}
	}
	mlx_put_image_to_window(cube->mlx, cube->win, screen->img, 0, 0);
	return screen;
}
// par side ne fonctionne pas, il n'y a pas de reperes lorsqu'on mets les textures pour changer de texture au bon moments