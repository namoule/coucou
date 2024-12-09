
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:10 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 08:53:24 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_args(t_command *head)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (head->args[i] && head->args[i][0] != '|')
	{
		if (head->args[i][0] == '<' || head->args[i][0] == '>')
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

void	fill_args(t_command *head, int count_args, char **new_args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (head->args[i] && j < count_args)
	{
		if (head->args[i][0] != '<' && head->args[i][0] != '>')
		{
			new_args[j] = ft_strdup(head->args[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	new_args[j] = NULL;
}

void	change_args_for_exec(t_command *cmd)
{
	t_command	*head;
	char		**new_args;
	int			count;

	count = 0;
	new_args = NULL;
	head = cmd;
	while (head)
	{
		count = count_args(head);
		new_args = malloc(sizeof(char *) * (count + 1));
		if (!new_args)
			return (perror("Error with malloc"));
		ft_bzero(new_args, count+1);
		fill_args(head, count, new_args);
		freetab(head->args);
		head->args = new_args;
		head = head->next;
	}
}
