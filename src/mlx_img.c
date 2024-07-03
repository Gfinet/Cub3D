/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:03:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/04 00:38:07 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void fill_map_char(t_maps *lvl, char c)
{
	int i;
	int j;
	char ch;
	i = -1;
	printf("filling %d %d\n", lvl->m_height, lvl->max_len);
	while (++i < lvl->m_height)
	{
		j = -1;
		while (++j < lvl->max_len)
		{
			ch = lvl->c_maps[i][j];
			if (ch != '0' && ch != '1'
				&& ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
				lvl->c_maps[i][j] = c;
			if (j == lvl->max_len - 1)
				lvl->c_maps[i][j] = 0;
		}
	}
}

void	draw_mini_pixel(t_maps *lvl, int w_h[2], int i[2])
{
	int	x;
	int	y;

	x = i[1] + WIN_WIDTH / 5 / (lvl->mini.witdh);
	y = i[0] + WIN_HEIGHT / 5 / (lvl->mini.height);
	if (lvl->c_maps[w_h[0]][w_h[1]] == '1')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, WHITE);
	else if (lvl->c_maps[w_h[0]][w_h[1]] == '0')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, GREEN);
	else if (lvl->c_maps[w_h[0]][w_h[1]] == '.'
		|| lvl->c_maps[w_h[0]][w_h[1]] == 0)
		my_mlx_pixel_put(&lvl->mini.maps, x, y, BLUE);
	else
		my_mlx_pixel_put(&lvl->mini.maps, x, y, GREEN);
}

void draw_player(t_cube *cube)
{
	int x;
	int y;
	int pos[2];
	int sum[2];

	pos[0] = cube->player->pos.x;
	pos[1] = cube->player->pos.y;
	y = -1;
	sum[0] = WIN_WIDTH / 5 / (cube->lvl->mini.witdh);
	sum[1] = WIN_HEIGHT / 5 / (cube->lvl->mini.height);
	while (++y < WIN_HEIGHT / 5)
	{
		x = -1;
		while (++x < WIN_WIDTH / 5)
			if (x + sum[0] > pos[0] && x + sum[0] < pos[0] + 1
				&& y + sum[1] > pos[1] && y + sum[1] < pos[1] + 1)
				my_mlx_pixel_put(&cube->lvl->mini.maps, x, y, RED);
	}
	printf("bonjour\n");
}

void draw_doom(t_cube *cube)
{
	mlx_clear_window(cube->mlx, cube->win);
	draw_background(cube, cube->lvl->floor, cube->lvl->ceiling);
	rcdda(cube, cube->maps->c_maps, *(cube->player));
	make_mini(cube, cube->lvl);
}