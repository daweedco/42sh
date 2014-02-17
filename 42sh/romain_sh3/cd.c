/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 17:43:03 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 21:01:12 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

t_cmd	*verif_dir(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(cmd->pwd));
	while (cmd->pwd[i])
	{
		if (cmd->pwd[i] == '/' && cmd->pwd[i + 1] == '/')
			i++;
		else
		{
			str[j] = cmd->pwd[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	cmd->pwd = ft_strdup(str);
	return (cmd);
}

t_cmd	*clean_dir2(t_cmd *cmd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(cmd->pwd));
	while (cmd->pwd[i])
	{
		if (cmd->pwd[i] == '.' && cmd->pwd[i + 1] == '/')
			i += 2;
		else if (cmd->pwd[i] == '.' && cmd->pwd[i + 1] == '\0')
			i++;
		else
		{
			str[j] = cmd->pwd[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	cmd->pwd = ft_strdup(str);
	return (cmd);
}

t_cmd	*clean_dir(t_cmd *cmd)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (cmd->pwd[i])
	{
		if (cmd->pwd[i] == '.' && cmd->pwd[i + 1] == '.')
			cpt++;
		i++;
	}
	i = 0;
	while (cmd->pwd[i])
		i++;
	cpt *= 2;
	while (cpt--)
	{
		while (i > 0 && cmd->pwd[i] != '/')
			i--;
		if (i > 0)
			i--;
	}
	cmd->pwd = ft_strsub(cmd->pwd, 0, i + 1);
	cmd = clean_dir2(cmd);
	return (cmd);
}

t_cmd	*do_cd(t_cmd *cmd)
{
	char	**set;

	set = (char **)malloc(sizeof(char *) * 3);
	cmd = verif_dir(cmd);
	if (chdir(cmd->pwd) == -1)
	{
		ft_putstr("cd : no such file or directory: ");
		ft_putendl(cmd->cmd_arg[1]);
		cmd->pwd = ft_strdup(cmd->old_pwd);
		return (cmd);
	}
	cmd = clean_dir(cmd);
	set[1] = ft_strdup("OLDPWD");
	set[2] = ft_strdup(cmd->old_pwd);
	cmd->env = modify_var(cmd->env, set);
	set[1] = ft_strdup("PWD");
	set[2] = ft_strdup(cmd->pwd);
	cmd->env = modify_var(cmd->env, set);
	return (cmd);
}

t_cmd	*my_cd(t_cmd *cmd, int i)
{
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], "PWD", 3) == 0)
			cmd->pwd = ft_strsub(cmd->env[i], 4, ft_strlen(cmd->env[i]) - 4);
		i++;
	}
	cmd->old_pwd = ft_strdup(cmd->pwd);
	cmd->cmd_arg = ft_strsplit_space(cmd->arg);
	if (cmd->cmd_arg[1] == NULL)
		return (cmd);
	if (cmd->cmd_arg[2] != NULL)
	{
		ft_putendl("cd: too many arguments");
		return (cmd);
	}
	if (cmd->cmd_arg[1][0] != '/')
	{
		cmd->pwd = ft_strjoin(cmd->pwd, "/");
		cmd->pwd = ft_strjoin(cmd->pwd, cmd->cmd_arg[1]);
	}
	else if (cmd->cmd_arg[1][0] == '/')
		cmd->pwd = ft_strdup(cmd->cmd_arg[1]);
	cmd = do_cd(cmd);
	return (cmd);
}
