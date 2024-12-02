/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:32:30 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_env_variable(const char *var_name, t_state *state, int i)
{
	char	*env_value;

	if (i > 1)
	{
		env_value = my_getenv(var_name, state->cmd->table->envp);
		state->i++;
		state->env_var = ft_strdup(env_value);
		return (1);
	}
	return (0);
}

void	handle_single_quotes(char *arg, t_state *state)
{
	char	*str;

	state->sq_open = !state->sq_open;
	if (state->sq_open)
	{
		str = helper_quotes(arg, '\'', state);
		if (str == NULL)
			return ;
		if (str[0] != '\0' && str)
		{
			state->n[1]++;
			state->cmd->token_quotes[state->n[1]] = ft_strdup(str);
		}
		else
			state->cmd->token_quotes[state->n[1]] = ft_strdup("");
		state->sq_open = 0;
		free(str);
	}
}

void	handle_double_quotes(char *arg, t_state *state)
{
	char	*str;

	state->dq_open = !state->dq_open;
	if (state->dq_open)
	{
		str = helper_quotes(arg, '\"', state);
		if (str == NULL)
			return ;
		state->cmd->result = process_char_helper(str, state);
		if (state->cmd->result && (state->cmd->result)[0] != '\0')
		{
			state->cmd->token_quotes[state->n[1]]
				= ft_strdup(state->cmd->result);
			state->n[1]++;
			state->dq_open = 0;
			if (state->cmd->result)
				ft_bzero(state->cmd->result,
					ft_strlen((const char *)state->cmd->result));
		}
		free(str);
	}
}

void	handle_regular_char(char *arg, t_state *state)
{
	state->cmd->token_quotes[state->n[1]] = malloc(2);
	if (!state->cmd->token_quotes[state->n[1]])
	{
		perror("Memory allocation failed");
		exit(1);
	}
	state->cmd->token_quotes[state->n[1]][0] = arg[state->n[0]];
	state->cmd->token_quotes[state->n[1]][1] = '\0';
	state->n[1]++;
	state->n[0]++;
}

void	handle_dollar_sign(char *arg, t_state *state)
{
	char	*str;

	str = make_expand(&arg[state->i], state);
	if (str)
		ft_strlcat(state->cmd->result, str, 1024);
	if (state->cmd->result && (state->cmd->result)[0])
	{
		state->cmd->token_quotes[state->n[1]] = ft_strdup(state->cmd->result);
		state->n[1]++;
		if (state->cmd->result)
			ft_bzero(state->cmd->result,
				ft_strlen((const char *)state->cmd->result));
	}
	free(str);
}
