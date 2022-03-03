/*1）本系统采用一个包含N个数据的结构体数组或单向链表，每个数据的结构应当包括：学号、姓名、性别、年龄、备注。
3）执行一个具体的功能之后，程序将重新显示菜单。
4）将学生基本信息保存到文件中。
5）进入系统之前要先输入密码。*/

//头文件包含
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pause system("pause")
#define cls system("cls")
#define N 1024

//定义结构体数组
typedef struct{
    long long sno; //学号
    char name[20]; //姓名
    char sex[4];   //性别
    int age;       //年龄
    char note[50];  //备注
}st;

//函数声明
int Displayinfor(st stu[], int n);
int Readfile(st stu[], int n);
int Updateinfor(st stu[], char pass[], int n);
void Menu();

//学生基本信息录入
void Inputinfor(st stu[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("请输入第 %d 个学生的信息(学号 姓名 性别 年龄 备注)：\n", i+1);
        scanf("%lld %s %s %d %s", &stu[i].sno, &stu[i].name,
              &stu[i].sex, &stu[i].age, &stu[i].note);
        printf("\n");
    }
    printf("*成功录入 %d 个学生的信息。\n\n", n);
    pause;
}

//学生基本信息显示
int Displayinfor(st stu[], int n){
    int i;
    FILE *fp;
    char *str[N];
    fp= fopen("D:\\C语言课程设计\\学生信息表.txt","r");
    printf("刚刚录入的学生信息：\n\n");
    printf("学号\t\t姓名\t性别\t年龄\t备注\n\n");
    for(i=0; i<n; i++){
        printf("%lld    ", stu[i].sno);
        printf("%s\t", stu[i].name);
        printf("%s\t", stu[i].sex);
        printf("%d岁\t", stu[i].age);
        printf("%s\t", stu[i].note);
        printf("\n\n");
    }
    printf("该班级的学生信息表：\n\n");
    printf("学号\t姓名\t性别\t年龄\t备注\n\n");
    i=0;
    while(!feof(fp)){
        i++;
        fscanf(fp, "%s", str);
        printf("%s\t", str);
        if(i==5){
            printf("\n\n");
            i=0;
        }
    }
    fclose(fp);
    printf("\n\n");
    pause;
    return 0;
}

//学生基本信息保存
int Saveinfor(st stu[], int n){
    int i, select;
    FILE *fp;
    printf("1、新建写入文件保存。\n\n");
    printf("2、追加写入文件保存。\n\n");
    printf("3、返回上级菜单。\n");
    scanf("%d", &select);
    if(select==1)
        fp= fopen("D:\\C语言课程设计\\学生信息表.txt","w");  //将学生信息写入文件
    if(select==2)
        fp= fopen("D:\\C语言课程设计\\学生信息表.txt","a");  //将学生信息追加写入文件
    if(select==3)
        return 1;
    if(fp==NULL){
        printf("\t\t输入有误或找不到文件。\n\n");
        pause;
        return 1;
    }
    for(i=0; i<n; i++){
        fprintf(fp, "%lld    ", stu[i].sno);
        fprintf(fp, "%s\t", stu[i].name);
        fprintf(fp, "%s\t", stu[i].sex);
        fprintf(fp, "%d岁\t", stu[i].age);
        fprintf(fp, "%s\t", stu[i].note);
        fputs("\n\n", fp);
    }
    fclose(fp);
    printf("*成功将学生信息保存在D:\\C语言课程设计\\学生信息表.txt\n\n");
    pause;
    return 0;
}

//学生基本信息删除
int Deleteinfor(st stu[], int n){
    int i=0, flag=0;
    int select;
    char str1[20], str2[20];
    long long sh1, sh2;
    Readfile(stu, n);
    printf("\n\n");
    printf("1.输入学号删除。\n\n");
    printf("2.输入姓名删除。\n\n");
    printf("3.返回上级菜单。\n");
    scanf("%d", &select);
    if(select==1){
        printf("请输入要删除的学生信息(学号)：\n");
        scanf("%lld", &sh1);
    }
    if(select==2){
        printf("请输入要删除的学生信息(姓名)：\n");
        scanf("%s", &str1);
    }
    if(select==3)
        return 1;
    for(i=0; i<n; i++){
        if(sh1==stu[i].sno || strcmp(str1, stu[i].name)==0){
            flag=1;
            sh2= stu[i].sno;
            strcpy(str2, stu[i].name);
            break;
        }
    }
    if(1== flag){
        stu[i].sno= 0;
        strcpy(stu[i].name, "null");
        strcpy(stu[i].sex, "null");
        stu[i].age= 0;
        strcpy(stu[i].note, "null");
        printf("\n成功删除学号: %lld ,姓名: %s 的学生信息。\n\n", sh2, str2);
    }
    if(0== flag)
        printf("输入有误或没有找到该学生的信息。\n\n");
    pause;
    return 0;
}

