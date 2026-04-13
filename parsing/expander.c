/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/13 17:04:03 by ecardoua         ###   ########.fr       */
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

// static char	*ft_env_search(char *src, t_env *env)
// {
// 	char	*expand;

// 	while (env->next)
// 	{
// 		if (ft_strncmp(env->line, src, ft_strlen(src)) == 0 && env->line[ft_strlen(src) +1] == '=')
// 		{
// 			expand = ft_substr(env->line, ft_strlen(src +1), ft_strlen(env->line - ft_strlen(src +1)));
// 			if (!expand)
// 				return (NULL);
// 		}
// 		env = env->next;
// 	}
// 	return (expand);
// }

int	size_malloc_expand(char *s)
{
	int	i;
	int	j;
	char	*variable = NULL;
	char	*tmp = NULL;
	char	*expand = NULL;

	i = 0;

	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i;
			j++;
			while (ft_isvariable(s[j]) == 0)
			{
				if (variable)
					tmp = variable;
				else
				{
					variable = ft_strdup("");
					if (!variable)
						return (-1);
				}
				tmp = ft_strdup(variable);
				//free(variable);
				variable = ft_strcharjoin(tmp, s[j++]);
				free(tmp);
			}
			printf("variable:%s\n", variable);
			if (expand)
				tmp = expand;
			else
			{
				tmp = ft_strdup("");
				if (!tmp)
					return (-1);
			}
			expand = ft_strjoin(tmp, getenv(variable));
			if (!expand)
				return (-1);
			free(tmp);
			i += ft_strlen(expand);
			printf("expand:%s\ni:%d\n", expand, i);
		}
		i++;
	}
	//free(variable);
	return (i);
}

char	*ft_expand_strdup(char *s)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*variable;
	char	*tmp;

	i = 0;
	tmp = getenv("USER");
	new_str = malloc(size_malloc_expand(s) *sizeof(char) + 1);
	printf("size string:%d\nexpand:%s\n", size_malloc_expand(s) +1, tmp);
	return (new_str);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			while (ft_isvariable(s[i]) == 0)
			{
				tmp = variable;
				variable = ft_strcharjoin(tmp, s[i++]);
				free(tmp);
			}
			tmp = new_str;
			new_str = ft_strjoin(tmp, getenv(variable));
			if (!new_str)
				return (NULL);
			free(tmp);
			j = ft_strlen(new_str);
		}
		new_str[j] = s[i]; //recheck index to fit
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**ft_cpytab(char **args, t_token *token)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(ft_lentab(token) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		printf("args:%s\n",args[i]);
		break ;
		new_tab[i] = ft_expand_strdup(args[i]);
		if (!new_tab[i])
			return (NULL);
	}
	return (new_tab);
}

bool	expander(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;

	(void)data;
	tmp = ft_cpytab((*cmd)->args, token);
	if (!tmp)
		return (NULL);
	free((*cmd)->args);
	(*cmd)->args = tmp;
	return (false);
}
