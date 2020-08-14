#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
  int i;
  i = 0;
  while (str[i]!=0)
    i++;
  return(i);
}
char *ft_strdup(char *str)
{
  int l;
  char *dst;
  int i;

  l = ft_strlen(str);
  if (!(dst = malloc(l+1)))
    return(0);
  i = 0;
  while (i < l)
  {
    dst[i]=str[i];
    i++;
  }
  dst[i]='\0';
  return(dst);
}
char *ft_strc(char *str, char c)
{
  int l;
  char *dst;
  int i;

  l = ft_strlen(str);
  if (!(dst = malloc(l+2)))
    return(0);
  i = 0;
  while (i < l)
  {
    dst[i]=str[i];
    i++;
  }
  dst[i]=c;
  dst[i+1]='\0';
  free(str);
  return(dst);
}
int get_next_line(char **line)
{
  char *buf;
  int ret;
  int flag;

  flag = 0;
  buf = malloc(1);
  if (line == NULL)
    return(-1);
  if (!(*line = ft_strdup("")))
    return(-1);
  while ((ret = read(0,buf,1)) > 0)
  {
    if (buf[0]=='\n' || buf[0]==EOF)
    {
      flag = 1;
      break;
    }
    *line = ft_strc(*line,buf[0]);
  }
  free(buf);
  return(flag);
}
