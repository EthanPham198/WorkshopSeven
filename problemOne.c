#include <stdio.h>
#include <windows.h>
#include <string.h>


#define MAXN 100
#define MAXCHOICE 5
char* lTrim(char s[]){
    int i = 0;
    while (s[i]==' ')i++;
    if (i>0) strcpy(&s[0], &s[i]);
    return s;

}
char* rTrim (char s[])
{ int i=strlen(s)-1;
    while (s[i]==' ') i--;
    s[i+1]='\0';
    return s;}

char* trim (char s[]) {
    rTrim(lTrim(s));
    char *ptr=strstr(s,"");
    while (ptr!=NULL) {
        strcpy (ptr, ptr+1);
        ptr = strstr(s, "");
    }
    return s;
}
char* nameStr (char s[]){
    trim(s);
    strlwr(s);
    int L = strlen(s);
    int i;
    for (i=0;i<L;i++)
        if (i==0||i>0 && (s[i-1]==' ')) s[i] = toupper (s[i]);
    return s;}
char getUserChoice()
{
    int c;
    printf("Welcome to Ethan's school directory.\n");
    printf("Press 1 to add a student\n");
    printf("Press 2 to remove a student\n");
    printf("Press 3 to search a student\n");
    printf("Press 4 to print the list in ascending order\n");
    printf("Press 5 to quit\n");
    printf("What is your choice? ");
    fflush(stdin);
    scanf("%c", &c);
    return c;
}

int isFull(char list[MAXN][21], int *pn) {
    return ((*pn) == MAXN);
}

int isEmpty(char list[MAXN][21], int *pn) {
    return ((*pn) == 0);
}

void add(char list[MAXN][21], int *pn) {
    char hs[21];
    int i, existed;
    do {
        printf("Enter the name of the student you would like to add: ");
        fflush(stdin);
        scanf("%20[^\n]", hs);
        existed = 1;
        for ( i = 0; i < *pn; i++)
            if (strcmp(hs,list[i]) == 0)
            {
                printf("Error! This name already exists. Please enter in another name. \n");
                existed = 0;
                i = *pn - 1;
            }
    } while (!existed);
    strcpy(list[*pn], hs);
    (*pn)++;
    printf("Student has been added.\n");
    system("pause");
    system("cls");
}

void search(char list[MAXN][21], int *pn)
{
    int i;
    printf("Enter the name of the student you are looking for.");
    char hs[21];
    fflush(stdin);
    scanf("%20[^\n]", &hs);
    for (i = 0; i < *pn; i++)
    {
        nameStr(hs);
        nameStr(list[i]);
        char * ptr = strstr(list[i], hs);
        if (ptr != '\0') printf("RESULT : Name[%d] : %s\n", i, list[i]);
    }
}
void removed(char list[MAXN][21], int *pn)
{
    search(list, pn);
    printf("Which name do you want to be removed?(input a number) : ");
    int del, i;
    scanf("%d", &del);
    if (del >= 0 && del < *pn) {
        for (i = del + 1; i < *pn; i++)
            strcpy(list[i-1], list[i]);
        printf("Removed!\n");
        (*pn)--;
    } else printf("Unremoved!\n");
    system("pause");
    system("cls");
}
void print(char list[MAXN][21], int *pn)
{
    int i, j;
    for (i = 0 ; i < *pn-1; i++)
        for (j = *pn-1; j > i; j--)
            if (strcmp(list[j] , list[j-1]) < 0)
            {
                char t[21];
                strcpy(t, list[j]);
                strcpy(list[j], list[j-1]);
                strcpy(list[j-1], t);
            }
    for (i = 0; i < (*pn); i++)
    {
        nameStr(list[i]);
        printf("Name[%d] : %s \n", i, list[i]);
    }
    system("pause");
    system("cls");
}
void halt()
{
    printf("Goodbye!\n");
}

int main()
{
    char userChoice;
    char list[MAXN][21];
    int n = 0;
    do
    {
        userChoice = getUserChoice();
        switch(userChoice)
        {
            case '1':
                if (isFull(list, &n)) printf("Impossible to add!\n");
                else add(list, &n);
                break;
            case '2':
                if (isEmpty(list, &n)) printf("Impossible to remove!\n");
                else removed(list, &n);break;
            case '3':
                if (isEmpty(list, &n)) printf("Nothing to search!\n");
                else search(list, &n);
                system("pause");
                system("cls");
                break;
            case '4':
                if (isEmpty(list, &n)) printf("Nothing to print!\n");
                else print(list, &n);
                break;
            case '5':
                halt();
                break;
        }
        if (userChoice < '1'  || userChoice >'5') printf("Input numbers 1 to 5 only!\n");
    } while (userChoice != MAXCHOICE);
}