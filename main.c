/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:14:49 by iannmari          #+#    #+#             */
/*   Updated: 2022/01/15 12:16:51 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_files(char **argv, int	*filein, int *fileout)
{
	*fileout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	*filein = open(argv[1], O_RDONLY);
	if (*filein == -1 || *fileout == -1)
		return (-1);
	else
		return (0);
}

void	child_pr(int filein, int *p, char **argv, char **env)
{
	if (filein == -1)
		error_exit("filein");
	dup2(filein, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(filein);
	ft_execute(argv[2], env);
}

void	parent_pr(int fileout, int *p, char **argv, char **env)
{
	if (fileout == -1)
		error_exit("filein error");
	dup2(fileout, STDOUT_FILENO);
	dup2(p[0], STDIN_FILENO);
	close(p[1]);
	close(fileout);
	ft_execute(argv[3], env);
	exit(EXIT_SUCCESS);
}

void	pipex(char **argv, char **env)
{
	int	filein;
	int	fileout;
	int	p[2];
	int	pid1;

	ft_get_files(argv, &filein, &fileout);
	pipe(p);
	pid1 = fork();
	if (pid1 == -1)
		error_exit("pipe error");
	if (pid1 == 0)
		child_pr(filein, p, argv, env);
	else
	{
		parent_pr(fileout, p, argv, env);
		waitpid(pid1, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		error_exit("Wrong nubmer of arguments");
	pipex(argv, env);
	exit(EXIT_SUCCESS);
}
