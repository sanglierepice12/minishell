#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_str_dup(char *src, char *msg)
{
	char	*dup;
	ssize_t	i;
	ssize_t	j;
	size_t	len;

	if (!src)
		return (NULL);
	if (msg)
		len = ft_strlen(src) + ft_strlen(msg);
	else
		len = ft_strlen(src);
	dup = calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	j = -1;
	while (++i, src[i])
		dup[i] = src[i];
	if (msg)
	{
		while (++j, msg[j])
			dup[i++] = msg[j];
	}
	return (dup);
}

int main(int arc, char **argv)
{
	char *coucou;
	if (!arc)
		return 0;
	coucou = ft_str_dup(argv[1], argv[2]);
	if (!coucou)
		return (-1);
	printf("coucou = %s\n", coucou);
	free(coucou);
	return (0);
}