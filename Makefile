#Definition
CC          	=   gcc
NAME        	=   cub3D
LIBFT			=	./Libft/libft.a
LIBFT_PATH		=	./Libft
MINILIBX		=	./minilibx/libmlx.a
MINILIBX_PATH	=	./minilibx
CFLAGS			=	-Wall -Werror -Wextra -g -I ./include -I ./Libft -I ./minilibx -O2
LFLAGS      	=   -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx
LEAKS			=	-fsanitize=address
RM				=	rm -f

#COLORS
GREEN = \033[1;32m
RED = \033[1;31m
GREY = \033[2;37m
MAGENTA = \033[0;35m
RESET = \033[m

#	All process use for compiling.
UNAME		:= $(shell uname -s)
NUMPROC		:= 8

#	Compiling with all threads.
ifeq ($(UNAME), Linux)
	NUMPROC	:= $(shell grep -c ^processor /proc/cpuinfo)
	OS = "You are connected from -$(CYAN)$(UNAME)$(X)- 🐧 Welcome -$(CYAN)$(USER)$(X)- 😄!"
else ifeq ($(UNAME), Darwin)
	NUMPROC	:= $(shell sysctl -n hw.ncpu)
	OS = "You are connected from 42 school's iMac 🖥 ! Welcome $(CYAN)$(USER)$(X)"
	ifeq ($(USER), ayaman)
		OS = "You are connected from -$(CYAN)KALIAQ$(X)- 💻 Welcome -$(CYAN)$(USER)$(X)-!"
	endif
endif
# You can use --> man sysctl -> shell: sysctl -a | grep "hw.ncpu"

#Directory
OBJ_DIR			=	obj/
SRC_DIR			= 	src/
LIBFT_DIR		=	Libft/
INC_DIR			=	includes/

#Files
COMMON			= 	error ft_strjoin_free get_map_info get_next_line get_texture init key_press list main parse_color parse_map parse player_position ray texture utils utils2


#FileCreate 
SRC_FILES		+=	$(addprefix $(SRC_COMMON),$(COMMON))


SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF			=	.cache_exists

all:		
	@$(MAKE) welcome $(NAME) -j $(NUMPROC)

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(SRC_COMMON)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@
			@echo Compiling Success file is : $< $(SRC_DIR) $@ 

norm:
			@echo "$(RED)$ Source Norminettes $(RESET)"
			@norminette $(SRC) | grep -v Norme -B1 || true
			@echo
			@echo "$(RED)$ Libft Norminettes $(RESET)"
			@norminette $(LIBFT_DIR) | grep -v Norme -B1 || true
			@echo
			@echo "$(RED)$ Includes Norminettes $(RESET)"
			@norminette $(INC_DIR) | grep -v Norme -B1 || true


$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
			@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -o $(NAME) $(LIBFT) $(MINILIBX)
			@echo $(NAME) compiled!
			
			
$(LIBFT):
			@${MAKE} all -C libft

$(MINILIBX):
			@${MAKE} all -C minilibx

clean:
			@$(RM) -rf $(OBJ_DIR)
			@$(RM) -f $(OBJF)const
			@${MAKE} clean -C libft
			@${MAKE} clean -C minilibx
			@echo Objects files cleaned!

fclean:		clean
			@$(RM) -f $(NAME)
			@${MAKE} fclean -C libft
			@${MAKE} clean -C minilibx
			@echo $(NAME) executable files cleaned!
			

re:			fclean all
			@echo Cleaned and rebuilt

welcome:
			@echo "$(RED)$ oozdiyar and ayaman $(RESET)"

.PHONY:		all clean fclean re bonus norm