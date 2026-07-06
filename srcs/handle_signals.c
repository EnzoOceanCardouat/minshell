/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:21:56 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/09 16:24:38 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_sigint_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_sigint_status(void)
{
	return (g_sigint_received);
}

void	reset_sigint_status(void)
{
	g_sigint_received = 0;
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(1, "\n", 1);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
