/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_ressources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:36:57 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
typedef struct s_indices {
    int i;
    int j;
} t_indices;

int	handle_special_cases(const char *input, t_state *state, t_indices *indices)
{
	char	*str;

	str = NULL;
	while (input[indices->j] == '$' && (input[indices->i] == '\'' || input[indices->i] == '\"'))
	{
		if (input[indices->i] == '\'')
			str = helper_quotes((char *)&input[indices->i], '\'', state);
		if (input[indices->i] == '\"')
			str = helper_quotes((char *)&input[indices->i], '\"', state);
		state->n[0]++;
		free(str);
		return (1);
	}
	if (input[indices->i] == '?')
	{
		state->env_var = get_exit_code(1, state);
		state->i++;
		return (1);
	}
	return (0);
}

int	handle_empty_or_double_dollar(const char *input, t_state *state)
{
	if ((input[0] == '$' && !input[1]) || (input[0] == '$' && input[1] == '$'))
	{
		state->env_var = ft_strdup("$\0");
		state->i++;
		return (1);
	}
	return (0);
}

void	handle_variable_name(const char *input, char *var_name, t_indices *indices,
		t_state *state)
{
	while (input[indices->i] && (ft_isalnum(input[indices->i]) || input[indices->i] == '_'))
	{
		var_name[indices->j] = input[indices->i];
		indices->i++;
		indices->j++;
	}
	state->i += indices->j;
	var_name[indices->j] = '\0';
}

void	handle_remaining_chars(const char *input, t_indices *indices, t_state *state)
{
	while (input[indices->i] && input[indices->i] != '$')
	{
		indices->i++;
		indices->j++;
	}
	state->i += indices->j;
	if (input[0] == '$')
		state->env_var = ft_substr(input, 0, indices->j);
	else
		state->env_var = ft_substr(input, indices->j - 1, indices->i - indices->j);
}

char	*make_expand(const char *input, t_state *state)
{
	t_indices	indices;
	char		var_name[1024];

	indices.i = 1;
	indices.j = 0;
	if (handle_special_cases(input, state, &indices))
		return (state->env_var);
	if (handle_empty_or_double_dollar(input, state))
		return (state->env_var);
	handle_variable_name(input, var_name, &indices, state);
	if (expand_env_variable(var_name, state, indices.i))
		return (state->env_var);
	handle_remaining_chars(input, &indices, state);
	return (state->env_var);
}