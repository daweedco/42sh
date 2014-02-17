/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 14:06:13 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/14 15:54:33 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PROG "42sh"

# define BUFF_QUOTE 2096

# define CMD 0
# define PIPE 1
# define SEP 2
# define REDIR 3
# define APPEND 4
# define OR 5
# define AND 6


typedef struct s_lexer		t_lexer;
typedef struct s_lx			t_lx;


struct				s_lexer
{
	char		*str;
	char		type;
	t_lexer		*next;
	t_lexer		*prev;
};

struct				s_lx
{
	t_lexer		*first;
	t_lexer		*last;
};


void		stp_star(char **cmd, char **env);
void		stp_tilde(char **cmd, char **env);
void		stp_dollar(char **cmd, char **env);


/*
** LEX_FIRST_STEP
*/
void		stp_quote(char **cmd, char **env);

/*
** LEX_MAKE
*/
void		make_lex(t_lx *lex, char *cmd);

/*
** LEX_FN1
*/
int			browse_quote(char *ptr);
int			lex_isquote(char *tolex);
void		add_token(t_lx *lex, t_lexer *token);
t_lexer		*new_token(void);
t_lx		*init_lex(void);

/*
** SH_LEXER
*/
int			sh_lexer(t_lx **lex, char **cmd, char **env);

#endif /* !LEXER_H */
