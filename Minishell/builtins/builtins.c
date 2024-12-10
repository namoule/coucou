/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:17 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/10 13:13:30 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(0);
	else if(ft_strcmp(cmd->args[0], "exit") == 0)
		return(0);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return(0);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return(0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return(0);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return(0);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return(0);
	return (-42);
}

int	is_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return(echo(cmd));
	else if(ft_strcmp(cmd->args[0], "exit") == 0)
		exit_shell(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return(pwd());
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(&cmd->table->envp, cmd->args[1]));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		cmd->table->envp = ft_export(cmd);
		return (1);
	}
	return (-1);
}