/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:48:07 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/18 15:03:55 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", ft_strlen("PATH=")))
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*ft_joiner(char **direction, char *command)
{
	int	i;

	i = 0;
	while (direction[i])
	{
		direction[i] = ft_strjoin(direction[i], "/");
		if (!direction[i])
			return (NULL);
		direction[i] = ft_strjoin(direction[i], command);
		if (!direction[i])
			return (NULL);
		if ((access(direction[i], F_OK)) == 0)
			return (ft_strdup(direction[i]));
		i++;
	}
	return (NULL);
}

char	*get_path_command(char *command, char **env)
{
	char	*path;
	char	**directions;
	char	*command_path;

	path = get_path(env);
	if (!path)
		put_message("command not found\n");
	directions = ft_split(path + 5, ':');
	if (!directions || !directions[0])
		put_message("command not found\n");
	command_path = ft_joiner(directions, command);
	if (!command_path)
		return (NULL);
	return (command_path);
}

char	*parse_command(char *command)
{
	if (command && !command[0])
		put_message("permission denied\n");
	if (command[0] == ' ' || command[0] == '\t' || command[0] == '\r'
		|| command[0] == '\n' || command[0] == '\v' || command[0] == '\f')
		put_message("command not found!\n");
	return (command);
}

void	execute_command(char *command, char **env)
{
	char	**cmd_flag;
	char	*path_command;

	command = parse_command(command);
	cmd_flag = ft_split(command, ' ');
	if (!cmd_flag || !cmd_flag[0])
		put_message("command not found!\n");
	if (cmd_flag[0][0] == '/' || cmd_flag[0][0] == '.')
	{
		if ((access(cmd_flag[0], F_OK)) != 0)
			put_message("Error: No such file or directory\n");
		path_command = cmd_flag[0];
	}
	else
	{
		path_command = get_path_command(cmd_flag[0], env);
		if (!path_command)
			put_message("command not found!\n");
	}
	if (execve(path_command, cmd_flag, env) < 0)
		put_message("command not found!\n");
}