//学生基本信息修改(先输入密码)
int Updateinfor(st stu[], char pass[], int n ){
    int i, j, flag=0;
    int select;
    char str1[20], str2[20];
    long long sh1, sh2;
    Readfile(stu, n);
    printf("\n\n");
    printf("1.输入学号修改。\n\n");
    printf("2.输入姓名修改。\n\n");
    printf("3.返回上级菜单。\n");
    scanf("%d", &select);
    if(select==1){
        printf("请输入要修改的学生信息(学号)：\n");
        scanf("%lld", &sh1);
    }
    if(select==2){
        printf("请输入修改的学生信息(姓名)：\n");
        scanf("%s", str1);
    }
    if(select==3)
        return 1;
    for(i=0; i<n; i++){
        if(sh1==stu[i].sno || strcmp(str1, stu[i].name)==0){
            flag=1;
            sh2=stu[i].sno;
            strcpy(str2, stu[i].name);
            j=i;
            break;
        }
    }
    if(1==flag){
        fflush(stdin);
        printf("请输入要修改的信息(学号 姓名 性别 年龄 备注：\n");
        scanf("%lld %s %s %d %s", &stu[j].sno, &stu[j].name,
        &stu[j].sex, &stu[j].age, &stu[j].note);
        stu[i].sno= stu[j].sno;
        strcpy(stu[i].name, stu[j].name);
        strcpy(stu[i].sex, stu[j].sex);
        stu[i].age=stu[j].age;
        strcpy(stu[i].note, stu[j].note);
        printf("\n成功修改学号: %lld ,姓名: %s 的学生信息。\n\n", sh2, str2);
    }
    if(0== flag)
        printf("没有找到该学生的信息。\n\n");
    pause;
    return 0;
}

//学生基本信息查询
int Checkinfor(st stu[], int n){
    int i, select, age, ret, flag=0;
    char name[20], sex[4];
    long long sno;
up_menu_88888888888888888888888:
    cls;
    Readfile(stu, n);
    printf("\n\n(1)按学号查询。\n\n");
    printf("(2)按姓名查询。\n\n");
    printf("(3)按性别查询。\n\n");
    printf("(4)按年龄查询。\n\n");
    printf("(5)返回上级菜单。\n");
    fflush(stdin);
    ret=scanf("%d", &select);
    if(select==1){
        printf("请输入学号：\n");  //(1)按学号查询
        scanf("%lld", &sno);
        for(i=0; i<n; i++){
            if(sno==stu[i].sno){
                flag=1;  //找到，flag=1
                break;
            }
        }
        if(1== flag){
            printf("该学生信息为：\n\n");
            printf("学号\t姓名\t性别\t年龄\t备注\n\n");
            printf("%lld\t%s\t%s\t%d岁\t%s\n\n", stu[i].sno, stu[i].name,
            stu[i].sex, stu[i].age, stu[i].note);
        }
        if(0== flag)
            printf("没有找到该学生的信息。\n\n");
        pause;
    }
    if(select==2){
        printf("请输入姓名：\n");   //(2)按姓名查询
        scanf("%s", &name);
        for(i=0; i<n; i++){
            if(strcmp(name, stu[i].name)==0){
                flag=1;  //找到，flag=1
                break;
            }
        }
        if(1== flag){
            printf("该学生信息为：\n\n");
            printf("学号\t姓名\t性别\t年龄\t备注\n\n");
            printf("%lld\t%s\t%s\t%d岁\t%s\n\n", stu[i].sno, stu[i].name,
            stu[i].sex, stu[i].age, stu[i].note);
        }
        if(0== flag)
            printf("没有找到该学生的信息。\n\n");
        pause;
    }
    if(select==3){
        printf("请输入性别：\n");   //(3)按性别查询
        scanf("%s", &sex);
        printf("学号\t姓名\t性别\t年龄\t备注\n\n");
        for(i=0; i<n; i++){
            if(strcmp(sex, stu[i].sex)==0){
                flag=1;
                printf("%lld\t%s\t%s\t%d岁\t%s\n\n", stu[i].sno, stu[i].name,
                stu[i].sex, stu[i].age, stu[i].note);
            }
        }
        if(0== flag)
            printf("没有找到该学生的信息。\n\n");
        pause;
    }
    if(select==4){
        printf("请输入年龄：\n");   //(4)按年龄查询
        scanf("%d", &age);
        printf("学号\t姓名\t性别\t年龄\t备注\n\n");
        for(i=0; i<n; i++){
            if(age==stu[i].age){
                flag=1;
                printf("%lld\t%s\t%s\t%d岁\t%s\n\n", stu[i].sno, stu[i].name,
                stu[i].sex, stu[i].age, stu[i].note);
            }
        }
        if(0== flag)
            printf("没有找到该学生的信息。\n\n");
        pause;
    }
    if(select==5)
        return 1;
    if(!ret || select!=1 ||  select!=2 || select!=3 || select!=4 || select!=5){
goto up_menu_88888888888888888888888;
    }
    return 0;
}

