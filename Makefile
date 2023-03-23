# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 11:52:41 by pfaria-d          #+#    #+#              #
#    Updated: 2023/03/23 14:02:48 by pfaria-d         ###   ########.fr        #
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
			  error_management.c \
			  utilities.c \
			  utilities2.c \
			  philo_phases.c \
			  end_checker.c \

SRCBONUS	= 

OBJS 		= $(SRC:.c=.o)

OBJSBONUS 	= $(SRCBONUS:.c=.o)

GCC 		= gcc

FLAGS		= -Wall -Wextra -Werror #-g -fsanitize=thread

RM  = rm -f

NAME = philo

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
