/************************************************************************/
/*   ��Ŀ���ƣ���ũ��ֲ��Ϣ����ϵͳ                                           */
/*   ����޸�ʱ�䣺2020-07-01                                                 */
/*   ���������� VS                                                            */
/*   ���ߣ�������                                                             */
/************************************************************************/

#include "info.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

//���������޲���
int main(){
    loadKind("dkind.csv");
    loadVeg("dbasic.csv");
    loadPlant("dplant.csv");//������һ�ε����������ļ�
    while(1){
		Menu();
		system("pause");
	}//ѭ��չʾ���������
    return 0;
}

//���ÿ���̨��Ϣ����ǿ�۸У��޲���
void Menu(){
	system("title ��ũ��ֲ��Ϣ����ϵͳ");//�޸Ŀ���̨����
	system(WIN_SIZE);//���ÿ���̨�ߴ�
	system("color 3e");//�ѱ�������Ϊ ǳ��ɫ
    showMenu(0);//��ʾ���˵�
}

//����ѡ��֣�����Ϊ���һ�еĿո����;��һ�еĿ����������ڲ���Ϊ�����ѡ����롣
int Scanf(int left,int top){
	int option;
	setTop(top);
	setLeft(left);
	printf("��ѡ��:");
	scanf("%d",&option);
	return option;
}

//����������ݣ���ڲ�����
void show(){
    system("cls");setTop(10);
    pvegkind now=hkind->next;
    while(now!=NULL){
        printKind(now);
        now=now->next;
    }
}

