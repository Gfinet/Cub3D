/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:03:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 20:20:05 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

	x = i[1] + WIN_WIDTH / 5 / (lvl->max_len - 1);
	y = i[0] + WIN_HEIGHT / 5 / (lvl->m_height + 1);
	if (lvl->c_maps[w_h[0]][w_h[1]] == '1')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x00FFFFFF);
	if (lvl->c_maps[w_h[0]][w_h[1]] == '0')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x5500FF00);
	if (lvl->c_maps[w_h[0]][w_h[1]] == 'N')
		my_mlx_pixel_put(&lvl->mini.maps, x, y, 0x00FF0000);
}
