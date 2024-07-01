/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:05:21 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/01 21:34:02 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_map(char *file)
{
	//check if 4 text are there
	//check if rgb val is ok
	//check if maps is close
	//check if map contain all info
	printf("%s\n", file);
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
		i++;
	}
	lvl->maps = malloc(sizeof(char*) * i);
	(lvl->maps)[0] = ft_strdup(tmp);
	free(tmp);
	str = get_next_line(fd[1]);
	i = 1;
	while (str)
	{
		(lvl->maps)[i++] = ft_strdup(str);
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
		printf("%d %d %s\n", k ,j , nb);
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
	printf("%s\n%s\n%s\n%s\n", lvl->no_text, lvl->so_text, lvl->we_text, lvl->ea_text);
	printf("%d %d %d\n", lvl->floor[0],lvl->floor[1], lvl->floor[2]);
	printf("%d %d %d\n", lvl->ceiling[0],lvl->ceiling[1], lvl->ceiling[2]);
	int i = 0;
	while (i < 14)
	{
		printf("%s\n", lvl->maps[i]);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	return (1);
}
