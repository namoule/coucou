/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:09 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 11:37:30 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_full_args_n(char *args)
{
	int	i;

	i = 0;
	if (args[0] == '-' && args[1] == 'n')
	{
		i = 2;
		while (args[i])
		{
			if (args[i] != 'n')
				return (-1);
			i++;
		}
	}
	return (0);
}

int	check_n(char **args)
{
	int	i;

	i = 1;
	while (args[i] && (ft_strncmp(args[i], "-n", 2) == 0))
	{
		if (ft_strcmp(args[i], "-n") == 0)
			i++;
		else if (check_full_args_n(args[i]) != 0)
			return (i);
		else
			i++;
	}
	return (i);
}

int	echo(t_command *cmd)
{
	int	ind_n;
	int	line;

	ind_n = check_n(cmd->args);
	if (ind_n != 1)
		line = 1;
	else
		line = 0;
	while (cmd->args[ind_n])
	{
		if (cmd->args[ind_n + 1] != NULL)
			printf("%s ", cmd->args[ind_n]);
		else
			printf("%s", cmd->args[ind_n]);
		ind_n++;
	}
	if (line != 1)
		printf("\n");
	return(0);
}
