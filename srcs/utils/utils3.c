/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:39:53 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/03 00:54:57 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lst_free(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->line);
		free(head);
		head = tmp;
	}
}

t_env	*char_to_ll(char **env)
{
	t_env	*head;
	t_env	*current;

	if (!env || !env[0])
		return (NULL);
	head = malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->line = ft_strdup(env[0]);
	head->next = NULL;
	current = head;
	head = char_to_ll_bis(env, current, head);
	return (head);
}

char	**ll_to_char(t_env *env_list)
{
	char	**env;
	int		i;
	int		count;
	t_env	*current;

	if (!env_list)
		return (NULL);
	count = 0;
	current = env_list;
	while (current)
	{
		if (ft_strchr(current->line, '=') != NULL)
			count++;
		current = current->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	env = ll_to_char_bis(env_list, env, current, i);
	return (env);
}

void	update_env_cpy(t_data *data)
{
	char	**new_env;

	new_env = ll_to_char(data->env_list);
	if (!new_env)
		return ;
	ft_free_split(data->env_cpy);
	data->env_cpy = new_env;
}

void	add_env(t_data *data, char *line)
{
	t_env	*new_node;
	t_env	*current;
	char	*equal_pos;
	int		var_len;

	equal_pos = ft_strchr(line, '=');
	if (equal_pos)
		var_len = equal_pos - line;
	else
		var_len = ft_strlen(line);
	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->line, line, var_len) == 0
			&& (current->line[var_len] == '='
				|| current->line[var_len] == '\0'))
		{
			free(current->line);
			current->line = ft_strdup(line);
			return ;
		}
		current = current->next;
	}
	new_node = NULL;
	add_env_bis(data, line, new_node, current);
}
