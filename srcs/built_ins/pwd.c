/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:12:31 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/03 00:46:33 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char	cwd[1024];
	char	**env;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	env = data->env_cpy;
	while (env && *env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			data->path = *env + 5;
			break ;
		}
		env++;
	}
	data->last_status = 0;
}
