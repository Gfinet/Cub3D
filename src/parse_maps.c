/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:05:21 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 16:42:04 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	cpy_line(t_maps *lvl, char *str, int ind)
{
	size_t len;
	lvl->c_maps[ind] = malloc(sizeof(char) * lvl->max_len + 2);
	// ft_memset((void *)lvl->c_maps[ind], 0, (size_t)lvl->max_len + 2);
	if (!lvl->c_maps[ind])
		return (0); //free_all
	len = ft_strlen(str);
	len -= str[len - 1] == '\n';
	printf("%zu\n",len);
	ft_strlcpy(lvl->c_maps[ind], str, len + 1);
	return (1);
}

void	set_map(t_maps *lvl, char *str, int fd[2])
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_strdup(str);
	while (str)
	{
		str = get_next_line(fd[0]);
		if ((int)ft_strlen(str) > lvl->max_len)
		{
			lvl->max_len = (int)ft_strlen(str) - (str[ft_strlen(str)] == '\n');
			//lvl->max_len -= str[lvl->max_len] == '\n';
		}
		i++;
	}
	lvl->c_maps = malloc(sizeof(char *) * i);
	cpy_line(lvl, tmp, 0);
	free(tmp);
	str = get_next_line(fd[1]);
	i = 1;
	while (str)
	{
		cpy_line(lvl, str, i++);
		free(str);
		str = get_next_line(fd[1]);
	}
	lvl->m_height = i;
	fill_map_char(lvl, '.');
}

void	set_floor_ceiling(int fl_ce[3], char *str)
{
	int		i;
	int		j;
	int		k;
	char	*nb;

	i = 0;
	k = 0;
	while (str[k] == ' ')
		k++;
	j = 0;
	while (i < 3)
	{
		k += j;
		j = 0;
		while (str[k + j] && str[k + j] != ',' && str[k + j] != '\n')
			j++;
		nb = ft_substr(str, (size_t)k, (size_t)j);
		fl_ce[i++] = ft_atoi(nb);
		free(nb);
		j++;
	}
}

void	fill_maps(t_maps *lvl, char *str, int fd[2])
{
	if (!str)
		return ;
	if (!ft_strncmp("NO", str, 2))
		lvl->no_text = get_text_dir(&str[2]);
	else if (!ft_strncmp("SO", str, 2))
		lvl->so_text = get_text_dir(&str[2]);
	else if (!ft_strncmp("WE", str, 2))
		lvl->we_text = get_text_dir(&str[2]);
	else if (!ft_strncmp("EA", str, 2))
		lvl->ea_text = get_text_dir(&str[2]);
	else if (str[0] == 'F')
		set_floor_ceiling(lvl->floor, &str[1]);
	else if (str[0] == 'C')
		set_floor_ceiling(lvl->ceiling, &str[1]);
	else if (str[0] == '\n')
		return ;
	else
		set_map(lvl, str, fd);
}

int	get_maps(t_cube *cube, char *file)
{
	int		fd[2];
	char	*str;

	if (!check_arg(cube, file))
		return (0);
	cube->lvl->max_len = 0;
	fd[0] = open(file, O_RDONLY);
	fd[1] = open(file, O_RDONLY);
	str = get_next_line(fd[0]);
	get_next_line(fd[1]);
	while (str)
	{
		fill_maps(cube->lvl, str, fd);
		free(str);
		str = get_next_line(fd[0]);
		get_next_line(fd[1]);
	}
	if (!check_map(cube))
		return (0);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
