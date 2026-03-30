/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:12:31 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/27 03:20:13 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	while (*data->env_cpy)
	{
		if (ft_strncmp(*data->env_cpy, "PATH=", 5) == 0)
		{
			data->path = *data->env_cpy + 5;
			break ;
		}
		data->env_cpy++;
	}
}