/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:30:51 by thcotza           #+#    #+#             */
/*   Updated: 2026/05/05 13:34:37 by ecardoua         ###   ########.fr       */
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

int	ft_lentab(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}

