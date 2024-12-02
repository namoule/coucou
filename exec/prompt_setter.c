/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:46:58 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/12/02 17:37:23 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line_to_history(const char *line)
{
	if (line && *line)
	{
		add_history(line);
	}
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*tmp;

	tmp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		tmp = ft_strjoin(cwd, " >> ");
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	**get_env(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (envp[i] != NULL)
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}


char	**get_env1(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (envp[i] != NULL)
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}


char	*get_line(char **envp)
{
	int		i;
	char	*line;
	char	*new_line;
	char	*prompt;

	i = 0;
	(void)envp;
	new_line = NULL;
	prompt = get_prompt();
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
		handle_exit(NULL, envp);
	if (check_line(line) != -1)
		add_line_to_history(line);
	new_line = good_char(line);
	free(line);
	if (!new_line)
	{
		free(new_line);
		return (NULL);
	}
	return (new_line);
}
