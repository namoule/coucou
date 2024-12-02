/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_assist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 18:16:42 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
}

int	handle_exit(char *line, char **env)
{
	if (!line)
	{
		if(env)
			freetab(env);
		exit(0);
	}
	else if (ft_strcmp(line, "exit") == 0)
	{
		freetab(env);
		free(line);
		exit(0);
	}
	return (0);
}

void	handle_interrupts(char *line)
{
	if (g_sig == 130 || g_sig == 131 || g_sig == 200)
	{
		handle_signal_interrupts(line);
		g_sig = 0;
	}
}
