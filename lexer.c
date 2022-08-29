#include <stdio.h>

typedef struct s_token
{
    char            *content;
    char            *type;
    // int              n;
    // char         sep;
    struct s_token  *next;
}               t_token;
// typedef  struct  s_cmd
// {
//  t_token *first_token;
//  t_token *next;
// }                t_cmd;
int ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != ‘\0’ && s2[i] != ‘\0’)
    {
        if (s1[i] == s2[i])
            i++;
        else
            break ;
    }
    return (s1[i] - s2[i]);
}
void    check_type(t_token *line)
{
    // while (line)
    // {
    //  line->type = “cmd”;
    //  if (line->next != NULL)
    //      line = line->next;
    //  else
    //      break ;
    //  line->type = “pipe”;
    //  while (ft_strcmp(line->content, “|”) != 0)
    //
    //      if (ft_strcmp(line->content, “>”) == 0 || ft_strcmp(line->content, “>>“) == 0
    //          || ft_strcmp(line->content, “<”) == 0 || ft_strcmp(line->content, “<<“) == 0)
    //      {
    //          line->type = “redir”;
    //      }
    //      else
    //      {
    //          line->type = “word”;
    //      }
    //      if (line->next != NULL)
    //          line = line->next;
    //      else
    //          break ;
    //  }
    //  if (line->next != NULL)
    //      line = line->next;
    //  else
    //      break ;
    // }
    while (line)
    {
        if (ft_strcmp(line->content, “|”) == 0)
        {
            line->type = “pipe”;
        }
        else if (ft_strcmp(line->content, “>”) == 0 || ft_strcmp(line->content, “>>“) == 0
            || ft_strcmp(line->content, “<”) == 0 || ft_strcmp(line->content, “<<“) == 0)
        {
            line->type = “redir”;
        }
        else
        {
            line->type = “word”;
        }
        if (line->next)
            line = line->next;
        else
            break;
    }
}
void    lexical_analysis(t_token *line)
{
    check_type(line);
    lexcial_analyze(line);
}
int main(void)
{
    t_token t_1;
    t_token t_2;
    t_token t_3;
    t_token t_4;
    t_token t_5;
    t_1.content = “echo”;
    t_2.content = “hello world”;
    t_3.content = “|”;
    t_4.content = “ls”;
    t_5.content = “>>“;
    t_1.next = &t_2;
    t_2.next = &t_3;
    t_3.next = &t_4;
    t_4.next = &t_5;
    t_5.next = NULL;
    t_token *token;
    token = &t_1;
    while (token)
    {
        printf(“%s\n”, token->content);
        token = token->next;
    }
    printf(“----------------\n”);
    token = &t_1;
    lexing(token);
    while (token)
    {
        printf(“%s\n”, token->type);
        token = token->next;
    }
}