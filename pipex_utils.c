/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:56:35 by iannmari          #+#    #+#             */
/*   Updated: 2022/01/15 12:39:47 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **env)
{
	int		i;
	char	*path;
	char	**path2;

	i = 0;
	path = NULL;
	while (path == NULL)
	{
		path = ft_strnstr(env[i], "PATH", 4);
		i++;
	}
	path2 = ft_split(path + 5, ':');
	return (path2);
}

void	ft_execute(char *argv, char **env)
{
	char	**cmd;
	char	**path2;
	char	*suff;
	char	*path_final;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	path2 = ft_path(env);
	while (path2[i++] != NULL)
	{
		suff = ft_strjoin("/", cmd[0]);
		path_final = ft_strjoin(path2[i], suff);
		free(suff);
		if (access(path_final, 0) != -1)
		{
			if (execve(path_final, cmd, env) < 0)
				error_exit("execve");
		}
		else
			free(path_final);
	}
	error_exit("Command not exist");
}

void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
