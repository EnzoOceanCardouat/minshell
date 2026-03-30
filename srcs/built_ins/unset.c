/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:11:10 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/30 13:20:21 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, t_token **token)
{
	char	**new_env;
	int		i;
	int		n;
	int		total;
	int		j;

	i = 0;
	j = 0;
	new_env = 0;
	total = 0;
	n = num_of_token(*token);
	if (!(*token)->next->next)
	{
		new_env = malloc(sizeof(char *) * (60 + 1));
		while(i < 61)
		{
			new_env[i] = ft_strdup(data->env_cpy[i]);
			i++;
		}
		new_env[i] = 0;
		data->env_cpy = new_env;
	}
	else
	{
		while (data->env_cpy[i])
			i++;
		new_env = malloc(sizeof(char *) * (i + 1 - n));
		total = i;
		i = 0;
		(*token) = (*token)->next;
		while (i < total + 1 - n)
		{
			if (ft_strcmp((*token)->value, data->env_cpy[i]) != 0)
			{
				new_env[j] = ft_strdup(data->env_cpy[i]);
				j++;
				i++;
			}
			else
			{
				i++;
				if ((*token)->next)
					(*token) = (*token)->next;
				else
					break ;
			}
		}
		new_env[j] = 0;
		data->env_cpy = new_env;
	}
}
