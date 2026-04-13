/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:11:10 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/13 14:44:48 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_var(t_data *data, char *var)
{
	t_env	*current;
	t_env	*prev;
	size_t	len;

	current = data->env_list;
	prev = NULL;
	len = ft_strlen(var);
	while (current)
	{
		if (ft_strncmp(var, current->line, len) == 0 && current->line[len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				data->env_list = current->next;
			free(current->line);
			free(current);
			if (prev)
				current = prev->next;
			else
				current = data->env_list;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
} // does not work if there's no '='

void	ft_unset(t_data *data, t_cmd **cmd)
{
	int	i;
	int	n;

	i = 0;
	n = num_of_args((*cmd)->args);
	if (!n)
	{
		lst_free(data->env_list);
		data->env_list = char_to_ll(data->original_env);
		//update_env_cpy(data);
	}
	else
	{
		while (i < n)
		remove_env_var(data, (*cmd)->args[i++]);
		//update_env_cpy(data);
	}
}
