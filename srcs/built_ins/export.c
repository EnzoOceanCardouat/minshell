/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:15:12 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/30 13:19:59 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_of_token(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}

void	ft_export(t_data *data, t_token **token)
{
	int 	i;
	char	**new_env;
	int		n;

	i = 0;
	n = num_of_token(*token);
	new_env = 0;
	if (!(*token)->next->next)
	{
		while (data->env_cpy[i])
			printf("declare -x %s\n", data->env_cpy[i++]);
	}
	else
	{
		while (data->env_cpy[i])
			i++;
		new_env = malloc(sizeof(char *) * (n + i + 1));
		if (!new_env)
			return ;
		i = -1;
		while (data->env_cpy[++i])
			new_env[i] = ft_strdup(data->env_cpy[i]);
		(*token) = (*token)->next;
		while ((*token)->next)
		{
			if ((*token)->type == WORD)
				new_env[i] = ft_strdup((*token)->value);
			i++;
			(*token) = (*token)->next;
		}
		new_env[++i] = 0;
		data->env_cpy = new_env;
	}
}
