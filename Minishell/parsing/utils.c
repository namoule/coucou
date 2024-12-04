/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 13:59:13 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_quotes(char current_char, int in_quote)
{
	if (in_quote == 0)
		return (current_char);
	else if (in_quote == current_char)
		return (0);
	return (in_quote);
}

int	check_pipe_validity(char *str, int i)
{
	int	j;
	int	k;

	j = i - 1;
	k = i + 1;
	while (j >= 0 && str[j] == ' ')
		j--;
	while (str[k] == ' ')
		k++;
	if (j >= 0 && str[j] != '|' && str[j] != '\0' && str[k] != '|'
		&& str[k] != '\0')
		return (1);
	return (0);
}

int	ft_count_pipe(char *str)
{
	int	i;
	int	count;
	int	in_quote;

	i = 0;
	count = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			in_quote = handle_quotes(str[i], in_quote);
		if (str[i] == '|' && in_quote == 0)
			count += check_pipe_validity(str, i);
		i++;
	}
	return (count + 2);
}

int	open_fct_check(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (filein);
}

void	new_t_command(t_command *cmd, t_table *table)
{
	t_command	*new_cmd;

	new_cmd = initialize_t_command(table);
	cmd->next = new_cmd;
}
