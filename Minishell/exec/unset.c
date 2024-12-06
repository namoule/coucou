/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:40 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 20:29:57 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

int check_word(char *to_find, char *envp)
{
	int i = 0;
	while(to_find[i])
	{
		if(to_find[i] == envp[i])
			i++;
		else
			break;
	}
	if(envp[++i] == '=')
	{
		return(0);
	}
	return(-1);
}
int check_unset(char **envp, char *lim)
{
	int i = 0;
	while(envp[i])
	{
		if(check_word(lim, envp[i]) == 0)
			return(0);
		i++;
	}
	return(-1);
}

int	unset(char ***envp, const char *var)
{
	int		count;
	char	**new_env;
	int		i;
	int		j;

	if(check_unset(*envp, (char *)var) == -1)
		return(-1);
	count = count_env_vars(*envp);
	new_env = malloc(sizeof(char *) * count);
	i = 0;
	j = 0;
	if (!new_env)
	{
		perror("malloc error");
		return (-1);
	}
	while (i < count)
	{
		if (ft_strncmp((*envp)[i], var, ft_strlen(var)) != 0
			|| (*envp)[i][ft_strlen(var)] != '=')
			new_env[j++] = (*envp)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}
