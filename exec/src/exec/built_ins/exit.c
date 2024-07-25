/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:44:23 by gostr             #+#    #+#             */
/*   Updated: 2024/06/19 17:44:23 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_checker(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				value;
	int				sign;

	i = 0;
	value = 0;
	sign = 1;
	while (ft_checker(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_checker(nptr[i]) == 2)
	{
		value = value * 10 + nptr[i] - 48;
		i++;
	}
	return (value * sign);
}

static bool	check_if_number(const char *cmd)
{
	size_t	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_glob *glob, t_input *cmd)
{
	//int				code;
	unsigned char	exit_code;

	if (!cmd)
		return (ft_err_printf("no cmd", 1));
	if (glob->cmd->args == 1)
	{
		printf("exit\n");
		ft_free_all(glob);
		exit(g_error_code);
	}
	if (!check_if_number(cmd->argv[1]))
	{
		ft_derror("exit", cmd->argv[1], "numeric argument required", 2);
		/*printf("MinisHell: exit: %s: numeric argument required\n", \
			cmd->argv[1]);
		code = 2;*/
	}
	else
		g_error_code = ft_atoi(cmd->argv[1]);
	if (glob->cmd->args > 2)
	{
		g_error_code = 1;
		return (printf("minisHell: exit: too many arguments\n"), (void) 0);
	}
	exit_code = (unsigned char)(g_error_code % 256);
	ft_free_all(glob);
	exit(exit_code);
}
