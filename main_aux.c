# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
//# include "ft_printf/ft_printf.h"
# include <math.h>
int main(void)
{ 
    char	*line;
	int		fd;

	fd = open("main_aux.txt", O_RDONLY);
	if (fd < 0)
        exit(0);
	line = get_next_line(fd);
    if (!line)
        printf("Nulo.");
	while (line)
    {
        printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
    return (0);
}