#ifndef _INFO_H
#define _INFO_H

#define eps 1e-8//浮点数的最高精度
#define MAX 3000//数组的最大长度
#define WIN_SIZE "mode con cols=250 lines=500"//控制台的基本参数

typedef struct VegKind{//蔬菜种类信息
    char k;
    char kind[8];
    struct VegKind *next;
    struct VegInfo *hinfo;
}vegkind,*pvegkind;

typedef struct VegInfo{//蔬菜基本信息
    int id;
    char name[20];
    char k;
    char nut[50];
    struct VegInfo *next;
    struct PlantInfo *hplant;
}veginfo,*pveginfo;

typedef struct PlantInfo{//蔬菜种植信息
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

char *title[]={"数据维护","数据查询","数据统计","数据导入导出","数据显示","退出系统",""};//0
char *title_maintain[]={"蔬菜种类信息维护","蔬菜基本信息维护","蔬菜种植信息维护","返回主菜单","退出系统",""};//1
char *title_maintain_kind[]={"蔬菜种类信息录入","蔬菜种类信息修改","蔬菜种类信息删除","返回上一级菜单","返回主菜单","退出系统",""};//2
char *title_maintain_info[]={"蔬菜基本信息录入","蔬菜基本信息修改","蔬菜基本信息删除","返回上一级菜单","返回主菜单","退出系统",""};//3
char *title_maintain_plant[]={"蔬菜种植信息录入","蔬菜种植信息修改","蔬菜种植信息删除","返回上一级菜单","返回主菜单","退出系统",""};//4
char *title_query[]={"蔬菜种类信息查询","蔬菜基本信息查询","蔬菜种植信息查询","返回主菜单","退出系统",""};//5
char *title_query_info[]={"蔬菜名称索引","蔬菜分类码及营养成分索引","返回上一级菜单","返回主菜单","退出系统",""};//6
char *title_query_plant[]={"蔬菜名称及种植年份索引","蔬菜名称索引","返回上一级菜单","返回主菜单","退出系统",""};//7
char *title_count[]={"某年各类蔬菜收获统计","各种蔬菜收获统计","某类蔬菜数量统计","包含某营养成分的蔬菜统计","某年收获量达到标准的蔬菜统计","返回主菜单","退出系统",""};//8
char *title_load_export[]={"数据导入","数据导出","返回主菜单","退出系统",""};//9
char *title_load[]={"蔬菜种类信息","蔬菜基本信息","蔬菜种植信息","返回上一级菜单","返回主菜单","退出系统",""};//10
char *title_export[]={"按年份各类蔬菜信息统计表","按蔬菜名称统计信息","自由查询信息","返回上一级菜单","返回主菜单","退出系统",""};//11

#endif
