/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 18:08:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/05 18:44:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "libft.h"
#include "ft_minishell.h"
#include "get_next_line.h"

static void		msh_treat_req(char *buf, char ***env)
{
	t_lex		*lexer;
	t_parse		*parsed;

	while (ft_isspace(*buf))
		buf++;
	if (*buf == '\0')
		return ;
	lexer = msh_lexer(buf);
	parsed = msh_parseur(lexer, env); //ajout de env dans parsed
	free_lex(lexer);
	if (parsed == NULL)
		return ;
//	parsed_print_tree(parsed); // print fn
	if (check_builtin_before(parsed)) //retrait de env ici !! suite !!
	{
		free_parsed(parsed);
		return ;
	}
	msh_exec(parsed); //retrait de env ici !! suite !!
	free_parsed(parsed); // a modifier pour free le path !! double free !!
}

void			msh_putprompt(void)
{
	time_t		local;
	char		*pwd;
	char		*ptr;

	local = time(NULL);
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	ptr = ft_strrchr(pwd, '/');
	write(1, "[", 1);
	write(1, ctime(&local) + 11, 5);
	write(1, "] ", 2);
	write(1, ptr, ft_strlen(ptr));
	write(1, "/* ", 3);
	free(pwd);
}

static char		**msh_env_init(void)
{
	extern char		**environ;
	char			**env;
	int				i;
	int				t;

	i = 0;
	t = 0;
	while (environ[i])
		i++;
	if ((env = (char **)(malloc(sizeof(char *) * (i + 1)))) == NULL)
		return (NULL);
	while (t < i)
	{
		env[t] = ft_strdup(environ[t]);
		t++;
	}
	env[t] = '\0';
	return (env);
}

int				main(void)
{
	char			*buf;
	char			**env;

	env = msh_env_init();
	buf = ft_strnew(0);
	while (ft_strcmp(buf, "exit") != 0)
	{
		signal(SIGINT, &set_signal);
		free(buf);
		msh_putprompt();
		if (get_next_line(0, &buf) <= 0)
			break ;
		signal(SIGINT, &set_signal2);
		msh_treat_req(buf, &env);
	}
	free(buf);
	ft_tabfree(&env);
	return (0);
}
