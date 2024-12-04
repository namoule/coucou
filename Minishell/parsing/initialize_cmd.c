/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:39:45 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 12:36:17 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_command *allocate_command_struct(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	return cmd;
}

void allocate_command_arrays(t_command *cmd)
{
	cmd->sargs = malloc(sizeof(char *) * 1024);
	cmd->args = malloc(sizeof(char *) * 1024);
	cmd->token_quotes = malloc(sizeof(char *) * 1024);
	cmd->result = malloc(sizeof(char) * 4096);
	if (!cmd->sargs || !cmd->token_quotes || !cmd->result || !cmd->args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void initialize_command_defaults(t_command *cmd, t_table *table)
{
	cmd->result[0] = '\0';
	for (int i = 0; i < 1024; i++)
		cmd->token_quotes[i] = NULL;
	cmd->fd_in = -2;
	cmd->here_doc = -2;
	cmd->lim = NULL;
	cmd->fd_out = -2;
	cmd->pprev = -2;
	cmd->table = table;
	cmd->next = NULL;
}

t_command *initialize_t_command(t_table *table)
{
	t_command *cmd = allocate_command_struct();
	allocate_command_arrays(cmd);
	initialize_command_defaults(cmd, table);
	return (cmd);
}