
# COLORS
NOCOL=\033[0m
RED=\033[1;31m
YEL=\033[1;33m
ORG=\033[0;33m
GRN=\033[1;32m
DGRAY=\033[1;30m
BLU=\033[1;34m

ORANGE = \033[38;5;216m
LBLUE = \033[38;5;153m
LYELLOW = \033[38;5;222m
BEIGE = \033[38;5;223m
LGREEN = \033[38;5;155m

DEF = \033[0m
BOLD = \033[1m
CUR = \033[3m
UL = \033[4m
UP = \033[A

# NAMES
NAME = philo

# MAKE
MAKE = make

# COMPILER
CC = gcc

# PATHS
INC_PATH = inc
SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = lib

CFLAGS = -g -Wall -Wextra -fsanitize=thread#-Werror

# ANIMATION
SRCS_COUNT = 0
SRCS_TOT = ${shell find ./src/ -type f -name '*.c' | wc -l}
SRCS_PRCT = ${shell expr 100 \* ${SRCS_COUNT} / ${SRCS_TOT}}
#determine the length of the progress bar.
BAR =  ${shell expr 23 \* ${SRCS_COUNT} / ${SRCS_TOT}}


# SOURCES
SRC_FILES = creat_processes.c utils.c philo_bonus.c parsing.c init_philosophers.c	

SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\n\n\n   ${BOLD}${CUR}${LYELLOW}FDF COMPILED ✨${DEF}\n"

# #is used to redirect both standard output (stdout) and standard error (stderr) to /dev/null
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) > /dev/null 2>&1

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
#The eval command allows you to perform dynamic evaluation and assignment within the Makefile.
	@${eval SRCS_COUNT = ${shell expr ${SRCS_COUNT} + 1}}
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo ""
	@echo " ${BOLD}${CUR}${BEIGE}-> Compiling ${DEF}${BOLD}${LYELLOW}[FDF]${DEF}"
	@printf " ${BEIGE}   [${LGREEN}%-23.${BAR}s${BEIGE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
#@echo "${UP}${UP}${UP}": Uses ANSI escape sequences (${UP}) to move the cursor up three lines
	@echo "${UP}${UP}${UP}"

clean:
	@rm -rf $(OBJ_PATH)

test : $(NAME)
	make
	./fdf test_maps/t2.fdf

fclean: clean
	@rm -rf $(NAME)

re: fclean all

norm:
	@printf "\n${GRN}##########${YEL} NORMINETTE ${GRN}##########${NOCOL}\n"
	@printf "\n${GRN}FDF:${BLU}\n\n"
	@norminette $(INC_PATH)
	@norminette $(SRC_PATH)
	@printf "${NOCOL}"

.PHONY: all clean fclean re norm
