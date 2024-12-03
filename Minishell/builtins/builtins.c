/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:17 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/03 10:46:25 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	deals_pipe(t_command *cmd)
{
	deal_in_pipe(cmd);
	deal_out_pipe(cmd);
	if (cmd->p[READ_END] >= 0)
		close(cmd->p[READ_END]);
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
}

void	choose(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		*cmd->table->exit_code = exit_shell(cmd, cmd->args, 1);
}

int	deal_builtins(t_command *cmd)
{
	if (pipe(cmd->p) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		deals_pipe(cmd);
		choose(cmd);
		free_table(cmd->table);
		free_cmd(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
	{
		perror("fork");
		return (-1);
	}
	cmd->table->ipids++;
	return (*cmd->table->exit_code);
}

int	deal_deal_builtins(t_command *cmd)
{
	if (deal_builtins(cmd) == -1)
		return (-1);
	if (cmd->pprev != -2 && cmd->pprev != -3)
		close(cmd->pprev);
	if (cmd->next == NULL)
	{
		if (cmd->p[READ_END] >= 0)
			close(cmd->p[READ_END]);
	}
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
	return (0);
}

int	is_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0 || ft_strcmp(cmd->args[0],
			"exit") == 0 || ft_strcmp(cmd->args[0], "pwd") == 0)
		return (deal_deal_builtins(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(unset(&cmd->table->envp, cmd->args[1]));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		cmd->table->envp = ft_export(cmd);
		return (1);
	}
	return (-1);
}
