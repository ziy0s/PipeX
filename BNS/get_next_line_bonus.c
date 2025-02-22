/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:56:24 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/15 19:07:31 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_next_line(int fd)
{
	char	*buff;
	int		readed;
	char	*line;

	line = NULL;
	buff = ft_malloc(2);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buff, 1);
		if (readed == 0 || buff[0] == '\n')
			break ;
		buff[readed] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}
