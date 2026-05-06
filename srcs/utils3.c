/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:39:53 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/09 20:16:16 by thcotza          ###   ########.fr       */
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
	int		i;

	if (!env || !env[0])
		return (NULL);
	head = malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->line = ft_strdup(env[0]);
	head->next = NULL;
	current = head;
	i = 1;
	while (env[i])
	{
		current->next = malloc(sizeof(t_env));
		if (!current->next)
		{
			lst_free(head);
			return (NULL);
		}
		current->next->line = ft_strdup(env[i]);
		current->next->next = NULL;
		current = current->next;
		i++;
	}
	return (head);
}

char	**ll_to_char(t_env *env_list)
{
	char	**env;
	int		i;
	t_env	*current;

	if (!env_list)
		return (NULL);
	env = malloc(sizeof(char *) * (lst_size(env_list) + 1));
	if (!env)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env[i] = ft_strdup(current->line);
		current = current->next;
		i++;
	}
	env[i] = NULL;
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

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	if (!data->env_list)
	{
		data->env_list = new_node;
		return ;
	}
	current = data->env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
