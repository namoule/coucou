/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:00:41 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_str_helper(int *i, int *j, t_state *state)
{
	*i = 0;
	*j = state->n[0];
	state->i = 0;
}

char	*helper_quotes(char *arg, char c, t_state *state)
{
	char	*str;
	int		i;
	int		j;

	init_str_helper(&i, &j, state);
	if (arg[j] != '$')
		j++;
	str = malloc(1024);
	while ((arg[j] != c && arg[j]))
	{
		str[i++] = arg[j++];
		if ((!state->dq_open && !state->sq_open && arg[j] == '\'')
			|| (!state->sq_open && !state->dq_open && arg[j] == '\"'))
			break ;
	}
	str[i] = '\0';
	if (!str)
	{
		if (state->dq_open || state->sq_open)
			state->n[0]++;
	}
	else if (!ft_strchr(str, '$') || state->sq_open || (ft_strchr(arg, '$')
			&& state->dq_open) || (ft_strchr(arg, '$') && !state->dq_open))
		state->n[0] = j + 1;
	return (str);
}

char	*copy_quotes_to_arg(t_command *cmd, int *i, t_state *state)
{
	int	j;

	j = 0;
	printf("state->n[0] in copy quote : %d\n", state->n[0]);
	printf("state->n[1] in copy quote : %d\n", state->n[1]);
	if (!state->n[1] || cmd->token_quotes[state->n[1] - 1] == NULL)
	{
		cmd->args[*i] = ft_strdup("");
		return (cmd->args[*i]);
	}
	cmd->args[*i] = malloc(sizeof(char) * 4096);
	if (!cmd->args[*i])
	{
		perror("Error allocating memory for cmd->args[*i]");
		exit(1);
	}
	cmd->args[*i][0] = '\0';
	j = 0;
	while (cmd->token_quotes && cmd->token_quotes[j])
	{
		ft_strlcat(cmd->args[*i], cmd->token_quotes[j], 4096);
		j++;
	}
	return (cmd->args[*i]);
}

void	process_quotes(t_command *cmd, t_state *state)
{
	int	i;

	i = 0;
	while (cmd->sargs[i])
	{
		if (ft_strchr(cmd->sargs[i], '\'') || ft_strchr(cmd->sargs[i], '\"')
			|| (ft_strchr(cmd->sargs[i], '$') && !ft_strncmp(cmd->sargs[0],
					"$?", 2)))
		{
			handle_quotes_and_expand(cmd->sargs[i], state);
			copy_quotes_to_arg(cmd, &i, state);
			printf("cmd->args[i] in process_quotes after : %s\n", cmd->args[i]);
		}
		i++;
	}
}
