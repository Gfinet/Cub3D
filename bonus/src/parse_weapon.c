/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_weapon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:10:01 by Gfinet            #+#    #+#             */
/*   Updated: 2024/07/25 14:49:07 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	get_weapon(t_cube *cube)
{
	int			i;
	size_t		len;
	t_weapon	*weap;

	weap = &cube->lvl->weap;
	len = ft_strlen((char *)weap->path);
	i = -1;
	weap->sprites = malloc(sizeof(t_data) * len);
	weap->sprites[0].width = 10;
	weap->sprites[0].height = 17;
	while (weap->path[++i])
	{
		xpm_to_img(cube, &weap->sprites[i], weap->path[i]);
		if (!weap->sprites[i].img)
			return (0);
	}
	weap->dmg = 50;
	return (1);
}

void	set_weapon(t_maps *lvl, char *str)
{
	char	*tmp;
	char	**lst;
	size_t	len;

	lst = ft_split(str, ' ');
	len = 0;
	while (lst[len] != 0)
		len++;
	tmp = ft_substr(lst[len - 1], 0, ft_strlen(lst[len - 1]) - 1);
	free(lst[len - 1]);
	lst[len - 1] = tmp;
	lst[len] = 0;
	lvl->weap.path = lst;
}

int	check_weapon(t_cube *cube, char *str)
{
	int		i;
	char	*tmp;
	char	**lst;
	size_t	len;
	t_data	data;

	(void)cube;
	len = 0;
	lst = ft_split(&str[1], ' ');
	while (lst[len] != 0)
		len++;
	if (len == 1)
		return (free_maps(lst, len), 0);
	tmp = ft_substr(lst[len - 1], 0, ft_strlen(lst[len - 1]) - 1);
	free(lst[len - 1]);
	lst[len - 1] = tmp;
	i = -1;
	while (++i < (int)len)
	{
		data.width = 100;
		data.height = 170;
		data.img = mlx_xpm_file_to_image(cube->mlx, lst[i],
				&data.width, &data.height);
		if (!data.img)
			return (0);
	}
	return (free_maps(lst, len), 1);
}
