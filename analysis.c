#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
FILE *fp;
int length;
char wd;
char token[100];

int main(int argc, char *argv[])
{
    fp = fopen(argv[1], "r");
    while (!feof(fp))
        getsym();
    fclose(fp);
    return 0;
}

void AddNul()
{
    token[length] = '\0';
}
void getch()
{
    wd = fgetc(fp);
}
void cat()
{
    token[length++] = wd;
}
void ungetch()
{
    ungetc(wd, fp);
}
void reserve()
{
    AddNul();
    if (strcmp(token, "BEGIN") == 0)
        printf("Begin\n");
    else if (strcmp(token, "END") == 0)
        printf("End\n");
    else if (strcmp(token, "FOR") == 0)
        printf("For\n");
    else if (strcmp(token, "IF") == 0)
        printf("If\n");
    else if (strcmp(token, "THEN") == 0)
        printf("Then\n");
    else if (strcmp(token, "ELSE") == 0)
        printf("Else\n");
    else
        printf("Ident(%s)\n", token);
}
void ClearToken()
{
    length = 0;
    memset(token, 0, sizeof(token));
}
int getNumber()
{
    AddNul();
    return atoi(token);
}
void error()
{
    printf("Unknown\n");
    exit(0);
}
void getsym()
{
    ClearToken();
    do
        getch();
    while (isspace(wd));
    if (isalpha(wd))
    {
        while (isalpha(wd) || isdigit(wd))
        {
            cat();
            getch();
        }
        ungetch();
        reserve();
    }
    else if (isdigit(wd))
    {
        while (isdigit(wd))
        {
            cat();
            getch();
        }
        ungetch();
        printf("Int(%d)\n", getNumber());
    }
    else if (wd == ':')
    {
        getch();
        if (wd == '=')
            printf("Assign\n");
        else
        {
            ungetch();
            printf("Colon\n");
        }
    }
    else if (wd == '+')
        printf("Plus\n");
    else if (wd == '*')
        printf("Star\n");
    else if (wd == ',')
        printf("Comma\n");
    else if (wd == '(')
        printf("LParenthesis\n");
    else if (wd == ')')
        printf("RParenthesis\n");
    else if (!feof(fp))
        error();
}