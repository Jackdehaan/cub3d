CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

LDFLAGS =
ifeq ($(shell uname -s),Linux)
    CC +=-fsanitize=leak
endif
ifdef FSAN
    CC +=-fsanitize=address
endif
ifdef BUG
    CFLAGS +=-g
endif

SRC_DIR = src
PARSING_DIR = parsing
UTILS_DIR = utils
GNL_DIR = gnl


SRC :=  $(wildcard $(SRC_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(PARSING_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(GNL_DIR)/*.c)

OBJS_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

NAME = cub3D

LIBS_TARGET = src/libft.a

LIBFT_DIR = libft

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ)
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Cleaned libft static library!$(DEFAULT)"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@echo "$(RED)Removed executables!$(DEFAULT)"
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(SRC_DIR)/libft.a
	@echo "$(RED)Removed libft static library in src directory!$(DEFAULT)"


$(LIBS_TARGET):
	$(MAKE) -C $(LIBFT_DIR)

library: $(LIBS_TARGET)

re: fclean all

$(NAME): $(OBJS_DIR) $(OBJ) $(LIBS_TARGET)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LINKERFLAGS) $(LIBS_TARGET) $(LIBS_TARGET)
	@echo "$(GREEN)Compiled cub3d!$(DEFAULT)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

fsan:
	$(MAKE) FSAN=1 BUG=1
.PHONY: fsan

resan:  fclean fsan
.PHONY: resan

debug:
	$(MAKE) BUG=1
.PHONY: debug

rebug:  fclean debug
.PHONY: rebug

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m