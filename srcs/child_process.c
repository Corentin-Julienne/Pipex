/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:27:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 01:50:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* in the first redir, we can see that if vars->fd_in does not exist
,then we need to return an EXIT_FAILURE to avoid waitpid to wait forever */

static void	first_redir(t_vars *vars)
{
	dup2(vars->pipes[1], STDOUT_FILENO);
	close(vars->pipes[1]);
	if (dup2(vars->fd_in, STDIN_FILENO) == -1)
		manage_syscall_err(vars);
	close(vars->fd_in);
}

static void	last_redir(t_vars *vars)
{
	dup2(vars->pipes[0], STDIN_FILENO);
	close(vars->pipes[0]);
	dup2(vars->fd_out, STDOUT_FILENO);
	close(vars->fd_out);
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
