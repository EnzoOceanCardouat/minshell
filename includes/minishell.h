/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:08:44 by thcotza           #+#    #+#             */
/*   Updated: 2026/07/11 16:55:51 by ecardoua         ###   ########.fr       */
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
# include <limits.h>
# include <string.h>
# include <sys/stat.h>

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

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
	int		fd_in;
	int		fd_out;
	int		verif;
	int		prev_fd;
	int		*child_pids;
	int		idx;
	int		pipefd[2];
	int		last_status;
	int		start;
	int		no_newline;
	char	*tmp;
	int		is_negative;
	int		j;
	int		length;
	char	*llong_max_str;
	char	*llong_min_str;
	t_env	*env_list;
	t_cmd	*cmd_head;
	t_token	*token_head;
	t_env	*current;
	t_env	*prev;
	size_t	len;
	t_env	*cur;
	size_t	klen;
	char	*tmp2;
	char	*tmpry;
}			t_data;

typedef enum e_token
{
	NONE = -1,
	WORD,
	REDIR,
	PIPE,
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
	bool			not_del_quote;
	bool			quote;
	int				in;
	int				out;
}					t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_classic
{
	char	*tmp;
	int		d_quote;
	int		s_quote;
	char	*variable;
	char	*expand;
	int		i;
	int		k;
	int		j;
	int		m;
	int		l;
	char	*s;
	char	**tab;
	char	**exel;
	bool	in;
	bool	append;
}			t_classic;

