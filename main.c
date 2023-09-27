/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:00:19 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/26 19:23:58 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

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

void	kid(char **argv, char **env, int *fd)
{
	t_pipe	p;

	close(fd[0]);
	p.cmd_ein = (char **)malloc(2 * sizeof(char *));
	if (p.cmd_ein == NULL)
		error("Memory allocation error");
	p.cmd_ein[0] = ft_strdup(argv[2]);
	p.cmd_ein[1] = NULL;
	child1_process(argv, env, fd, p.cmd_ein);
	free(p.cmd_ein[0]);
	free(p.cmd_ein);
}

void	dad(char **argv, char **env, int *fd)
{
	t_pipe	p;

	close(fd[1]);
	p.pid = fork();
	if (p.pid == -1)
		error("Second Child Pipe Error");
	if (p.pid == 0)
	{
		p.cmd_zwei = (char **)malloc(2 * sizeof(char *));
		if (p.cmd_zwei == NULL)
			error("Memory allocation error");
		p.cmd_zwei[0] = ft_strdup(argv[3]);
		p.cmd_zwei[1] = NULL;
		child2_process(argv, env, fd, p.cmd_zwei);
		free(p.cmd_zwei[0]);
		free(p.cmd_zwei);
	}
	else
	{
		waitpid(-1, &p.status, 0);
		waitpid(-1, &p.status, 0);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	p;
	int		fd[2];

	if (argc != 5)
		error("Wrong number of inputs");
	if (pipe(fd) == -1)
		error("Pipe creation error");
	p.pid = fork();
	if (p.pid == -1)
		error("First Child Pipe Error");
	if (p.pid == 0)
		kid(argv, env, fd);
	else
		dad(argv, env, fd);
	exit(EXIT_FAILURE);
}
