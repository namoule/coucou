/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:03:09 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/06 11:28:01 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int	check_export(char *exported, char **envp)
{
	int	i;
	int	len;
	int equal;

	i = 0;
	len = 0;
	equal = 0;
	while (exported[len] && exported[len] != '=')
		len++;
	if(exported[len] == '=')
		equal++;
	if(equal != 1)
		return(-1);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(exported, envp[i], len) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}


char    **export_1(char *exported, char **envp, int al_here)
{
    int        i;
    char    **res;

    i = 0;
    res = malloc(sizeof(char *) * (get_env_size(envp) + 1));
    while (envp[i])
    {
        if (i == al_here)
            res[i] = ft_strdup(exported);
        else
            res[i] = ft_strdup(envp[i]);
        i++;
    }
    res[i] = NULL;
    freetab(envp); // <---------- changement efffectue
    return (res);
}

char    **export_2(char *exported, char **envp)
{
    int        i;
    char    **res;

    i = 0;
    res = malloc(sizeof(char *) * (get_env_size(envp) + 2));
    while (envp[i])
    {
        res[i] = ft_strdup(envp[i]);
        i++;
    }
    res[i] = ft_strdup(exported);
    i++;
    res[i] = NULL;
    freetab(envp); // <---------- changement efffectue
    return (res);
}
char	**ft_export(t_command *cmd)
{
	char	**res;
	int		al_here;

	al_here = check_export(cmd->args[1], cmd->table->envp);
	if(al_here == -1)
		return(cmd->table->envp);
	if (al_here != 0)
		res = export_1(cmd->args[1], cmd->table->envp, al_here);
	else
		res = export_2(cmd->args[1], cmd->table->envp);
	return (res);
}
