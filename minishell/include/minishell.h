/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:17:25 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:31:11 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft.h"

# define ERROR_TOKENIZE 2
# define ERROR_PARSE 2
# define ERROR_OPEN_REDIR 1
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef struct s_token			t_token;
typedef enum e_token_kind		t_token_kind;
typedef enum e_node_kind		t_node_kind;
typedef struct s_node			t_node;
typedef struct s_map			t_map;
typedef struct s_item			t_item;
typedef struct s_token			t_token;
typedef struct s_node			t_node;
typedef struct s_context		t_context;

extern volatile sig_atomic_t	g_signal_received;

enum e_token_kind {
	TOKEN_WORD,
	TOKEN_NULL,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_NEWLINE,
	TOKEN_UNKNOWN,
};
typedef enum e_token_kind		t_token_kind;

enum e_node_kind {
	NODE_PIPELINE,
	NODE_SIMPLE_CMD,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
	NODE_REDIR_APPEND,
	NODE_REDIR_HEREDOC,
};
typedef enum e_node_kind		t_node_kind;

struct s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
	int				export_flag;
	bool			non_double_quote_valuable;
};

struct s_node {
	t_node_kind	kind;
	bool		is_delim_unquoted;
	int			targetfd;
	int			filefd;
	int			stashed_targetfd;
	int			input_fd;
	int			inter_process_pipe[2];
	t_token		*args_token;
	t_token		*filename_token;
	t_token		*delimiter_token;
	t_node		*cmd_node;
	t_node		*redirects_node;
	t_node		*next;
};

// Redirecting output example
// cmd_node          : "echo hello 1 > out"
// targetfd         : 1
// filename_token         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

# define ATTR_EXPORT 0x0000001

struct s_item {
	char	*name;
	char	*value;
	int		attributes;
	t_item	*next;
};

struct s_map {
	t_item	item_head;
};

struct s_context {
	int						last_status;
	bool					syntax_error;
	bool					readline_interrupted;
	t_map					*envmap;
};

/* ************************************************************************** */
/*///////////
// Builtin //
*////////////

//builtin_cd.c
int		builtin_cd(char **argv, t_context *ctx);

//buitin_echo.c
int		builtin_echo(char **argv);

//builtin_env.c
int		builtin_env(char **argv, t_context *ctx);

//builtin_exit.c
int		builtin_exit(char **argv, t_context *ctx);

//builtin_export.c
int		builtin_export(char **argv, t_context *ctx);

//builtin_filepath.c
bool	consume_path(char **rest, char *path, char *elm);
void	delete_last_path_elm(char *path);
void	append_path_elm(char *dst, size_t dstsize, char **rest, char *src);

//builtin_pwd.c
int		builtin_pwd(char **argv, t_context *ctx);

//builtin_unset.c
int		builtin_unset(char **argv, t_context *ctx);

//builtin.c
int		exec_builtin(t_node *node, t_context *ctx);
bool	is_builtin(t_node *node);

/* ************************************************************************** */
/*///////////
// Environ //
*////////////

//environ_map_put.c
int		map_put(t_map *map, const char *string, bool allow_empty, int attr);

//environ_map_set.c
int		map_set_attr(t_map *map, const char *name, const char *value, int attr);
int		map_set(t_map *map, const char *name, const char *value);

//environ_utils.c
bool	is_identifier(const char *s);
bool	item_exported(t_item *item);
t_item	*map_get(t_map *map, const char *name);
int		map_unset(t_map *map, const char *name);

//environ.c
void	initenv(t_context *ctx);

/* ************************************************************************** */
/*/////////
// Error //
*//////////

//error_exit.c
void	fatal_error(const char *msg)__attribute__((noreturn));
void	assert_error(const char *msg)__attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status)\
		__attribute__((noreturn));
void	todo(const char *msg)__attribute__((noreturn));

//error_syntax.c
void	unclose_error(const char *location, char **rest, char *line, \
	t_context *ctx);
void	tokenize_error(const char *location, char **rest, t_token *tok, \
	t_context *ctx);
void	parse_error(const char *location, t_token **rest, t_token *tok, \
	t_context *ctx);

