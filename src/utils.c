/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:07:51 by gfinet            #+#    #+#             */
/*   Updated: 2024/08/31 17:38:19 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_and_gnl(char **str, int fd)
{
	free(*str);
	*str = get_next_line(fd);
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

int	new_img(t_cube *cube, t_data *new_img, int width, int height)
{
	new_img->img = mlx_new_image(cube->mlx, width, height);
	if (!new_img->img)
		return (0);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bits_per_pixel,
			&new_img->line_length, &new_img->endian);
	return (1);
}

void	free_maps(char **maps, int ind, int f)
{
	int	i;

	i = -1;
	while (++i <= ind)
		free(maps[i]);
	if (f)
		free(maps);
}

void	free_cube(t_cube *cube)
{
	if (cube->lvl)
		free_maps(cube->lvl->c_maps, cube->lvl->m_height - 1, 1);
	if (cube->screen && cube->screen->img)
		mlx_destroy_image(cube->mlx, cube->screen->img);
	free(cube->screen);
	if (cube->lvl && cube->lvl->mini.maps.img)
		mlx_destroy_image(cube->mlx, cube->lvl->mini.maps.img);
	if (cube->texture[0].img)
		mlx_destroy_image(cube->mlx, cube->texture[0].img);
	if (cube->texture[1].img)
		mlx_destroy_image(cube->mlx, cube->texture[1].img);
	if (cube->texture[2].img)
		mlx_destroy_image(cube->mlx, cube->texture[2].img);
	if (cube->texture[3].img)
		mlx_destroy_image(cube->mlx, cube->texture[3].img);
}
