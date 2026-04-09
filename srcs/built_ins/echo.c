/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:14:17 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/02 17:44:37 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_word_fd(int fd, t_cmd **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->args[i])
	{
		ft_putstr_fd((*cmd)->args[i], fd);
		if ((*cmd)->args[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo_file(t_cmd **cmd, t_data *data)
{
	if (data->fd_out > -1)
	{
		write_word_fd(data->fd_out, cmd);
		close(data->fd_out);
	}
	else if (data->fd_in > -1)
	{
		write_word_fd(data->fd_in, cmd);
		close(data->fd_in);
	}
	close(data->fd_in);
}

void	ft_echo(t_cmd **cmd, t_data *data)
{
	if (!(*cmd)->args)
		write(1, " \n", 2);
	else if (data->fd_in > -1 || data->fd_out > -1)
		ft_echo_file(cmd, data);
	else
	{
		write_word_fd(1, cmd);
		write(1, "\n", 1);
	}
}
