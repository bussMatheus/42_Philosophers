SRC = main.c parse.c em_and_frees.c utils.c inits.c monitor.c \
	philo_routine.c safe_handling.c

OBJ = $(SRC:%.c=%.o)

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -D DEBUG=0

AR = ar rcs
RM = rm -rf

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# ANSI color codes
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m  # No Color (reset)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compiled $(NAME) successfully$(NC)"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Removing object files...$(NC)"
	@$(RM) $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing binary: $(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
