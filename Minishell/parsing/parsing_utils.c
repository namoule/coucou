/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 13:58:41 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	helper_fd_out(t_command *cmd, char *file, int flags)
{
	int	fd;

	if (cmd->fd_out != -2 && cmd->fd_out != -3)
		close(cmd->fd_out);
	fd = open_fct_check(file, flags);
	if (fd == -1)
	{
		cmd->fd_out = -3;
		return (perror(file), 1);
	}
	cmd->fd_out = fd;
	return (0);
}

int	find_fd_out(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->sargs[i])
	{
		if (ft_strcmp(cmd->sargs[i], ">") == 0)
			if (helper_fd_out(cmd, cmd->sargs[++i], 1))
				return (1);
		if (ft_strcmp(cmd->sargs[i], ">>") == 0)
			if (helper_fd_out(cmd, cmd->sargs[++i], 2))
				return (1);
		i++;
	}
	return (0);
}

t_command	*fill_t_command(char *input, char **envp, int return_value)
{
	t_command	*cmd;

	(void)input;
	cmd = tokenize_input(input, envp, return_value);
	if (!cmd)
		return (NULL);
	change_args_for_exec(cmd);
	return (cmd);
}
