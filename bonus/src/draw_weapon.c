/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:26:20 by Gfinet            #+#    #+#             */
/*   Updated: 2024/07/25 16:08:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	draw_weapons(t_cube *cube)
{
	int			n_w_h[3];
	int			u_w;
	static int	i = 1;
	static int	fps = 0;
	t_weapon	*weap;

	weap = cube->lvl->weap;
	u_w = cube->player->use_weap;
	n_w_h[0] = (WIN_WIDTH - weap[u_w].sprites[i].width) / 2;
	n_w_h[1] = WIN_HEIGHT - weap[u_w].sprites[i].height;
	while (weap[u_w].path[n_w_h[2]] != 0)
		n_w_h[2]++;
	mlx_put_image_to_window(cube->mlx, cube->win,
		weap[u_w].sprites[i].img, n_w_h[0], n_w_h[1]);
	fps++;
	if (fps == cube->frame)
		i++;
	i %= (n_w_h[2] - 1);
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
