/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:50 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/31 17:09:04 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_dup_env(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_cpy = malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = -1;
	while (envp[++i])
		env_cpy[i] = ft_strdup(envp[i]);
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*token;
	t_token	*head;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	token = malloc(sizeof(t_token));
	token->next = NULL;
	token->value = NULL;
	head = token;
	cmd = malloc(sizeof(t_cmd));
	cmd->next = NULL;
	cmd->args = ft_strdup("");
	cmd->infile = NULL;
	cmd->outfile = NULL;
	data.env_cpy = ft_dup_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	write(1, "\033[32m        _       _     _          _ _\n\033[36m  /\\/\\ (_)_ __ (_)___| |__   ___| | |\n\033[33m /    \\| | '_ \\| / __| '_ \\ / _ \\ | |\n\033[35m/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |\n\033[31m\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n\n", 221);
	while (1)
	{
		data.input = readline("minishell> ");
		if (!data.input)
			break ;
		if (data.input[0] != '\0')
			add_history(data.input);
		if (!parse_input(&data, &token, &cmd))
			manage_commands(head, &data);
		free_data(&data);
	}
	printf("exit\n");
	return (0);
}
