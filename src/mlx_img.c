/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:03:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 16:47:08 by Gfinet           ###   ########.fr       */
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
		while (++j < lvl->max_len - 1)
		{
			ch = lvl->c_maps[i][j];
			if (ch != '0' && ch != '1'
				&& ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
				lvl->c_maps[i][j] = c;
			printf("%c", lvl->c_maps[i][j]);
		}
		printf("\n");
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_mini_pixel(t_maps *lvl, int w_h[2], int i[2])
{
	int	x;
	int	y;

	x = i[1] + WIN_WIDTH / 5 / (lvl->mini.witdh);
	y = i[0] + WIN_HEIGHT / 5 / (lvl->mini.height);
	if (lvl->c_maps[w_h[0]][w_h[1]] == '1')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x00FFFFFF);
	if (lvl->c_maps[w_h[0]][w_h[1]] == '0')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x5500FF00);
	if (lvl->c_maps[w_h[0]][w_h[1]] == 'N')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x00FF0000);
}
