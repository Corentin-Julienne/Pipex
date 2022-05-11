/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 18:14:16 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	leaks_killer(void)
{
	system("leaks pipex");
}

static void	file_opener(t_vars *vars, int type)
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
		vars->fd_out = open(vars->av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static int	pipex(t_vars *vars)
{
	int			pipeline[2];
	int			rtn_code;

	if (pipe(pipeline) == -1)
	{
		close_in_and_out(vars->fd_in, vars->fd_out);
		manage_syscall_err(vars);
	}
	vars->pipes = pipeline;
	redirection(vars, vars->av[2], 0);
	redirection(vars, vars->av[3], 1);
	close(pipeline[0]);
	close(pipeline[1]);
	vars->rtn_code = wait_process_and_exit_status(vars, 0);
	vars->rtn_code = wait_process_and_exit_status(vars, 1);
	rtn_code = vars->rtn_code;
	cleaner(vars);
	return (rtn_code);
}

static int	handle_fds(t_vars *vars)
{
	int			rtn_code;

	file_opener(vars, IN);
	file_opener(vars, OUT);
	rtn_code = pipex(vars);
	return (rtn_code);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	if (ac != 5)
	{
		ft_putstr_fd("pipex : Wrong number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
	{
		ft_putstr_fd("pipex : Cannot allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_struct(vars, av, env);
	return (handle_fds(vars));
}
