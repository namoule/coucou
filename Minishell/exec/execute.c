/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/03 10:14:12 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_command *cmd, char **envp)
{
	char	*pathoche;

	if (!cmd || !cmd->args || !cmd->args[0])
		perror("invalid command");
	if (ft_strncmp(cmd->args[0], "/", 1) == 0)
		pathoche = cmd->args[0];
	else
		pathoche = find_path(cmd);
	if (!pathoche)
	{
		perror(cmd->args[0]);
		free_table(cmd->table);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	if(access(pathoche, X_OK) == 0)
	{
		if (execve(pathoche, cmd->args, envp) == -1)
		{
			free(pathoche);
			perror("command execution failed");
		}
	}
}

int	execute_cmd(t_command *cmd, char **envp)
{
	if (pipe(cmd->p) == -1)
		perror("pipe");
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		if (cmd->here_doc != -2 && cmd->here_doc != -3)
			cmd->fd_in = here_doc(cmd->lim);
		deal_in_pipe(cmd);
		deal_out_pipe(cmd);
		close(cmd->p[WRITE_END]);
		close(cmd->p[READ_END]);
		execute(cmd, envp);
		perror(cmd->args[0]);
		free_table(cmd->table);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
		perror("fork");
	else
		close(cmd->p[WRITE_END]);
	cmd->table->ipids++;
	return (0);
}
