#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <dirent.h>

typedef struct s_build
{
	char	*pwd;
}				t_build;

typedef struct s_input
{
	char	*command;
	char	**argv;
	int		args;
}				t_input;

typedef struct s_glob
{
	t_build	build;
	t_input	command;
}				t_glob;

/*********PARSE*********/
int		check_command(char *input);
int 	parse_in_struct(t_glob *glob, char *input);

/*********UTILS*********/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_str_dup(char *src, char *msg);

/*********EXEC*********/
void	ft_pwd(t_build *build);

/*********BUILT_INS_CALLS*********/
void	ft_call(t_glob *glob, char *input);
void	ft_pwd_call(t_glob *glob, char *dup);
void	ft_cd(char *input);
void	ft_ls();

/*********ALLOC*********/
void	ft_bzero(void *s, size_t n);
void	*ft_cal_loc(size_t nmemb, size_t size);
void	ft_free_all(t_glob *glob);

/*********PRINTING*********/
size_t	ft_strlen(const char *str);
#endif
