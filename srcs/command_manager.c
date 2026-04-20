/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:16:23 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/20 13:17:27 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static char	**build_argv(t_cmd *cmd)
{
	int	count;
	char	**argv;
	int i;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	argv = malloc(sizeof(char *) * (count + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd->cmd);
	i = 0;
	while (i < count)
	{
		argv[i + 1] = ft_strdup(cmd->args[i]);
		i++;
	}
	argv[count + 1] = NULL;
	return (argv);
}

static void	exec_external(t_cmd *cmd, t_data *data)
{
	char	**argv;
	char	*tmp;
	char	*full_path;
	char	**env;

	argv = build_argv(cmd);
	if (!argv)
		exit(1);
	if (ft_strchr(cmd->cmd, '/'))
	{
		execve(cmd->cmd, argv, data->env_cpy);
		perror(cmd->cmd);
		ft_free_split(argv);
		exit(127);
	}
	env = data->env_cpy;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd);
		ft_free_split(argv);
		exit(127);
	}
	data->paths = ft_split(*env + 5, ':');
	data->i = 0;
	while (data->paths[data->i])
	{
		tmp = ft_strjoin(data->paths[data->i], "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, argv, data->env_cpy);
			perror(full_path);
			free(full_path);
			break ;
		}
		free(full_path);
		data->i++;
	}
	ft_free_split(data->paths);
	fprintf(stderr, "Command not found: %s\n", cmd->cmd);
	ft_free_split(argv);
	exit(127);
}

static void	execute_child(t_cmd *cmd, t_data *data)
{
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (!cmd->cmd)
		exit(1);
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
		exec_external(cmd, data);
	exit(0);
}

static int	count_commands(t_cmd *cmd)
{
	int count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	manage_commands(t_cmd *cmd, t_data *data)
{
	int		*child_pids;
	int		idx;
	int		pipefd[2];
	int		prev_fd;
	t_cmd	*current;

	data->env_list = char_to_ll(data->env_cpy);
	idx = 0;
	prev_fd = -1;
	child_pids = malloc(sizeof(int) * count_commands(cmd));
	if (!child_pids)
		return ;
	current = cmd;
	while (current)
	{
		if (current->next && pipe(pipefd) == -1)
			perror("pipe");
		child_pids[idx] = fork();
		if (child_pids[idx] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			execute_child(current, data);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
				prev_fd = -1;
		}
		current = current->next;
		idx++;
	}
	while (--idx >= 0)
		waitpid(child_pids[idx], NULL, 0);
	free(child_pids);
}
