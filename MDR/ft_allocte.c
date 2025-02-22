/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:24:09 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/17 13:56:52 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(void *ptr, int flag)
{
	static void	*lst[INT_MAX];
	static int	i;
	int			j;

	if (flag)
	{
		j = 0;
		while (lst[j])
		{
			free(lst[j]);
			j++;
		}
	}
	else
		lst[i++] = ptr;
}

void	ft_exit(int flag)
{
	ft_free(NULL, 1);
	exit(flag);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Pipex (Malloc)");
		ft_exit(1);
	}
	ft_free(ptr, 0);
	return (ptr);
}
