/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:15 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/18 15:17:56 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(char *command, char **env, int infd, int outfd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_close();
		put_message("Error: fork()\n");
	}
	if (pid == 0)
	{
		if (dup2(infd, STDIN_FILENO) < 0)
			ft_exit(1);
		if (dup2(outfd, STDOUT_FILENO) < 0)
			ft_exit(1);
		ft_close();
		execute_command(command, env);
	}
}

static void	pipeline(int s[], char **av, char **env, int infd)
{
	int	outfd;
	int	fds[2];
	int	prev_in;
	int	i;

	i = s[0];
	prev_in = infd;
	while (i < s[1] - 2)
	{
		piper(fds, prev_in, infd);
		child_process(av[i], env, prev_in, fds[1]);
		ft_closer(prev_in, fds[1], -1, -1);
		prev_in = fds[0];
		i++;
	}
	outfd = ft_opner_file(s[0], av[s[1] - 1]);
	if (outfd < 0)
	{
		ft_close();
		put_message("Error: no such file or directory\n");
	}
	child_process(av[i], env, prev_in, outfd);
	ft_close();
	while (wait(NULL) > 0)
		;
}

static void	read_and_fill(char **av)
{
	char	*line;
	int		tmpfd;

	tmpfd = ft_opner_file(2, "/tmp/.here_doc");
	if (tmpfd < 0)
		put_message("Error: no such file or directory\n");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(av[2], line, ft_strlen(av[2])) == 0)
			break ;
		line = ft_strjoin(line, "\n");
		if (!line)
			return (write(2, "Error:\npermission denied\n", 26), ft_exit(1));
		write(tmpfd, line, ft_strlen(line));
	}
	close(tmpfd);
}

static void	here_doc(int s[], char **av, char **env)
{
	int	tmpfd;

	read_and_fill(av);
	tmpfd = ft_opner_file(5, "/tmp/.here_doc");
	if (tmpfd < 0)
	{
		unlink("/tmp/.here_doc");
		put_message("Error: no such file or directory\n");
	}
	pipeline(s, av, env, tmpfd);
	close(tmpfd);
	unlink("/tmp/.here_doc");
}

int	main(int c, char *v[], char **env)
{
	int		infd;
	int		start_end[2];

	start_end[0] = 2;
	start_end[1] = c;
	if (c < 5 || !*env)
		put_message("Error: invalid arguments!\n");
	if (ft_strncmp("here_doc", v[1], 8) == 0)
	{
		if (c != 6)
			put_message("Error: invalid arguments!\n");
		start_end[0] = 3;
		here_doc(start_end, v, env);
	}
	else
	{
		infd = open(v[1], O_RDONLY);
		if (infd < 0)
			put_message("Error: no such file or directory\n");
		pipeline(start_end, v, env, infd);
	}
	return (0);
}