// error.c
void	perror_prefix(void);
void	xperror2(const char *s1, const char *err_msg);
void	xperror3(const char *s1, const char *s2, const char *err_msg);
void	xperror_invalid_identifier(const char *s, const char *identifier);

/* ************************************************************************** */
/*////////
// Exec	//
*/////////

//exec_get_environ.c
char	**get_environ(t_map *map);

//exec_prepare_pipe.c
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

//exec_search_path.c
char	*search_path(const char *filename_token, t_context *ctx);

//exec.c
int		exec(t_node *node, t_context *ctx);

/* ************************************************************************** */
/*//////////
// Expand //
*///////////

//expand_if.c
void	trim_ifs(char **rest, char *p, t_context *ctx);
bool	consume_ifs(char **rest, char *line, t_context *ctx);

//expand_parameter.c
void	expand_parameter(t_node *node, t_context *ctx);

//expand_quote_removal.c
void	expand_quote_removal(t_node *node);

//expand_special_parameter.c
void	expand_special_parameter_str(char **dst, char **rest, char *p, \
	t_context *ctx);
bool	is_special_parameter(char *s);

//expand_utils.c
void	append_char(char **s, char c);
void	append_single_quote(char **dst, char **rest, char *p);
void	append_double_quote(char **dst, char **rest, char *p, t_context *ctx);

//expand_variable.c
void	expand_variable_str(char **dst, char **rest, char *p, t_context *ctx);
bool	is_variable(char *s);

//expand_word_splitting.c
void	expand_word_splitting(t_node *node, t_context *ctx);

//expand.c
void	expand(t_node *node, t_context *ctx);

/* ************************************************************************** */
/*///////
// Lib //
*////////

void	*xcalloc(size_t count, size_t size);
int		xclose(int fd);
int		xdup2(int fildes, int fildes2);
char	*xgetenv(const char *name, t_context *ctx);
void	*xmalloc(size_t size);
int		xpipe(int fildes[2]);
char	*xstrdup(const char *s1);
char	*xstrndup(const char *s1, size_t size);

/* ************************************************************************** */
/*/////////
// Parse //
*//////////

//parse_redirections.c
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);

//parse_utils.c
t_node	*new_node(t_node_kind new_kind);
t_token	*tokdup(t_token *tok);
void	append_tok(t_token **tok, t_token *elm);
bool	equal_op(t_token *tok, char *op);

//parse.c
t_node	*parse_commands(t_token **rest, t_token *tok, t_context *ctx);

/* ************************************************************************** */
/*////////////
// Redirect	//
*/////////////

//redirect_heredoc.c
int		read_heredoc(const char *delimiter_token, bool is_delim_unquoted, \
	t_context *ctx);

//redirect_open_redir_file.c
int		open_redir_file(t_node *node, t_context *ctx);
int		openfd(t_node *node, t_context *ctx);

//redirect_stashfd.c
int		stashfd(int fd);

//redirect.c
void	do_redirect(t_node *redir, t_context *ctx);
void	reset_redirect(t_node *redir);

/* ************************************************************************** */
/*//////////
// Signal //
*///////////

//signal_handle.c
void	reset_sig(int signum);
void	ignore_sig(int signum);
void	handle_sig(int signum);

//signal.c
void	setup_signal(void);
void	reset_signal(void);

/* ************************************************************************** */
/*////////////
// Tokenize //
*/////////////

//tokenize_word.c
t_token	*word(char **rest, char *line, t_context *ctx);

// tokenize.c
t_token	*tokenize(char *line, t_context *ctx);
bool	is_metacharacter(char c);

/* ************************************************************************** */
/*/////////
// Utils //
*//////////

//token_list_to_argv.c
char	**token_list_to_argv(t_token *tok);

//utils.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	at_eof(t_token *tok);
t_token	*new_token(char *word, t_token_kind kind);
bool	startswith(const char *s, const char *keyword);

/* ************************************************************************** */
/*////////
// Main //
*/////////

//destructor.c
void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

//main.c
int		main(void);
/* ************************************************************************** */
/*/////////
// Debug //
*//////////
// void		print_token_list(t_token *head);
// void		print_node_list(t_node *head);
// const char	*node_kind_to_string(t_node_kind kind);
// const char	*token_kind_to_string(t_token_kind kind);
#endif
