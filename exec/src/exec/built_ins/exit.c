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

void	ft_exit(t_glob *glob)
{

	ft_free_all(glob);
/*	if (glob->cmd->args == 1)
		printf("exit\n");*/
	exit(0);
	//return(atoi cast en unsigned char)
}