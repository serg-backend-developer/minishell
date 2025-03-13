#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*gnl_strchr(char *str, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(char *str);

char	*get_next_line(int fd);

#endif
