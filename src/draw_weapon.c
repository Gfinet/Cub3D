/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:26:20 by Gfinet            #+#    #+#             */
/*   Updated: 2024/07/25 13:42:11 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_weapons(t_cube *cube)
{
	int			n_w_h[2];
	static int	i = 1;
	static int	fps = 0;
	t_weapon	*weap;

	weap = &cube->lvl->weap;
	n_w_h[0] = (WIN_WIDTH - weap->sprites[i].width) / 2;
	n_w_h[1] = WIN_HEIGHT - weap->sprites[i].height;
	mlx_put_image_to_window(cube->mlx, cube->win,
		weap->sprites[i].img, n_w_h[0], n_w_h[1]);
	fps++;
	if (fps == cube->frame)
		i++;
	i %= ((int)ft_strlen((char *)weap->path) - 1);
	fps %= cube->frame;
}

int	xpm_to_img(t_cube *cube, t_data *new_img, char *name)
{
	new_img->img = mlx_xpm_file_to_image(cube->mlx, name,
			&new_img->width, &new_img->height);
	if (!new_img->img)
		return (0);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bits_per_pixel,
			&new_img->line_length, &new_img->endian);
	return (1);
}
