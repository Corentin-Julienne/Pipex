/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:52:54 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 03:01:44 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/* use cleaner function in case of pb and free vars completely and close fds */

void	cleaner(t_vars *vars)
{
	free_split(vars->new_paths);
	if (vars->pids != NULL)
		free(vars->pids);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars);
}

void	manage_syscall_err(t_vars *vars)
{
	free_split(vars->new_paths);
	if (vars->pids != NULL)
		free(vars->pids);
	free(vars);
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_problem_split(char **split, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}

void	close_in_and_out(int fd_in, int fd_out)
{	
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
}
