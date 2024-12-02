/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:27:13 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:00:53 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_double(char *str, int i)
{
	if ((str[i] == '>' || str[i] == '<') && check_line(&str[i + 1]) == -1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		return (-1);
	}
	else if (str[i] == '<' && str[i + 1] == '<' && (str[i + 2] == '<' || str[i
				+ 2] == '>'))
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (-1);
	}
	return (0);
}

int	check_red(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<' && str[i
			+ 3] == '<')
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (-1);
	}
	else if (str[i] == '>' && str[i + 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (-1);
	}
	else if (str[i] == '<' && str[i + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (-1);
	}
	if (check_double(str, i) == -1)
		return (-1);
	return (0);
}

int	check_pipe(char *str, int i)
{
	if (str[i] == '|')
	{
		if (i == 0 || str[i + 1] == '\0' || str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (-1);
		}
		if (check_line(&str[i + 1]) == -1)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (-1);
		}
	}
	return (0);
}

int	check(char *str, int i)
{
	if (check_pipe(str, i) == -1)
		return (-1);
	if (check_red(str, i) == -1)
		return (-1);
	return (0);
}

int	syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check(str, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
