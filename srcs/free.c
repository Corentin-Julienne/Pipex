/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:52:54 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 17:51:07 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* use cleaner function in case of pb and free vars completely and close fds */

void	cleaner(t_vars *vars)
{
	free_split(vars->new_paths);
	if (vars->pids != NULL)
		free(vars->pids);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars);
}

// wip !!!!!!!!

void	child_cleaner(t_vars *vars)
{
	free(vars);
	exit(EXIT_FAILURE);
}

/* in case of syscall failure : exit, clear malloqued elems and print err msg
!!!! NB : does not close fds !!!!*/

void	manage_syscall_err(t_vars *vars)
{
	free_split(vars->new_paths);
	if (vars->pids != NULL)
		free(vars->pids);
	free(vars);
	exit(EXIT_FAILURE);
}

/* quite self-explanatory */

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

/* use in case of problem in alloc memory while using a split */

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
