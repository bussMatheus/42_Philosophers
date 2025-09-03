SRC = main.c parse.c em_and_frees.c utils.c

OBJ = $(SRC:%.c=%.o)

NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -rf

# ANSI color codes
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m  # No Color (reset)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compiled philo successfully$(NC)"

$(OBJS): %.o: %.c
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Removing object files: $(NAME)$(NC)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(RED)Removing static library: $(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re