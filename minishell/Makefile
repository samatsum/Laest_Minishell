NAME     = minishell
CC       = cc
RM       = rm -rf
RLDIR    = /usr
INCLUDES = -I include -I$(RLDIR)/include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBFTDIR = libft
LIBFT    = $(LIBFTDIR)/libft.a
LIBS     = -lreadline -L$(RLDIR)/lib -lft -L$(LIBFTDIR)
SRC_DIR  = src/
OBJ_DIR  = object_files/

SUBDIRS  = $(shell find $(SRC_DIR) -type d | sed 's|$(SRC_DIR)||' | grep -v '^$$')

SRC =	main \
		destructor \
    	$(addprefix builtin/, builtin builtin_exit builtin_export builtin_unset builtin_env builtin_cd builtin_echo builtin_pwd builtin_filepath) \
    	$(addprefix environ/, environ_map_set environ_map_put environ environ_utils) \
		$(addprefix error/, error error_exit error_syntax) \
		$(addprefix exec/, exec exec_search_path exec_prepare_pipe exec_get_environ exec_wait_pipeline) \
		$(addprefix expand/, expand expand_quote_removal expand_parameter expand_word_splitting expand_ifs expand_variable expand_special_parameter expand_utils) \
    	$(addprefix lib/, xdup2 xstrndup xcalloc xstrdup xpipe xclose xmalloc xgetenv) \
		$(addprefix parse/, parse parse_redirection parse_utils) \
		$(addprefix redirect/, redirect redirect_open_redir_file redirect_stashfd redirect_heredoc) \
		$(addprefix signal/, signal signal_handle) \
		$(addprefix tokenize/, tokenize tokenize_word) \
		$(addprefix utils/, token_list_to_argv utils) \

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
OBJ_SUBDIRS = $(addprefix $(OBJ_DIR), $(SUBDIRS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR) $(OBJ_SUBDIRS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_SUBDIRS): | $(OBJ_DIR)
	@mkdir -p $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re

# /*
#[export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort]:status NG, expected 0 but got 139

# valgrind --leak-check=full ./minishell 2>ERR_LOG.txt
# valgrind --leak-check=full --show-leak-kinds=all ./minishell 2>ERR_LOG_kind.txt
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2>ERR_LOG_show_track.txt
# */