/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:39:54 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/03 10:49:06 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_isnumber(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	exit_shell(t_command *cmd, char **argv, int i)
{
	long			exit_code;
	unsigned char	final_exit_code;

	exit_code = 0;
	if (argv[1])
	{
		if (!ft_isnumber(argv[1]))
		{
			printf("minishell: exit: numeric argument required\n");
			return (2);
		}
		else if (argv[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		else
			exit_code = ft_atol(argv[1]);
	}
	final_exit_code = (unsigned char)(exit_code % 256);
	if (i == 0)
		printf("exit\n");
	free_table(cmd->table);
	free_cmd(cmd);
	exit(final_exit_code);
}
