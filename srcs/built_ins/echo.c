/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:14:17 by thcotza           #+#    #+#             */
/*   Updated: 2026/05/04 22:46:18 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_word_fd(int fd, t_cmd **cmd, int start)
{
	int	i;

	i = start;
	while ((*cmd)->args[i])
	{
		ft_putstr_fd((*cmd)->args[i], fd);
		if ((*cmd)->args[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo_file(t_cmd **cmd, t_data *data, int start)
{
	if (data->fd_out > -1)
	{
		write_word_fd(data->fd_out, cmd, start);
		close(data->fd_out);
	}
	else if (data->fd_in > -1)
	{
		write_word_fd(data->fd_in, cmd, start);
		close(data->fd_in);
	}
	close(data->fd_in);
}

void	ft_echo(t_cmd **cmd, t_data *data)
{
	int	start;
	int	no_newline;

	start = 0;
	no_newline = 0;
	if ((*cmd)->args && !ft_strncmp((*cmd)->args[0], "-n", 3))
	{
		start = 1;
		no_newline = 1;
	}
	if (!(*cmd)->args || !(*cmd)->args[start])
	{
		if (!no_newline)
			write(1, "\n", 1);
	}
	else if (data->fd_in > -1 || data->fd_out > -1)
		ft_echo_file(cmd, data, start);
	else
	{
		write_word_fd(1, cmd, start);
		if (!no_newline)
			write(1, "\n", 1);
	}
}

