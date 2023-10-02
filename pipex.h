/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:01:57 by otuyishi          #+#    #+#             */
/*   Updated: 2023/10/02 14:14:44 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_pipe
{
	int		i;
	int		j;
	char	**path;
	char	**cmd;
	char	*path_cmd;
	char	*tmp;
	pid_t	pid;
	int		status;
	char	**cmd_ein;
	char	**cmd_zwei;
}			t_pipe;

//ft_utils
int		parent_process(char **argv, char **env, int *fd);
int		child2_process(char **argv, char **env, int *fd, char **cmd2_argv);
int		child1_process(char **argv, char **env, int *fd, char **cmd1_argv);

//libft
char	**ft_split(char const *str, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

//main
void	error(char *s);
void	kid(char **argv, char **env, int *fd);
void	dad(char **argv, char **env, int *fd);
int		main(int argc, char **argv, char **env);

//pipex
void	free_up(char **path);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*execute_command(char *str_cmds, char **env);

#endif
