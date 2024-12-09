/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:39:45 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/09 17:18:06 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_table	*initialize_t_main(char *line, char **envp, int *return_value)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->num_pids = ft_count_pipe(line);
	table->pids = malloc(sizeof(int) * 1024);
	ft_bzero(table->pids, table->num_pids);
	i = 0;
	while (i < table->num_pids)
	{
		table->pids[i] = -1;
		i++;
	}
	table->ipids = 0;
	table->envp = envp;
	table->exit_code = return_value;
	return (table);
}

t_state	*initialize_t_state(void)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	ft_bzero(state->n, sizeof(int) * 2);
	state->i = 0;
	state->dq_open = 0;
	state->sq_open = 0;
	state->cmd = NULL;
	state->env_var = 0;
	return (state);
}
