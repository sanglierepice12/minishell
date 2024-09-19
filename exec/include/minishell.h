/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:29:49 by arbenois          #+#    #+#             */
/*   Updated: 2024/08/29 20:20:54 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int	g_error_code;

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_env
{
	char			*value;
	char			*path;
	bool			flag;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct	s_heredoc
{
	bool	is_there_any;
	char	*type_infile;
	char	**file_infile;
	char	*type_outfile;
	char	*file_outfile;
	char	**rest_heredoc;
}				t_heredoc;

typedef struct s_input
{
	char		*command;
	char		**argv;
	char		**path;
	int			fd;
	size_t		args;
	t_heredoc	heredoc;
}				t_input;

typedef struct s_glob
{
	size_t		count_cmd;
	t_input		*cmd;
	t_env		*env;
	t_heredoc	heredoc;
}				t_glob;

typedef struct	s_redir
{
	int	left;
	int	right;
}				t_redir;

typedef struct	s_input_data
{
	char	*input;
	int		i;
	int		lenght;
}				t_input_data;

/*----------PARSE----------*/
int		check_command(char *input);
int 	parse_in_struct(t_glob *glob, char *input);
int		ft_strlen_quote(char *str, int len, int *quote);
int		if_in_quote(char *str, int i);
char	*delete_quote(char *tab, int i);
char	**set_argv(char *input, unsigned long num, t_glob *glob);
int		count_args(char *input, int lenght);
int		get_length_num(char *input, int number);
char	*expend_env_var(char *word, t_glob *glob);
char	**check_apply_heredoc(char **argv, t_input *command);
int		remove_and_stock_all_heredoc(char **argv, t_input *cmd, unsigned long i);
void	remove_heredoc(char **argv, int pos, t_input *command);
char	*ft_itoa(int num);

void	show_struct(t_input *command);

/*----------LIB----------*/
int		ft_isspace(char c);

/*----------UTILS----------*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_comp_str(const char *src, const char *str);
int		ft_comp_str_for_alpha(const char *s1, const char *s2);
char	*ft_super_dup(char *src, char *msg);
char	*ft_dup(const char *s);
char	*ft_str_copy_n(const char *str, size_t n);
t_env	*ft_find_thing_in_env(t_env **env, char *value);
void	ft_dell_node(t_env **temp, t_env **head);
size_t	ft_strlen(const char *str);
size_t	ft_strlen_double(char **str);
int		ft_strlen_bis(char **tab);
int		ft_str_chr(const char *src, char c);
bool	ft_is_numbalpha(char c);
bool	ft_export_is_printable(char *c);
char	*ft_str_join(char *begin, char *end);
void	ft_free_double_tab(char **tab);
char	**ft_split(char const *s, char c);
void	ft_main_get_env(t_glob *glob);
bool	ft_is_minus(char *c);

/*----------BUILT_INS_CALLS----------*/
bool	ft_is_builtin(char *cmd);
void	ft_call_builtins(t_glob *glob, t_input cmd);

/*----------BUILT_INS----------*/
void	ft_pwd(t_input *cmd, t_env **env);
void	ft_cd(t_glob *glob, t_input *cmd);
void	ft_echo(t_input *cmd);
void	ft_ls();
void	ft_get_env(t_glob *glob, char **env);
void	ft_unset(t_glob *glob, t_input *cmd);
void	ft_export(t_env **env, t_input *cmd);
void	ft_exit(t_glob *glob, t_input *cmd);
void	ft_env(t_glob *glob, t_input *cmd);

/*----------EXECUTION----------*/
void	ft_init_exec(t_glob *glob);
char	**ft_get_all_path(t_env	**env);
void	ft_reset_in_out(t_glob *glob);
void	ft_unlink_cmd(t_glob *glob);
bool	ft_here_doc_tester(t_input *cmd);
void	ft_executor(t_glob *glob);
void	ft_exec_built_in(t_glob *glob);
void	ft_children(t_glob *glob, int pipefd[2], size_t *i);

/*----------SIGNALS----------*/
void	ft_handle_signal();
void	ft_handle_execution_signal(void);

/*----------FREE&&ALLOC----------*/
void	ft_bzero(void *s, size_t n);
void	*ft_cal_loc(size_t nmemb, size_t size);
void	ft_free_here_doc(t_heredoc *heredoc);
void	ft_free_cmd(t_glob *glob);
void	ft_free_env(t_env *env);
void	ft_free_this_node(t_env *head);
void	free_tab(char **tab, int lenght);
void	ft_free_lst(t_env **lst);
void	ft_free_all(t_glob *glob);
void	free_parse(t_glob *glob, int i, ssize_t size_cmd);
void	ft_derror(char *cmd, char *variable, char *followed, int code);
void	ft_env_derror(char *cmd, char *variable, char *followed, int code);
void	ft_err_printf(char *msg, int code);
void	ft_not_found(char *cmd, char *msg, int code);
void	ft_error(int code);

/*----------LINKED_LIST----------*/
void	ft_print_this_node(t_env **env, char *value);
void	print_env(t_env **head, int env);
t_env	*ft_lst_last(t_env *lst);
void	ft_lst_add_front(t_env **lst, t_env *new);
void	ft_lst_add_back(t_env **head, t_env *new);
t_env	*ft_new_node(char *value, char *path, bool flag);
void	ft_change_node(t_env **head, char *value, char *path);
void	bubble_sort(t_env **head);
void	ft_swap_nodes(t_env *a, t_env *b);
t_env	*copy_node(t_env *head);
t_env	*copy_list(t_env *head);

#endif
