/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:01:57 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/26 19:22:40 by otuyishi         ###   ########.fr       */
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

//libft
char	**ft_split(char const *str, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);

//pipex
// int		execute(char *str_cmds, char **env);
int		execute_command(char *str_cmds, char **env);
// void	execute_command(char *command, char **env);
char	**parse_path(char **env);
void	free_up(char **path);
//main
int		main(int argc, char **argv, char **env);
int		child_process(char **argv, char **env, int *fd);
int		parent_process(char **argv, char **env, int *fd);

#endif
