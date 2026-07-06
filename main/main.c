/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:50 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/12 16:47:04 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_dup_env(char **envp)
{
	char	**env_cpy;
	int		i;

	if (!envp)
		return (NULL);

	i = 0;
	while (envp[i])
		i++;
	env_cpy = malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		if (!env_cpy[i])
		{
			while (i-- > 0)
				free(env_cpy[i]);
			free(env_cpy);
			return (NULL);
		}
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

static  void	ft_init_all(t_data *data, t_token **token, t_cmd **cmd, char **envp)
{
	*cmd = NULL;
	ft_bzero(data, sizeof(t_data));
	*token = ft_calloc(1, sizeof(t_token));
	if (!*token)
		return ;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->type = NONE;
	(*token)->not_del_quote = false;
	(*token)->quote = false;
	data->fd_in = -1;
	data->fd_out = -1;
	data->last_status = 0;
	data->env_cpy = ft_dup_env(envp);
	data->env_list = char_to_ll(envp);
	data->cmd_head = NULL;
	data->token_head = *token;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*token;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	ft_init_all(&data, &token, &cmd, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	//write(1, "\033[32m        _       _     _          _ _\n\033[36m  /\\/\\ (_)_ __ (_)___| |__   ___| | |\n\033[33m /    \\| | '_ \\| / __| '_ \\ / _ \\ | |\n\033[35m/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |\n\033[31m\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n\n", 221);
	while (1)
	{
		data.input = readline("minishell> ");
		if (!data.input)
			break ;
		if (get_sigint_status())
			data.last_status = 130;
		if (data.input[0] != '\0')
			add_history(data.input);
		if (!parse_input(&data, &token, &cmd))
			manage_commands(cmd, &data);
		reset_sigint_status();
		free_box(&data, &cmd, &token);
	}
	lst_free(data.env_list);
	ft_free_split(data.env_cpy);
	free_box(&data, &cmd, &token);
	clear_history();
	printf("exit\n");
	return (data.last_status);
}
