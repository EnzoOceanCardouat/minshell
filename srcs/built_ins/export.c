/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 04:15:12 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 13:15:37 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_count(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		if (!(env_list->line[0] == '_' && env_list->line[1] == '='))
			count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	**env_to_array(t_env *env_list, int count)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		if (!(env_list->line[0] == '_' && env_list->line[1] == '='))
			env[i++] = env_list->line;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

static void	sort_env_array(char **env, int count)
{
	int		i;
	int		j;
	int		min;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		min = i;
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[j], env[min]) < 0)
				min = j;
			j++;
		}
		if (min != i)
		{
			tmp = env[i];
			env[i] = env[min];
			env[min] = tmp;
		}
		i++;
	}
}

int	num_of_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_data *data, t_cmd **cmd)
{
	int		i;
	int		n;
	int		count;
	char	**env_array;

	i = 0;
	n = num_of_args((*cmd)->args);
	if (!n)
	{
		count = env_count(data->env_list);
		env_array = env_to_array(data->env_list, count);
		if (!env_array)
			return ;
		sort_env_array(env_array, count);
		while (i < count)
			printf("declare -x %s\n", env_array[i++]);
		free(env_array);
	}
	else
	{
		while (i < n)
		{
			if (!is_valid_identifier((*cmd)->args[i]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd((*cmd)->args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				data->last_status = 1;
			}
			else
			{
				add_env(data, (*cmd)->args[i]);
				data->last_status = 0;
			}
			i++;
		}
		update_env_cpy(data);
	}
}
