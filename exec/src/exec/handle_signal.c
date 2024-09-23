/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:47:22 by gostr             #+#    #+#             */
/*   Updated: 2024/09/23 17:47:22 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ft_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_error_code = 130;
	}
	if (sig == SIGQUIT)
	{
		g_error_code = 131;
		write(2, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_handle_signal(t_sig SIG)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (SIG == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_sigint);
	}
	if (SIG == CHILD)
	{
		signal(SIGINT, &ft_sigint_child);
		signal(SIGQUIT, &ft_sigint_child);
	}
	if (SIG == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_handle_heredoc);
	}
}