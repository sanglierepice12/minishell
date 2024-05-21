/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:43:43 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 18:43:43 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	put_str_fd(char *str, int fd)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, &str, len);
}