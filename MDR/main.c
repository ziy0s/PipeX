/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:11:48 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/20 10:39:22 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	finish_main(t_pipex *ptr)
{
	int	out;

	close(ptr->pip[0]);
	close(ptr->pip[1]);
	close(ptr->fd1);
	close(ptr->fd2);
	waitpid(ptr->pid1, &out, 0);
	waitpid(ptr->pid2, &out, 0);
	ft_exit(0);
}

static void	first_cmd(t_pipex *ptr, char **env)
{
	close(ptr->pip[0]);
	if (dup2(ptr->fd1, STDIN_FILENO) < 0)
		ft_exit(1);
	if (dup2(ptr->pip[1], STDOUT_FILENO) < 0)
		ft_exit(1);
	close(ptr->pip[1]);
	if (execve(ptr->path, ptr->cmd1, env) < 0)
		error(ptr);
}

static void	midel_main(t_pipex *ptr, char *v[], char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	ptr->cmd2 = ft_split(v[3], ' ');
	if (pipe(ptr->pip) == -1)
		error(ptr);
	ptr->pid1 = fork();
	if (ptr->pid1 < 0)
		error(ptr);
	if (!ptr->pid1)
		first_cmd(ptr, env);
	ptr->path = crate_cmd(env, i, v[3], &ptr->cmd1);
}

void	error(t_pipex *ptr)
{
	perror("PipeX");
	if (ptr)
		finish_main(ptr);
	ft_exit(1);
}

int	main(int c, char *v[], char **env)
{
	t_pipex	*ptr;

	if (c != 5 || !*env)
		return (write(2, "Error\nInvalide Args\n", 21), ft_exit(1), 0);
	if (v[1][0] == '\0' || v[2][0] == '\0' || v[3][0] == '\0' ||
		v[4][0] == '\0')
	{
		write(2, "Error\nInvalide Args\n", 21);
		ft_exit(1);
	}
	ptr = ft_malloc(sizeof(t_pipex));
	ptr = ferst_check(ptr, v, env);
	ptr->v = v;
	midel_main(ptr, v, env);
	ptr->pid2 = fork();
	if (ptr->pid2 < 0)
		error(ptr);
	close(ptr->fd1);
	ptr->fd2 = open(v[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!ptr->pid2)
		sec_cmd(ptr, env);
	finish_main(ptr);
}
