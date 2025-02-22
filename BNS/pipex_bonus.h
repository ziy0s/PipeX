/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:57:57 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/18 12:26:24 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*get_path(char **env);
char	*get_path_command(char *command, char **env);
char	*parse_command(char *command);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_opner_file(int status, char *filename);
int		ft_isalpha(int c);
size_t	ft_strlen(const char *s);
void	execute_command(char *command, char **env);
void	ft_closer(int read_end, int write_end, int infd, int outfd);
void	piper(int fds[], int prev_in, int infd);
void	ft_close(void);
void	*ft_malloc(size_t size);
void	ft_exit(int flag);
void	put_message(char *msg);

#endif
