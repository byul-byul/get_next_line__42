// bgadzhil

#include "get_next_line.h"

static int	handle_params(t_params *p)
{
	int		separator_pos;

	separator_pos = ft_chrinstr(p->buff, SEPARATOR);
	if (separator_pos != -1)
	{
		if (!p->line)
			p->line = ft_substr(buff, 0, separator_pos);
		else
			ft_straddstr(p->line, ft_substr(buff, 0, separator_pos));
		buff[separator_pos] = '\0';
		ft_strcpy(buff, buff + separator_pos + 1);
	}
	else
	{
		if (!p->line)
			p->line = p->buff;
		else
			ft_straddstr(&(p->line), &(ft_substr(buff, 0, separator_pos)));
		p->buff = NULL;
	}
	return (separator_pos);
}

char		*get_next_line(int fd)
{
	int			readed_bytes;
	t_params	params;
	
	params.line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (params.buff)
		if (handle_params(&params) != -1)
			return (params.line);
	while (1)
	{
		readed_bytes = read(fd, params.buff, BUFFER_SIZE);
		if (readed_bytes != -1)
			if (handle_params(&params) != -1)
				break ;
	}
	return (params.line);
}
