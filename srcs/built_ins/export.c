/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:15:12 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/02 17:06:38 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_of_args(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

void	ft_export(t_data *data, t_cmd **cmd)
{
	int 	i;
	int		n;
	t_env	*current;
	t_env	*new_node;

	i = 0;
	n = num_of_args((*cmd)->args);
	if (!(*cmd)->args)
	{
		while (data->env_cpy[i])
			printf("declare -x %s\n", data->env_cpy[i++]);
	}
	else
	{
		current = data->env_list;
		if (current)
		{
			while (current->next)
				current = current->next;
		}
		while (i < n)
		{
			new_node = malloc(sizeof(t_env));
			if (!new_node)
				return;
			new_node->line = ft_strdup((*cmd)->args[i]);
			new_node->next = NULL;
			if (!data->env_list)
				data->env_list = new_node;
			else
				current->next = new_node;
			current = new_node;
			i++;
		}
	}
}