void	ft_bzero(void *s, size_t n);
void	handle_sigint(int sig);
bool	parse_input(t_data *data, t_token **token, t_cmd **cmd);
void	manage_commands(t_cmd *cmd, t_data *data);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcharjoin(char const *s1, char const s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_echo(t_cmd **cmd, t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_cmd **cmd, t_data *data);
void	ft_exit(t_cmd *cmd, t_data *data, int is_piped);
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
char	**ft_cpytab(char **args, t_token *token, t_data *data, bool del);
int		ft_lentab(t_token *token, t_data *data);
void	free_box(t_data *data, t_cmd **cmd, t_token **token);
char	*ft_chardup(char c);
void	child_execute(int prev_fd, int pipefd[2], t_cmd *current, t_data *data);
int		execute_builtin(t_cmd *cmd, t_data *data, int is_piped);
void	execute_command(t_cmd *cmd, t_data *data, int is_piped);
int		count_commands(t_cmd *cmd);
int		is_builtin(char *cmd);
char	**build_argv(t_cmd *cmd);
void	exec_external(t_cmd *cmd, t_data *data);
void	exec_search_paths(t_cmd *cmd, t_data *data, char **argv);
void	exec_with_direct_path(t_cmd *cmd, char **argv,
			char **env_cpy, t_data *data);
void	exec_path_failure(char *path, char **argv, char **paths, t_data *data);
void	wait_children(int *child_pids, int count, t_data *data);
int		create_pipe_or_error(t_data *data, int idx);
int		count_args(t_cmd *cmd);
char	**duplicate_args(t_cmd *cmd, int count);
int		ft_isvariable(int c);
void	init_size_malloc_expand(t_classic *clas, char *s, int k);
int		dollar_and_no_s_quote(char *s, t_classic *clas, t_data *data);
void	free_cmds(t_cmd *cmd);
void	free_tokens_list(t_token *token);
void	free_data(t_data *data);
char	*ft_expand_strdup(char *s, t_data *data);
int		is_valid_number(char *str);
t_env	*char_to_ll_bis(char **env, t_env *current, t_env *head);
char	**ll_to_char_bis(t_env *env_list, char **env, t_env *current, int i);
void	add_env_bis(t_data *data, char *line, t_env *new_node, t_env *current);
void	exec_search_path_bis(t_cmd *cmd, char **argv,
			t_data *data, char *full_path);
int		is_out_of_range_bis(char *str, t_data *data);
void	reset_sigint_status(void);
int		get_sigint_status(void);
bool	need_expand(t_cmd *cmd, char *s, bool tab);
void	free_child_resources(t_data *data);
char	*del_quote(char *args, bool keep_quotes);
bool	ft_isexpand(int c, int s_quote, int d_quote);
bool	need_del_quote(t_cmd *cmd, char *s, bool tab);
void	heredoc_sigint(int sig);
void	set_heredoc_signals(void);
char	*ft_env_search(char *src, t_data *data);
int		while_is_variable(char *s, char **variable, int *i);
int		split_expand_size(char *s, t_data *data, bool need_expand);
bool	need_split_expand(char *s, bool need_expand, t_data *data);
void	child_execute_bis(int pipefd[2], t_cmd *current, t_data *data);
bool	token_next_init(t_token **token);
bool	token_init(t_token **token);
void	quote_state(int *s_quote, int *d_quote, char *s, int i);
bool	env_val_need_split_exp(t_classic *clas, t_data *data,
			int s_quote, int d_quote);
int		count_cmd_words(t_token *token);
char	*ft_env_search(char *src, t_data *data);
void	init_size_malloc_expand(t_classic *clas, char *s, int k);
char	*wiv_tmp_set(char *variable);
int		while_is_variable(char *s, char **variable, int *i);
int		dollar_and_no_s_quote(char *s, t_classic *clas, t_data *data);
void	quote_state(int *s_quote, int *d_quote, char *s, int i);
int		size_malloc_expand(char *s, t_data *data);
bool	ft_isexpand(int c, int s_quote, int d_quote);
bool	variable_digit_q_mark(t_classic *clas);
bool	expand_variable_set(t_classic *clas);
bool	set_expand(t_data *data, t_classic *clas, char **new_str);
char	*ft_expand_strdup(char *s, t_data *data);
bool	expand_str(t_classic *clas, t_data *data, char **new_str);
bool	split_doll_ex(t_classic *clas, t_data *data, char **env_value, int *h);
int		split_dollar_no_squote(t_classic *clas, t_data *data);
bool	split_set_expand(t_classic *clas, t_data *data, char ***split_expand);
bool	split_expand_extra(t_classic *clas, t_data *data, char ***split_expand);
int		split_size_malloc_expand(char *s, t_data *data, int *k);
bool	split_expand_l(t_classic *clas, t_data *data, char ***split_expand);
bool	split_init(t_classic *clas, char *s,
			char ***split_expand, t_data *data);
char	**split_ft_expand_strdup(char *s, t_data *data);
size_t	num_del_quote(char *args);
char	*del_quote(char *args, bool keep_quotes);
void	del_quote_extra(t_classic *clas, char **new_args);
bool	word_tok_ex(t_classic *clas, t_env *env,
			t_token **token, char **nw_wrd);
bool	quote_env(char *src, t_env *env);
int		ft_keep_quote(char *args, int i, t_env *env);
bool	word_token_init(t_token **token, char *word);
bool	fd_need_exp_del_quote(t_classic *clas, char *word, t_data *data);
bool	token_init(t_token **token);
bool	token_next_init(t_token **token);
bool	word_tokenizer(t_classic *clas, t_token **token, t_env *env);
bool	redir_fd_condition(t_classic *clas);
bool	redir_fd_extra(char **word, t_classic *clas);
bool	opn_fd_redir(t_classic *clas, char *word,
			t_data *data, t_token **token);
int		redir_fd(t_classic *clas, t_data *data, t_token **token);
bool	ft_delimiter_extra(char **delimiter, char **tmp, char *args, int i);
bool	result_heredoc(ssize_t r, t_classic *clas, char *delimiter);
int		here_doc_sig(char **line, char **delimiter, t_data **data);
char	*ft_delimiter(char *args, int *i);
int		here_doc(t_classic *clas, t_data **data);
bool	quote_count(char **args);
bool	lexer(char *args, t_token **tok, t_data **data);
bool	lexer_code_return(t_classic clas, t_data **data);
void	lexer_redir_pipe(t_classic *clas, t_data **data, t_token **token);
bool	r_here_doc(int r, t_data **data);
bool	quote_del(t_cmd **cmd, t_token *token, t_data *data);
bool	need_expand_extra(t_cmd *cmd);
bool	need_expand(t_cmd *cmd, char *s, bool tab);
bool	need_del_q_extra(t_cmd *cmd);
bool	need_del_quote(t_cmd *cmd, char *s, bool tab);
void	set_index_create_cmd(int *clas_1, int *clas_2, int one, int two);
int		len_newtab(char **args);
bool	del_args(t_cmd **cmd);
int		size_del_args(t_cmd *cmd);
bool	need_parser(t_token *prev_token, t_data *data);
bool	create_cmd(t_cmd **cmd);
void	final_part_create_cmd(t_classic *clas, t_cmd **cmd);
bool	alloc_tab_create_cmd(t_classic *clas, t_cmd **dup);
bool	alloc_create_cmd(t_classic *clas, t_cmd **dup);
t_cmd	*create_node_cmd(void);
int		here_doc(t_classic *clas, t_data **data);
int		else_heredoc(char **delimiter, pid_t pid, t_data **data);
int		heredoc_part(t_classic *clas, char **delimiter,
			pid_t *pid, char **line);
int		else_heredoc(char **delimiter, pid_t pid, t_data **data);
void	pid_zero(char **line, char *delimiter);
int		env_count(t_env *env_list);
void	ft_export_bis(t_data *data, t_cmd **cmd, int i, int n);
void	third_exec_search_path_bis(t_data *data, t_cmd *cmd,
			char **argv, char *full_path);
void	ascii_art(void);
int		is_valid_identifier(char *str);
void	ft_verif_exit(t_data *data, int is_piped);


#endif
