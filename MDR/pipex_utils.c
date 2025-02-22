/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:02:36 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/18 14:13:09 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	begwithsp(char *str, char *file, t_pipex *ptr)
{
	int	i;
	int	fd;

	i = 0;
	if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v'
		&& str[i] != '\f' && str[i] != '\r')
		return (0);
	if (file)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error(ptr);
		close(fd);
		perror("PipeX");
	}
	else if (!file)
		perror("PipeX");
	return (1);
}

t_pipex	*ferst_check(t_pipex *ptr, char *v[], char **env)
{
	int	i;

	i = 0;
	ptr->fd1 = open(v[1], O_RDONLY);
	if (ptr->fd1 < 0)
		perror("PipeX");
	else
		if (access(v[1], F_OK | R_OK))
			perror("PipeX");
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	ptr->path = crate_cmd(env, i, v[2], &ptr->cmd1);
	ptr->cmd2 = ft_split(v[3], ' ');
	if (begwithsp(v[3], v[4], ptr) == 1)
		error(ptr);
	begwithsp(v[2], NULL, ptr);
	return (ptr);
}

void	sec_cmd(t_pipex *ptr, char **env)
{
	close(ptr->pip[1]);
	if (dup2(ptr->fd2, STDOUT_FILENO) < 0)
	{
		write(2, "Pipex: permission denied: ", 27);
		ft_putstr_fd(ptr->v[4], 2);
		ft_exit(1);
	}
	if (dup2(ptr->pip[0], STDIN_FILENO) < 0)
	{
		write(2, "Pipex: permission denied: ", 27);
		ft_putstr_fd(ptr->v[4], 2);
		ft_exit(1);
	}
	close(ptr->pip[0]);
	if (execve(ptr->path, ptr->cmd1, env) < 0)
		error(ptr);
}

static char	*return_cmd(char ***cmd, char **path)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (path[len])
		len++;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], *cmd[0]);
		if (!path[i])
		{
			write(1, "permission denied\n", 19);
			ft_exit(1);
		}
		if (!access(path[i], F_OK | R_OK | X_OK))
			break ;
		i++;
	}
	if (!path[i])
		i--;
	return (path[i]);
}

char	*crate_cmd(char **env, int i, char *v, char ***cmd)
{
	char	**path;

	if (!env[i] || !*env)
		return (ft_putstr_fd("Error", 2), ft_exit(1), NULL);
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (write(2, "Error\n", 7), ft_exit(1), NULL);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	*cmd = ft_split(v, ' ');
	if (!*cmd)
		return (write(2, "permission denied\n", 19), ft_exit(1), NULL);
	if (*cmd[0][0] == '/' || *cmd[0][0] == '.')
	{
		if (!access(*cmd[0], F_OK | R_OK | X_OK))
			return (*cmd[0]);
		else
			return (return_cmd(cmd, path));
	}
	return (return_cmd(cmd, path));
}
