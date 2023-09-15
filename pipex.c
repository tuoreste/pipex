/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:30:39 by otuyishi          #+#    #+#             */
/*   Updated: 2023/09/15 13:06:51 by otuyishi         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		count;
	char		*dst_dst;
	const char	*src_src;

	count = 0;
	dst_dst = (char *)dst;
	src_src = (const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		dst_dst[count] = src_src[count];
		count++;
	}
	return (dst);
}

char	**parse_path(char **env)
{
	t_pipe	pi;

	pi.i = -1;
	pi.path = 0;
	while (env[++pi.i])
	{
		if (ft_strncmp(env[pi.i], "PATH=", 5) == 0)
		{
			pi.path = ft_split(env[pi.i], ':');
			if (!pi.path)
				return (env);
			pi.j = -1;
			while (pi.path[++pi.j])
			{
				pi.tmp = pi.path[pi.j];
				pi.path[pi.j] = ft_strjoin(pi.tmp, "/");
				free(pi.tmp);
			}
		}
	}
	return (pi.path);
}

int	execute(char *str_cmds, char **env)
{
	t_pipe	pi;

	pi.path = parse_path(env);
	pi.cmd = ft_split(str_cmds, ' ');
	while (pi.path[++pi.i])
	{
		pi.path_cmd = ft_strjoin(pi.path[pi.i], pi.cmd[0]);
		if (access(pi.path_cmd, F_OK | X_OK) == 0)
		{
			free_up(pi.path);
			if (execve(pi.path_cmd, pi.cmd, env) == -1)
			{
				free_up(pi.cmd);
				ft_putendl_fd("Command Error", 2);
				return (EXIT_FAILURE);
			}
		}
		free(pi.path_cmd);
	}
	return (1);
}
