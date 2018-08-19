NAME	=	ft_ls

SRC_BASE		=	classic_display.c \
					column.c \
					column_part2.c \
					display_errors.c \
					display_colors.c \
					free.c \
					long_display.c \
					long_format_details_part1.c \
					long_format_details_part2.c \
					long_format.c \
					main.c \
					merge_sorting.c \
					parsing_misc.c \
					parsing_names.c \
					parsing_options.c \
					recursive_search.c \
					reverse_sorting.c \
					sorting.c
 
CC            =    gcc
FLAGS        =    -Wall -Wextra -Werror
    
LEN_NAME    =    `printf "%s" $(NAME) |wc -c`
DELTA        =    $$(echo "$$(tput cols)-24-$(LEN_NAME)"|bc)

LIBFT_DIR    =    libft/
LIBFT_LIB    =    $(LIBFT_DIR)libft.a
LIBFT_INC    =    $(LIBFT_DIR)includes/
    
SRC_DIR        =    srcs/
INC_DIR        =    includes/
OBJ_DIR        =    objs/
    
SRCS        =    $(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS        =    $(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

all :            $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIBFT_INC) $(LIBFT_LIB) $(OBJS) -o $(NAME)
	@echo "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K"

$(LIBFT_LIB):
	@make -j -C $(LIBFT_DIR)
    
$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))
    
$(OBJ_DIR)%.o :    $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -MMD -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_INC)
	@printf "\r\033[38;5;11m⌛ MAKE %s     plz wait :  %*s\033[0m\033[K" $(NAME) $(DELTA) "$@"

clean: cleanlib
	@rm -rf $(OBJ_DIR)
	@echo "\r\033[38;5;202m✖ clean $(NAME).\033[0m\033[K"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:	clean fcleanlib
	@rm -f $(NAME)
	@echo "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K"

fcleanlib: cleanlib
	@make -C $(LIBFT_DIR) fclean
re:	fclean all

relib: fcleanlib $(LIBFT_LIB)

.PHONY :        fclean clean re relib cleanlib fcleanlib
