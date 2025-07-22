#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_len(int n)
{
	int			l;
	int			min;
	long int	nbr;

	min = 0;
	nbr = n;
	l = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		min -= 1;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		l++;
	}
	if (min == -1)
		return (l + 1);
	return (l);
}

char	*ft_itoa2(long int n, char *str)
{
	if (n > 9)
		str = ft_itoa2(n / 10, str);
	*str = n % 10 + '0';
	return (str + 1);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	char		*str;

	nbr = (long int)n;
	str = malloc(ft_len(n) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		ft_itoa2(-nbr, &str[1]);
	}
	else
		ft_itoa2(nbr, str);
	str[ft_len(n)] = 0;
	return (str);
}


void write_file(char *file) {
    char buf[64] = {0};
    char og[8] = "test";

    printf("writing to %s\n", file);
    int fd = open(file, O_CREAT | O_WRONLY, 0644);
    for(int i = 0; i < 10000; i++) {
        strcpy(buf, og);
        strcpy(buf + 4, ft_itoa(i));
        write(fd, buf, strlen(buf));
        write(fd, "\n", 1);
    }
}

int main(void) {
    write_file("test.txt");
}