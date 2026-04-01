/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:14:17 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/01 14:11:34 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_word_fd(int fd, t_token **token)
{
	while ((*token) && (*token)->next && (*token)->type == WORD)
	{
		ft_putstr_fd((*token)->value, fd);
		if ((*token)->next->next)
			write(fd, " ", 1);
		(*token) = (*token)->next;
	}
}

void	ft_echo_file(t_token **token, t_data *data)
{
	(*token) = (*token)->next;
	write_word_fd(data->fd_in, token);
	if ((*token)->type == D_MORE || (*token)->type == MORE)
	{
		(*token) = (*token)->next;
		if ((*token)->next)
			(*token) = (*token)->next;
		write_word_fd(data->fd_in, token);
	}
	close(data->fd_in);
}

void	ft_echo(t_token **token, t_data *data)
{
	if (!(*token)->next->value)
		write(1, " \n", 2);
	else if (data->fd_in > -1)
		ft_echo_file(token, data);
	else
	{
		(*token) = (*token)->next;
		write_word_fd(1, token);
		write(1, "\n", 1);
	}
}
