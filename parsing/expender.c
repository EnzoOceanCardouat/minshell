/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/09 15:41:05 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_env_search(char *src, t_env *env)
{
	char	*expend;

	while (env->next)
	{
		if (ft_strncmp(env->line, src, ft_strlen(src)) == 0 && env->line[ft_strlen(src) +1] == '=')
		{
			expend = ft_substr(env->line, ft_strlen(src +1), ft_strlen(env->line - ft_strlen(src +1)));
			if (!expend)
				return (NULL);
		}
		env = env->next;
	}
	return (expend);
}

static bool	rebuild_args(char *result,t_cmd *args, t_cmd **cmd, int i)
{
	char	*new_args;
	char	*tmp;
	int		j;

	j = -1;
	while (args->args[i][++j] != '$')
	{
		tmp = new_args;
		new_args = ft_strcharjoin(tmp, args->args[i][j++]);
		free(tmp);
	}
	tmp = new_args;
	free(new_args);
	new_args = ft_strjoin(tmp, result);
	if (!new_args)
		return (true);
	free(tmp);
	free((*cmd)->args[i]);
	(*cmd)->args[i] = new_args;
	return (false);
}

static void	ft_extra_expender(char *args, char **result, t_data *data)
{
	int	j;

	j = 0;
	while (args[j])
	{
		if (args[j] == '$')
		{
			j++;
			if (ft_isdigit(args[j]) == 1)
			{
				*result = ft_strdup("");
			}
			*result = ft_env_search(ft_strdup(args), data->env_list);
		}
		j++;
	}
}

bool	expender(t_data *data, t_cmd *args, t_cmd **cmd, t_token *token)
{
	int		i;
	char	*result;

	i = 0;
	while (i < ft_lentab(token) -1)
		printf("args:%s\n", args->args[i++]);
	return (false);
	while (i < ft_lentab(token))
	{
		ft_extra_expender(args->args[i], &result, data);
		i++;
	}
	if (rebuild_args(result, args, cmd, i))
		return (true);
	return (false);
}
