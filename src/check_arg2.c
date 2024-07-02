/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:54:06 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 22:36:35 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_dir(char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		return (0);
	else if (!ft_strncmp(str, "SO", 2))
		return (1);
	else if (!ft_strncmp(str, "WE", 2))
		return (2);
	else if (!ft_strncmp(str, "EA", 2))
		return (3);
	else
		return (-1000);
}

char *get_text_dir(char *str)
{
	size_t len;
	int start;

	start = 0;
	while (str[start] == ' ')
		start++;
	len = ft_strlen(&str[start]) - 1;
	return (ft_substr(str, start, len));
}
