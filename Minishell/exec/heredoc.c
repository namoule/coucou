/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:33:25 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/09 23:34:40 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*give_random_file(char *filename)
{
	int	i;
	char *itooa;

	i = 0;
	if (filename == NULL)
		filename = ft_strdup("filetemp");	// to protect
	while (!access(filename, F_OK))
	{
		free(filename);
		itooa = ft_itoa(i);	// to protect
		filename = ft_strjoin(("tmpfile"), itooa);	// to protect
		free(itooa);
		i++;
	}
	return (filename);
}

int	open_randomfile(char *filename)
{
	int	ret_fd;

	ret_fd = 0;
	ret_fd = open(filename, O_CREAT | O_RDWR, 0666);
	if (ret_fd < 0)
		perror("error open");
	return (ret_fd);
}

void	sigint_handler(int signum)
{
	(void)signum;
	exit(EXIT_FAILURE);
}

void	child_here(char *lim, char *filename, int fd_read)
{
	char	*line;

	(void)filename;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		line = readline(" >> ");
		if (!line)
			break ;
		if (ft_strcmp(lim, line) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_read);
		ft_putchar_fd('\n', fd_read);
		free(line);
	}
	close(fd_read);
}


int	here_doc(t_command *cmd, char *lim, char **tokens, t_state *state)
{
	char	*tmpfile;
	char *lime = ft_strdup(lim);
	int		fd;
	int		fork_id;

	tmpfile = give_random_file(NULL);
	fd = open_randomfile(tmpfile);
	if (fd < 0)
		return (-1);
	fork_id = fork();
	if (fork_id == 0)
	{
		free(cmd->args);
		freetab(cmd->table->envp);
		free(cmd->table->pids);
		free(cmd->table);
		free_cmd1(cmd);
		freetab(tokens);
		free(state);
		child_here(lime, tmpfile, fd);
		free(lime);
		free(tmpfile);
		exit(EXIT_SUCCESS);
	}
	else if (fork_id > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(fork_id, NULL, 0);
		signal(SIGINT, SIG_DFL);
		close(fd);
		fd = open(tmpfile, O_RDONLY);
		unlink(tmpfile);
		free(tmpfile);
		free(lime);
		return (fd);
	}
	return (0);
}
