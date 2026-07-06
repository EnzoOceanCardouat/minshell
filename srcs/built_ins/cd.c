/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:22:57 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/08 00:24:40 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(t_data *data, const char *key)
{
	t_env	*cur;
	size_t	klen;

	if (!data || !key)
		return (NULL);
	cur = data->env_list;
	klen = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->line, (char *)key, klen) == 0
			&& cur->line[klen] == '=')
			return (ft_strdup(cur->line + klen + 1));
		cur = cur->next;
	}
	return (NULL);
}

static void	set_env_var(t_data *data, const char *key, const char *value)
{
	if (!data || !key || !value)
		return ;
	data->klen = ft_strlen(key);
	data->tmp2 = ft_strjoin(key, "=");
	data->tmp = ft_strjoin(data->tmp2, value);
	free(data->tmp2);
	data->cur = data->env_list;
	while (data->cur)
	{
		if (ft_strncmp(data->cur->line, (char *)key, data->klen) == 0
			&& data->cur->line[data->klen] == '=')
		{
			free(data->cur->line);
			data->cur->line = data->tmp;
			update_env_cpy(data);
			return ;
		}
		data->cur = data->cur->next;
	}
	add_env(data, data->tmp);
	update_env_cpy(data);
	free(data->tmp);
}

void	ft_cd_bis(t_cmd **cmd, t_data *data, char *path, char *oldpwd)
{
	char	*newpwd;

	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		data->last_status = 1;
		free(oldpwd);
		if (!((*cmd)->args && (*cmd)->args[0]))
			free(path);
		return ;
	}
	if (oldpwd)
		set_env_var(data, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
		set_env_var(data, "PWD", newpwd);
	free(newpwd);
	if (!((*cmd)->args && (*cmd)->args[0]))
		free(path);
}

void	ft_cd(t_cmd **cmd, t_data *data)
{
	char	*path;
	char	*oldpwd;

	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->args && (*cmd)->args[0])
		path = (*cmd)->args[0];
	else
		path = get_env_value(data, "HOME");
	if (!path)
	{
		printf("cd: HOME not set\n");
		data->last_status = 1;
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	ft_cd_bis(cmd, data, path, oldpwd);
	data->last_status = 0;
}
