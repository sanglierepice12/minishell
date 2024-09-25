/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:00:34 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 11:34:15 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_redir_error(char *c)
{
	printf("minisHell: syntax error near unexpected token `%s'\n", c);
	g_error_code = 2;
	return (0);
}

static int	check_more_redir(char **argv, t_redir *redir, size_t i, int y)
{
	if ((redir->left >= 2 || redir->right >= 2) && argv[i][y] == '|')
		return (print_redir_error("|"));
	else if (redir->right > 3)
		return (print_redir_error(">>"));
	else if (redir->right == 3)
		return (print_redir_error(">"));
	else if (redir->right == 2 && redir->left == 1)
		return (print_redir_error("<"));
	else if (redir->right == 2 && redir->left >= 2 && argv[i][y - 1] == '<')
		return (print_redir_error("<<"));
	else if (redir->left > 3)
		return (print_redir_error("<<"));
	else if (redir->left == 3)
		return (print_redir_error("<"));
	else if (redir->left == 2 && redir->right == 1)
		return (print_redir_error(">"));
	else if (redir->left == 2 && redir->right >= 2)
		return (print_redir_error(">>"));
	redir->left = 0;
	redir->right = 0;
	return (1);
}

static int	remove_all_quote(char **argv, t_glob *glob, unsigned long num)
{
	int	i;

	i = 0;
	(void) glob;
	(void) num;
	while (argv[i])
	{
		if (has_quote(argv[i]) == 0)
			argv[i] = delete_quote(argv[i], 0);
		if (!argv[i])
			return (0);
		i++;
	}
	return (1);
}

static int	handle_redir(char **argv, t_redir *redir, size_t i, int y)
{
	if (argv[i][y] == '>')
	{
		if (redir->right == 1 || redir->left == 1)
		{
			if (argv[i][y + 1] == '>')
				return (print_redir_error(">>"));
			return (print_redir_error(">"));
		}
		redir->right++;
	}
	else if (argv[i][y] == '<')
	{
		if (redir->right == 1 || redir->left == 1)
		{
			if (argv[i][y + 1] == '<')
				return (print_redir_error("<<"));
			return (print_redir_error("<"));
		}
		redir->left++;
	}
	return (1);
}

int	check_redir(char **argv, t_glob *glob, unsigned long num)
{
	size_t	i;
	int		y;
	t_redir	redir;

	i = -1;
	redir.left = 0;
	redir.right = 0;
	while (++i != glob->cmd[num].args)
	{
		y = -1;
		while (argv[i][++y])
		{
			if (if_in_quote(argv[i], y) != 0)
				continue ;
			if (!handle_redir(argv, &redir, i, y))
				return (0);
			if (!check_more_redir(argv, &redir, i, y))
				return (0);
		}
	}
	if (redir.right > 0 || redir.left > 0)
		return (print_redir_error("newline"));
	return (remove_all_quote(argv, glob, num));
}
