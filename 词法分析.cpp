#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define MAXN 10000
//定义种类编码
/*
    < begin,1 >
    < end,2 >
    < integer,3 >
    < if,4 >
    < then,5 >
    < else,6 >
    < function,7 >
    < read,8 >
    < write,9 >
    < 标识符,10 >
    < 常数,11 >
    < =,12 >
    < <>,13 >
    < <=,14 >
    < <,15 >
    < >=,16 >
    < >,17 >
    < -,18 >
    < *,19 >
    < :=,20 >
    < (,21 >
    < ),22 >
    < ;,23 >
 */

//保留字表
static char reserveWord[9][16] = {
    "begin","end","integer","if","then","else","function","read","write"
};

//查找保留字
int searchReserve(char reserveWord[][16], char s[]){
    for (int i = 0; i < 9; i++)
    {
        if (strcmp(reserveWord[i], s) == 0)
        {
            return i + 1;//返回种别码
        }
    }
    return -1;//否则返回-1，代表查找不成功，即为标识符
}

int judgetep(char tep){
    /* 
    检测一个字符
    字母返回 1
    数字返回 2
    = 返回 3
    - 返回 4
    * 返回 5
    ( 返回 6
    ) 返回 7
    < 返回 8
    > 返回 9
    : 返回 10
    ; 返回 11
    */
    if (tep >= 'a'&&tep <= 'z' || tep >= 'A'&&tep <= 'Z'|| tep=='_')
    {
        return 1;
    }
    else if (tep >= '0'&&tep <= '9')
    {
        return 2;
    }
    else if (tep =='=')
    {
        return 3;
    }
    else if (tep =='-')
    {
        return 4;
    }
    else if (tep == '*')
    {
        return 5;
    }
    else if (tep == '(')
    {
        return 6;
    }
    else if (tep == ')')
    {
        return 7;
    }
    else if (tep == '<')
    {
        return 8;
    }
    else if (tep == '>')
    {
        return 9;
    }
    else if (tep == ':')
    {
        return 10;
    }    
    else if (tep == ';')
    {
        return 11;
    }
    else
    {
        return 0;
    }
}

//预处理,去掉注释
void predo(char project[],int Pproject){
    char temp[MAXN];
    int cot = 0;
    for(int i = 0;i<=Pproject;i++){
        if (project[i]=='/'&&project[i+1]=='/')
        {
            while (project[i]!='\n')
            {
                i++;
            }
        }
        if (project[i]=='/'&&project[i+1]=='*')
        {
            i+=2;
            while (project[i]!='*'&&project[i+1]!='/')
            {
                i++;
                if(project[i]=='@'){
                    printf("注释有误，请查证后重试！\n");
                    exit(0);
                }
            }
            i+=2;
        }
        if (project[i]!='\n'&&project[i]!='\t'&&project[i]!='\v'&&project[i]!='\r'){
            temp[cot++]=project[i];
        }
    }
    temp[cot]='\0';
    strcpy(project,temp);
}


void Reader(int &syn,char resourceproject[],char token[],int &Pproject){
    int i,cot=0;
    char tep;
    tep = resourceproject[Pproject];
    while (tep==' ')
    {
        Pproject++;
        tep = resourceproject[Pproject];
    }
    for (int i = 0; i < 16; i++)
    {
        token[i]='\0';
    }
    //结束判断
    if (resourceproject[Pproject] == '@')
    {
        syn = 0;
        token[0]='@';
        token[1]='\0';
        return;
    }
    switch (judgetep(tep))
    {
    case 1:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        while (judgetep(resourceproject[Pproject])==1||judgetep(resourceproject[Pproject]==2)){
            token[cot++]=resourceproject[Pproject];
            Pproject++;
        }
        token[cot]='\0';
        syn = searchReserve(reserveWord,token);
        if(syn == -1){
            syn = 10;
        }
        break;
    case 2:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        while (judgetep(resourceproject[Pproject])==2)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
        }
        token[cot]='\0';
        syn = 11;
        break;
    case 3:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 12;
        break;
    case 4:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 18;
        break;
    case 5:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 19;
        break;
    case 6:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 21;
        break;
    case 7:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 22;
        break;
    case 8:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==3)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 14;
        }
        else if (judgetep(resourceproject[Pproject])==9)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 13;
        }
        else
        {        
            token[cot]='\0';
            syn = 15;
        }
        break;
    case 9:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==12)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 16;            
        }
        else
        {
            token[cot]='\0';
            syn = 17;    
        }
        break;
    case 10:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==3)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 20;            
        }
        else
        {
            printf("未查到对应字符，请重试\n");
            exit(0);            
        }
        break;
    case 11:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 23;  
        break;
    default:
        printf("未查到对应字符，请重试\n");
        exit(0);
        break;
    }
    return;
}

//主函数
int main(){
    char resourceproject[MAXN];
    char token[16] = {0};
    int syn = -1;
    int i;
    int Pproject = 0;//源程序读取指针
    FILE *fp,*fp1;
    if((fp=fopen("D:\\project.txt","r"))==NULL){
        cout<<"Can't open this file~";
        exit(0);
    }
    resourceproject[Pproject]=fgetc(fp);
    while (resourceproject[Pproject]!='@')
    {
        Pproject++;
        resourceproject[Pproject]=fgetc(fp);
    }
    resourceproject[++Pproject]='\0';
    fclose(fp);
    cout<<"源程序为:"<<endl;
    cout<<resourceproject<<endl;
    predo(resourceproject,Pproject);
    Pproject = 0;
    printf("-------------------------begin---------------------------\n");
    printf("种别----------------------------------------------单词符号\n");
    while (syn != 0)
    {
        Reader(syn,resourceproject,token,Pproject);
        switch (syn)
        {
        case 0:
            printf("结束符-------------------------------------------------%s\n",token);
            break;            
        case 10:
            printf("标识符-------------------------------------------------%s\n",token);
            break;
        case 11:
            printf("常数---------------------------------------------------%s\n",token);
            break;
        case 12:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 13:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 14:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 15:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 16:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 17:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 18:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 19:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 20:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 21:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 22:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 23:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        default:
            printf("关键词-------------------------------------------------%s\n",token);
            break;
        }
    }
    printf("-----------------------finshed!--------------------------\n");
    
}