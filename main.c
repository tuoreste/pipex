/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:00:19 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/15 18:37:43 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process(char **argv, char **env, int *fd)
{
	t_pipe	pi;

	pi.in_file = open(argv[1], O_RDONLY, 0644);
	if (pi.in_file < 0)
	{
		ft_putendl_fd("Infile Error", 2);
		return (EXIT_FAILURE);
	}
	dup2(pi.in_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(argv[2], env);
	return (0);
}

int	parent_process(char **argv, char **env, int *fd)
{
	t_pipe	pi;

	pi.out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pi.out_file < 0)
	{
		ft_putendl_fd("Outfile Error", 2);
		return (EXIT_FAILURE);
	}
	dup2(fd[0], STDOUT_FILENO);
	dup2(pi.out_file, STDIN_FILENO);
	close(fd[1]);
	execute(argv[3], env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of inputs", 2);
		return (EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("Pipe Error", 2);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child_process(argv, env, fd);
	else
		parent_process(argv, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
