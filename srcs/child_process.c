/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:27:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 17:48:42 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	first_redir(t_vars *vars)
{
	if (dup2(vars->pipes[1], STDOUT_FILENO) == -1)
		manage_syscall_err(vars);
	if (close(vars->pipes[1]) == -1)
		manage_syscall_err(vars);
	if (dup2(vars->fd_in, STDIN_FILENO) == -1)
		manage_syscall_err(vars);
	if (close(vars->fd_in) == -1)
		manage_syscall_err(vars);
}

static void	last_redir(t_vars *vars)
{
	if (dup2(vars->pipes[0], STDIN_FILENO) == -1)
		manage_syscall_err(vars);
	if (close(vars->pipes[0]) == -1)
		manage_syscall_err(vars);
	if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
		manage_syscall_err(vars);
	if (close(vars->fd_out) == -1)
		manage_syscall_err(vars);
}

static void	smart_dup2(t_vars *vars, int iter)
{
	if (iter == 0)
		first_redir(vars);
	else
		last_redir(vars);
}

int	child_process(t_vars *vars, char *cmd, int iter)
{
	if (iter == 0)
		close(vars->pipes[0]);
	else
		close(vars->pipes[1]);
	smart_dup2(vars, iter);
	cmd_exec(vars, cmd);
	return (0);
}
