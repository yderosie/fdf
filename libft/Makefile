# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/08 12:52:10 by yderosie          #+#    #+#              #
#    Updated: 2014/12/17 10:53:05 by yderosie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = 	ft_memset		\
			ft_bzero		\
			ft_memcpy		\
			ft_memccpy		\
			ft_memmove		\
			ft_memchr		\
			ft_memcmp		\
			ft_strlen		\
			ft_strdup		\
			ft_strcpy		\
			ft_strncpy		\
			ft_strcat		\
			ft_strncat		\
			ft_strlcat		\
			ft_strchr		\
			ft_strrchr		\
			ft_strstr		\
			ft_strnstr		\
			ft_strcmp		\
			ft_strncmp		\
			ft_atoi			\
			ft_isalpha		\
			ft_isdigit		\
			ft_isalnum		\
			ft_isascii		\
			ft_isprint		\
			ft_toupper		\
			ft_tolower		\
			ft_memalloc		\
			ft_memdel		\
			ft_strnew		\
			ft_strdel		\
			ft_strclr		\
			ft_striter		\
			ft_striteri		\
			ft_strmap		\
			ft_strmapi		\
			ft_strequ		\
			ft_strnequ		\
			ft_strsub		\
			ft_strjoin		\
			ft_strtrim		\
			ft_strsplit		\
			ft_itoa			\
			ft_putchar		\
			ft_putstr		\
			ft_putendl		\
			ft_putnbr		\
			ft_putchar_fd	\
			ft_putstr_fd	\
			ft_putendl_fd	\
			ft_putnbr_fd	\
			ft_lstadd		\
			ft_lstdel		\
			ft_lstdelone	\
			ft_lstiter		\
			ft_lstnew		\
			get_next_line	\
			ft_realloc

SRCS	= $(addsuffix .c, $(FILES))
OBJ		= $(SRCS:%.c=obj/%.o)

.PHONY: all clean fclean re
.SILENT: clean fclean re all $(NAME)

all: dirobj $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

obj/%.o: %.c
	@$(CC) $(CFLAGS) -I./ -o $@ -c $^

clean:
	test ! -d obj || \
		rm -rf obj

fclean: clean
	test ! -f $(NAME) || \
		rm -f $(NAME)

re: fclean all

dirobj:
	test -d obj || \
		mkdir -p obj