//���溯������ڲ���option���Ƶ�ǰ��ʾ�Ľ���
void showMenu(int option){
    char k,k1;
    int id,id1,s,s1,year,year1;
    float weight,weight1;
    char *nut=(char *)malloc(50);
    char *name=(char *)malloc(20);
    char *name1=(char *)malloc(20);
    char *filename=(char *)malloc(50);
	int select,flag;//select��ʾ�û��ڵ�ǰ����ѡ��ڼ��flag��ʾ�û���ѡ������ɺ��״̬��
	switch(option){
    case 0://������
        drawMenu(title,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) showMenu(1);
        else if(select==2) showMenu(5);
        else if(select==3) showMenu(8);
        else if(select==4) showMenu(9);
        else if(select==5) show();
        else if(select==6){//�˳�ǰ��������
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 1://����ά������
        drawMenu(title_maintain,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) showMenu(2);
        else if(select==2) showMenu(3);
        else if(select==3) showMenu(4);
        else if(select==4) showMenu(0);
        else if(select==5){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 2://�߲�������Ϣά������
        drawMenu(title_maintain_kind,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//��������
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ӵ��߲�������Ϣ����ʽΪ������,��������,�������߲������Զ��ŷָ���:\n");
            memset(str,0,sizeof(str));
            setLeft(100);scanf("%s",str);getchar();
            flag=addKind(str);
            if(!flag) setLeft(100),printf("error:there is a conflict!\n");//�߲��������Ѵ��ڵ�����������������ӵ��������Ʋ������෴������������ì��
            else setLeft(100),printf("success!\n");//�����ɹ�
        }
        else if(select==2){//�޸�����
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ�޸ĵ��߲�������:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("�������µ��߲���������:");
            memset(str,0,sizeof(str));
            scanf("%s",str);getchar();
            flag=changeKind(k,str);
            if(!flag) setLeft(100),printf("error: cannot find the expected kind!\n");//�Ҳ�����Ӧ������
            else setLeft(100),printf("success\n");
        }
        else if(select==3){//ɾ������
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫɾ�����߲�������:");
            getchar();scanf("%c",&k);getchar();
            flag=delKind(k);
            if(flag) setLeft(100),printf("success!\n");
            else setLeft(100),printf("error:cannot find the kind!\n");
        }
        else if(select==4) showMenu(1);//�����ϼ��˵�
        else if(select==5) showMenu(0);//�������˵�
        else if(select==6){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 3://�߲˻�����Ϣά������
        drawMenu(title_maintain_info,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//����߲�
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ӵ��߲˱��:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("������Ҫ��ӵ��߲�����:");
            memset(name,0,20);
            scanf("%s",name);getchar();
            setLeft(100);printf("������Ҫ��ӵ��߲˷�����:");
            scanf("%c",&k);getchar();
            setLeft(100);printf("������Ҫ��ӵ��߲�Ӫ���ɷ�:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            flag=addVeg(id,name,k,nut,NULL);
            if(!flag) setLeft(100),printf("error:this kind:%c cannot be found,please create it first!",k);//�߲����಻����
            else if(flag==1) setLeft(100),printf("error:the %s has a different id!\n",name);//�߲������Ѵ��ڵ���Ų�ͬ
            else if(flag==2) setLeft(100),printf("error:the %d has already been created!\n",id);//�Ѿ�������ͬ���߲�
            else setLeft(100),printf("success!\n");
        }
        else if(select==2){//�޸��߲˻�����Ϣ
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ�޸ĵ��߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("�������µ��߲�����:");
            memset(name1,0,20);
            scanf("%s",name1);getchar();
            setLeft(100);printf("�������µ��߲�Ӫ���ɷ�:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            flag=changeVeg(name,name1,nut);
            if(!flag) setLeft(100),printf("error:%s cannot be found!\n",name);
            else setLeft(100),printf("success!\n");
        }
        else if(select==3){//ɾ���߲˻�����Ϣ
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫɾ�����߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            flag=delVeg(name);
            if(flag) setLeft(100),printf("success!\n");
            else setLeft(100),printf("error:%s cannot be found!\n",name);
        }
        else if(select==4) showMenu(1);
        else if(select==5) showMenu(0);
        else if(select==6){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 4://�߲���ֲ��Ϣά��
        drawMenu(title_maintain_plant,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//����߲���ֲ��Ϣ
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ӵ���ֲ�߲˱��:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("������Ҫ��ӵ���ֲ�߲����:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("������Ҫ��ӵ���ֲ�߲�����:");
            scanf("%f",&weight);getchar();
            setLeft(100);printf("������Ҫ��ӵ���ֲ�߲����:");
            scanf("%d",&year);getchar();
            flag=addPlant(id,s,weight,year);
            if(!flag) setLeft(100),printf("error:%d cannot be found!\n",id);//δ�ҵ�ָ����ŵ��߲�
            else setLeft(100),printf("success!\n");
        }
        else if(select==2){//�޸��߲���ֲ��Ϣ
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ�޸ĵ���ֲ�߲˱��:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("������Ҫ�޸ĵ���ֲ�߲����:");
            scanf("%d",&year);getchar();
            setLeft(100);printf("�������µ���ֲ�߲����:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("�������µ���ֲ�߲�����:");
            scanf("%f",&weight);getchar();
            flag=changePlant(id,year,s,weight);
            if(!flag) setLeft(100),printf("error:the plant cannot be found!\n");
            else setLeft(100),printf("success!\n");
        }
        else if(select==3){//ɾ���߲���ֲ��Ϣ
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫɾ�����߲˱��:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("������Ҫɾ������ֲ�߲����:");
            scanf("%d",&year);getchar();
            flag=delPlant(id,year);
            if(flag) setLeft(100),printf("success!\n");
            else setLeft(100),printf("error:the plant cannot be found!\n");
        }
        else if(select==4) showMenu(1);
        else if(select==5) showMenu(0);
        else if(select==6) exit(0);
        break;
    case 5://���ݲ�ѯ����
        drawMenu(title_query,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�������:");
            getchar();scanf("%c",&k);getchar();
            flag=qKind(k);
            if(!flag) setLeft(100),printf("error:the kind %c cannot be found!\n",k);//�߲�����δ�ҵ�
        }
        else if(select==2) showMenu(6);
        else if(select==3) showMenu(7);
        else if(select==4) showMenu(0);
        else if(select==5){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 6://�߲˻�����Ϣ��ѯ
        drawMenu(title_query_info,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//�߲���������
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            flag=qInfoA(name);
            if(!flag) setLeft(100),printf("error:the vegetables with name %s cannot be found!\n",name);
        }
        else if(select==2){//�߲˷����뼰Ӫ���ɷ�����
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�������:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("������Ҫ��ѯ���߲�Ӫ���ɷ�:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            flag=qInfoB(k,nut);
            if(!flag) printf("error:the vegetables with kind %c and the nutrition %s cannot be found!\n",k,nut);
        }
        else if(select==3) showMenu(5);
        else if(select==4) showMenu(0);
        else if(select==5){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 7://�߲���ֲ��Ϣ��ѯ
        drawMenu(title_query_plant,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//�߲����Ƽ���ֲ�������
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲����:");
            scanf("%d",&year);getchar();
            flag=qPlantA(name,year);
            if(!flag) setLeft(100),printf("error:the vegetables cannot be found!\n");
        }
        else if(select==2){//�߲���������
            system("cls");setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            flag=qPlantB(name);
            if(!flag) printf("error:the vegetables cannot be found!\n");
        }
        else if(select==3) showMenu(5);
        else if(select==4) showMenu(0);
        else if(select==5){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 8://����ͳ�ƽ���
        drawMenu(title_count,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//ĳ������߲��ջ�ͳ��
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲����:");
            getchar();scanf("%d",&year);getchar();
            countA(year);
        }
        else if(select==2){//�����߲��ջ�ͳ��
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���ʼ���:");
            getchar();scanf("%d",&year);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���ֹ���:");
            scanf("%d",&year1);getchar();
            countB(year,year1);
        }
        else if(select==3) countC();//ĳ���߲�����ͳ��
        else if(select==4){//����ĳӪ���ɷֵ��߲�ͳ��
            setLeft(100);printf("������Ҫ��ѯ���߲�Ӫ���ɷ�:");
            memset(nut,0,50);
            getchar();scanf("%s",nut);getchar();
            countD(nut);
        }
        else if(select==5){//ĳ���ջ����ﵽ��׼���߲�ͳ��
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲����:");
            getchar();scanf("%d",&year);getchar();
            setLeft(100);printf("������Ҫ�������ֲ���:");
            scanf("%d",&s);getchar();
            countE(year,s);
        }
        else if(select==6) showMenu(0);
        else if(select==7){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 9://���뵼������
        drawMenu(title_load_export,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) showMenu(10);
        else if(select==2) showMenu(11);
        else if(select==3) showMenu(0);
        else if(select==4){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 10://���ݵ���
        drawMenu(title_load,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//�߲�������Ϣ����
            setLeft(100);printf("�����뵼���ļ��ľ���·��:");
            memset(filename,0,50);
            getchar();scanf("%s",filename);getchar();
            loadKind(filename);
        }
        else if(select==2){//�߲˻�����Ϣ����
            setLeft(100);printf("�����뵼���ļ��ľ���·��:");
            memset(filename,0,50);
            getchar();scanf("%s",filename);getchar();
            loadVeg(filename);
        }
        else if(select==3){//�߲���ֲ��Ϣ����
            setLeft(100);printf("�����뵼���ļ��ľ���·��:");
            memset(filename,0,50);
            getchar();scanf("%s",filename);getchar();
            loadPlant(filename);
        }
        else if(select==4) showMenu(9);
        else if(select==5) showMenu(0);
        else if(select==6){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 11://���ݵ���
        drawMenu(title_export,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) exportA();//����ݸ����߲���Ϣͳ�Ʊ�
        else if(select==2){//���߲�����ͳ�Ʊ�
            setTop(10);setLeft(100);
            printf("������Ҫ��ѯ���߲�����:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���ֹ���:");
            scanf("%d",&year);getchar();
            exportB(name,year);
        }
        else if(select==3){//���ɲ�ѯ��Ϣ��
            system("cls");setTop(10);
            setLeft(100);printf("������Ҫ��ѯ���߲������ţ���߽磩:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("������Ҫ��ѯ���߲������ţ��ұ߽磩:");
            scanf("%c",&k1);getchar();
            setLeft(100);printf("������Ҫ��ѯ���߲���������:");
            memset(str,0,sizeof(str));
            scanf("%s",str);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲˱�ţ���߽磩:");
            scanf("%d",&id);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲˱�ţ��ұ߽磩:");
            scanf("%d",&id1);getchar();
            setLeft(100);printf("������Ҫ��ѯ���߲�����:");
            memset(name,0,20);
            scanf("%s",name);getchar();
            setLeft(100);printf("������Ҫ��ѯ���߲�Ӫ���ɷ�:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲��������߽磩:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲�������ұ߽磩:");
            scanf("%d",&s1);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���������߽磩:");
            scanf("%f",&weight);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲��������ұ߽磩:");
            scanf("%f",&weight1);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���ݣ���߽磩:");
            scanf("%d",&year);getchar();
            setLeft(100);printf("������Ҫ��ѯ����ֲ�߲���ݣ��ұ߽磩:");
            scanf("%d",&year1);getchar();
            int i,a[8];
            flag=0;
            a[0]=1;
            for(i=1;i<8;i++) a[i]=a[i-1]<<1;
            if(k1>0) flag|=a[0];
            if(str[0]!='0') flag|=a[1];
            if(id1>0) flag|=a[2];
            if(name[0]!='0') flag|=a[3];
            if(nut[0]!='0') flag|=a[4];
            if(s1>0) flag|=a[5];
            if(weight1>eps) flag|=a[6];
            if(year1>0) flag|=a[7];//���û�ѡ�����������ȷ��״̬��
            exportC(k,k1,str,id,id1,name,nut,s,s1,weight,weight1,year,year1,flag);
        }
        else if(select==4) showMenu(9);
        else if(select==5) showMenu(0);
        else if(select==6){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    }
}

int drawMenu(char *str[],int left,int top,int line_height,int line_flag){//��ڲ���Ϊ�����е�ѡ����࣬�ϼ�࣬�иߣ��б�־�������������
	int i=0,k,count=1,max=0,maxStrLength=0;
	while(strcmp(str[i],"")!=0){
		max=strlen(str[i]);
		if(max>maxStrLength) maxStrLength = max;
		i++;
	}
	i=0;
	system("cls");
	setTop(top);//�����ϼ��
	while(strcmp(str[i],"")!=0){
		setLeft(left);//��������
		if(i==0){
			for(k=1;k<=maxStrLength/2+1;k++){
				if(k==1) printf("��");
				printf("����");
				if(k==maxStrLength/2+1) printf("��\n\n\n\n");
			}
			setLeft(left);
		}
		if(line_flag) printf("��     %d.",count);
		printf("%s",str[i++]);
		count++;
		setTop(line_height);//�����и�
	}
	printf("\n\n\n\n");
	setLeft(left);
	for(k=1;k<=maxStrLength/2+1;k++){
		if(k==1) printf("��");
		printf("����");
		if(k==maxStrLength/2+1) printf("��\n");
	}
	return count-1;
}

int setLeft(int left){//��������
    int i;
	for(i=0;i<left;i++) printf(" ");
	return left;
}

int setTop(int top){//�����ϼ��
    int i;
	for(i=0;i<top;i++) printf("\n");
	return top;
}

void loadKind(char *filename){//����������Ϣ���������Ϊ�ļ��ľ���·��
    char cr;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        setLeft(100);
        printf("open failed!\n");//�޷���ָ���ļ�
        return;
    }
    do{
        cr=fgetc(fp);
    }while(cr!='\n');
    hkind=(pvegkind)malloc(sizeof(vegkind));
    hkind->next=NULL;
    while((cr=fgetc(fp))!=EOF){//��ȡ��Ϣ
        fscanf(fp,"%[^\n]",str+1);
        str[0]=cr;
        addKind(str);
        cr=fgetc(fp);
        memset(str,0,sizeof(str));
    }
    fclose(fp);
}

int addKind(char *str){//���������Ϣ
    /*get the value*/
    char k=str[0],*kind=(char *)malloc(8*sizeof(char));
    memset(kind,0,8);
    int i,j,len=strlen(str);
    for(i=2,j=0;i<len;i++,j++){
        if(str[i]==',') break;
        kind[j]=str[i];
    }
    /*check if the kind exist*/
    /*flag=1        not exist*/
    /*flag=0         conflict*/
    /*flag=-1           exist*/
    int flag=1;
    pvegkind now=hkind->next;
    while(now!=NULL){
        if(now->k==k&&strcmp(kind,now->kind)!=0){flag=0;break;}
        if(now->k!=k&&strcmp(kind,now->kind)==0){flag=0;break;}
        if(now->k==k&&strcmp(kind,now->kind)==0){flag=-1;break;}
        now=now->next;
    }
    if(!flag) return 0;
    else if(flag==1){//create a new kind
        now=(pvegkind)malloc(sizeof(vegkind));
        now->k=k;
        memset(now->kind,0,sizeof(now->kind));
        strcpy(now->kind,kind);
        now->next=hkind->next;
        hkind->next=now;
        now->hinfo=(pveginfo)malloc(sizeof(veginfo));
        now->hinfo->next=NULL;
    }
    i++;
    while(i<len){//��ȡÿһ���߲����ƣ�����߲���Ϣ
        if(str[i]==',') break;
        char *name=(char *)malloc(20*sizeof(char));
        memset(name,0,20);
        for(j=0;i<len;i++,j++){
            if(str[i]==',') break;
            name[j]=str[i];
        }
        addVeg(0,name,k,NULL,now);
        i++;
    }
    return 1;
}

int delKind(char k){//ɾ��������Ϣ����ڲ���Ϊ�߲�������
    pvegkind now=hkind->next,pre=hkind;
    while(now!=NULL){
        if(now->k==k) break;
        pre=now;
        now=now->next;
    }
    if(now==NULL) return 0;
    pveginfo x=now->hinfo->next,y;
    while(x!=NULL){//�ݹ��ͷ���������ڴ�ռ�
        y=x;
        x=x->next;
        free(y);
    }
    free(now->hinfo);
    pre->next=now->next;
    free(now);
    return 1;
}

int changeKind(char k,char *kind){//�޸�������Ϣ����ڲ���Ϊ�߲������ţ������������
    pvegkind now=hkind->next;
    while(now!=NULL){
        if(now->k==k) break;
        now=now->next;
    }
    if(now==NULL) return 0;
    memset(now->kind,0,sizeof(now->kind));
    strcpy(now->kind,kind);
    return 1;
}

void printKind(pvegkind now){//���������Ϣ����ڲ���Ϊָ������Ľṹ���Ա
    setLeft(100);printf("%c.%s:\n",now->k,now->kind);
    pveginfo x=now->hinfo->next;
    while(x!=NULL){
        printVeg(x);
        x=x->next;
    }
}

void exportKind(char *filename){//����������Ϣ���������Ϊ�ļ��ľ���·������csv�ĸ�ʽ��������Ϣ
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"������,��������,�߲�����\n");
    pvegkind now=hkind->next;
    pveginfo x;
    while(now!=NULL){
        fprintf(fp,"%c,%s",now->k,now->kind);
        x=now->hinfo->next;
        while(x!=NULL){
            fprintf(fp,",%s",x->name);
            x=x->next;
        }
        fprintf(fp,"\n");
        now=now->next;
    }
    fclose(fp);
}

void loadVeg(char *filename){//�����߲˻�����Ϣ���������Ϊ�ļ��ľ���·��
    char k,cr;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        setLeft(100);
        printf("open failed!\n");
        return;
    }
    do{
        cr=fgetc(fp);
    }while(cr!='\n');
    int id;
    char *name=(char *)malloc(20);
    char *nut=(char *)malloc(50);
    while((cr=fgetc(fp))!=EOF){
        id=0;
        do{
            id+=cr-'0';
            cr=fgetc(fp);
        }while(cr!=',');
        memset(name,0,20);
        fscanf(fp,"%[^,]",name);//��ȡ�߲�����
        cr=fgetc(fp);
        k=fgetc(fp);
        cr=fgetc(fp);
        memset(nut,0,50);
        fscanf(fp,"%[^\n]",nut);//��ȡ�߲�Ӫ���ɷ�
        cr=fgetc(fp);
        //printf("id:%d name:%s nut:%s kind:%c\n",id,name,nut,k);
        addVeg(id,name,k,nut,NULL);
    }
    fclose(fp);
}

int addVeg(int id,char *name,char k,char *nut,pvegkind now){//����߲���Ϣ���������Ϊ�߲˱�ţ��߲����ƣ��߲������ţ��߲�Ӫ���ɷ֣��߲˴���������ṹ���Ա
    pvegkind now1=hkind->next;
    pveginfo x;
    while(now1!=NULL){
        x=now1->hinfo->next;
        while(x!=NULL){
            if(x->id==id&&id) return 2;
            x=x->next;
        }
        now1=now1->next;
    }
    if(now==NULL){
        now=hkind->next;
        while(now!=NULL){
            if(now->k==k) break;
            now=now->next;
        }
        if(now==NULL) return 0;
    }
    pveginfo veg=now->hinfo->next;
    while(veg!=NULL){
        if(!strcmp(name,veg->name)) break;
        veg=veg->next;
    }
    if(veg==NULL){
        veg=(pveginfo)malloc(sizeof(veginfo));
        veg->id=id;
        memset(veg->name,0,sizeof(veg->name));
        strcpy(veg->name,name);
        veg->k=k;
        memset(veg->nut,0,sizeof(veg->nut));
        if(nut!=NULL) strcpy(veg->nut,nut);
        veg->hplant=(pplantinfo)malloc(sizeof(plantinfo));
        veg->hplant->next=NULL;
        veg->next=now->hinfo->next;
        now->hinfo->next=veg;
    }
    else{
        if(veg->id==0) veg->id=id;//����߲˱��Ϊ��ʼ״̬�����޸�Ϊ��ǰ�ı��
        else if(veg->id!=id) return 1;
        if(!strlen(veg->nut)&&nut!=NULL) strcpy(veg->nut,nut);
    }
    return 3;
}

int delVeg(char *name){//ɾ���߲���Ϣ���������Ϊ�߲�����
    pvegkind now=hkind->next;
    while(now!=NULL){
        pveginfo veg=now->hinfo->next,pre=now->hinfo;
        while(veg!=NULL){
            if(!strcmp(name,veg->name)) break;
            pre=veg;
            veg=veg->next;
        }
        now=now->next;
        if(veg==NULL) continue;
        pre->next=veg->next;
        free(veg);
        break;
    }
    if(now==NULL) return 0;
    return 1;
}

int changeVeg(char *name,char *name1,char *nut1){//�޸��߲���Ϣ����ڲ���Ϊ�߲����ƣ��µ��߲����ƣ��µ�Ӫ���ɷ�
    pvegkind now=hkind->next;
    while(now!=NULL){
        pveginfo veg=now->hinfo->next;
        while(veg!=NULL){
            if(!strcmp(name,veg->name)) break;
            veg=veg->next;
        }
        if(veg==NULL){
            now=now->next;
            continue;
        }
        memset(veg->name,0,sizeof(veg->name));
        memset(veg->nut,0,sizeof(veg->nut));
        strcpy(veg->name,name1);
        strcpy(veg->nut,nut1);
        break;
    }
    if(now==NULL) return 0;
    return 1;
}

void printVeg(pveginfo now){//����߲���Ϣ����ڲ���Ϊָ��������߲˻�����Ϣ�ṹ���Ա
    setLeft(100);printf("    id:%d name:%s kind:%c nutrition:%s\n",now->id,now->name,now->k,now->nut);
    pplantinfo x=now->hplant->next;
    while(x!=NULL){
        setLeft(100);printf("        square:%d weight:%f year:%d\n",x->s,x->weight,x->year);
        x=x->next;
    }
}

void exportVeg(char *filename){//�����߲˻�����Ϣ���������Ϊ�ļ��ľ���·��
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"�߲˱��,�߲�����,������,Ӫ���ɷ�\n");
    pvegkind now=hkind->next;
    pveginfo x;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            fprintf(fp,"%d,%s,%c,%s\n",x->id,x->name,x->k,x->nut);
            x=x->next;
        }
        now=now->next;
    }
    fclose(fp);
}

void loadPlant(char *filename){//�����߲���ֲ��Ϣ���������Ϊ�ļ��ľ���·��
    char cr;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        setLeft(100);
        printf("open failed!\n");
        return;
    }
    do{
        cr=fgetc(fp);
    }while(cr!='\n');
    int s,id,year;
    float weight;
    while((cr=fgetc(fp))!=EOF){
        cr=fgetc(fp);
        fscanf(fp,"%d,%d,%f,%d",&id,&s,&weight,&year);//���ζ��������Ϣ
        cr=fgetc(fp);
        //printf("name:%s nut:%s kind:%c\n",name,nut,k);
        addPlant(id,s,weight,year);
    }
    fclose(fp);
}

int addPlant(int id,int s,float weight,int year){//����߲���ֲ��Ϣ���������Ϊ�߲˱�ţ���ֲ������ջ���������ֲ���
    pvegkind now=hkind->next;
    pveginfo veg;
    pplantinfo tmp;
    while(now!=NULL){
        veg=now->hinfo->next;
        while(veg!=NULL){
            if(veg->id==id) break;//Ѱ��ָ���߲˱�ŵ��߲�
            veg=veg->next;
        }
        if(veg==NULL){
            now=now->next;
            continue;
        }
        tmp=veg->hplant->next;
        while(tmp!=NULL){
            if(tmp->year==year){
                tmp->s+=s;
                tmp->weight+=weight;
                break;
            }
            tmp=tmp->next;
        }
        if(tmp==NULL){
            tmp=(pplantinfo)malloc(sizeof(plantinfo));
            tmp->s=s;
            tmp->weight=weight;
            tmp->year=year;
            tmp->next=veg->hplant->next;
            veg->hplant->next=tmp;
        }
        break;
    }
    if(now==NULL) return 0;
    return 1;
}

int delPlant(int id,int year){//ɾ���߲���ֲ��Ϣ����ڲ���Ϊ�߲˱�ź���ֲ���
    pvegkind now=hkind->next;
    pveginfo veg;
    while(now!=NULL){
        veg=now->hinfo->next;
        while(veg!=NULL){
            if(veg->id==id) break;
            veg=veg->next;
        }
        if(veg==NULL){
            now=now->next;
            continue;
        }
        pplantinfo tmp=veg->hplant->next,pre=veg->hplant;
        while(tmp!=NULL){
            if(tmp->year==year) break;
            pre=tmp;
            tmp=tmp->next;
        }
        if(tmp==NULL){
            now=now->next;
            continue;
        }
        pre->next=tmp->next;
        free(tmp);
        break;
    }
    if(now==NULL) return 0;
    return 1;
}

int changePlant(int id,int year,int s,float weight){//�޸��߲���ֲ��Ϣ����ڲ���Ϊ�߲˱�ţ��µ���ֲ��ݣ���ֲ������ջ�����
    pvegkind now=hkind->next;
    pveginfo veg;
    while(now!=NULL){
        veg=now->hinfo->next;
        while(veg!=NULL){
            if(veg->id==id) break;
            veg=veg->next;
        }
        if(veg==NULL){
            now=now->next;
            continue;
        }
        pplantinfo tmp=veg->hplant->next;
        while(tmp!=NULL){
            if(tmp->year==year) break;
            tmp=tmp->next;
        }
        if(tmp==NULL){
            now=now->next;
            continue;
        }
        if(s>=0) tmp->s=s;
        if(weight>=eps) tmp->weight=weight;
        break;
    }
    if(now==NULL) return 0;
    return 1;
}

void exportPlant(char *filename){//�����߲���ֲ��Ϣ����ڲ���Ϊ�ļ��ľ���·��
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"���,�߲˱��,��ֲ���,�ջ�����,��ֲ���\n");
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    int tot=0;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            tmp=x->hplant->next;
            while(tmp!=NULL){
                fprintf(fp,"%d,%d,%d,%f,%d\n",++tot,x->id,tmp->s,tmp->weight,tmp->year);
                tmp=tmp->next;
            }
            x=x->next;
        }
        now=now->next;
    }
    fclose(fp);
}

int qKind(char k){//�߲������ѯ����ڲ���Ϊ�����ţ���������߲����е������Ϣ
    pvegkind now=hkind->next;
    while(now!=NULL){
        if(now->k==k) break;
        now=now->next;
    }
    if(now==NULL) return 0;
    else system("cls"),printKind(now);
    return 1;
}

int qInfoA(char *name){//�߲˻�����Ϣ��ѯ����ڲ���Ϊ�߲����ƣ����������ҵ����Ӧ���߲ˣ���������Ϣ
    int flag=0;
    pvegkind now=hkind->next;
    pveginfo x;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            if(strstr(x->name,name)!=NULL){
                if(!flag) system("cls"),setTop(10);
                printVeg(x),flag=1;
            }
            x=x->next;
        }
        now=now->next;
    }
    if(!flag) return 0;
    return 1;
}

int qInfoB(char k,char *nut){//�߲˻�����Ϣ��ѯ����ڲ���Ϊ�߲������ź��߲�Ӫ���ɷ�
    int flag=0;
    pvegkind now=hkind->next;
    pveginfo x;
    while(now!=NULL){
        if(now->k==k){
            x=now->hinfo->next;
            while(x!=NULL){
                if(strstr(x->nut,nut)!=NULL){
                    if(!flag) system("cls"),setTop(10);
                    printVeg(x),flag=1;
                }
                x=x->next;
            }
            break;
        }
        now=now->next;
    }
    if(!flag) return 0;
    return 1;
}

int qPlantA(char *name,int year){//�߲���ֲ��Ϣ��ѯ����ڲ���Ϊ�߲����ƺ���ֲ���
    int flag=0;
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            if(strstr(x->name,name)!=NULL){
                tmp=x->hplant->next;
                while(tmp!=NULL){
                    if(tmp->year==year){
                        if(!flag) system("cls"),setTop(10);
                        flag=1;
                        printVeg(x);
                        break;
                    }
                    tmp=tmp->next;
                }
            }
            x=x->next;
        }
        now=now->next;
    }
    if(!flag) return 0;
    return 1;
}

int qPlantB(char *name){//�߲���ֲ��Ϣ��ѯ����ڲ���Ϊ�߲�����
    int flag=0;
    pvegkind now=hkind->next;
    pveginfo x;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            if(strstr(x->name,name)!=NULL){
                if(!flag) system("cls"),setTop(10);
                flag=1;
                printVeg(x);
            }
            x=x->next;
        }
        now=now->next;
    }
    if(!flag) return 0;
    return 1;
}

void exportA(){//���ݵ���
    FILE *fp;
    fp=fopen("����ݸ����߲���Ϣͳ�Ʊ�.csv","w");
    fprintf(fp,"���,��������,��ֲ������֣�,�ջ���������kg��\n");
    int i;
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    while(now!=NULL){
        x=now->hinfo->next;
        memset(s,0,sizeof(s));
        memset(weight,0.0,sizeof(weight));
        while(x!=NULL){
            tmp=x->hplant->next;
            while(tmp!=NULL){
                s[tmp->year]+=tmp->s;
                weight[tmp->year]+=tmp->weight;
                tmp=tmp->next;
            }
            x=x->next;
        }
        for(i=0;i<MAX;i++){
            if(s[i]==0) continue;
            fprintf(fp,"%d,%s,%d,%f\n",i,now->kind,s[i],weight[i]);
        }
        now=now->next;
    }
    fclose(fp);
}

void exportB(char *name,int Y){//���ݵ�������ڲ���Ϊ�߲����ƺͽ�ֹ���
    FILE *fp;
    fp=fopen("���߲�����ͳ����Ϣ��.csv","w");
    fprintf(fp,"���,�߲�����,��������,��ֲ������֣�,�ջ�������kg��\n");
    int i;
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            if(!strcmp(x->name,name)){
                tmp=x->hplant->next;
                memset(s,0,sizeof(s));
                memset(weight,0.0,sizeof(weight));
                while(tmp!=NULL){
                    s[tmp->year]+=tmp->s;
                    weight[tmp->year]+=tmp->weight;
                    tmp=tmp->next;
                }
                for(i=Y-2;i<=Y;i++) fprintf(fp,"%d,%s,%s,%d,%f\n",i,name,now->kind,s[i],weight[i]);
                fclose(fp);
                return;
            }
            x=x->next;
        }
        now=now->next;
    }
    printf("error:cannot find the vegetables!\n");
    fclose(fp);
}

