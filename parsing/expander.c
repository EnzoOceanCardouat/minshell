/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/14 14:34:53 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isvariable(int c)
{
	if (((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')) || c == '_')
		return (0);
	return (1);
}

static char	*ft_env_search(char *src, t_env *env)
{
	char	*expand;

	while (env->next)
	{
		/*
		 does not get into the if below
		*/
		if (ft_strncmp(env->line, src, ft_strlen(src)) == 0 && (env->line[ft_strlen(src) +1] == '=' || env->line[ft_strlen(src) +1] == '\0'))
		{
			expand = ft_substr(env->line, ft_strlen(src +1), ft_strlen(env->line - ft_strlen(src +1)));
			if (!expand)
				return (NULL);
		}
		env = env->next;
	}
	return (expand);
}

int	size_malloc_expand(char *s, t_env *env)
{
	int		i;
	int		j;
	char	*variable;
	char	*tmp;
	char	*expand;

	i = 0;

	variable = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && s[0] != '\'')
		{
			j = i;
			j++;
			while (ft_isvariable(s[j]) == 0)
			{
				tmp = variable;
				variable = ft_strcharjoin(tmp, s[j++]);
				free(tmp);
			}
			tmp = expand;
			expand = ft_strjoin(tmp, ft_env_search(variable, env));
			// (void)env;
			// expand = ft_strjoin(tmp, getenv(variable));
			free(tmp);
			if (!expand)
				return (-1);
			i += ft_strlen(expand);
		}
		i++;
	}
	//free(variable);
	return (i);
}

char	*ft_expand_strdup(char *s, t_env *env)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*variable;
	char	*tmp;
	char	*expand;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(size_malloc_expand(s, env)));
	if (!new_str)
		return (NULL);
	variable = ft_strdup("");
	if (!variable)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && s[0] != '\'')
		{
			i++;
			while (ft_isvariable(s[i]) == 0)
			{
				tmp = variable;
				variable = ft_strcharjoin(tmp, s[i++]);
				free(tmp);
			}
			tmp = new_str;
			expand = ft_env_search(variable, env);
			// (void)env;
			// expand = getenv(variable);
			new_str = ft_strjoin(tmp, expand);
			if (!new_str)
				return (NULL);
			free(tmp);
			j = ft_strlen(new_str);
		}
		new_str[j] = s[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**ft_cpytab(char **args, t_token *token, t_env *env)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(ft_lentab(token) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		new_tab[i] = ft_expand_strdup(args[i], env);
		if (!new_tab[i])
			return (NULL);
	}
	return (new_tab);
}

bool	expander(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_cpytab((*cmd)->args, token, data->env_list);
	if (!tmp)
		return (NULL);
	free((*cmd)->args);
	(*cmd)->args = tmp;
	// while (tmp[i])
	// 	printf("new_tab:%s\n", tmp[i++]);
	return (false);
}
