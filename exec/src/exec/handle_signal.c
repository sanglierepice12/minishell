/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:52:28 by gostr             #+#    #+#             */
/*   Updated: 2024/07/16 19:52:28 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigpipe(int sig)
{
	if (sig == SIGPIPE)
	{
		g_error_code = 141;
		write(STDERR_FILENO, "Broken pipe\n", 12);
	}
}

void	handle_sigint(int sig)
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

void	handle_sigchild(int sig)
{
	if (sig == SIGINT)
		g_error_code = 130;
	if (sig == SIGQUIT)
	{
		g_error_code = 131;
		write(2, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_sighere(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		handle_sigint(sig);
		g_error_code = 131;
	}
}

void	ft_handle_signal(t_sig SIG)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_pipe;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sigemptyset(&sa_pipe.sa_mask);
	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	ft_memset(&sa_pipe, 0, sizeof(sa_pipe));
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sa_pipe.sa_flags = SA_RESTART;
	if (SIG == PARENT)
	{
		sa_int.sa_handler = handle_sigint;
		sa_quit.sa_handler = SIG_IGN;
	}
	else if (SIG == CHILD)
	{
		sa_int.sa_handler = handle_sigchild;
		sa_quit.sa_handler = handle_sigquit;
		sa_pipe.sa_handler = SIG_IGN;
		if (sigaction(SIGPIPE, &sa_pipe, NULL) == -1)
			return (ft_error(1));
	}
	else if (SIG == HEREDOC)
	{
		sa_int.sa_handler = handle_sighere;
		sa_quit.sa_handler = SIG_IGN;
	}
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (ft_error(1));
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (ft_error(1));
}
