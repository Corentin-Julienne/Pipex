/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:39:06 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/12 03:02:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>

# define IN		0
# define OUT	1

typedef struct s_vars
{
	int		i;
	char	**av;
	char	**env;
	char	**paths;
	char	**new_paths;
	int		fd_in;
	int		fd_out;
	int		*pipes;
	pid_t	*pids;
	int		num_of_pipes;
	int		num_cmds;
	int		cmds_used;
	int		rtn_code;
}			t_vars;

/* child_process_bonus.c */

int		child_process(t_vars *vars, char *cmd, int iter);

/* exec_bonus.c */

void	cmd_exec(t_vars *vars, char *cmd);

/* free_bonus.c */

void	manage_syscall_err(t_vars *vars);
void	cleaner(t_vars *vars);
void	free_split(char **split);
void	free_problem_split(char **split, int i);
void	close_in_and_out(int fd_in, int fd_out);

/* init_struct_bonus.c */

void	init_struct(t_vars *vars, char **av, char **env);

/* paths_bonus.c */

char	**paths_with_slash(t_vars *vars);
char	**recup_paths(t_vars *vars);

/* pipes_bonus.c */

void	pipes_activation(t_vars *vars, int num_pipes);
void	close_all_pipes(t_vars *vars);

/* redir_bonus.c */

int		wait_process_and_exit_status(t_vars *vars, int iter);
void	redirection(t_vars *vars, char *cmd, int iter);

#endif
