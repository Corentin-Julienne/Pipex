/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:40:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 01:59:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// static void	first_redir(t_vars *vars)
// {
// 	if (dup2(vars->pipes[1], STDOUT_FILENO) == -1)
// 	{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (dup2(vars->fd_in, STDIN_FILENO) == -1)
// 	{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (close(vars->fd_in) == -1)
// 		perror("pipex");
// }

// static void	last_redir(t_vars *vars, int iter)
// {
// 	if (dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
// 	{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
// 	{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (close(vars->fd_out) == -1)
// 		perror("pipex");
// }

// static void	smart_dup2(t_vars *vars, int iter)
// {
// 	if (iter == 0)
// 		first_redir(vars);
// 	else if (iter == vars->num_of_pipes)
// 		last_redir(vars, iter);
// 	else
// 	{
// 		if (dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
// 		{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 		}
// 		if (dup2(vars->pipes[(iter * 2) + 1], STDOUT_FILENO) == -1)
// 		{
// 		child_cleaner(vars);
// 		perror("pipex");
// 		exit(EXIT_FAILURE);
// 		}
// 	}
// }

static void	first_redir(t_vars *vars)
{
	dup2(vars->pipes[1], STDOUT_FILENO);
	dup2(vars->fd_in, STDIN_FILENO);
	close(vars->fd_in);
}

static void	last_redir(t_vars *vars, int iter)
{
	dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO);
	dup2(vars->fd_out, STDOUT_FILENO);
	close(vars->fd_out);
}

static void	smart_dup2(t_vars *vars, int iter)
{
	if (iter == 0)
		first_redir(vars);
	else if (iter == vars->num_of_pipes)
		last_redir(vars, iter);
	else
	{
		dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO);
		dup2(vars->pipes[(iter * 2) + 1], STDOUT_FILENO);
	}
}

static void	close_useless_pipes(t_vars *vars, int iter)
{
	int			i;

	i = 0;
	while (iter == 0 && i < vars->num_of_pipes * 2)
	{
		if (i != 1)
			close(vars->pipes[i]);
		i++;
	}
	while (iter > 0 && i < vars->num_of_pipes * 2)
	{
		if (i != ((iter * 2) - 2) && i != ((iter * 2) + 1))
			close(vars->pipes[i]);
		i++;
	}
}

int	child_process(t_vars *vars, char *cmd, int iter)
{
	close_useless_pipes(vars, iter);
	smart_dup2(vars, iter);
	cmd_exec(vars, cmd);
	return (0);
}
