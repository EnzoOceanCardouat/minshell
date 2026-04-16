/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/16 14:43:23 by ecardoua         ###   ########.fr       */
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
	size_t	len;

	len = ft_strlen(src);
	while (env->next)
	{
		/*
		 does not get into the if below
		*/
		if (ft_strncmp(env->line, src, len) == 0 && (env->line[len] == '=' || env->line[len] == '\0'))
		{
			expand = ft_substr(env->line, len + 1, ft_strlen(env->line) - len -1);
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

size_t	num_del_quote(char *args)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (args[++i])
	{
		if (args[i] == '\'' && (d_quote == 0 || d_quote%2 == 0))
			s_quote++;
		if (args[i] == '"' && (s_quote == 0 || s_quote%2 == 0))
			d_quote++;
	}
	return (s_quote + d_quote);
}

char	*del_quote(char *args)
{
	int	d_quote;
	int	s_quote;
	int	i;
	char	*new_args;
	int	j;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	j = 0;
	new_args = malloc(sizeof(ft_strlen(args) - num_del_quote(args)));
	while (args[i])
	{
		if (args[i] == '\'' && d_quote%2 == 0)
		{
			s_quote++;
			i++;
		}
		else if (args[i] == '"' && s_quote%2 == 0)
		{
			d_quote++;
			i++;
		}
		else
			new_args[j++] = args[i++];
	}
	new_args[j] = '\0';
	return (new_args);
}

char	**ft_cpytab(char **args, t_token *token, t_env *env, bool del)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(ft_lentab(token) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (del)
			new_tab[i] = del_quote(args[i]);
		else
			new_tab[i] = ft_expand_strdup(args[i], env);
		if (!new_tab[i])
			return (NULL);
		i++;
	}
	return (new_tab);
}

bool	expander(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_cpytab((*cmd)->args, token, data->env_list, false);
	if (!tmp)
		return (true);
	free((*cmd)->args);
	(*cmd)->args = tmp;
	// while (tmp[i])
	// 	printf("new_tab:%s\n", tmp[i++]);
	return (false);
}
