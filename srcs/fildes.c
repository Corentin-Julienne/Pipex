/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fildes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:22:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/11 17:50:10 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_in_and_out(int fd_in, int fd_out)
{	
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
}
