/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/03 22:28:14 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	launch_exec(t_command *cmd, char **envp)
{
	execute_cmd(cmd, envp);
	if (cmd->pprev != -2)
		close(cmd->pprev);
	if (cmd->next == NULL && cmd->p[READ_END] >= 0)
		close(cmd->p[READ_END]);
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
}

int	flunch(t_command *cmd)
{
	int			val;
	int			return_value;
	t_command	*quentin;

	quentin = cmd;
	while (quentin && quentin->args[0])
	{
		val = is_builtins(quentin);
		if (val == -1 && check_cmd(quentin, cmd->table->envp) == 0)
		{
			g_sig = 200;
			launch_exec(quentin, cmd->table->envp);
		}
		else
		{
			quentin->table->pids[quentin->table->ipids] = val;
			quentin->table->ipids++;
		}
		quentin = quentin->next;
	}
	return_value = wait_pids(cmd);
	if (g_sig == 130 || g_sig == 131)
		return_value = g_sig;
	g_sig = 0;
	return (return_value);
}


char	**exec_command(char *line, char **envp, int *return_value)
{
	char		**env = NULL;
	t_command	*cmd;

	if (check_line(line) == -1)
	{
		free(line);
		return (envp);
	}
	if (syntax(line) == -1)
	{
		free(line);
		return (envp);
	}
	cmd = fill_t_command(line, envp, *return_value);
	free(line);
	if (!cmd)
		return (envp);
	if (ft_strcmp(cmd->args[0], "exit") == 0 && !cmd->next)
		exit_shell(cmd, cmd->args, 0);
	*return_value = flunch(cmd);
	env = get_env(cmd->table->envp);
	free_table(cmd->table);
	free_cmd(cmd);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		return_value;
	char	**env;

	return_value = 0;
	env = get_env(envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		setup_signals();
		line = get_line(env);
		if (!line || handle_exit(line, env))
			continue ;
		if (line[0] != '\0' && line[0] != '\n')
			env = exec_command(line, env, &return_value);
		else
			free(line);
		handle_interrupts(line);
	}
	return (return_value);
}
