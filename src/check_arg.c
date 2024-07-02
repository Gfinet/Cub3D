/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:40:39 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 20:27:13 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_texture(t_cube *cube, char *str)
{
	t_data	data;
	size_t	len;
	int		size[2];
	char	*tmp;

	size[0] = 5;
	size[1] = 5;
	len = ft_strlen(str) - 1;
	tmp = ft_substr(str, 0, len);
	data.img = mlx_xpm_file_to_image(cube->mlx,
			tmp, &size[0], &size[1]);
	free(tmp);
	if (!data.img)
		return (0);
	return (1);
}

static int	check_all_text(t_cube *cube, char *file)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(file, O_RDONLY);
	i = -1;
	while (++i < 4)
	{
		str = get_next_line(fd);
		if (str && ((!ft_strncmp(str, "NO ", 3) && i == 0)
				|| (!ft_strncmp(str, "SO ", 3) && i == 1)
				|| (!ft_strncmp(str, "WE ", 3) && i == 2)
				|| (!ft_strncmp(str, "EA ", 3) && i == 3)))
		{
			if (!check_texture(cube, &str[3]))
				return (close(fd), 0);
		}
		else
			return (close(fd), 0);
		free(str);
	}
	close(fd);
	return (1);
}

static int	check_rgb(char *str)
{
	int	i;
	int	val[3];

	set_floor_ceiling(val, str);
	i = -1;
	while (++i < 3)
	{
		if (val[i] < 0 || val[i] > 255)
			return (0);
	}
	return (1);
}

static int	check_color(char *file)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(file, O_RDONLY);
	printf("%d\n", fd);
	i = -1;
	str = get_next_line(fd);
	while (++i < 6)
	{
		free(str);
		str = get_next_line(fd);
	}
	if (str[0] != 'F')
		return (free(str), close(fd), 0);
	if (!check_rgb(&str[2]))
		return (free(str), close(fd), 0);
	free(str);
	str = get_next_line(fd);
	if (str[0] != 'C')
		return (free(str), close(fd), 0);
	if (!check_rgb(&str[2]))
		return (free(str), close(fd), 0);
	free(str);
	return (1);
}

int	check_map(t_cube *cube, char *file)
{
	//check if 4 text are there
	//check if rgb val is ok
	//check if maps is close
	//check if map contain all info
	if (!check_all_text(cube, file))
		return (0);
	if (!check_color(file))
		return (0);
	//if (!check)
	printf("%s\n", file);
	return (1);
}
