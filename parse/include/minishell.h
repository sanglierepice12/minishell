/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:29:49 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 03:29:51 by arbenois         ###   ########.fr       */
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

typedef struct s_env
{
	char			*value;
	char			*path;
	bool			flag;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_build
{
	char	*pwd;
}				t_build;

typedef struct	s_heredoc
{
	char	*type_infile;
	char	*file_infile;
	char	*type_outfile;
	char	*file_outfile;
	char	**rest_heredoc;
}				t_heredoc;

typedef struct s_input
{
	char		*command;
	char		**argv;
	t_heredoc	heredoc;
	int			args;
}				t_input;

typedef struct s_glob
{
	t_build	build;
	t_input	*command;
	t_env	*env;
}				t_glob;

/*********PARSE*********/
int		check_command(char *input);
int 	parse_in_struct(t_glob *glob, char *input);
int		ft_strlen_quote(char *str, int len, int *quote);
int		if_in_quote(char *str, int i);
char	*delete_quote(char *tab, int i);
char	**set_argv(char *input, int num, t_glob *glob);
int		count_args(char *input, int lenght);
int		get_length_num(char *input, int number);
char	*expend_env_var(char *word, t_glob *glob);
char	**check_apply_heredoc(char **argv, t_input *command);
int		ft_strlen_bis(char **tab);
void	remove_and_stock_all_heredoc(char **argv, t_input *command);
void	remove_heredoc(char **argv, int pos, t_input *command);
void	free_parse(t_glob *glob, int i);

void	show_struct(t_input *command);

/*********UTILS*********/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_comp_str(char *src, char *str);
char	*ft_super_dup(char *src, char *msg);
char	*ft_dup(const char *s);
char	*ft_str_copy_n(char *str, int n);
t_env	*ft_find_thing_in_env(t_env **env, char *value);
void	ft_dell_node(t_env **temp, t_env **head);
void	ft_free_this_node(t_env *head);
void	free_tab(char **tab, int lenght);

/*********BUILT_INS_CALLS*********/
void	ft_call(t_glob *glob, char *input);
void	ft_pwd_call(t_glob *glob, char *dup);

/*********EXEC*********/
void	ft_pwd(t_build *build);
void	ft_cd(t_glob *glob, char *input);
void	ft_echo(char *input);
void	ft_ls();
void	ft_get_env(t_glob *glob, char **env);
void	ft_unset(t_glob *glob, char *input);
void	ft_export(t_env **env, char *input);

/*********ALLOC*********/
void	ft_bzero(void *s, size_t n);
void	*ft_cal_loc(size_t nmemb, size_t size);
void	ft_free_all(t_glob *glob);

/*********PRINTING*********/
size_t	ft_strlen(const char *str);

/*********LINKED_LIST*********/
void	print_env(t_env **head, int env);
t_env	*ft_lst_last(t_env *lst);
void	ft_lst_add_front(t_env **lst, t_env *new);
void	ft_lst_add_back(t_env **head, t_env *new);
t_env	*ft_new_node(char *value, char *path, bool flag);
void	ft_free_lst(t_env **lst);

#endif
