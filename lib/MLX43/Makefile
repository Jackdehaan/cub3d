CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

SRC_DIR = src
PARSING_DIR = parsing
UTILS_DIR = utils
GNL_DIR = gnl
DRAW_DIR = draw

SRC :=  $(wildcard $(SRC_DIR)/*.c) \
	    $(wildcard $(SRC_DIR)/$(PARSING_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/$(GNL_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/$(DRAW_DIR)/*.c) 


OBJS_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

NAME = cub3D

LIBFT_DIR = libft
LIBFT_TARGET = src/libft.a

LIBMLX_TARGET    := lib/MLX42/build/libmlx42.a 


# LIBMLX_target = libmlx42.a 

.PHONY: all clean fclean re libmlx

all: $(NAME)

$(LIBMLX_TARGET):
	make -C $(@D)

clean:
	rm -rf $(OBJ)
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"
	$(MAKE) -C $(LIBFT_DIR) clean
	make -C $(dir $(LIBMLX_TARGET)) clean
	@echo "$(YELLOW)Cleaned libft static library!$(DEFAULT)"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@echo "$(RED)Removed executables!$(DEFAULT)"
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(LIBFT_TARGET)
	@echo "$(RED)Removed libft static library in src directory!$(DEFAULT)"

$(LIBFT_TARGET):
	$(MAKE) -C $(LIBFT_DIR)

library: $(LIBFT_TARGET)

re: fclean all

$(NAME): $(OBJS_DIR) $(OBJ) $(LIBFT_TARGET) $(LIBMLX_TARGET)
	$(CC) -o $(NAME) $(OBJ) $(LIBMLX_TARGET) $(LDFLAGS) $(LINKERFLAGS) -ldl -lglfw -pthread -lm $(LIBFT_TARGET)
	@echo "$(GREEN)Compiled cub3D!$(DEFAULT)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

/fsan:
	$(MAKE) FSAN=1 BUG=1
.PHONY: fsan

resan:  fclean fsan
.PHONY: resan

debug:
	$(MAKE) BUG=1
.PHONY: debug

rebug:  fclean debug
.PHONY: rebug
