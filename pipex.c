/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:08:41 by sben-ela          #+#    #+#             */
/*   Updated: 2022/12/07 21:04:08 by sben-ela         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **strs)
{
	int	j;

	j = 0;
	while (strs[j])
	{
		free(strs[j]);
		j++;
	}
	free(strs);
}

char	*check_access(char **env, char *comm)
{
	char	*str;
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(ft_check_path(env), ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, comm);
		free (tmp);
		if (!access(str, X_OK))
		{
			ft_free (path);
			return (str);
		}
		free (str);
		i ++;
	}
	ft_free(path);
	return (0);
}

void	ft_ex_second_comm(int fd[], char **path, char **args2, char *av[])
{
	char	*str;
	int		o_fd;

	str = check_access(path, args2[0]);
	if (!str)
	{
		perror("ERROR");
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	o_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(o_fd, 1);
	execve(str, args2, path);
}

void	ft_ex_first_comm(int fd[], char **path, char **args, char *av[])
{
	char	*str;
	int		i_fd;

	str = check_access(path, args[0]);
	if (!str)
	{
		perror("ERROR");
		exit(1);
	}
	i_fd = open(av[1], O_RDONLY);
	if (i_fd < 0)
	{
		perror("error");
		exit(1);
	}
	dup2(i_fd, 0);
	dup2(fd[1], 1);
	execve(str, args, path);
}

int	main(int ac, char **av, char **env)
{
	char	**args;
	char	**args2;
	int		fd[2];
	pid_t	ps;

	if (ac != 5)
	{
		write(1, "invalid number of arguments", 27);
		return (0);
	}
	args = ft_split(av[2], ' ');
	args2 = ft_split(av[3], ' ');
	pipe(fd);
	ps = fork();
	if (!ps)
		ft_ex_first_comm(fd, env, args, av);
	ps = fork();
	if (!ps)
		ft_ex_second_comm(fd, env, args2, av);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
