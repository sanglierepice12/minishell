/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:52:28 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 06:07:44 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		handle_sigint(sig);
		g_error_code = 131;
	}
}

static void	set_signal_handlers(t_sig SIG, struct sigaction *sa_int, \
	struct sigaction *sa_quit)
{
	if (SIG == PARENT)
	{
		sa_int->sa_handler = handle_sigint;
		sa_quit->sa_handler = SIG_IGN;
	}
	else if (SIG == CHILD)
	{
		sa_int->sa_handler = handle_sigchild;
		sa_quit->sa_handler = handle_sigquit;
	}
	else if (SIG == HEREDOC)
	{
		sa_int->sa_handler = handle_sighere;
		sa_quit->sa_handler = SIG_IGN;
	}
}

void	ft_handle_signal(t_sig SIG)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	signal(SIGSEGV, &handle_sigsegv);
	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	set_signal_handlers(SIG, &sa_int, &sa_quit);
	if (sigaction(SIGINT, &sa_int, NULL) == -1 || \
		sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (ft_error(1));
}
*/
