/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 12:37:40 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_token_arguments(char **tokens, t_command *cmd, int *j)
{
	int	i;

	i = 0;
	while (tokens[*j] && ft_strcmp(tokens[*j], "|"))
	{
		cmd->sargs[i] = ft_strdup(tokens[*j]);
		if (!cmd->sargs[i])
		{
			perror("Error duplicating token");
			exit(1);
		}
		i++;
		(*j)++;
	}
	cmd->sargs[i] = NULL;
}

int	expand_tokens(char **tokens, t_command *cmd, t_state *state, int j)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	state->cmd = cmd;
	while (tokens[j] && ft_strcmp(tokens[j], "|"))
	{
		state->i = 0;
		if (ft_strchr(tokens[j], '$') || ft_strchr(tokens[j], '\"')
			|| ft_strchr(tokens[j], '\''))
		{
			if (ft_strchr(tokens[j], '\"') || ft_strchr(tokens[j], '\''))
				handle_quotes_and_expand(tokens[j], state);
			else
				process_char_helper(tokens[j], state);
			copy_quotes_to_arg(cmd, &i, state);
		}
		else
			cmd->args[i] = ft_strdup(cmd->sargs[i]);
		i++;
		j++;
	}
	cmd->args[i] = NULL;
	return (0);
}

int	process_tokens(char **tokens, t_command *cmd, int *j)
{
	t_state	*state;
	int		ret;
	int		i;

	i = *j;
	ret = 0;
	state = initialize_t_state();
	process_token_arguments(tokens, cmd, j);
	find_fd_in(cmd);
	if (cmd->fd_in != -3)
		find_fd_out(cmd);
	if (cmd->fd_in == -3 || cmd->fd_out == -3)
		ret = -3;
	expand_tokens(tokens, cmd, state, i);
	free(state);
	return (ret);
}

int	split_and_process_tokens(t_command *cmd, char **tokens, t_table *table)
{
	int			j;
	int			ret;
	t_command	*tmp;

	ret = 0;
	j = 0;
	tmp = cmd;
	while (tokens[j])
	{
		ret = process_tokens(tokens, tmp, &j);
		if (tokens[j] && ft_strcmp(tokens[j], "|") == 0)
		{
			new_t_command(tmp, table);
			tmp = tmp->next;
			j++;
		}
	}
	return (ret);
}

t_command	*tokenize_input(char *input, char **envp, int return_value)
{
	char		**tokens;
	t_table		*table;
	t_command	*cmd;
	t_command	*head;

	if (!input)
		return (NULL);
	table = initialize_t_main(input, envp, &return_value);
	cmd = initialize_t_command(table);
	if (!cmd)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	head = cmd;
	tokens = ft_split(input, ' ');
	if (split_and_process_tokens(cmd, tokens, table))
		return (NULL);
	freetab(tokens);
	return (head);
}