//读取学生信息表文件
int Readfile(st stu[], int n){
    int i;
    FILE *fp;
    char *str[N];
    fp= fopen("D:\\C语言课程设计\\学生信息表.txt","r");
    if(fp==NULL){
        printf("\t\t\t\t找不到文件。\n\n");
        pause;
        return 1;
    }
    printf("该班级的学生信息表：\n\n");
    i=0;
    while(!feof(fp)){
        i++;
        fscanf(fp, "%s", str);
        printf("%s\t", str);
        if(i==5){
            printf("\n\n");
            i=0;
        }
    }
    fclose(fp);
    printf("\n\n");
    return 0;
}

//验证密码
int Throughpass(void){
    FILE *fp, *fp1;
    int select, choice, ret, i=0, flag=0, count1=5;
    char pass[20], pass1[20];
    do{
up_select:
        cls;
        fflush(stdin);
        printf("\t\t      输入密码\n\n");
        printf("\t\t1、设置or重置密码。\n\n");
        printf("\t\t2、验证已有的密码。\n\n");
        printf("\t\t3、返回上级菜单。\n\n");
        printf("\t\t4、退出程序。\n");
        printf("\t\t注：操作1会清空学生信息表。\n\t\t");
        ret=scanf("%d", &select);
        switch(select){
            case 1:
                fp=fopen("D:\\C语言课程设计\\密码.txt","w");
                fp1= fopen("D:\\C语言课程设计\\学生信息表.txt","w");
                fclose(fp1);
                if(fp==NULL || fp1==NULL){
                    printf("\t\t找不到文件。\n\n");
                    pause;
                    return 1;
                }
                fflush(stdin);
                printf("请输入新密码(以‘/’结束)：\n");
                i=0;
                while(((pass[i]=getchar()) != '/')){
                    i++;
                }
                fflush(stdin);
                printf("请再次输入新密码(以‘/’结束)：\n");
                i=0;
                while(((pass1[i]=getchar()) != '/')){
                    i++;
                }
                i=0;
                while((pass[i]!='\0') || (pass1[i]!='\0')){
                    if(pass[i]!=pass1[i]){
                        flag=0;  //密码不一致，flag=0
                        break;
                    }
                    if(pass[i]==pass1[i])
                        flag=1;  //密码一致，flag=1
                    i++;
                }
                if(!flag){
                    printf("失败。两次输入的密码不匹配。\n");
                    pause;
                    cls;
                    printf("************************\n");
                    printf("按任意键返回上级菜单。\n");
                    fflush(stdin);
                    getchar();
                }
                if(flag){
                    fflush(stdin);
                    i=0;
                    while((pass1[i]!='\0')){
                        fprintf(fp, "%c", pass1[i]);
                        i++;
                    }
                    printf("\n***************");
                    printf("\n*1读取密码文件*");
                    printf("\n***************\n");
                    for(i=0; pass1[i]!='\0'; i++){
                        printf("%c", pass1[i]);
                    }
                    printf("\n\n");
                    fclose(fp);
                    printf("************************\n");
                    printf("密码设置/重置成功。\n\n");
                    printf("按任意键返回上级菜单。\n");
                    fflush(stdin);
                    getchar();
                }
goto up_select;
                pause;
                break;
            case 2:
                fp=fopen("D:\\C语言课程设计\\密码.txt","r");
                i=0;
                fflush(stdin);
                while(fscanf(fp, "%c", &pass1[i])!=EOF){
                    i++;
                }
                printf("\n***************");
                printf("\n*2读取密码文件*");
                printf("\n***************\n");
                for(i=0; pass1[i]!='\0'; i++){
                    printf("%c", pass1[i]);
                }
                printf("\n\n");
                fclose(fp);
                if(fp==NULL){
                    printf("\t\t找不到文件。\n\n");
                    pause;
                    return 1;
                }
                for(int count=1; count<=5; count++){
                    fflush(stdin);
                    printf("第 %d 次输入密码(以‘/’结束)：\n", count);
                    i=0;
                    while((pass[i]=getchar())!='/'){
                        i++;
                    }
                    i=0;
                    while(pass[i]!='\0' || pass1[i]!='\0' ){
                        if(pass[i]!=pass1[i]){
                            flag=0;  //密码不一致，flag=0
                            break;
                        }
                        if(pass[i]==pass1[i])
                            flag=1;  //密码一致，flag=1
                        i++;
                    }
                    count1--;
                    if(flag){
                        printf("密码正确。\n\n");
                        pause;
                        return 1;
                    }
                    if(!flag){
                        printf("密码错误。\n\n");
                        printf("还有 %d 次机会。\n\n", count1);
                        pause;
                        if(0==count1){
                            cls;
                            printf("************************\n");
                            printf("5次输入密码的次数已用完。\n\n");
                            printf("1、返回主菜单。\n\n");
                            printf("2、退出程序。\n");
                            fflush(stdin);
                            scanf("%d", &choice);
                            if(choice==1){
                                printf("\t\t*********未验证密码，已退出程序*********\n");
                                choice=getchar();
                                pause;
                            }
                            if(choice==2){
                                printf("\n*退出程序\n");
                                pause;
                                exit(0);
                            }
                        }
                    }
                }
                break;
            case 3: getchar(); printf("\t*********未验证密码，已退出程序*********\n"); pause; break;
            case 4: printf("\n*退出程序\n"); pause; exit(0);
            default:
                printf("输入有误。\n\n");
                pause;
                break;
        }
    }while(ret!=1);
    return 0;
}

