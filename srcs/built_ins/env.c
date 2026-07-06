/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:07:58 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/08 14:44:06 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->env_cpy && data->env_cpy[i])
	{
		printf("%s\n", data->env_cpy[i]);
		i++;
	}
	data->last_status = 0;
}
