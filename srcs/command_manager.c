/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:16:23 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/08 14:07:53 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**command_plus_null(char *command, t_data *data)
{
	data->cmd = malloc(sizeof(char *) * 2);
	if (!data->cmd)
		return (NULL);
	data->cmd[0] = ft_strdup(command);
	data->cmd[1] = NULL;
	return (data->cmd);
}

void	exec_command(t_data *data)
{
	while (data->paths[data->i])
	{
		data->full_path = ft_strjoin(data->paths[data->i], "/");
		data->full_path = ft_strjoin(data->full_path, data->command);
		if (access(data->full_path, X_OK) == 0)
		{
			data->id = fork();
			if (data->id == 0)
			{
				data->cmd = command_plus_null(data->command, data);
				execve(data->full_path, data->cmd, data->env_cpy);
				printf("Executing command: %s\n", data->full_path);
				free(data->full_path);
			}
			else
				waitpid(data->id, NULL, 0);
			free(data->full_path);
			break ;
		}
		free(data->full_path);
		data->i++;
	}
}

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	search_path(char *command, t_data *data)
{
	data->command = ft_strdup(command);
	while (*data->env_cpy)
	{
		if (ft_strncmp(*data->env_cpy, "PATH=", 5) == 0)
		{
			data->path = *data->env_cpy + 5;
			break ;
		}
		data->env_cpy++;
	}
	if (!data->path)
	{
		printf("Command not found: %s\n", command);
		return ;
	}
	data->paths = ft_split(data->path, ':');
	data->i = 0;
	exec_command(data);
	if (!data->paths[data->i])
		printf("Command not found: %s\n", command);
	ft_free_split(data->paths);
}

// void verif_redirection(t_token *token, t_data *data)
// {
// 	while (token && token->next)
// 	{
// 		if (token->type == MORE || token->type == D_MORE)
// 		{
// 			if (token->next->type == WORD)
// 			{
// 				if (token->type == MORE)
// 				{
// 					data->fd = open((const char *)token->next->value, O_TRUNC);
// 					close(data->fd);
// 					data->fd = open((const char *)token->next->value, O_RDWR);
// 				}
// 				else
// 					data->fd = open((const char *)token->next->value, O_WRONLY | O_APPEND);
// 			}
// 		}
// 		token = token->next;
// 	}
// }

void	manage_commands(t_cmd *cmd, t_data *data)
{
	//verif_redirection(token_cpy, data);
    data->env_list = char_to_ll(data->env_cpy);
	while (cmd)
	{
		if (cmd->cmd)
		{
			if (ft_strcmp(cmd->cmd, "echo") == 0)
				ft_echo(&cmd, data);
			else if (ft_strcmp(cmd->cmd, "cd") == 0)
				ft_cd(&cmd);
			else if (ft_strcmp(cmd->cmd, "pwd") == 0)
				ft_pwd(data);
			else if (ft_strcmp(cmd->cmd, "export") == 0)
				ft_export(data, &cmd);
			else if (ft_strcmp(cmd->cmd, "unset") == 0)
				ft_unset(data, &cmd);
			else if (ft_strcmp(cmd->cmd, "env") == 0)
				ft_env(data);
			else if (ft_strcmp(cmd->cmd, "exit") == 0)
				ft_exit(data);
			else
				search_path(cmd->cmd, data);
		}
		cmd = cmd->next;
	}
}
