/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:52:31 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/13 18:50:00 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_up(char **path)
{
	t_pipe	pi;

	pi.i = -1;
	while (path[++pi.i])
		free(path[pi.i]);
	free(pi.path);
}

char	**parse_path(char **env)
{
	t_pipe	pi;
	char	*tmp;

	pi.i = -1;
	pi.path = 0;
	while (env[++pi.i])
	{
		if (ft_strncmp(env[pi.i], "PATH=", 5) == 0)
		{
			pi.path = ft_split(&env[pi.i], ':');
			if (!pi.path)
				return (env);
			pi.j = -1;
			while (pi.path[++pi.j])
			{
				tmp = pi.path[pi.j];
				pi.path[pi.j] = ft_strjoin(tmp, "/");
				free(tmp);
			}
		}
	}
	return (pi.path);
}

void	parent_process(char **argv, char **env, int *fd)
{
	;
}

void	child_process(char **argv, char **env, int *fd)
{
	;
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc != 5)
		return ("Wrong number of inputs", EXIT_FAILURE);
	if (pipe(fd) == -1)
		return ("Pipe Error", EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		child_process(argv, env, fd);
	parent_process(argv, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