//主菜单
void Menu(void){
    cls;
    fflush(stdin);
    printf("\t\t\t* * * * * * * * * * * * *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* a.学生基本信息录入。  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* b.学生基本信息显示。  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* c.学生基本信息保存。  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* d.学生基本信息删除。  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* e.学生基本信息修改。  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* f.学生基本信息查询。  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* g.退出系统。          *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* * * * * * * * * * * * *\n");
}

//0.0主函数
int main(){
    st stu[N];
    int ret, n, ans;
    char select, pass[20];
    ans=Throughpass();
    if(ans==1){
        do{
            Menu();
            printf("\t\t      *请选择并输入编号进行相应操作*:\n\t\t\t");
            fflush(stdin);
            ret=scanf("%c", &select);
            switch(select){
                case 'a':
                    cls;
                    printf("请输入要录入信息的学生人数:\n", &n);
                    scanf("%d", &n);
                    Inputinfor(stu, n);
                    break;
                case 'b': cls; Displayinfor(stu, n); break;
                case 'c': cls; Saveinfor(stu, n); break;
                case 'd': cls; Deleteinfor(stu, n); break;
                case 'e':
                    cls;
                    ans=Throughpass();
                    if(ans){
                        cls;
                        Updateinfor(stu, pass, n);
                    }
                    break;
                case 'f': cls; Checkinfor(stu, n); break;
                case 'g': cls; printf("*程序结束。\n"); exit(0);
            default:
                printf("\t\t*****************************************\n");
                printf("\t\t* *输入有误，请选择（a-g）进行相应操作* *。\n");
                printf("\t\t*****************************************\n\t\t");
                pause;
                break;
            }
        }while(ret==1);
        pause;
    }
    else
        exit(0);
    return 0;
}
