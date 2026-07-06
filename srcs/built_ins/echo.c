/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:14:17 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 12:10:48 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_echo(t_cmd **cmd, t_data *data)
{
	int	out_fd;

	out_fd = 1;
	data->start = 0;
	data->no_newline = 0;
	while ((*cmd)->args && (*cmd)->args[data->start]
		&& is_n_option((*cmd)->args[data->start]))
	{
		data->start++;
		data->no_newline = 1;
	}
	if ((*cmd)->outfile > -1)
		out_fd = (*cmd)->outfile;
	if ((*cmd)->args && (*cmd)->args[data->start])
		write_word_fd(out_fd, cmd, data->start);
	if (!data->no_newline)
		write(out_fd, "\n", 1);
	data->last_status = 0;
}
