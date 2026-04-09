/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:22:57 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/02 16:09:40 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_cmd **cmd)
{
	char	*path;
	
	path = (*cmd)->args[0];
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
}
