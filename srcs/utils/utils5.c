/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:04:37 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 13:00:35 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_box(t_data *data, t_cmd **cmd, t_token **token)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (access("tmp_heredoc", F_OK) == 0)
	{
		if (unlink("tmp_heredoc") != 0)
			write(2, "Error deleting the tmp_heredoc file\n", 36);
	}
	if (*cmd)
	{
		free_cmds(*cmd);
		*cmd = NULL;
	}
	if (*token)
	{
		free_tokens_list(*token);
		*token = NULL;
	}
	data->cmd_head = NULL;
	data->token_head = NULL;
}

void	add_env_bis(t_data *data, char *line, t_env *new_node, t_env *current)
{
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

char	**ll_to_char_bis(t_env *env_list, char **env, t_env *current, int i)
{
	current = env_list;
	while (current)
	{
		if (ft_strchr(current->line, '=') != NULL)
			env[i++] = ft_strdup(current->line);
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}

t_env	*char_to_ll_bis(char **env, t_env *current, t_env *head)
{
	int	i;

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

int	is_out_of_range_bis(char *str, t_data *data)
{
	if (data->length < 19)
		return (0);
	if (data->is_negative)
	{
		if (ft_strncmp(&str[data->j], data->llong_min_str, 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(&str[data->j], data->llong_max_str, 19) > 0)
			return (1);
	}
	return (0);
}
