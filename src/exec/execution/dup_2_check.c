/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_2_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:21:15 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 18:21:15 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_dup_two(int fd, int std, t_glob *glob)
{
	if (dup2(fd, std) == -1)
	{
		perror("miniHell");
		ft_free_all(glob);
		exit(EXIT_FAILURE);
	}
}
