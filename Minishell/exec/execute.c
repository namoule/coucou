/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/09 23:39:12 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void free_exec(t_command *cmd)
{
	free_table(cmd->table);
	free_cmd(cmd);
}

void execute(t_command *cmd, char **envp)
{
    char *pathoche;
    struct stat file_stat;

    if (!cmd || !cmd->args || !cmd->args[0])
    {
        perror("invalid command");
        return;
    }
    if (ft_strchr(cmd->args[0], '/') != 0)
        pathoche = ft_strdup(cmd->args[0]);
    else
        pathoche = find_path(cmd);
    if (!pathoche)
    {
        perror(cmd->args[0]);
		free_exec(cmd);
        return;
    }
    if (stat(pathoche, &file_stat) == -1)
    {
        perror(cmd->args[0]);
		free_exec(cmd);
        free(pathoche);
        return;
    }
    if (!S_ISREG(file_stat.st_mode) || access(pathoche, X_OK) != 0)
    {
        perror(cmd->args[0]);
		free_table(cmd->table);
		free_cmd(cmd);
        free(pathoche);
        return;
    }
    if (execve(pathoche, cmd->args, envp) == -1)
    {
        perror("Erreur d'exécution : ");
        free(pathoche);
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
	cmd->table->ipids++;
	return (0);
}
