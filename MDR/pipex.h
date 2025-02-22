/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:46:52 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/20 10:40:15 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	char	*path;
	char	**v;
	pid_t	pid1;
	pid_t	pid2;
	int		pip[2];
}				t_pipex;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*crate_cmd(char **env, int i, char *v, char ***cmd);
char		*ft_strdup(const char *s1);
void		*ft_malloc(size_t size);
void		ft_exit(int flag);
void		sec_cmd(t_pipex *ptr, char **env);
void		error(t_pipex *ptr);
void		ft_putstr_fd(char *s, int fd);
t_pipex		*ferst_check(t_pipex *ptr, char *v[], char **env);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);

#endif