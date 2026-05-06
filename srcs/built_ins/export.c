/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:15:12 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/09 20:29:54 by thcotza          ###   ########.fr       */
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

	i = 0;
	n = num_of_args((*cmd)->args);
	if (!n)
	{
		current = data->env_list;
		while (current)
		{
			printf("declare -x %s\n", current->line);
			current = current->next;
		}
	}
	else
	{
		while (i < n)
		{
			add_env(data, (*cmd)->args[i]);
			update_env_cpy(data);
			i++;
		}
	}
}

//fonctionne ?
