/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 02:53:21 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 07:56:09 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>

void	free_child_resources(t_data *data)
{
	if (data->cmd_head)
		free_cmds(data->cmd_head);
	if (data->token_head)
		free_tokens_list(data->token_head);
	if (data->child_pids)
		free(data->child_pids);
	free_data(data);
}

void	exec_search_paths(t_cmd *cmd, t_data *data, char **argv)
{
	char	**env;
	char	*full_path;

	env = data->env_cpy;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
	{
		ft_putstr_fd("Command not found: \n", 2);
		ft_putendl_fd(cmd->cmd, 2);
		ft_free_split(argv);
		exit(127);
	}
	data->paths = ft_split(*env + 5, ':');
	data->i = 0;
	full_path = NULL;
	exec_search_path_bis(cmd, argv, data, full_path);
}

void	exec_external(t_cmd *cmd, t_data *data)
{
	char	**argv;

	argv = build_argv(cmd);
	if (!argv)
	{
		free_child_resources(data);
		exit(1);
	}
	if (ft_strchr(cmd->cmd, '/'))
		exec_with_direct_path(cmd, argv, data->env_cpy, data);
	exec_search_paths(cmd, data, argv);
}

char	**build_argv(t_cmd *cmd)
{
	int		arg_count;
	char	**dup;

	if (!cmd || !cmd->cmd)
		return (NULL);
	arg_count = count_args(cmd);
	dup = duplicate_args(cmd, arg_count);
	return (dup);
}

void	exec_path_failure(char *path, char **argv, char **paths, t_data *data)
{
	int	exec_status;

	if (errno == EACCES)
		exec_status = 126;
	else
		exec_status = 127;
	perror(path);
	if (paths)
		ft_free_split(paths);
	ft_free_split(argv);
	free_child_resources(data);
	exit(exec_status);
}
