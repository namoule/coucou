/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 15:00:45 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_here_doc(t_command *cmd, int *i)
{
	cmd->fd_in = here_doc(cmd->sargs[*i + 1]);
	(*i)++;
}

int	handle_file_redirection(t_command *cmd, int *i)
{
	int	fd;

	if (cmd->fd_in != -2 && cmd->fd_in != -3)
		close(cmd->fd_in);
	fd = open_fct_check(cmd->sargs[*i + 1], 0);
	if (fd == -1)
	{
		cmd->fd_in = -3;
		perror(cmd->sargs[*i + 1]);
		return (1);
	}
	cmd->fd_in = fd;
	(*i)++;
	return (0);
}

int	find_fd_in(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->sargs[i])
	{
		if (ft_strcmp(cmd->sargs[i], "<<") == 0)
			handle_here_doc(cmd, &i);
		else if (ft_strcmp(cmd->sargs[i], "<") == 0)
		{
			if (handle_file_redirection(cmd, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
