/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 15:13:37 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	deal_out_pipe(t_command *cmd)
{
	if (cmd->fd_out != -2 && cmd->fd_out != -3)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("1dup2");
		if (cmd->fd_out != 2)
			close(cmd->fd_out);
	}
	else if (cmd->next != NULL)
	{
		if (dup2(cmd->p[WRITE_END], STDOUT_FILENO) == -1)
			perror("2dup2");
	}
}

void	deal_in_pipe(t_command *cmd)
{
	if (cmd->fd_in != -2 && cmd->fd_in != -3)
	{
		if (fcntl(cmd->fd_in, F_GETFD) == -1)
			perror("fd_in is not open or invalid");
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			printf("chu la fd = [%d]\n", cmd->fd_in);
			perror("3dup2");
		}
		if (cmd->fd_in != 2)
			close(cmd->fd_in);
	}
	else if (cmd->pprev != -2 && cmd->pprev != -3)
	{
		if (fcntl(cmd->pprev, F_GETFD) == -1)
		{
			perror("pprev is not open or invalid");
		}
		if (dup2(cmd->pprev, STDIN_FILENO) == -1)
		{
			perror("4dup2");
		}
		if (cmd->pprev != 2)
			close(cmd->pprev);
	}
}
