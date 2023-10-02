/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:32:43 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/29 10:36:16 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child1_process(char **argv, char **env, int *fd, char **cmd1_argv)
{
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
	dup2(fd[1], 1);
	dup2(open(argv[1], O_RDONLY), 0);
	close(fd[0]);
	close(fd[1]);
	execute_command(cmd1_argv[0], env);
	return (0);
}

int	child2_process(char **argv, char **env, int *fd, char **cmd2_argv)
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
	execute_command(cmd2_argv[0], env);
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
