/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/06 12:39:06 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_command *cmd, char **envp)
{
	char	*pathoche;

	if (!cmd || !cmd->args || !cmd->args[0])
		perror("invalid command");
	if (ft_strchr(cmd->args[0], '/') != 0)
		pathoche = ft_strdup(cmd->args[0]);
	else
		pathoche = find_path(cmd);
	if (!pathoche)
	{
		perror("pathoche vide : ");
		return ;
	}
	if(access(pathoche, X_OK) == 0)
	{
		if (execve(pathoche, cmd->args, envp) == -1)
		{
			free(pathoche);
			perror(cmd->args[0]);
		}
	}
}

void execute_line(t_command *cmd)
{
	if(is_builtins(cmd) == -1)
		execute(cmd, cmd->table->envp);
	exit(0);
}

int	execute_cmd(t_command *cmd)
{
	if (pipe(cmd->p) == -1)
		perror("pipe");
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		setup_signals();
		deal_in_pipe(cmd);
		deal_out_pipe(cmd);
		close(cmd->p[WRITE_END]);
		close(cmd->p[READ_END]);
		execute_line(cmd);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
		perror("fork");
	else
		close(cmd->p[WRITE_END]);
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa%d----------------%s\n\n\n\n\n",cmd->table->pids[cmd->table->ipids], cmd->args[0]);
	cmd->table->ipids++;
	return (0);
}
