/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzooceancardouat <enzooceancardouat@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:21:56 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/17 15:37:47 by enzooceanca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0); //undeclared function on my MacBook
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}
