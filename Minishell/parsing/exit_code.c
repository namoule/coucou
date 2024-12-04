/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 12:34:48 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exit_code(int len, t_state *state)
{
	char	*env;

	env = ft_itoa(*(state->cmd->table->exit_code));
	if (env)
		state->i += len;
	return (env);
}

char	*dollar_question_case(char *arg, t_state *state)
{
	size_t	ij[2];
	size_t	total_size;
	char	*exit_c;

	ij[0] = 0;
	ij[1] = 0;
	total_size = 4096;
	exit_c = ft_itoa(*(state->cmd->table->exit_code));
	if (!exit_c)
		return (NULL);
	while (arg[ij[0]])
	{
		if (arg[ij[0]] == '$' && arg[ij[0] + 1] == '?')
			concat_exit_code(exit_c, ij, total_size, state);
		else
			state->env_var[ij[1]++] = arg[ij[0]++];
	}
	state->env_var[ij[1]] = '\0';
	free(exit_c);
	return (state->env_var);
}

int	check_pair_quotes(char *str)
{
	int	i;
	int	j;
	int	count_sq;
	int	count_dq;

	i = 0;
	j = 0;
	count_dq = 0;
	count_sq = 0;
	while (*str++)
	{
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		{
			if (*str == '\'' && !(count_dq % 2))
				count_sq = !count_sq;
			if (*str == '\"' && !(count_sq % 2))
				count_dq = !count_dq;
		}
	}
	if ((count_sq % 2) || (count_dq % 2))
		return (1);
	return (0);
}

char	*my_getenv(const char *name, char **custom_env)
{
	size_t	name_len;

	if (!name || !custom_env)
		return (NULL);
	name_len = ft_strlen(name);
	while (*custom_env)
	{
		if (ft_strncmp(*custom_env, name, name_len) == 0
			&& (*custom_env)[name_len] == '=')
			return (*custom_env + name_len + 1);
		custom_env++;
	}
	return (NULL);
}