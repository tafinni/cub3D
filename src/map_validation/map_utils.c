/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:49 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/11 16:16:02 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**duplicate_arr(char **map, int len)
{
	char	**res;
	int		width;
	int		y;

	y = 0;
	res = NULL;
	res = (char **)malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	while (y < len)
	{
		width = ft_strlen(map[y]) + 1;
		res[y] = NULL;
		res[y] = malloc(sizeof(char) * width);
		if (!res[y])
		{
			free_array(res, y);
			return (NULL);
		}
		ft_memcpy(res[y], map[y], width);
		y++;
	}
	return (res);
}

int	scroll_empty(char *str, int i)
{
	if (!str || ft_isalpha(str[i]))
		return (FAIL);
	while ((str[i] && str[i] > 9 && str[i] < 13) || (str[i] && str[i] == ' '))
		i++;
	return (i);
}

int	path_start(char *str, char *find, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (str[i])
		{
			if (str[i + 1] && str[i + 2] && str[i] == \
			find[0] && str[i + 1] == find[1])
				return (i + 2);
			i++;
		}
	}
	else if (flag == 2)
	{
		while (str[i])
		{
			if (str[i] == find[0])
				return (i + 1);
			i++;
		}
	}
	return (FAIL);
}

int	check_texture_type(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && (str[i] == '	' || str[i] == ' '))
		i--;
	if (str[i] != 'm' || str[i - 1] != 'p' || \
	str[i - 2] != 'x' || str[i - 3] != '.')
		return (FAIL);
	return (SUCCESS);
}

int	max_x_len(t_list *list, int best, int current, int x)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL && ft_strchr(temp->str, '1'))
	{
		x = 0;
		current = 0;
		while (temp->str[x])
		{
			if (temp->str[x] == 'X')
				return (FAIL);
			if (temp->str[x] != '\n')
				current++;
			if (temp->str[x] == '	')
				current += 7;
			if (temp->str[x] == ' ' || temp->str[x] == '\n')
				temp->str[x] = 'X';
			x++;
		}
		if (current > best)
			best = current;
		temp = temp->next;
	}
	return (best);
}
