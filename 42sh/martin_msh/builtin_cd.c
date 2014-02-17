/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:09:02 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/29 12:42:01 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_minishell.h"

static void		cd_managepwd(char ***env)
{
	char	*buf;
	char	*old;

	buf = NULL;
	buf = getcwd(buf, 0);
	old = msh_get_env("PWD=", *env);
	ft_setenv("PWD", buf, 1, env);
	ft_setenv("OLDPWD", old, 1, env);
	free(buf);
	free(old);
}

static void		cd_print_error(char *name, int error)
{
	if (error == 1)
		write(2, "cd: no such file or directory: ", 31);
	else if (error == 2)
		write(2, "cd: permission denied: ", 23);
	ft_putendl_fd(name, 2);
}

static int		cd_is_dirpath(char *dir, char *dir_path)
{
	if (access(dir, F_OK) == -1)
		return (1);
	if (access(dir, R_OK) == -1)
		return (2);
	if (access(dir_path, F_OK) == -1)
		return (1);
	if (access(dir_path, R_OK) == -1)
		return (2);
	return (0);
}

static int		cd_home(char ***env, char *cd)
{
	char	*newdir;

	if (cd == NULL)
		newdir = msh_get_env("HOME=", *env);
	else
		newdir = msh_get_env("OLDPWD=", *env);
	chdir(newdir);
	free(newdir);
	cd_managepwd(env);
	return (1);
}

int				msh_cd(char **cd, char ***env)
{
	char	*buf;
	char	*tmp;
	int		error;

	buf = NULL;
	cd++;
	if (!(*cd) || !ft_strcmp(*cd, "-"))
		return (cd_home(env, *cd));
	buf = getcwd(buf, 0);
	tmp = ft_strjoinwsep(buf, *cd, '/');
	if ((error = cd_is_dirpath(*cd, tmp)) > 0)
	{
		free(tmp);
		free(buf);
		cd_print_error(*cd, error);
		return (-1);
	}
	if (chdir(*cd) != 0)
		chdir(tmp);
	cd_managepwd(env);
	free(tmp);
	free(buf);
	return (1);
}
