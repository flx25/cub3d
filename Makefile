NAME = 			cub3D

OBJ_DIR = 		build
SRC_DIR =		srcs
PARSER_DIR =	parser
INCL_DIR =		includes

SRC = 			main draw init raycasting raycasting_utils raycasting_utils_2 \
				textures mouse keyboard terminate minimap animations navigate \
				sprite fireball doors player npc npc_utils mouse_center
PARSER =		parser so_long_parser get_next_line get_next_line_utils \
				check_map_enclosure parser_utils parser_mapcheck \
				parser_utils_2 parser_utils_3

OBJS =			$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))
OBJS +=			$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(PARSER)))

LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a

CC = 			cc

UNAME_S =		$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  MLX_DIR =		libmlx_opengl
else
  MLX_DIR =		libmlx_linux
endif

MLX =			$(MLX_DIR)/libmlx.a


CFLAGS =		-Wall -Werror -Wextra -g
INCL =			-I./$(INCL_DIR)
LIBS =			-L$(LIBFT_DIR) \
				-L$(MLX_DIR) \
				-lm -lft -lmlx

ifeq ($(UNAME_S),Darwin)
  LIBS +=		-framework OpenGL \
				-framework AppKit
else
  LIBS +=		-L/opt/X11/lib \
				-lX11 -lXext
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(MLX):
	$(MAKE) -s -C $(MLX_DIR) 2>/dev/null

$(LIBFT):
	$(MAKE) -s -C $(LIBFT_DIR) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -fr $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
