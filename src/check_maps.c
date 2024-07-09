/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:40:39 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/09 18:54:43 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_surrounding(t_cube *cube, int x, int y, char c)
{
	size_t len;
	char **maps;

	maps = cube->lvl->c_maps;
	len = ft_strlen(maps[x]);
	if (x == 0 || y == 0 || x == cube->lvl->m_height - 1)
		return (printf("debug 1\n"), 0);
	if (y > 0 && (maps[x][y - 1] == c || maps[x][y - 1] == 0))
		return (printf("debug 2\n"), 0);
	if (y < (int)len && (maps[x][y + 1] == c || maps[x][y + 1] == 0))
		return (printf("debug 3, %d %d [%c] [%c]\n",x, y, maps[x][y], maps[x][y + 1]), 0);
	if (x > 0 && (maps[x - 1][y] == c || maps[x - 1][y] == 0))
		return (printf("debug 4\n"), 0);
	if (x < cube->lvl->m_height && (maps[x + 1][y] == c || maps[x + 1][y] == 0))
		return (printf("debug 5\n"), 0);
	return (1);
}

int check_map(t_cube *cube)
{
	//check if maps is close
	//check if map contain all info
	int i = -1;
	int j = 0;

	// while (++i < cube->lvl->m_height)
	// 	printf("%s\n", cube->lvl->c_maps[i]);
	i = -1;
	while (++i < cube->lvl->m_height)
	{
		j = -1;
		printf("%s\n", cube->lvl->c_maps[i]);
		while (++j < cube->lvl->max_len)
		{
			if (cube->lvl->c_maps[i][j] == '0')
				if (!check_surrounding(cube, i, j, '.'))
					return (0);
		}
	}
	printf("\nmap ok\n");
	return (1);
}