//���ɲ�ѯ��������ڲ���Ϊ���п��������Ĳ�����flag��¼��Щ��������������
void exportC(char k1,char k2,char *kind,int id1,int id2,char *name,char *nut,int s1,int s2,float weight1,float weight2,int year1,int year2,int flag){
    FILE *fp;
    fp=fopen("����ͳ����Ϣ��.csv","w");
    fprintf(fp,"������,��������,�߲˱��,�߲�����,Ӫ���ɷ�,��ֲ������֣�,�ջ�������kg��,��ֲ���\n");
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    int i,a[8];
    a[0]=1;
    for(i=1;i<8;i++) a[i]=a[i-1]<<1;
    while(now!=NULL){
        if((flag&a[0])&&(now->k<k1||now->k>k2)){
            now=now->next;
            continue;
        }
        if((flag&a[1])&&(strstr(now->kind,kind)==NULL)){
            now=now->next;
            continue;
        }
        x=now->hinfo->next;
        while(x!=NULL){
            if((flag&a[2])&&(x->id<id1||x->id>id2)){
                x=x->next;
                continue;
            }
            if((flag&a[3])&&(strstr(x->name,name)==NULL)){
                x=x->next;
                continue;
            }
            if((flag&a[4])&&(strstr(x->nut,nut)==NULL)){
                x=x->next;
                continue;
            }
            tmp=x->hplant->next;
            while(tmp!=NULL){
                if((flag&a[5])&&(tmp->s<s1||tmp->s>s2)){
                    tmp=tmp->next;
                    continue;
                }
                if((flag&a[6])&&(tmp->weight<weight1||tmp->weight>weight2)){
                    tmp=tmp->next;
                    continue;
                }
                if((flag&a[7])&&(tmp->year<year1||tmp->year>year2)){
                    tmp=tmp->next;
                    continue;
                }
                fprintf(fp,"%c,%s,%d,%s,%s,%d,%f,%d\n",now->k,now->kind,x->id,x->name,x->nut,tmp->s,tmp->weight,tmp->year);
                tmp=tmp->next;
            }
            x=x->next;
        }
        now=now->next;
    }
    fclose(fp);
}

int countA(int Y){//ĳ������߲��ջ�ͳ�ƣ����������߲����࣬ͳ����Ϣ�������ô�����״ͼ
    int n=0;
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    memset(str,0,sizeof(str));
    memset(s,0,sizeof(s));
    memset(weight,0.0,sizeof(weight));
    while(now!=NULL){
        str[n]=now->k;
        x=now->hinfo->next;
        while(x!=NULL){
            tmp=x->hplant;
            while(tmp!=NULL){
                if(tmp->year==Y){
                    s[n]+=tmp->s;
                    weight[n]+=tmp->weight;
                    break;
                }
                tmp=tmp->next;
            }
            x=x->next;
        }
        now=now->next;
        ++n;
    }
    int i,j,k;
    for(i=0;i<n;i++){
        k=i;
        for(j=i+1;j<n;j++) if(weight[j]>weight[k]) k=j;
        char tmp1=str[i];str[i]=str[k];str[k]=tmp1;
        int tmp2=s[i];s[i]=s[k];s[k]=tmp2;
        float tmp3=weight[i];weight[i]=weight[k];weight[k]=tmp3;
    }
    system("cls");setTop(10);
    for(i=0;i<n;i++){
        if(s[i]==0) break;
        now=hkind->next;
        while(now!=NULL){
            if(now->k==str[i]){
                setLeft(100);
                printf("%s %d %f\n",now->kind,s[i],weight[i]);
                int num=weight[i];
                for(j=0;j<5;j++){
                    setLeft(100);
                    for(k=0;k<num;k++) printf("*");
                    printf("\n");
                }
                break;
            }
            now=now->next;
        }
    }
    return 0;
}

int countB(int Ys,int Yt){//�����߲��ջ�ͳ�ƣ���ڲ���Ϊ��ʼ��ݺͽ�ֹ���
    int n=0;
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    memset(id,0,sizeof(id));
    memset(str,0,sizeof(str));
    memset(s,0,sizeof(s));
    memset(weight,0.0,sizeof(weight));
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            str[n]=now->k;
            id[n]=x->id;
            tmp=x->hplant;
            while(tmp!=NULL){
                if(tmp->year>=Ys&&tmp->year<=Yt){
                    s[n]+=tmp->s;
                    weight[n]+=tmp->weight;
                    break;
                }
                tmp=tmp->next;
            }
            x=x->next;
            ++n;
        }
        now=now->next;
    }
    int i,j,k;
    for(i=0;i<n;i++){
        k=i;
        for(j=i+1;j<n;j++) if(weight[j]>weight[k]) k=j;
        char tmp1=str[i];str[i]=str[k];str[k]=tmp1;
        int tmp2=s[i];s[i]=s[k];s[k]=tmp2;
        tmp2=id[i];id[i]=id[k];id[k]=tmp2;
        float tmp3=weight[i];weight[i]=weight[k];weight[k]=tmp3;
    }
    system("cls");setTop(10);
    for(i=0;i<n;i++){
        if(s[i]==0) break;
        now=hkind->next;
        while(now!=NULL){
            if(now->k==str[i]){
                x=now->hinfo->next;
                while(x!=NULL){
                    if(x->id==id[i]){
                        setLeft(100);
                        printf("%s %s %d %f\n",x->name,now->kind,s[i],weight[i]);
                        break;
                    }
                    x=x->next;
                }
                break;
            }
            now=now->next;
        }
    }
    return 0;
}

