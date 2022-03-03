/*1����ϵͳ����һ������N�����ݵĽṹ�������������ÿ�����ݵĽṹӦ��������ѧ�š��������Ա����䡢��ע��
3��ִ��һ������Ĺ���֮�󣬳���������ʾ�˵���
4����ѧ��������Ϣ���浽�ļ��С�
5������ϵͳ֮ǰҪ���������롣*/

//ͷ�ļ�����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pause system("pause")
#define cls system("cls")
#define N 1024

//����ṹ������
typedef struct{
    long long sno; //ѧ��
    char name[20]; //����
    char sex[4];   //�Ա�
    int age;       //����
    char note[50];  //��ע
}st;

//��������
int Displayinfor(st stu[], int n);
int Readfile(st stu[], int n);
int Updateinfor(st stu[], char pass[], int n);
void Menu();

//ѧ��������Ϣ¼��
void Inputinfor(st stu[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("������� %d ��ѧ������Ϣ(ѧ�� ���� �Ա� ���� ��ע)��\n", i+1);
        scanf("%lld %s %s %d %s", &stu[i].sno, &stu[i].name,
              &stu[i].sex, &stu[i].age, &stu[i].note);
        printf("\n");
    }
    printf("*�ɹ�¼�� %d ��ѧ������Ϣ��\n\n", n);
    pause;
}

