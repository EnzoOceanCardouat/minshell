/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:08:44 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/31 15:09:53 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_git/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_data
{
	char	*input;
	char    *path;
    char    **paths;
    int        i;
    char    *full_path;
    char    **cmd;
    int     id;
	char    **env_cpy;
	char	*command;
	int		fd;
	int		verif;
}			t_data;

typedef enum e_token
{
	WORD,
	LESS,
	MORE,
	D_LESS,
	D_MORE,
	PIPE,
}		t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
	//0 = word
	//1 = <
	//2 = >
	//3 = <<
	//6 = >>
	//5 = |
}					t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			*args;
	char			*infile;
	char			*outfile;
	t_type			append;
	struct s_cmd	*next;
}					t_cmd;

void	ft_bzero(void *s, size_t n);
void	free_data(t_data *data);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
bool	parse_input(t_data *data, t_token **token, t_cmd **cmd);
void	manage_commands(t_token *token, t_data *data);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcharjoin(char const *s1, char const s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_echo(t_token **token, t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_token **token);
void	ft_exit(t_data *data);
void	ft_env(t_data *data);
void	ft_export(t_data *data, t_token **token);
int		num_of_token(t_token *token);
void	ft_unset(t_data *data, t_token **token);
bool	parser(t_token *token, t_cmd **cmd);

#endif
