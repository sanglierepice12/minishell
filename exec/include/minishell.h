/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:29:49 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 07:40:52 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/ioctl.h>
# include <signal.h>

extern int	g_error_code;

/*********ENUM**********/
typedef enum s_sig
{
	PARENT,
	CHILD,
	HEREDOC
}				t_sig;

/********STRUCT********/
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			flag;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_heredoc
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
	int			*check_m;
	size_t		args;
	ssize_t		initargs;
	t_heredoc	heredoc;
}				t_input;

typedef struct s_glob
{
	size_t		count_cmd;
	int			check_mes;
	t_input		*cmd;
	t_env		*env;
	t_heredoc	heredoc;
}				t_glob;

typedef struct s_redir
{
	int	left;
	int	right;
}				t_redir;

typedef struct s_input_data
{
	char	*input;
	int		i;
	int		lenght;
}				t_input_data;

/*----------PARSE----------*/
int		check_command(char *input);
int		parse_in_struct(t_glob *glob, char *input);
int		ft_strlen_quote(char *str, int len, int *quote);
int		if_in_quote(const char *str, size_t i);
char	*delete_quote(char *tab, int i);
char	**set_argv(char *input, unsigned long num, t_glob *glob);
int		count_args(char *input, int lenght);
int		get_length_num(char *input, unsigned long number);
char	**check_apply_heredoc(char **argv, t_input *command);
char	*expand_single_var(char *word, t_glob *glob, const size_t *i);
int		remove_and_stock_all_heredoc(char **argv, \
		t_input *cmd, unsigned long i);
void	remove_heredoc(char **argv, int pos, t_input *command);
char	*ft_itoa(int num);
int		check_env(char **argv, t_glob *glob, unsigned long num);
int		check_redir(char **argv, t_glob *glob, unsigned long num);
char	*parse_word(char *input, int *i, t_glob *glob);
char	*copy_word_env(char *input, size_t i);
int		get_heredoc_infile(char **argv, t_input *cmd);
char	**add_tab(char *input, char **tab, size_t *size);
int		get_heredoc_outfile(char **argv, t_input *cmd);
char	**rs_heredoc(char **argv, t_input *cmd, int i);

void	show_struct(t_input *command);

/*----------LIB----------*/
int		ft_isspace(char c);
void	*ft_memset(void *s, int c, size_t n);

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
char	*ft_strdup(const char *str);
char	**ft_strstrdup(char **str);

/*----------BUILT_INS_CALLS----------*/
bool	ft_is_builtin(char *cmd);
void	ft_call_builtins(t_glob *glob, t_input cmd);

/*----------BUILT_INS----------*/
void	ft_pwd(t_input *cmd, t_env **env);
void	ft_cd(t_glob *glob, t_input *cmd);
void	ft_echo(t_input *cmd);
void	ft_get_env(t_glob *glob, char **env);
void	ft_get_env_follow(char **env, t_glob *glob);
void	ft_unset(t_glob *glob, t_input *cmd);
void	ft_export(t_env **env, t_input *cmd);
void	ft_exit(t_glob *glob, t_input *cmd);
void	ft_env(t_glob *glob, t_input *cmd);
void	ft_update_old_pwd(t_env **env, char *value, char *path);
void	ft_update_env_value(t_env *temp, char *path, t_env **env);

/*----------EXECUTION----------*/
void	ft_init_exec(t_glob *glob);
char	**ft_get_all_path(t_env	**env);
void	ft_get_all_path_follow(t_env *temp, size_t *len);
void	ft_reset_in_out(t_glob *glob);
void	ft_unlink_cmd(t_glob *glob);
bool	ft_here_doc_tester(t_input *cmd);
void	ft_executor(t_glob *glob);
void	ft_exec_built_in(t_glob *glob);
void	ft_children(t_glob *glob, int pipefd[2], const size_t *i);

/*----------SIGNALS----------*/
void	ft_handle_signal(t_sig SIG);
void	ft_handle_execution_signal(void);
void	handle_sigpipe(int sig);
void	handle_sigint(int sig);
void	handle_sigchild(int sig);
void	handle_sighere(int sig);

/*----------FREE&&ALLOC----------*/
void	ft_bzero(void *s, size_t n);
void	*ft_cal_loc(size_t nmemb, size_t size);
void	ft_free_here_doc(t_heredoc *heredoc);
void	ft_free_cmd(t_glob *glob);
void	ft_free_env(t_env *env);
void	ft_free_this_node(t_env *head);
void	free_tab(char **tab, size_t lenght);
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

/*----------COLORS----------*/
# define RESET   "\033[0m"
# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */
# define YELLOW  "\033[33m"      /* Yellow */
# define BLUE    "\033[34m"      /* Blue */
# define MAGENTA "\033[35m"      /* Magenta */
# define CYAN    "\033[36m"      /* Cyan */
# define WHITE   "\033[37m"      /* White */
# define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
# define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif
