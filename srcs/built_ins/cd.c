/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:22:57 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/27 03:33:40 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_token **token)
{
	char	*path;
	
	path = (*token)->next->value;
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
	(*token) = (*token)->next;
}
