/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/03/30 14:35:28 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expend(t_token **token)
{
	*token = (*token)->next;
	if (ft_isdigit((*token)->value) == 1)
	{
		(*token)->value = ft_strdup("");
		return ;
	}
	else
	{
		(*token)->value = ft_strdup("stand by");
	}
}
