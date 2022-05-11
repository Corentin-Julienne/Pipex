/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:28:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 00:10:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* copycat bash behavior returning exit code 126 */

static void	handle_access_denied(char *path_with_cmd,
	t_vars *vars, char **cmd_args)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(path_with_cmd, STDERR_FILENO);
	ft_putstr_fd(" : Permission denied\n", STDERR_FILENO);
	free_split(cmd_args);
	free(path_with_cmd);
	cleaner(vars);
	exit(126);
}

/* check if path 1) exist and 2) allow access to a given CMD */

static int	is_path_functionnal(char *path_with_cmd,
	t_vars *vars, char **cmd_args)
{
	if (access(path_with_cmd, R_OK) == 0)
	{
		if (access(path_with_cmd, X_OK) != 0)
		{
			handle_access_denied(path_with_cmd, vars, cmd_args);
			return (1);
		}
		else
			return (0);
	}
	else
		return (1);
}

static char	*join_cmd_to_path(t_vars *vars, char **cmd_args, int i)
{
	char	*path;
	char	*cmd_slash;

	cmd_slash = ft_strchr(cmd_args[0], '/');
	if (cmd_slash && cmd_slash[0] == '/')
		return (cmd_args[0]);
	path = ft_strjoin(vars->new_paths[i], cmd_args[0]);
	if (!path)
	{
		ft_putstr_fd("pipex : Unable to allocate memory\n", STDERR_FILENO);
		free_split(cmd_args);
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	return (path);
}

static void	display_cmd_not_found(char **cmd_args)
{
	if (ft_strchr(cmd_args[0], '/'))
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("pipex: Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/* cmd_exec is executed only within child processes
exit code 127 is execve not activated succesfully,
otherwise 0 if cmd activated succesfully */

void	cmd_exec(t_vars *vars, char *cmd)
{
	char		**cmd_args;
	char		*path_with_cmd;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	vars->i = 0;
	while (vars->new_paths[vars->i])
	{
		path_with_cmd = join_cmd_to_path(vars, cmd_args, vars->i);
		if (is_path_functionnal(path_with_cmd, vars, cmd_args) == 0)
			execve(path_with_cmd, cmd_args, vars->env);
		free(path_with_cmd);
		vars->i++;
	}
	display_cmd_not_found(cmd_args);
	free_split(cmd_args);
	cleaner(vars);
	exit(127);
}
