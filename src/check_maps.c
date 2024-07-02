/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:40:39 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 00:30:21 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_surrounding(t_cube *cube, int x, int y)
{
	char **maps;

	maps = cube->lvl->c_maps;
	if (x == 0 || y == 0)
		return (printf("%c", maps[x][y]), 0);
	if (x > 0 && maps[x - 1][y] == 0)
		return (0);
	if (x < cube->lvl->max_len && maps[x + 1][y] == 0)
		return (0);
	if (y > 0 && maps[x][y - 1] == 0)
		return (0);
	if (y < cube->lvl->m_height && maps[x][y + 1] == 0)
		return (0);
	//printf("%c", maps[x][y]);
	return (1);
}

int check_map(t_cube *cube)
{
	//check if maps is close
	//check if map contain all info
	int i = 0;
	int j = 0;
	while (i < cube->lvl->m_height)
		printf("%s\n", cube->lvl->c_maps[i++]);
	i = -1;
	while (++i < cube->lvl->m_height)
	{
		j = -1;
		while (++j < cube->lvl->max_len)
		{
			if (cube->lvl->c_maps[i][j] == '0')
				if (!check_surrounding(cube, i, j))
					return (0);
		}
	}
	printf("\nmap ok\n");
	return (1);
}
