/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 21:28:28 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 21:20:11 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

static char	*search_path(char **path, char *cmd)
{
	int		i;
	char	*line;

	i = 0;
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{
			execute_error(cmd);
			return (NULL);
		}
	}
	while (path[i])
	{
		line = ft_strjoin((char const *)path[i], "/");
		line = ft_strjoin((char const *)line, (char const *)cmd);
		if (access(line, F_OK) == 0)
			return (line);
		i++;
	}
	execute_error(cmd);
	return (NULL);
}

char		*ft_clean(char *cmd, int i, int j)
{
	char	*str;

	if (cmd)
	{
		while (cmd[j])
		{
			if (cmd[j++] != '"')
				i++;
		}
		str = (char *)malloc(sizeof(char) * i);
		i = 0;
		j = 0;
		while (cmd[j])
		{
			if (cmd[j] != '"')
				str[i++] = cmd[j];
			j++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

char		*which_path(char *cmd)
{
	int		i;
	char	**path;
	char	*line;

	i = 0;
	cmd = ft_clean(cmd, 0, 0);
	if (ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "unsetenv") == 0
		|| ft_strcmp(cmd, "setenv") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0)
		return (cmd);
	if (cmd[0] == '/')
		return (search_path(path, cmd));
	while (environ[i])
	{
		if (ft_strncmp((const char *)environ[i], "PATH=", 5) == 0)
			line = ft_strdup(environ[i]);
		i++;
	}
	line = ft_strsub((char const *)line, 5, ft_strlen(line) - 5);
	path = ft_strsplit((char const *)line, ':');
	free(line);
	return (search_path(path, cmd));
}

int			open_file(char *dir, char *dest)
{
	int		fd;

	fd = -1;
	if (ft_strcmp(dir, ">") == 0)
		fd = open(dest, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (ft_strcmp(dir, ">>") == 0)
		fd = open(dest, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("zsh: permission denied: ", 2);
		ft_putendl_fd(dest, 2);
	}
	return (fd);
}

void		init_cmd(t_cmd *cmd)
{
	cmd->i = 0;
	while (cmd->cmd[cmd->i])
	{
		if (cmd->exec == 0)
		{
			cmd->path = which_path(cmd->cmd[cmd->i]);
			cmd->arg = ft_clean(cmd->cmd[cmd->i], 0, 0);
			cmd->exec = 1;
		}
		else if (cmd->cmd[cmd->i][0] == '>')
		{
			cmd->fd = open_file(cmd->cmd[cmd->i], cmd->cmd[cmd->i + 1]);
			cmd->i++;
		}
		else if (cmd->cmd[cmd->i][0] != ';' && cmd->cmd[cmd->i][0] != '|')
		{
			cmd->arg = ft_strjoin(cmd->arg, " ");
			cmd->arg = ft_strjoin(cmd->arg, ft_clean(cmd->cmd[cmd->i], 0, 0));
		}
		if (cmd->cmd[cmd->i][0] == '|' && cmd->path != NULL)
			cmd = init_pipe(cmd);
		else if (cmd->cmd[cmd->i][0] == ';' || cmd->cmd[cmd->i + 1] == NULL)
				cmd = execute_cmd(cmd);
		cmd->i++;
	}
}
