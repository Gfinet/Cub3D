/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:05:21 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 17:28:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int cpy_line(t_maps *lvl, char *str, int ind)
{
	//lvl->c_maps[ind] = ft_calloc(sizeof(char), (size_t)lvl->max_len);
	lvl->c_maps[ind] = malloc(sizeof(char) * lvl->max_len + 2);
	ft_memset((void*)lvl->c_maps[ind], '.', (size_t)lvl->max_len + 2);
	if (!lvl->c_maps[ind])
		return (0); //free_all
	ft_strlcpy(lvl->c_maps[ind], str, (size_t)lvl->max_len + 1);
	return (1);
}

void set_map(t_maps *lvl, char *str, int fd[2])
{
	int i;
	char *tmp;

	i = 1;
	tmp = ft_strdup(str);
	while (str)
	{
		str = get_next_line(fd[0]);
		if ((int)ft_strlen(str) > lvl->max_len)
			lvl->max_len = (int)ft_strlen(str);
		i++;
	}
	lvl->c_maps = malloc(sizeof(char*) * i);
	printf("%d\n", lvl->max_len);
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
}

void set_floor_ceiling(int fl_ce[3], char *str)
{
	int i;
	int j;
	int k;
	char *nb;
	
	i = 0;
	k = 0;
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

void fill_maps(t_maps *lvl, char *str, int fd[2])
{
	size_t len;

	len = ft_strlen(str);
	if (!str)
		return ;
	if (str[0] == 'N')
		lvl->no_text = ft_substr(str, 3, len - 4);
	else if (str[0] == 'S')
		lvl->so_text = ft_substr(str, 3, len - 4);
	else if (str[0] == 'W')
		lvl->we_text = ft_substr(str, 3, len - 4);
	else if (str[0] == 'E')
		lvl->ea_text = ft_substr(str, 3, len - 4);
	else if (str[0] == 'F')
		set_floor_ceiling(lvl->floor, &str[2]);
	else if (str[0] == 'C')
		set_floor_ceiling(lvl->ceiling, &str[2]);
	else if (str[0] == '\n')
		return ;
	else
		set_map(lvl, str, fd);

}
int get_maps(t_maps *lvl, char *file)
{
	int fd[2];
	char *str;
	if (!check_map(file))
		return (0);
	lvl->max_len = 0;
	fd[0] = open(file, O_RDONLY);
	fd[1] = open(file, O_RDONLY);
	str = get_next_line(fd[0]);
	get_next_line(fd[1]);
	while (str)
	{
		fill_maps(lvl, str, fd);
		free(str);
		str = get_next_line(fd[0]);
		get_next_line(fd[1]);
	}
	int i = 0;
	while (i < lvl->m_height)
		printf("%s", lvl->c_maps[i++]);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
