/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:30:51 by thcotza           #+#    #+#             */
/*   Updated: 2026/07/06 08:49:18 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
		write(fd, &s[i++], 1);
}

int	lst_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**duplicate_args(t_cmd *cmd, int count)
{
	char	**argv;
	int		i;

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

void	wait_children(int *child_pids, int idx, t_data *data)
{
	int	status;
	int	first_status_set;

	first_status_set = 0;
	while (--idx >= 0)
	{
		if (waitpid(child_pids[idx], &status, 0) > 0 && !first_status_set)
		{
			if (WIFEXITED(status))
				data->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->last_status = 128 + WTERMSIG(status);
			first_status_set = 1;
		}
	}
}

int	create_pipe_or_error(t_data *data, int idx)
{
	if (pipe(data->pipefd) == -1)
	{
		perror("pipe");
		if (data->prev_fd != -1)
			close(data->prev_fd);
		wait_children(data->child_pids, idx, data);
		return (-1);
	}
	return (0);
}
