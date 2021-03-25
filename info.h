#ifndef _INFO_H
#define _INFO_H

#define eps 1e-8//����������߾���
#define MAX 3000//�������󳤶�
#define WIN_SIZE "mode con cols=250 lines=500"//����̨�Ļ�������

typedef struct VegKind{//�߲�������Ϣ
    char k;
    char kind[8];
    struct VegKind *next;
    struct VegInfo *hinfo;
}vegkind,*pvegkind;

typedef struct VegInfo{//�߲˻�����Ϣ
    int id;
    char name[20];
    char k;
    char nut[50];
    struct VegInfo *next;
    struct PlantInfo *hplant;
}veginfo,*pveginfo;

typedef struct PlantInfo{//�߲���ֲ��Ϣ
    int s;
    float weight;
    int year;
    struct PlantInfo *next;
}plantinfo,*pplantinfo;

void Menu();
void show();
void showMenu(int option);
int drawMenu(char *str[],int left,int top,int line_height,int line_flag);
int Scanf(int left,int top);
int setLeft(int left);
int setTop(int top);


void loadKind(char *filename);
int addKind(char *str);
int delKind(char cr);
int changeKind(char k,char *kind);
void printKind(pvegkind now);
void exportKind(char *filename);

void loadVeg(char *filename);
int addVeg(int id,char *name,char k,char *nut,pvegkind now);
int delVeg(char *name);
int changeVeg(char *name,char *name1,char *nut1);
void printVeg(pveginfo now);
void exportVeg(char *filename);

void loadPlant(char *filename);
int addPlant(int id,int s,float weight,int year);
int delPlant(int id,int year);
int changePlant(int id,int year,int s,float weight);
void exportPlant(char *filename);

int qKind(char k);
int qInfoA(char *name);
int qInfoB(char k,char *nut);
int qPlantA(char *name,int year);
int qPlantB(char *name);

void exportA();
void exportB(char *name,int Y);
void exportC(char k1,char k2,char *kind,int id1,int id2,char *name,char *nut,int s1,int s2,float weight1,float weight2,int year1,int year2,int flag);

int countA(int Y);
int countB(int Ys,int Yt);
int countC();
int countD(char *nut);
int countE(int Y,int S);

char str[1000];
int s[3000],id[100];
float weight[3000];
pvegkind hkind;

char *title[]={"����ά��","���ݲ�ѯ","����ͳ��","���ݵ��뵼��","������ʾ","�˳�ϵͳ",""};//0
char *title_maintain[]={"�߲�������Ϣά��","�߲˻�����Ϣά��","�߲���ֲ��Ϣά��","�������˵�","�˳�ϵͳ",""};//1
char *title_maintain_kind[]={"�߲�������Ϣ¼��","�߲�������Ϣ�޸�","�߲�������Ϣɾ��","������һ���˵�","�������˵�","�˳�ϵͳ",""};//2
char *title_maintain_info[]={"�߲˻�����Ϣ¼��","�߲˻�����Ϣ�޸�","�߲˻�����Ϣɾ��","������һ���˵�","�������˵�","�˳�ϵͳ",""};//3
char *title_maintain_plant[]={"�߲���ֲ��Ϣ¼��","�߲���ֲ��Ϣ�޸�","�߲���ֲ��Ϣɾ��","������һ���˵�","�������˵�","�˳�ϵͳ",""};//4
char *title_query[]={"�߲�������Ϣ��ѯ","�߲˻�����Ϣ��ѯ","�߲���ֲ��Ϣ��ѯ","�������˵�","�˳�ϵͳ",""};//5
char *title_query_info[]={"�߲���������","�߲˷����뼰Ӫ���ɷ�����","������һ���˵�","�������˵�","�˳�ϵͳ",""};//6
char *title_query_plant[]={"�߲����Ƽ���ֲ�������","�߲���������","������һ���˵�","�������˵�","�˳�ϵͳ",""};//7
char *title_count[]={"ĳ������߲��ջ�ͳ��","�����߲��ջ�ͳ��","ĳ���߲�����ͳ��","����ĳӪ���ɷֵ��߲�ͳ��","ĳ���ջ����ﵽ��׼���߲�ͳ��","�������˵�","�˳�ϵͳ",""};//8
char *title_load_export[]={"���ݵ���","���ݵ���","�������˵�","�˳�ϵͳ",""};//9
char *title_load[]={"�߲�������Ϣ","�߲˻�����Ϣ","�߲���ֲ��Ϣ","������һ���˵�","�������˵�","�˳�ϵͳ",""};//10
char *title_export[]={"����ݸ����߲���Ϣͳ�Ʊ�","���߲�����ͳ����Ϣ","���ɲ�ѯ��Ϣ","������һ���˵�","�������˵�","�˳�ϵͳ",""};//11

#endif
