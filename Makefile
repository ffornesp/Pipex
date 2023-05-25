# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 19:51:17 by ffornes-          #+#    #+#              #
#    Updated: 2023/05/25 12:54:56 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

LIBFT_DIR = libft/
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))

###############################################################################
#									SRCS									  #
###############################################################################

SRCS_DIR = srcs/
SRC_FILES =	 pipex.c get_path.c error_handle.c pipex_utils.c

SRCS_BONUS_DIR = bonus/
SRC_BONUS_FILES = pipex_bonus.c heredoc_bonus.c
SRC_BONUS_PS_FILES = get_path.c error_handle.c pipex_utils.c

###############################################################################
#									OBJS									  #
###############################################################################

OBJS_DIR =	objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ_FILES))

OBJ_BONUS_PS_FILES = $(SRC_BONUS_PS_FILES:.c=.o)
OBJS_BONUS_PS = $(addprefix $(OBJS_DIR), $(OBJ_BONUS_PS_FILES))

OBJS_BONUS_DIR = objs_bonus/
OBJ_BONUS_FILES = $(SRC_BONUS_FILES:.c=.o)
OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR), $(OBJ_BONUS_FILES))

###############################################################################
#									OTHER									  #
###############################################################################

HDR_FILES = pipex.h
HDR_BONUS_FILES = pipex.h pipex_bonus.h
HDR_DIR = include/
HDRS = $(addprefix $(HDR_DIR), $(HDR_FILES))
HDRS_BONUS = $(addprefix $(HDR_DIR), $(HDR_BONUS_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rc
INCLUDE  = -I ./include/ -I ./libft/include/

###############################################################################
#									RULES									  #
###############################################################################

all: 		m_libft $(NAME)

bonus:		m_libft $(NAME_BONUS)

m_libft:
			@make -C $(LIBFT_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
			$(CC) $(INCLUDE) $(OBJS) -Llibft/ -lft -o $@

$(NAME_BONUS):	$(OBJS_DIR) $(OBJS_BONUS_PS) $(OBJS_BONUS_DIR) $(OBJS_BONUS)
				$(CC) $(INCLUDE) $(OBJS_BONUS) $(OBJS_BONUS_PS) -Llibft/ -lft -o $@			

$(OBJS_DIR):
						@mkdir $@

$(OBJS_BONUS_DIR):
						@mkdir $@

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(LIBFT) $(HDRS)
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJS_BONUS_DIR)%.o:	$(SRCS_BONUS_DIR)%.c $(LIBFT) $(HDRS_BONUS)
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean: 		
			make -C $(LIBFT_DIR) clean
			@$(RM) $(OBJS)
			@$(RM) $(OBJS_BONUS)

fclean: 	clean
			make -C $(LIBFT_DIR) fclean
			@$(RM) $(NAME)
			@$(RM) $(NAME_BONUS)

re:			fclean all
			

.PHONY: all clean fclean re bonus m_libft
