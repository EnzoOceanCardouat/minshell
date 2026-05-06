/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:16:23 by thcotza           #+#    #+#             */
/*   Updated: 2026/05/05 11:40:05 by ecardoua         ###   ########.fr       */
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
	int	i;

	if (!cmd || !cmd->cmd)
		return (NULL);
	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	argv = malloc(sizeof(char *) * (count + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd->cmd);
	if (!argv[0])
	{
		free(argv);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		argv[i + 1] = ft_strdup(cmd->args[i]);
		if (!argv[i + 1])
		{
			ft_free_split(argv);
			return (NULL);
		}
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
	int	exec_status;

	argv = build_argv(cmd);
	if (!argv)
		exit(1);
	if (ft_strchr(cmd->cmd, '/'))
	{
		execve(cmd->cmd, argv, data->env_cpy);
		if (errno == EACCES)
			exec_status = 126;
		else
			exec_status = 127;
		perror(cmd->cmd);
		ft_free_split(argv);
		exit(exec_status);
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
			if (errno == EACCES)
				exec_status = 126;
			else
				exec_status = 127;
			perror(full_path);
			free(full_path);
			ft_free_split(data->paths);
			ft_free_split(argv);
			exit(exec_status);
		}
		free(full_path);
		data->i++;
	}
	ft_free_split(data->paths);
	fprintf(stderr, "Command not found: %s\n", cmd->cmd);
	ft_free_split(argv);
	exit(127);
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

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

static void	execute_builtin(t_cmd *cmd, t_data *data, int is_piped, t_token **token)
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
		ft_exit(cmd, data, is_piped, token);
}

static void	execute_command(t_cmd *cmd, t_data *data, int is_piped, t_token **token)
{
	if (is_builtin(cmd->cmd))
		execute_builtin(cmd, data, is_piped, token);
	else
		exec_external(cmd, data);
}

void	manage_commands(t_cmd *cmd, t_data *data, t_token **token)
{
	int		*child_pids;
	int		idx;
	int		pipefd[2];
	int		prev_fd;
	t_cmd	*current;
	int		num_cmds;

	if (!cmd)
		return ;
	idx = 0;
	prev_fd = -1;
	num_cmds = count_commands(cmd);
	if (num_cmds == 0)
		return ;
	child_pids = malloc(sizeof(int) * num_cmds);
	if (!child_pids)
		return ;
	current = cmd;
	while (current)
	{
		if (!current->next && prev_fd == -1 && is_builtin(current->cmd))
			execute_builtin(current, data, 0, token);
		else
		{
			if (current->next && pipe(pipefd) == -1)
			{
				perror("pipe");
				if (prev_fd != -1)
					close(prev_fd);
				while (--idx >= 0)
					waitpid(child_pids[idx], NULL, 0);
				free(child_pids);
				return ;
			}
			child_pids[idx] = fork();
			if (child_pids[idx] == -1)
			{
				perror("fork");
				if (current->next)
				{
					close(pipefd[0]);
					close(pipefd[1]);
				}
				if (prev_fd != -1)
					close(prev_fd);
				while (--idx >= 0)
					waitpid(child_pids[idx], NULL, 0);
				free(child_pids);
				return ;
			}
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
					execute_command(current, data, 1, token);
				}
				else
					execute_command(current, data, 0, token);
				exit(EXIT_SUCCESS);
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
			idx++;
		}
		current = current->next;
	}
	while (--idx >= 0)
		waitpid(child_pids[idx], NULL, 0);
	free(child_pids);
}
