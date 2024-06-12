#################################################################################
#### ARGUMENTS ####

NAME	=	philosophers

CFLAGS	=	-Wall -Wextra -Werror -pthread

CC		=	cc

#################################################################################
#### COULEUR ####

GREEN 	= \033[1;32m
PURPLE 	= \033[1;35m
NC 		= \033[0m

#################################################################################
#### SOURCES ####

SRC_FILES	=	action \
				init   \
				main  \
				threads \
				utils \

OBJ_DIR 	= .o

OBJ_FILES	=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

#################################################################################
#### REGLES ####

all: $(OBJ_DIR) $(NAME)
		@echo "$(GREEN)Compilation réussie$(NC)!"

$(NAME): $(OBJ_FILES) 
		@$(CC) $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@echo "$(PURPLE)Compilation en cours...$(NC)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
		@echo "$(PURPLE)Nettoyage en cours...$(NC)"
		@rm -rf $(OBJ_DIR)/*.o
		@rmdir -p $(OBJ_DIR)

fclean: clean
		@echo "$(GREEN)Nettoyage effectuer !"
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re