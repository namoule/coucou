/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:33:25 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:39:22 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*give_random_file(char *filename)
{
	int	i;

	i = 0;
	if (filename == NULL)
		filename = ft_strdup("filetemp");
	while (!access(filename, F_OK))
	{
		filename = ft_strdup(ft_strjoin("tmpfile", ft_itoa(i)));
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

int	here_doc(char *lim)
{
	char	*tmpfile;
	int		fd_read;
	int		fork_id;

	tmpfile = give_random_file(NULL);
	fd_read = open_randomfile(tmpfile);
	if (fd_read < 0)
		return (-1);
	fork_id = fork();
	if (fork_id == 0)
	{
		child_here(lim, tmpfile, fd_read);
		free(lim);
		free(tmpfile);
		exit(EXIT_SUCCESS);
	}
	else if (fork_id > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(fork_id, NULL, 0);
		signal(SIGINT, SIG_DFL);
		close(fd_read);
		fd_read = open(tmpfile, O_RDONLY);
		unlink(tmpfile);
		return (fd_read);
	}
	return (0);
}
