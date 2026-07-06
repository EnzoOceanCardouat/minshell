/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:11:10 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/03 00:47:01 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(t_data *data, char *var)
{
	data->current = data->env_list;
	data->len = ft_strlen(var);
	while (data->current)
	{
		if (ft_strncmp(var, data->current->line, data->len) == 0
			&& (data->current->line[data->len] == '='
				|| data->current->line[data->len] == '\0'))
		{
			if (data->prev)
				data->prev->next = data->current->next;
			else
				data->env_list = data->current->next;
			free(data->current->line);
			free(data->current);
			if (data->prev)
				data->current = data->prev->next;
			else
				data->current = data->env_list;
		}
		else
		{
			data->prev = data->current;
			data->current = data->current->next;
		}
	}
}

void	ft_unset(t_data *data, t_cmd **cmd)
{
	int		i;
	int		n;

	i = 0;
	n = num_of_args((*cmd)->args);
	if (n)
	{
		while (i < n)
			remove_env_var(data, (*cmd)->args[i++]);
		update_env_cpy(data);
	}
	data->last_status = 0;
}
