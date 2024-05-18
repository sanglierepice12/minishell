#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_input
{
	char	*command;
	char	**argv;
	int		args;
}				t_input;

int		check_command(char *input);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	parse_in_struct(t_input *command, char *input);
size_t	ft_strlen(const char *str);

#endif
