/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:00:19 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/04 13:39:17 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd1, char *cmd1)
{
	int	fd2;

	if (dup2(fd1, fd2) < 0)
		return ("Dup failure");
	close(stdin);
	dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd1);
	// excve
	exit(EXIT_FAILURE);
}

void	parent_process(int fd2, char *cmd2)
{
	int	status;

	waitpid(-1, &status, 0);
	if (dup2(fd1, fd2) < 0)
		return ("Dup failure");
	close(stdin);
	dup2(fd2, STDOUT_FILENO);
	dup2(end[0], STDOUT_FILENO);
	close(end[1]);
	close(fd2);
	//excve
	exit(EXIT_FAILURE);
}

void	pipex(int fd1, int fd2, char **argv, char **env)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: No infile created"));
	if (parent == 0)
		child_process(fd1, argv[2]);
	else
		parent_process(fd2, argv[3]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDONLY | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, argv, env);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		fd;
// 	char	*file;

// 	file = argv[1];
// 	if (argc == 2)
// 	{
// 		if (!access(file, W_OK))
// 		{
// 			fd = open(file, O_WRONLY | O_CREAT, 0644);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			printf("I do have permission to write in this file\n");
// 		}
// 		else
// 			printf("I have no permission to write in this file");
// 	}
// 	return (0);
// }
