/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:32:43 by otuyishi          #+#    #+#             */
/*   Updated: 2023/10/02 14:17:03 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*s2;

	s_len = ft_strlen(s1) + 1;
	s2 = malloc(s_len);
	if (s2 == NULL)
		return (NULL);
	return ((char *)ft_memcpy(s2, s1, s_len));
}

int	child1_process(char **argv, char **env, int *fd, char **cmd1_argv)
{
	t_pipe	pi;
	int		infile;

	if (access(argv[1], F_OK) != 0)
	{
		perror("No such file error\n");
		exit(1);
	}
	if (access(argv[1], R_OK) != 0)
	{
		perror("Permission Denied Error");
		exit(1);
	}
	infile = open(argv[1], O_RDONLY);
	dup2(fd[1], 1);
	dup2(infile, 0);
	close(fd[0]);
	close(fd[1]);
	close (infile);
	pi.path_cmd = execute_command(cmd1_argv[0], env);
	pi.cmd = ft_split(cmd1_argv[0], ' ');
	if (execve(pi.path_cmd, pi.cmd, env) == -1)
		error("Execution Error");
	return (0);
}

int	child2_process(char **argv, char **env, int *fd, char **cmd2_argv)
{
	int		out;
	t_pipe	pi;

	out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out == -1)
	{
		perror("Permission Denied Error");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[0]);
	close(fd[1]);
	close(out);
	pi.path_cmd = execute_command(cmd2_argv[0], env);
	pi.cmd = ft_split(cmd2_argv[0], ' ');
	if (execve(pi.path_cmd, pi.cmd, env) == -1)
		error("Execution Error");
	return (0);
}

int	parent_process(char **argv, char **env, int *fd)
{
	int	out;

	out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out == -1)
	{
		perror("Permission Denied Error");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[0]);
	close(fd[1]);
	execute_command(argv[3], env);
	return (0);
}
