/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:55:15 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 01:57:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	handle_slashes_prbl(t_vars *vars, char **paths_v2)
{
	free_problem_split(paths_v2, vars->i);
	free_split(vars->paths);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars);
	ft_putstr_fd("pipex : Unable to allocate memory\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/* add the ending slashes '/' to the path
in order to strjoin it later with the cmd */

static void	add_slashes(t_vars *vars, char **paths_v2)
{
	char	*tmp;

	while (vars->paths[vars->i])
	{
		paths_v2[vars->i] = ft_strdup(vars->paths[vars->i]);
		if (!paths_v2[vars->i])
			handle_slashes_prbl(vars, paths_v2);
		tmp = ft_strjoin(paths_v2[vars->i], "/");
		if (!tmp)
		{
			free(paths_v2[vars->i]);
			handle_slashes_prbl(vars, paths_v2);
		}
		free(paths_v2[vars->i]);
		paths_v2[vars->i] = tmp;
		if (!paths_v2[vars->i])
			handle_slashes_prbl(vars, paths_v2);
		vars->i++;
	}
	paths_v2[vars->i] = NULL;
}

char	**paths_with_slash(t_vars *vars)
{
	size_t	arr_len;
	char	**paths_v2;

	arr_len = 0;
	while (vars->paths[arr_len])
		arr_len++;
	paths_v2 = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!paths_v2)
	{
		free_split(vars->paths);
		free(vars);
		ft_putstr_fd("pipex: Unable to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars->i = 0;
	add_slashes(vars, paths_v2);
	free_split(vars->paths);
	return (paths_v2);
}

static void	no_path_in_env(t_vars *vars)
{
	free(vars);
	ft_putstr_fd("pipex: There is no path present in the env\n",
		STDERR_FILENO);
	exit(EXIT_FAILURE);
}

char	**recup_paths(t_vars *vars)
{
	char	**paths;
	char	*path_str;

	vars->i = 0;
	path_str = NULL;
	while (vars->env[vars->i])
	{
		if (!ft_strncmp(vars->env[vars->i], "PATH=", 5))
		{
			path_str = vars->env[vars->i] + 5;
			break ;
		}
		vars->i++;
	}
	if (!path_str)
		no_path_in_env(vars);
	paths = ft_split(path_str, ':');
	if (!paths)
	{
		free(vars);
		ft_putstr_fd("pipex: Unable to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (paths);
}
