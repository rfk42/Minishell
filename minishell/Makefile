NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror 

SRC_DIR = ./src/

SRC_FILES = main.c \
			begin_and_end.c \
			signals.c \
			builtins/builtins.c \
			builtins/export.c \
			builtins/unset.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/exit.c \
			parsing/check_quotes.c \
			parsing/check_metas.c \
			parsing/check_metas_utils.c \
			parsing/tokenizer.c \
			parsing/tokenizer_helper.c \
			parsing/token_utils.c \
			parsing/tokens_to_list.c \
			exec/exec.c \
			exec/expand.c \
			exec/wildcards.c \
			exec/utils.c \
			exec/child.c \
			exec/parent.c \
			exec/more_utils.c \
			exec/more_and_more_utils.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC = -Iincludes/ -Ilibft -I/opt/homebrew/include

LDFLAGS = -Llibft -lft -L/opt/homebrew/lib -lreadline

OBJ_DIR = .obj/

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_LIB = ./libft/libft.a

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	@if [ ! -f $(NAME) ] || [ `find $(OBJ) -newer $(NAME) | wc -l` -ne 0 ]; then \
		$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LDFLAGS); \
		printf "$(ERASE)$(GREEN)👷 Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created! 👷\n$(RESET)"; \
	else \
		printf "$(ERASE)$(YELLOW)No relink needed for$(RESET) $(CYAN)$(BOLD)$(NAME)\n$(RESET)"; \
	fi

$(LIBFT_LIB):
	@$(MAKE) -sC libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	@$(MAKE) -sC libft clean
	@$(RM) ./.obj/

fclean: clean
	@printf "$(ERASE)$(GREEN)Fcleaning up...$(RESET)"
	@$(RM) ${NAME}
	@$(RM) ${LIBFT_LIB}
	@printf "$(ERASE)🧼 $(GREEN)Fclean finished! 🧼\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re 

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
ERASE = \033[2K\r
RESET = \033[0m
