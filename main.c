#include "minishell.h"

int main(void)
{
    t_token t_1;
    t_token t_2;
    t_token t_3;
    t_token t_4;
    t_token t_5;
    t_1.content = "echo";
    t_2.content = "hello world";
    t_3.content = "|";
    t_4.content = "ls";
    t_5.content = "-a";
    t_1.next = &t_2;
    t_2.next = &t_3;
    t_3.next = &t_4;
    t_4.next = &t_5;
    t_5.next = NULL;

    t_token *token = &t_1;
    while (token)
    {
        printf("%s\n", token->content);
        token = token->next;
    }
    printf("----------------\n");
    token = &t_1;
    if (lexcial_analyze(token) < 0)
    {
        printf("error!\n");
        return (-1);
    }
    while (token)
    {
        printf("%c\n", token->type);
        token = token->next;
    }

    split_cmd(token);
}