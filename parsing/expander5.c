/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:54:25 by ecardoua          #+#    #+#             */
/*   Updated: 2026/07/06 08:45:32 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_ft_expand_strdup(char *s, t_data *data)
{
	t_classic	clas;
	char		**split_expand;

	if (split_init(&clas, s, &split_expand, data))
		return (NULL);
	while (clas.s[clas.i])
	{
		while (clas.l < split_expand_size(clas.s, data, true))
		{
			split_expand[clas.l++] = ft_calloc(split_size_malloc_expand(clas.s,
						data, &clas.m) + 1, sizeof(char));
			if (!split_expand[clas.l - 1])
			{
				ft_free_split(split_expand);
				return (NULL);
			}
		}
		clas.l = 0;
		quote_state(&clas.s_quote, &clas.d_quote, clas.s, clas.i);
		if (split_expand_extra(&clas, data, &split_expand))
			return (NULL);
	}
	split_expand[++clas.l] = NULL;
	return (split_expand);
}

void	del_quote_extra(t_classic *clas, char **new_args)
{
	if (clas->s[clas->i] == '\'' && clas->d_quote % 2 == 0)
	{
		clas->s_quote++;
		clas->i++;
	}
	else if (clas->s[clas->i] == '"' && clas->s_quote % 2 == 0)
	{
		clas->d_quote++;
		clas->i++;
	}
	else
		(*new_args)[clas->j++] = clas->s[clas->i++];
	return ;
}

char	*del_quote(char *args, bool keep_quotes)
{
	char		*new_args;
	t_classic	clas;

	if (!args)
		return (NULL);
	if (keep_quotes)
		return (ft_strdup(args));
	clas.d_quote = 0;
	clas.s_quote = 0;
	clas.i = 0;
	clas.j = 0;
	clas.s = args;
	new_args = malloc((ft_strlen(args) - num_del_quote(args) + 1)
			* sizeof(char));
	while (clas.s[clas.i])
		del_quote_extra(&clas, &new_args);
	new_args[clas.j] = '\0';
	return (new_args);
}
