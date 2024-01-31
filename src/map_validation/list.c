/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:26:01 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 18:57:28 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_list	*add_map_line(char *str)
{
	t_list	*temp;

	temp = NULL;
	temp = malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->str = NULL;
	temp->str_len = 0;
	temp->str = str;
	temp->next = NULL;
	return (temp);
}

char	*list_help(t_data *data, char *str, int fd, int flag)
{
	char	*res;

	res = NULL;
	if (flag == 0)
	{
		res = ft_strjoin(data->buffer, str);
		free(data->buffer);
		free(str);
		data->buffer = NULL;
	}
	else if (flag == 1)
	{
		error_msg("Malloc fail");
		free_data(data, 0);
		close(fd);
	}
	return (res);
}

int	read_to_list(t_data *data, int fd, t_list **list)
{
	char	*str;
	t_list	*temp;
	int		count;

	count = 0;
	while (1)
	{
		str = NULL;
		str = get_next_line(fd);
		if (data->buffer != NULL)
			str = list_help(data, str, fd, 0);
		if (!str || str == NULL || (ft_strlen(str) < 1 && count == 0))
			break ;
		count++;
		temp = add_map_line(str);
		if (temp == NULL)
		{
			list_help(data, str, fd, 1);
			return (free_list((*list)));
		}
		(*list) = add_temp_back((*list), temp);
	}
	close(fd);
	return (SUCCESS);
}

t_list	**list_move(t_list **list, int flag)
{
	int	i;

	if (flag == 1)
	{
		if ((*list)->next != NULL)
			(*list) = (*list)->next;
	}
	if ((*list) == NULL)
		return (NULL);
	while ((*list)->next != NULL)
	{
		i = 0;
		while ((*list)->str[i] && ((*list)->str[i] == '	' || \
		(*list)->str[i] == ' ' || (*list)->str[i] == '\n'))
			i++;
		if ((*list)->str[i] && ((*list)->str[i] != '	' || \
		(*list)->str[i] != ' ' || (*list)->str[i] != '\n'))
			return (list);
		(*list) = (*list)->next;
	}
	return (list);
}

t_list	*add_temp_back(t_list *list, t_list *temp)
{
	t_list	*last;
	t_list	*prev;

	if (!list)
	{
		list = temp;
		list->next = NULL;
		list->previous = NULL;
	}
	else
	{
		last = list;
		while (last->next != NULL)
			last = last->next;
		last->next = temp;
		prev = last;
		last = last->next;
		last->next = NULL;
		last->previous = prev;
	}
	return (list);
}