int countC(){//ĳ���߲�����ͳ�ƣ�ͳ��ÿ���߲����Ѽ�¼���߲�����
    pvegkind now=hkind->next;
    pveginfo x;
    int cnt;
    system("cls");setTop(10);
    while(now!=NULL){
        cnt=0;
        x=now->hinfo->next;
        while(x!=NULL){
            if(x->id) cnt++;
            x=x->next;
        }
        setLeft(100);
        printf("%s %d\n",now->kind,cnt);
        now=now->next;
    }
    return 0;
}

int countD(char *nut){//����ĳӪ���ɷֵ��߲�ͳ�ƣ���ڲ���ΪӪ���ɷֱ�
    pvegkind now=hkind->next;
    pveginfo x;
    system("cls");setTop(10);setLeft(100);
    while(now!=NULL){
        x=now->hinfo->next;
        while(x!=NULL){
            if(strstr(x->nut,nut)!=NULL) printf("%s ",x->name);
            x=x->next;
        }
        now=now->next;
    }
    printf("\n");
    return 0;
}

int countE(int Y,int S){//ĳ���ջ����ﵽ��׼���߲�ͳ�ƣ���ڲ���Ϊ��ֲ��ݺ���ֲ�����׼
    pvegkind now=hkind->next;
    pveginfo x;
    pplantinfo tmp;
    system("cls");setTop(10);setLeft(100);
    while(now!=NULL){
        int num=0;
        x=now->hinfo->next;
        while(x!=NULL){
            tmp=x->hplant->next;
            while(tmp!=NULL){
                if(tmp->year==Y) num+=tmp->s;
                tmp=tmp->next;
            }
            x=x->next;
        }
        if(num>=S) printf("%s ",now->kind);
        now=now->next;
    }
    printf("\n");
    return 0;
}
