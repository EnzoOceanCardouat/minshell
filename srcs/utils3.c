/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:39:53 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/27 13:53:45 by ecardoua         ###   ########.fr       */
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

int	ft_lentab(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}
