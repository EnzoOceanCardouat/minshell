/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:08:44 by thcotza           #+#    #+#             */
/*   Updated: 2026/05/06 10:10:17 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_git/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>


typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char	*input;
	char	*path;
	char	**paths;
	int		i;
	char	*full_path;
	char	**cmd;
	int		id;
	char	**env_cpy;
	char	**original_env;
	char	*command;
	int		fd_in;
	int		fd_out;
	int		verif;
	t_env	*env_list;
}			t_data;

typedef enum e_token
{
	WORD,
	LESS,
	MORE,
	D_LESS,
	D_MORE,
	PIPE,
}	t_type;

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
	char			**args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

void	ft_bzero(void *s, size_t n);
void	handle_sigint(int sig);
bool	parse_input(t_data *data, t_token **token, t_cmd **cmd);
void	manage_commands(t_cmd *cmd, t_data *data, t_token **token);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcharjoin(char const *s1, char const s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_echo(t_cmd **cmd, t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_cmd **cmd);
void	ft_exit(t_cmd *cmd, t_data *data, int is_piped, t_token **token);
void	ft_env(t_data *data);
void	ft_export(t_data *data, t_cmd **cmd);
int		num_of_args(char **args);
void	ft_unset(t_data *data, t_cmd **cmd);
bool	parser(t_token *token, t_cmd **cmd);
t_env	*char_to_ll(char **env);
void	lst_free(t_env *head);
char	**ll_to_char(t_env *env_list);
void	update_env_cpy(t_data *data);
void	add_env(t_data *data, char *line);
void	ft_free_split(char **split);
int		lst_size(t_env *head);
bool	expander(t_cmd **cmd, t_token *token, t_data *data);
char	**ft_cpytab(char **args, t_token *token, t_env *env, bool del);
int	ft_lentab(t_token *token);
void	free_box(t_data *data, t_cmd **cmd, t_token **token);

#endif
