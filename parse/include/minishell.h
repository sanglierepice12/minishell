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

typedef struct s_input
{
	char	*command;
	char	**argv;
	int		args;
}				t_input;

int		check_command(char *input);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		parse_in_struct(t_input *command, char *input);
size_t	ft_strlen(const char *str);
int		ft_strlen_quote(char *str, int len, int *quote);

#endif
