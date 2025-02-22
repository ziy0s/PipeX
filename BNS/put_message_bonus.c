/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:59:00 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/20 10:39:58 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	put_message(char *msg)
{
	write(2, msg, ft_strlen(msg));
	if (ft_strncmp(msg, "command not found!", \
	ft_strlen("command not found!")) == 0)
		ft_exit(127);
	ft_exit(1);
}

void	ft_closer(int read_end, int write_end, int infd, int outfd)
{
	if (read_end != -1)
		close(read_end);
	if (write_end != -1)
		close(write_end);
	if (infd != -1)
		close(infd);
	if (outfd != -1)
		close(outfd);
}

void	piper(int fds[], int prev_in, int infd)
{
	if (pipe(fds) == -1)
	{
		ft_closer(prev_in, -1, infd, -1);
		put_message("Error: pipe\n");
	}
}
