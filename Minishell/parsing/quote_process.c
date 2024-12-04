/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 14:29:18 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_state_quotes(t_state *state)
{
	state->i = 0;
	state->sq_open = 0;
	state->dq_open = 0;
}

void	update_quotes(char ch, t_state *state, size_t result_size)
{
	if (ch == '\'' && !state->dq_open)
	{
		state->sq_open = !state->sq_open;
		ft_strlcat(state->cmd->result, "\'", result_size);
	}
	else if (ch == '\"' && !state->sq_open)
	{
		state->dq_open = !state->dq_open;
		ft_strlcat(state->cmd->result, "\"", result_size);
	}
}

int		helper_process(t_state *state, const char *input, char **env, char *temp)
{
	if (input[state->i] == '$' && !state->sq_open)
	{
		*env = make_expand(&input[state->i], state);
		if (*env)
			ft_strlcat(state->cmd->result, *env, 4096);
		free(*env);
		if (!input[state->i])
			return (1);
	}
	else if (input[state->i])
	{
		ft_strlcat(state->cmd->result, temp, 4096);
		state->i++;
		state->n[0]++;
	}
	if (state->cmd->result && (state->cmd->result)[0])
	{
		state->cmd->token_quotes[state->n[1]] = ft_strdup(state->cmd->result);
		state->n[1]++;
	}
	if (input[state->i] == '\'' || input[state->i] == '\"')
		return (1);
	return (0);
}

char	*process_char_helper(const char *input, t_state *state)
{
	char	temp[2];
	char	*env;

	env = NULL;
	while (input[state->i])
	{
		if (state->cmd->result)
				ft_bzero(state->cmd->result,
					ft_strlen((const char *)state->cmd->result));
		temp[0] = input[state->i];
		temp[1] = '\0';
		update_quotes(input[state->i], state, 4096);
		if (helper_process(state, input, &env, temp))
			return (handle_state_quotes(state), NULL);
	}
	handle_state_quotes(state);
	return (state->cmd->result);
}

void	handle_quotes_and_expand(char *arg, t_state *state)
{
	state->n[0] = 0;
	while (arg && arg[state->n[0]])
	{
		if (arg[state->n[0]] == '\'')
			handle_single_quotes(arg, state);
		else if (arg[state->n[0]] == '\"')
			handle_double_quotes(arg, state);
		else if (arg[state->n[0]] == '$' && !state->sq_open)
		{
			process_char_helper(&arg[state->n[0]], state);
			state->n[0] += state->i; // Sync n[0] with i after processing
		}
		else
		{
			handle_regular_char(arg, state);
		}
		if (state->n[1] >= 4096)
		{
			perror("Too many quoted strings");
			exit(1);
		}
	}
}
