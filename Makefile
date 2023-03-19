# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 11:52:41 by pfaria-d          #+#    #+#              #
#    Updated: 2023/03/19 11:53:38 by pfaria-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOCOLOR			= \033[0m
WHITE			= \033[1;37m
RED				= \033[0;31m
LIGHTPURPLE		= \033[1;35m
CLEAR			= \r\033[K
LIGHTGRAY		= \033[0;37m
GREEN			= \033[0;32m

SRC 		= philosophers.c \
			  error_management.c 

SRCBONUS	= 

OBJS 		= $(SRC:.c=.o)

OBJSBONUS 	= $(SRCBONUS:.c=.o)

GCC 		= gcc

FLAGS		= -Wall -Wextra -Werror

RM  = rm -f

NAME = philosophers

ifdef 	MAKEBONUS
    OBJS = $(OBJSBONUS)
endif

NORM = $(shell norminette | grep Error: | wc -l | awk '{print $1}' | xargs)

NORMINETTE = 0

ifeq (${NORM}, ${NORMINETTE})
	NORMINETTE = "${WHITE}NORM : ${GREEN}OK${NOCOLOR}\n"
else
	NORMINETTE = "${WHITE}NORM : ${RED}${NORM} errors${NOCOLOR}\n"
endif

all: 		$(NAME)

.c.o:
			@printf "${CLEAR}🌂 ${LIGHTPURPLE}%s ${LIGHTGRAY}compiling...${NOCOLOR}" ${notdir $<}
			@$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)


$(NAME):	$(OBJS)
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}Philosophers ${LIGHTGRAY}compiled\n${NOCOLOR}"
			@$(GCC) $(FLAGS) $(OBJS) -o $(NAME) 
			@echo ${NORMINETTE}

bonus:		fclean
			@make MAKEBONUS=1 all

clean:
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}.o files  ${LIGHTGRAY}cleaned\n${NOCOLOR}"
			@$(RM) $(OBJS) $(OBJSBONUS)

fclean:		clean
			@printf "${CLEAR}☂️  ${LIGHTPURPLE}Philosophers ${LIGHTGRAY}cleaned\n${NOCOLOR}"
			@$(RM) $(NAME)

re:			fclean $(NAME)