//ѧ��������Ϣ��ʾ
int Displayinfor(st stu[], int n){
    int i;
    FILE *fp;
    char *str[N];
    fp= fopen("D:\\C���Կγ����\\ѧ����Ϣ��.txt","r");
    printf("�ո�¼���ѧ����Ϣ��\n\n");
    printf("ѧ��\t\t����\t�Ա�\t����\t��ע\n\n");
    for(i=0; i<n; i++){
        printf("%lld    ", stu[i].sno);
        printf("%s\t", stu[i].name);
        printf("%s\t", stu[i].sex);
        printf("%d��\t", stu[i].age);
        printf("%s\t", stu[i].note);
        printf("\n\n");
    }
    printf("�ð༶��ѧ����Ϣ��\n\n");
    printf("ѧ��\t����\t�Ա�\t����\t��ע\n\n");
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

//ѧ��������Ϣ����
int Saveinfor(st stu[], int n){
    int i, select;
    FILE *fp;
    printf("1���½�д���ļ����档\n\n");
    printf("2��׷��д���ļ����档\n\n");
    printf("3�������ϼ��˵���\n");
    scanf("%d", &select);
    if(select==1)
        fp= fopen("D:\\C���Կγ����\\ѧ����Ϣ��.txt","w");  //��ѧ����Ϣд���ļ�
    if(select==2)
        fp= fopen("D:\\C���Կγ����\\ѧ����Ϣ��.txt","a");  //��ѧ����Ϣ׷��д���ļ�
    if(select==3)
        return 1;
    if(fp==NULL){
        printf("\t\t����������Ҳ����ļ���\n\n");
        pause;
        return 1;
    }
    for(i=0; i<n; i++){
        fprintf(fp, "%lld    ", stu[i].sno);
        fprintf(fp, "%s\t", stu[i].name);
        fprintf(fp, "%s\t", stu[i].sex);
        fprintf(fp, "%d��\t", stu[i].age);
        fprintf(fp, "%s\t", stu[i].note);
        fputs("\n\n", fp);
    }
    fclose(fp);
    printf("*�ɹ���ѧ����Ϣ������D:\\C���Կγ����\\ѧ����Ϣ��.txt\n\n");
    pause;
    return 0;
}

//ѧ��������Ϣɾ��
int Deleteinfor(st stu[], int n){
    int i=0, flag=0;
    int select;
    char str1[20], str2[20];
    long long sh1, sh2;
    Readfile(stu, n);
    printf("\n\n");
    printf("1.����ѧ��ɾ����\n\n");
    printf("2.��������ɾ����\n\n");
    printf("3.�����ϼ��˵���\n");
    scanf("%d", &select);
    if(select==1){
        printf("������Ҫɾ����ѧ����Ϣ(ѧ��)��\n");
        scanf("%lld", &sh1);
    }
    if(select==2){
        printf("������Ҫɾ����ѧ����Ϣ(����)��\n");
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
        printf("\n�ɹ�ɾ��ѧ��: %lld ,����: %s ��ѧ����Ϣ��\n\n", sh2, str2);
    }
    if(0== flag)
        printf("���������û���ҵ���ѧ������Ϣ��\n\n");
    pause;
    return 0;
}

//ѧ��������Ϣ�޸�(����������)
int Updateinfor(st stu[], char pass[], int n ){
    int i, j, flag=0;
    int select;
    char str1[20], str2[20];
    long long sh1, sh2;
    Readfile(stu, n);
    printf("\n\n");
    printf("1.����ѧ���޸ġ�\n\n");
    printf("2.���������޸ġ�\n\n");
    printf("3.�����ϼ��˵���\n");
    scanf("%d", &select);
    if(select==1){
        printf("������Ҫ�޸ĵ�ѧ����Ϣ(ѧ��)��\n");
        scanf("%lld", &sh1);
    }
    if(select==2){
        printf("�������޸ĵ�ѧ����Ϣ(����)��\n");
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
        printf("������Ҫ�޸ĵ���Ϣ(ѧ�� ���� �Ա� ���� ��ע��\n");
        scanf("%lld %s %s %d %s", &stu[j].sno, &stu[j].name,
        &stu[j].sex, &stu[j].age, &stu[j].note);
        stu[i].sno= stu[j].sno;
        strcpy(stu[i].name, stu[j].name);
        strcpy(stu[i].sex, stu[j].sex);
        stu[i].age=stu[j].age;
        strcpy(stu[i].note, stu[j].note);
        printf("\n�ɹ��޸�ѧ��: %lld ,����: %s ��ѧ����Ϣ��\n\n", sh2, str2);
    }
    if(0== flag)
        printf("û���ҵ���ѧ������Ϣ��\n\n");
    pause;
    return 0;
}

//ѧ��������Ϣ��ѯ
int Checkinfor(st stu[], int n){
    int i, select, age, ret, flag=0;
    char name[20], sex[4];
    long long sno;
up_menu_88888888888888888888888:
    cls;
    Readfile(stu, n);
    printf("\n\n(1)��ѧ�Ų�ѯ��\n\n");
    printf("(2)��������ѯ��\n\n");
    printf("(3)���Ա��ѯ��\n\n");
    printf("(4)�������ѯ��\n\n");
    printf("(5)�����ϼ��˵���\n");
    fflush(stdin);
    ret=scanf("%d", &select);
    if(select==1){
        printf("������ѧ�ţ�\n");  //(1)��ѧ�Ų�ѯ
        scanf("%lld", &sno);
        for(i=0; i<n; i++){
            if(sno==stu[i].sno){
                flag=1;  //�ҵ���flag=1
                break;
            }
        }
        if(1== flag){
            printf("��ѧ����ϢΪ��\n\n");
            printf("ѧ��\t����\t�Ա�\t����\t��ע\n\n");
            printf("%lld\t%s\t%s\t%d��\t%s\n\n", stu[i].sno, stu[i].name,
            stu[i].sex, stu[i].age, stu[i].note);
        }
        if(0== flag)
            printf("û���ҵ���ѧ������Ϣ��\n\n");
        pause;
    }
    if(select==2){
        printf("������������\n");   //(2)��������ѯ
        scanf("%s", &name);
        for(i=0; i<n; i++){
            if(strcmp(name, stu[i].name)==0){
                flag=1;  //�ҵ���flag=1
                break;
            }
        }
        if(1== flag){
            printf("��ѧ����ϢΪ��\n\n");
            printf("ѧ��\t����\t�Ա�\t����\t��ע\n\n");
            printf("%lld\t%s\t%s\t%d��\t%s\n\n", stu[i].sno, stu[i].name,
            stu[i].sex, stu[i].age, stu[i].note);
        }
        if(0== flag)
            printf("û���ҵ���ѧ������Ϣ��\n\n");
        pause;
    }
    if(select==3){
        printf("�������Ա�\n");   //(3)���Ա��ѯ
        scanf("%s", &sex);
        printf("ѧ��\t����\t�Ա�\t����\t��ע\n\n");
        for(i=0; i<n; i++){
            if(strcmp(sex, stu[i].sex)==0){
                flag=1;
                printf("%lld\t%s\t%s\t%d��\t%s\n\n", stu[i].sno, stu[i].name,
                stu[i].sex, stu[i].age, stu[i].note);
            }
        }
        if(0== flag)
            printf("û���ҵ���ѧ������Ϣ��\n\n");
        pause;
    }
    if(select==4){
        printf("���������䣺\n");   //(4)�������ѯ
        scanf("%d", &age);
        printf("ѧ��\t����\t�Ա�\t����\t��ע\n\n");
        for(i=0; i<n; i++){
            if(age==stu[i].age){
                flag=1;
                printf("%lld\t%s\t%s\t%d��\t%s\n\n", stu[i].sno, stu[i].name,
                stu[i].sex, stu[i].age, stu[i].note);
            }
        }
        if(0== flag)
            printf("û���ҵ���ѧ������Ϣ��\n\n");
        pause;
    }
    if(select==5)
        return 1;
    if(!ret || select!=1 ||  select!=2 || select!=3 || select!=4 || select!=5){
goto up_menu_88888888888888888888888;
    }
    return 0;
}

//��ȡѧ����Ϣ���ļ�
int Readfile(st stu[], int n){
    int i;
    FILE *fp;
    char *str[N];
    fp= fopen("D:\\C���Կγ����\\ѧ����Ϣ��.txt","r");
    if(fp==NULL){
        printf("\t\t\t\t�Ҳ����ļ���\n\n");
        pause;
        return 1;
    }
    printf("�ð༶��ѧ����Ϣ��\n\n");
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

//��֤����
int Throughpass(void){
    FILE *fp, *fp1;
    int select, choice, ret, i=0, flag=0, count1=5;
    char pass[20], pass1[20];
    do{
up_select:
        cls;
        fflush(stdin);
        printf("\t\t      ��������\n\n");
        printf("\t\t1������or�������롣\n\n");
        printf("\t\t2����֤���е����롣\n\n");
        printf("\t\t3�������ϼ��˵���\n\n");
        printf("\t\t4���˳�����\n");
        printf("\t\tע������1�����ѧ����Ϣ��\n\t\t");
        ret=scanf("%d", &select);
        switch(select){
            case 1:
                fp=fopen("D:\\C���Կγ����\\����.txt","w");
                fp1= fopen("D:\\C���Կγ����\\ѧ����Ϣ��.txt","w");
                fclose(fp1);
                if(fp==NULL || fp1==NULL){
                    printf("\t\t�Ҳ����ļ���\n\n");
                    pause;
                    return 1;
                }
                fflush(stdin);
                printf("������������(�ԡ�/������)��\n");
                i=0;
                while(((pass[i]=getchar()) != '/')){
                    i++;
                }
                fflush(stdin);
                printf("���ٴ�����������(�ԡ�/������)��\n");
                i=0;
                while(((pass1[i]=getchar()) != '/')){
                    i++;
                }
                i=0;
                while((pass[i]!='\0') || (pass1[i]!='\0')){
                    if(pass[i]!=pass1[i]){
                        flag=0;  //���벻һ�£�flag=0
                        break;
                    }
                    if(pass[i]==pass1[i])
                        flag=1;  //����һ�£�flag=1
                    i++;
                }
                if(!flag){
                    printf("ʧ�ܡ�������������벻ƥ�䡣\n");
                    pause;
                    cls;
                    printf("************************\n");
                    printf("������������ϼ��˵���\n");
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
                    printf("\n*1��ȡ�����ļ�*");
                    printf("\n***************\n");
                    for(i=0; pass1[i]!='\0'; i++){
                        printf("%c", pass1[i]);
                    }
                    printf("\n\n");
                    fclose(fp);
                    printf("************************\n");
                    printf("��������/���óɹ���\n\n");
                    printf("������������ϼ��˵���\n");
                    fflush(stdin);
                    getchar();
                }
goto up_select;
                pause;
                break;
            case 2:
                fp=fopen("D:\\C���Կγ����\\����.txt","r");
                i=0;
                fflush(stdin);
                while(fscanf(fp, "%c", &pass1[i])!=EOF){
                    i++;
                }
                printf("\n***************");
                printf("\n*2��ȡ�����ļ�*");
                printf("\n***************\n");
                for(i=0; pass1[i]!='\0'; i++){
                    printf("%c", pass1[i]);
                }
                printf("\n\n");
                fclose(fp);
                if(fp==NULL){
                    printf("\t\t�Ҳ����ļ���\n\n");
                    pause;
                    return 1;
                }
                for(int count=1; count<=5; count++){
                    fflush(stdin);
                    printf("�� %d ����������(�ԡ�/������)��\n", count);
                    i=0;
                    while((pass[i]=getchar())!='/'){
                        i++;
                    }
                    i=0;
                    while(pass[i]!='\0' || pass1[i]!='\0' ){
                        if(pass[i]!=pass1[i]){
                            flag=0;  //���벻һ�£�flag=0
                            break;
                        }
                        if(pass[i]==pass1[i])
                            flag=1;  //����һ�£�flag=1
                        i++;
                    }
                    count1--;
                    if(flag){
                        printf("������ȷ��\n\n");
                        pause;
                        return 1;
                    }
                    if(!flag){
                        printf("�������\n\n");
                        printf("���� %d �λ��ᡣ\n\n", count1);
                        pause;
                        if(0==count1){
                            cls;
                            printf("************************\n");
                            printf("5����������Ĵ��������ꡣ\n\n");
                            printf("1���������˵���\n\n");
                            printf("2���˳�����\n");
                            fflush(stdin);
                            scanf("%d", &choice);
                            if(choice==1){
                                printf("\t\t*********δ��֤���룬���˳�����*********\n");
                                choice=getchar();
                                pause;
                            }
                            if(choice==2){
                                printf("\n*�˳�����\n");
                                pause;
                                exit(0);
                            }
                        }
                    }
                }
                break;
            case 3: getchar(); printf("\t*********δ��֤���룬���˳�����*********\n"); pause; break;
            case 4: printf("\n*�˳�����\n"); pause; exit(0);
            default:
                printf("��������\n\n");
                pause;
                break;
        }
    }while(ret!=1);
    return 0;
}

//���˵�
void Menu(void){
    cls;
    fflush(stdin);
    printf("\t\t\t* * * * * * * * * * * * *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* a.ѧ��������Ϣ¼�롣  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* b.ѧ��������Ϣ��ʾ��  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* c.ѧ��������Ϣ���档  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* d.ѧ��������Ϣɾ����  *\n\t\t\t*\t\t\t*\n ");
    printf("\t\t\t* e.ѧ��������Ϣ�޸ġ�  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* f.ѧ��������Ϣ��ѯ��  *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* g.�˳�ϵͳ��          *\n\t\t\t*\t\t\t*\n");
    printf("\t\t\t* * * * * * * * * * * * *\n");
}

//0.0������
int main(){
    st stu[N];
    int ret, n, ans;
    char select, pass[20];
    ans=Throughpass();
    if(ans==1){
        do{
            Menu();
            printf("\t\t      *��ѡ�������Ž�����Ӧ����*:\n\t\t\t");
            fflush(stdin);
            ret=scanf("%c", &select);
            switch(select){
                case 'a':
                    cls;
                    printf("������Ҫ¼����Ϣ��ѧ������:\n", &n);
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
                case 'g': cls; printf("*���������\n"); exit(0);
            default:
                printf("\t\t*****************************************\n");
                printf("\t\t* *����������ѡ��a-g��������Ӧ����* *��\n");
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
