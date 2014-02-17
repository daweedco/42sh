/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 13:09:32 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/13 14:24:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# define NB_BUILTIN 6
# define USAGE_SE " Usage: setenv NAME=value"
# define USAGE_USE " Usage: unsetenv NAME=value"

# define COMMAND 1
# define CMD 1
# define PIPE 2
# define S_C 3
# define REDIR 4
# define APPEND 5

typedef struct s_lexer		t_lexer;
typedef struct s_pipe		t_pipe;
typedef struct s_redir		t_redir;
typedef struct s_append		t_append;
typedef struct s_inst		t_inst;
typedef struct s_cmd		t_cmd;
typedef int (*builtin_ptr)(char **, char ***);

typedef struct		s_setenv
{
	char			*name;
	char			*value;
	int				ow;
}					t_setenv;

struct				s_lexer
{
	char		*str;
	char		type;
	t_lexer		*prev;
	t_lexer		*next;
};

typedef struct		s_lex
{
	t_lexer		*start;
	t_lexer		*last;
}					t_lex;

struct					s_redir
{
	char		left;
	char		right;
	char		*name;
	t_redir		*r_next;
	t_append	*a_next;
};

struct					s_append
{
	char		left;
	char		right;
	char		*name;
	t_append	*a_next;
	t_redir		*r_next;
};

struct				s_inst
{
	char		**arg;
	t_redir		*redir;
	t_append	*append;
	int			in_p;
	int			out_p;
	t_inst		*next;
	t_inst		*prev;
};

struct				s_cmd
{
	t_inst		*inst;
	t_redir		*redir;
	t_cmd		*next;
	t_cmd		*prev; // besoin ?
};

typedef struct		s_parse
{
	t_cmd		*cmd;
	char		**path;
	char		***env;
}					t_parse;

typedef struct		s_builtin
{
	char			*name;
	builtin_ptr		fn;
}					t_builtin;

/*
** MINISHELL1
** static void	msh_treat_req(char *buf, char ***env)
** static char	**msh_env_init(void)
** int			main(void)
*/
void		msh_putprompt(void);

/*
** MSH_LEXER
** static void	trim_ncheck(t_lexer *lex)
** static int	check_key(char *ptr)
** static void	add_separator(t_lex *lex, int ret, char *tolex)
** static void	add_to_lex(char *orig, char *tolex, t_lex *lex, int ret)
*/
t_lex		*msh_lexer(char *orig);

/*
** LEXER_FN
*/
void		free_lex(t_lex *lexer);
t_lex		*init_lex(void);
void		free_node(t_lexer *del);
t_lexer		*new_node(void);
int			browse_quote(char *ptr);

/*
** MSH_PARSEUR
** static t_parse	*browse_lex(t_lexer *lex, char ***env)
** static int		first_check(t_lex *lexer)
** static void		get_type(t_lex *lexer)
*/
t_parse		*msh_parseur(t_lex *lexer, char ***env);

/*
** PARSEUR_LEX
*/
void		add_cmd_tree(t_parse *tree);
void		add_inst_tree(t_parse *tree, t_lexer *lex);
void		cat_inst_tree(t_parse *tree, t_lexer *lex);

/*
** PARSEUR_INIT
*/
t_cmd		*init_cmd(void); //new
t_inst		*init_inst(char *str); //new
t_redir		*init_redir(char *name, char *type);
t_append	*init_append(char *name, char *type);
t_parse		*init_parse(char ***env);

/*
** PARSEUR_FN1
*/
void		get_type_append(t_append *append, char *type);
void		get_type_redir(t_redir *redir, char *type);
int			parse_error(char *str);
char		keytotype(char *str);

/*
** REDIR_APPEND
** static void	redir_is_first(t_parse *tree, t_redir *redir)
*/
void		add_redir_append(t_parse *tree, t_lexer *lex);

/*
** PARSEUR_REDIR
** static void	redir_to_inst(t_inst *inst, t_redir *redir)
** static void	redir_to_append(t_inst *inst, t_redir *redir)
** static void	add_redir_to_first(t_cmd *cmd, t_redir *redir, t_lexer *lex)
*/
void		add_redir(t_parse *tree, t_redir *redir, t_lexer *lex);

/*
** PARSEUR_APPEND
** static void	append_to_inst(t_inst *inst, t_append *append)
** static void	append_to_redir(t_inst *inst, t_append *append)
** static void	add_append_to_first(t_cmd *cmd, t_append *append, t_lexer *lex)
*/
void		add_append(t_parse *tree, t_append *append, t_lexer *lex);

/*
** MSH_BUILTIN
** static int	msh_do_builtin(char **req, t_builtin builtin, char ***env)
*/
int			check_builtin(char **arg, char ***env);
int			check_builtin_before(t_parse *parsed);

/*
** FREE_FN
*/
void		free_inst(t_inst *inst);
void		free_lst_append(t_append *append);
void		free_lst_redir(t_redir *redir);
void		free_lst_inst(t_inst *inst);
void		free_parsed(t_parse *parsed);

/*
** MSH_EXEC
** static void	exec_inst(t_cmd *cmd, t_parse *tree)
** static int	exec_cmd(t_inst *inst, t_parse *tree)
** static int	msh_do_command(char *path, char **req, char **env)
*/
int			msh_exec(t_parse *parsed);

/*
** EXEC_PIPE
** static void	close_pipe(int infile, int outfile, t_inst *inst)
** static void	pipe_inst(t_inst *inst, t_parse *tree, int in, int out)
** static int	exec_cmd_pipe(t_inst *inst, t_parse *tree)
*/
void		exec_pipe(t_inst *inst, t_parse *tree);



//t_parse		*treat_command_plus(t_parse *tree, t_lexer *lex);
//t_parse		*add_pipe(t_parse *tree, t_lexer *lex);

int			msh_cd(char **cd, char ***env);
int			msh_env(char **req, char ***env);
int			msh_echo(char **req, char ***env);
int			msh_setenv(char **env_mod, char ***env);
int			msh_unsetenv(char **req, char ***env);
int			msh_exit(char **req, char ***env);
int			ft_setenv(const char *name, const char *value, int ow, char ***env);

//void		exec_pipe(t_parse *parsed, char **path, char ***env);
void		do_commandpipe(int nb, t_pipe *last, t_parse *pars);
//int			pipe_command(char **arg, char **path, char ***env);
int			pipe_command(t_inst *inst, t_parse *tree);

int			check_access(char *path);
int			access_error(char *name, char **path);

int			ft_print_error(char *error);

void		free_lex(t_lex *lexer);

int			check_redir_append(t_lexer *lex);
//t_parse		*manage_redir_append(t_parse *tree, t_lexer *lex);
//t_parse		*add_redir(t_parse *tree, t_lexer *lex);
void		add_redir(t_parse *tree, t_redir *redir, t_lexer *lex);
void		add_append(t_parse *tree, t_append *append, t_lexer *lex);
void		exec_redir(t_parse *parsed, char **path, char ***env);
void		pipe_redir(t_pipe *pipex, char **arg, char **path, char ***env);

void		add_redir_append(t_parse *tree, t_lexer *lex);

void		set_signal(int sig);
void		set_signal2(int sig);

int			msh_isenv(const char *env, const char *tofind);
char		*msh_get_env(char *var, char **env);
char		**ft_strsplitspace(char const *s);

void		parsed_print_tree(t_parse *tree);

#endif /* !FT_MINISHELL_H */
