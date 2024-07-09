/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:03:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/09 19:27:56 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void get_player_pos(t_cube *cube)
{
	int i[2];
	char c;
	char **m;

	m = cube->lvl->c_maps;
	i[0] = -1;
	c = 0;
	while (++i[0] < cube->lvl->m_height && !c)
	{
		i[1] = -1;
		while (i[1]++ < cube->lvl->max_len)
		{
			if (m[i[0]][i[1]] == 'N' || m[i[0]][i[1]] == 'S'
			|| m[i[0]][i[1]] == 'E' || m[i[0]][i[1]] == 'W')
			{
				c = m[i[0]][i[1]];
				cube->player->pos = (t_point){i[1], i[0]};
				break;
			}
		}
	}
	cube->player->dir = (t_point){(c == 'E') - (c == 'W'),
		(c == 'S') - (c == 'N')};
	cube->player->prev_pos = (t_point){cube->player->pos.x, cube->player->pos.y};
	cube->player->jump = 0;
}
void fill_map_char(t_maps *lvl, char c)
{
	int i;
	int j;
	size_t len;
	char ch;
	i = -1;
	while (++i < lvl->m_height)
	{
		j = -1;
		len = ft_strlen(lvl->c_maps[i]);
		while (++j < lvl->max_len)
		{
			ch = lvl->c_maps[i][j];
			if ((ch != '0' && ch != '1'
				&& ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
				|| ( j > (int)len && j < lvl->max_len - 1))
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
		my_mlx_pixel_put(&lvl->mini.maps, x, y, WHITE + 0x55000000);
	else if (lvl->c_maps[w_h[0]][w_h[1]] == '0')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, GREEN);
	else if (lvl->c_maps[w_h[0]][w_h[1]] == '.'
		|| lvl->c_maps[w_h[0]][w_h[1]] == 0)
		my_mlx_pixel_put(&lvl->mini.maps, x, y, BLUE + 0x55000000);
	else
		my_mlx_pixel_put(&lvl->mini.maps, x, y, GREEN);
}

void draw_player(t_cube *cube)
{
	int x;
	int y;
	int pos[2];
	int sum[2];

	pos[0] = cube->player->pos.x + 1;
	pos[1] = cube->player->pos.y + 1;
	sum[0] = WIN_WIDTH / 5 / (cube->lvl->mini.witdh);
	sum[1] = WIN_HEIGHT / 5 / (cube->lvl->mini.height);
	y = -1;
	while (++y < WIN_HEIGHT / 5)
	{
		x = -1;
		while (++x < WIN_WIDTH / 5)
			if (x / sum[0] >= pos[0] && x / sum[0] < pos[0] + 1
				&& y / sum[1] >= pos[1] && y / sum[1] < pos[1] + 1)
				my_mlx_pixel_put(&cube->lvl->mini.maps, x, y, RED);
	}
}

void draw_doom(t_cube *cube)
{
	mlx_clear_window(cube->mlx, cube->win);
	rcdda(cube, cube->maps->c_maps, *(cube->player));
	draw_mini_background(cube->lvl);
	draw_maps(cube);
	draw_player(cube);
}
/*
*/