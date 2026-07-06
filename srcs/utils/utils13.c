/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:29:03 by ecardoua          #+#    #+#             */
/*   Updated: 2026/07/03 12:02:52 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	alloc_create_cmd(t_classic *clas, t_cmd **dup)
{
	clas->l = len_newtab((*dup)->args);
	clas->tab = ft_calloc(clas->l + 1, sizeof(char *));
	if (!clas->tab)
		return (true);
	clas->s = ft_calloc(ft_strlen((*dup)->args[0]) + 1, sizeof(char));
	if (!clas->s)
	{
		free(clas->tab);
		return (true);
	}
	set_index_create_cmd(&clas->i, &clas->j, 0, 1);
	return (false);
}

bool	alloc_tab_create_cmd(t_classic *clas, t_cmd **dup)
{
	while (clas->i < clas->l - 1)
	{
		clas->tab[clas->i++] = ft_calloc(ft_strlen((*dup)->args[clas->j++]) + 1,
				sizeof(char));
		if (!clas->tab[clas->i - 1])
		{
			free(clas->s);
			ft_free_split(clas->tab);
			return (true);
		}
	}
	set_index_create_cmd(&clas->i, &clas->j, 0, 0);
	while ((*dup)->args[0][clas->j])
		clas->s[clas->i++] = (*dup)->args[0][clas->j++];
	set_index_create_cmd(&clas->i, &clas->k, 1, 0);
	return (false);
}

void	final_part_create_cmd(t_classic *clas, t_cmd **cmd)
{
	clas->tab[clas->k] = NULL;
	(*cmd)->cmd = clas->s;
	clas->i = 0;
	while ((*cmd)->args[clas->i])
		free((*cmd)->args[clas->i++]);
	free((*cmd)->args);
	(*cmd)->args = clas->tab;
	clas->tab = NULL;
	clas->s = NULL;
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isvariable(int c)
{
	if (((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')) || c == '_' || c == '?')
		return (0);
	else
		return (1);
}
