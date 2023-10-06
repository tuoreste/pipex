/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:30:39 by otuyishi          #+#    #+#             */
/*   Updated: 2023/10/06 16:25:41 by otuyishi         ###   ########.fr       */
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
	pi.path = NULL;
	while (env[++pi.i])
	{
		if (ft_strncmp(env[pi.i], "PATH=", 5) == 0)
		{
			pi.path = ft_split(env[pi.i], ':');
			if (!pi.path)
				return (NULL);
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

char	*execute_command(char *str_cmds, char **env)
{
	t_pipe	pi;

	pi.i = -1;
	pi.path = parse_path(env);
	if (!pi.path)
		error("Path Error");
	pi.cmd = ft_split(str_cmds, ' ');
	if (!pi.cmd)
		error("Command Error");
	while (pi.path[++pi.i])
	{
		pi.path_cmd = ft_strjoin(pi.path[pi.i], pi.cmd[0]);
		if (access(pi.path_cmd, F_OK | X_OK) == 0)
			return (pi.path_cmd);
		free(pi.path_cmd);
	}
	return (pi.cmd[0]);
}
