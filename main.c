/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:00:19 by otuyishi          #+#    #+#             */
/*   Updated: 2023/10/04 18:01:32 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	kid(char **argv, char **env, int *fd)
{
	t_pipe	pi;

	close(fd[0]);
	pi.cmd_ein = (char **)malloc(2 * sizeof(char *));
	if (pi.cmd_ein == NULL)
		error("Memory allocation error");
	pi.cmd_ein[0] = ft_strdup(argv[2]);
	pi.cmd_ein[1] = NULL;
	child1_process(argv, env, fd, pi.cmd_ein);
	free(pi.cmd_ein[0]);
	free(pi.cmd_ein);
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
		//----------------------------------------------------------
		if (argv[3])
		{
			p.cmd_zwei = (char **)malloc(2 * sizeof(char *));
			if (p.cmd_zwei == NULL)
				error("Memory allocation error");
			p.cmd_zwei[0] = ft_strdup(argv[3]);
			p.cmd_zwei[1] = NULL;
		}
		else
			error("Permission Denied");
		child2_process(argv, env, fd, p.cmd_zwei);
		free(p.cmd_zwei[0]);
		free(p.cmd_zwei);
		//----------------------------------------------------------
	}
	waitpid(p.pid, &p.status, 0);
}

int	main(int argc, char **argv, char *envp[])
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
		kid(argv, envp, fd);
	else
		dad(argv, envp, fd);
	waitpid(p.pid, NULL, 0);
	exit(EXIT_SUCCESS);
}
