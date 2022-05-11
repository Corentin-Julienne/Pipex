/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 23:53:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	file_opener(t_vars *vars, int type, int ac)
{	
	if (type == IN)
	{
		if (access(vars->av[1], F_OK) != 0)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(vars->av[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		vars->fd_in = open(vars->av[1], O_RDONLY);
	}
	else
		vars->fd_out = open(vars->av[ac - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static int	pipex(t_vars *vars)
{	
	int			rtn_code;
	
	pipes_activation(vars, vars->num_of_pipes);
	vars->cmds_used = 0;
	while (vars->cmds_used < vars->num_cmds)
	{
		redirection(vars, vars->av[vars->cmds_used + 2], vars->cmds_used);
		vars->cmds_used++;
	}
	close_all_pipes(vars);
	vars->cmds_used = 0;
	while (vars->cmds_used < vars->num_cmds)
	{
		wait_process_and_exit_status(vars, vars->cmds_used);
		vars->cmds_used++;
	}
	rtn_code = vars->rtn_code;
	cleaner(vars);
	return (rtn_code);
}

static int	handle_fds(t_vars *vars, int ac)
{
	int			rtn_code;

	file_opener(vars, IN, ac);
	file_opener(vars, OUT, ac);
	rtn_code = pipex(vars);
	return (rtn_code);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	if (ac < 5)
	{
		ft_putstr_fd("Error : not enough arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
	{
		ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars->num_of_pipes = ac - 4;
	init_struct(vars, av, env);
	return (handle_fds(vars, ac));
}
