NAME = Cub3d

LIBFT = libft/libft.a

MLX_DIR = ./mlx
MLX_PATH = mlx/libmlx.a
MLX =  -L /usr/lib -lXext -lX11 -lm -lz 
MLX_OBJ = -I/usr/include -Imlx_linux -O3

MLX_LIB = -L $(MLX_DIR) -lmlx

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS =	source/main.c \
		source/parsing.c \
		

OBJ_DIR = Objects
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling MLX..."
	@make -s -C $(MLX_DIR) > /dev/null
	@echo "Compiling Libft..."
	@make -s bonus -C libft
	@echo "Building $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLX_LIB) $(MLX) -o $(NAME)
	@echo "Compiled successfully."

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@make -s clean -C libft
	@$(RM) $(OBJ_DIR)
	@$(RM) mlx/*.o
	@if [ -f traces.txt ]; then $(RM) traces.txt; fi
	@if [ -f 0 ]; then $(RM) 0; fi
	@echo "Cleaned successfully."

fclean : clean
	@make -s fclean -C libft
	@$(RM) $(NAME)
	@echo "Program cleaned successfully."

re : fclean all
