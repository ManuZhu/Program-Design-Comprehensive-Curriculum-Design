/************************************************************************/
/*   项目名称：菜农种植信息管理系统                                           */
/*   最后修改时间：2020-07-01                                                 */
/*   开发环境： VS                                                            */
/*   作者：朱文天                                                             */
/************************************************************************/

#include "info.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

//主函数，无参数
int main(){
    loadKind("dkind.csv");
    loadVeg("dbasic.csv");
    loadPlant("dplant.csv");//加载上一次导出的数据文件
    while(1){
		Menu();
		system("pause");
	}//循环展示主程序界面
    return 0;
}

//设置控制台信息，增强观感，无参数
void Menu(){
	system("title 菜农种植信息管理系统");//修改控制台标题
	system(WIN_SIZE);//设置控制台尺寸
	system("color 3e");//把背景设置为 浅绿色
    showMenu(0);//显示主菜单
}

//读入选项部分，参数为距第一列的空格数和距第一行的空行数，出口参数为读入的选项号码。
int Scanf(int left,int top){
	int option;
	setTop(top);
	setLeft(left);
	printf("请选择:");
	scanf("%d",&option);
	return option;
}

//输出所有数据，入口参数无
void show(){
    system("cls");setTop(10);
    pvegkind now=hkind->next;
    while(now!=NULL){
        printKind(now);
        now=now->next;
    }
}

//界面函数，入口参数option控制当前显示的界面
void showMenu(int option){
    char k,k1;
    int id,id1,s,s1,year,year1;
    float weight,weight1;
    char *nut=(char *)malloc(50);
    char *name=(char *)malloc(20);
    char *name1=(char *)malloc(20);
    char *filename=(char *)malloc(50);
	int select,flag;//select表示用户在当前界面选择第几项，flag表示用户所选操作完成后的状态码
	switch(option){
    case 0://主界面
        drawMenu(title,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) showMenu(1);
        else if(select==2) showMenu(5);
        else if(select==3) showMenu(8);
        else if(select==4) showMenu(9);
        else if(select==5) show();
        else if(select==6){//退出前保存数据
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 1://数据维护界面
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
    case 2://蔬菜种类信息维护界面
        drawMenu(title_maintain_kind,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//增加种类
            system("cls");setTop(10);setLeft(100);
            printf("请输入要添加的蔬菜种类信息（格式为种类编号,种类名称,包含的蔬菜名称以逗号分隔）:\n");
            memset(str,0,sizeof(str));
            setLeft(100);scanf("%s",str);getchar();
            flag=addKind(str);
            if(!flag) setLeft(100),printf("error:there is a conflict!\n");//蔬菜种类编号已存在但已有种类名称与添加的种类名称不符或相反情况下输出存在矛盾
            else setLeft(100),printf("success!\n");//创建成功
        }
        else if(select==2){//修改种类
            system("cls");setTop(10);setLeft(100);
            printf("请输入要修改的蔬菜种类编号:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("请输入新的蔬菜种类名称:");
            memset(str,0,sizeof(str));
            scanf("%s",str);getchar();
            flag=changeKind(k,str);
            if(!flag) setLeft(100),printf("error: cannot find the expected kind!\n");//找不到对应的种类
            else setLeft(100),printf("success\n");
        }
        else if(select==3){//删除种类
            system("cls");setTop(10);setLeft(100);
            printf("请输入要删除的蔬菜种类编号:");
            getchar();scanf("%c",&k);getchar();
            flag=delKind(k);
            if(flag) setLeft(100),printf("success!\n");
            else setLeft(100),printf("error:cannot find the kind!\n");
        }
        else if(select==4) showMenu(1);//返回上级菜单
        else if(select==5) showMenu(0);//返回主菜单
        else if(select==6){
            exportKind("dkind.csv");
            exportVeg("dbasic.csv");
            exportPlant("dplant.csv");
            exit(0);
        }
        break;
    case 3://蔬菜基本信息维护界面
        drawMenu(title_maintain_info,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//添加蔬菜
            system("cls");setTop(10);setLeft(100);
            printf("请输入要添加的蔬菜编号:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("请输入要添加的蔬菜名称:");
            memset(name,0,20);
            scanf("%s",name);getchar();
            setLeft(100);printf("请输入要添加的蔬菜分类编号:");
            scanf("%c",&k);getchar();
            setLeft(100);printf("请输入要添加的蔬菜营养成分:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            flag=addVeg(id,name,k,nut,NULL);
            if(!flag) setLeft(100),printf("error:this kind:%c cannot be found,please create it first!",k);//蔬菜种类不存在
            else if(flag==1) setLeft(100),printf("error:the %s has a different id!\n",name);//蔬菜名称已存在但编号不同
            else if(flag==2) setLeft(100),printf("error:the %d has already been created!\n",id);//已经存在相同的蔬菜
            else setLeft(100),printf("success!\n");
        }
        else if(select==2){//修改蔬菜基本信息
            system("cls");setTop(10);setLeft(100);
            printf("请输入要修改的蔬菜名称:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("请输入新的蔬菜名称:");
            memset(name1,0,20);
            scanf("%s",name1);getchar();
            setLeft(100);printf("请输入新的蔬菜营养成分:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            flag=changeVeg(name,name1,nut);
            if(!flag) setLeft(100),printf("error:%s cannot be found!\n",name);
            else setLeft(100),printf("success!\n");
        }
        else if(select==3){//删除蔬菜基本信息
            system("cls");setTop(10);setLeft(100);
            printf("请输入要删除的蔬菜名称:");
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
    case 4://蔬菜种植信息维护
        drawMenu(title_maintain_plant,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//添加蔬菜种植信息
            system("cls");setTop(10);setLeft(100);
            printf("请输入要添加的种植蔬菜编号:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("请输入要添加的种植蔬菜面积:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("请输入要添加的种植蔬菜重量:");
            scanf("%f",&weight);getchar();
            setLeft(100);printf("请输入要添加的种植蔬菜年份:");
            scanf("%d",&year);getchar();
            flag=addPlant(id,s,weight,year);
            if(!flag) setLeft(100),printf("error:%d cannot be found!\n",id);//未找到指定编号的蔬菜
            else setLeft(100),printf("success!\n");
        }
        else if(select==2){//修改蔬菜种植信息
            system("cls");setTop(10);setLeft(100);
            printf("请输入要修改的种植蔬菜编号:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("请输入要修改的种植蔬菜年份:");
            scanf("%d",&year);getchar();
            setLeft(100);printf("请输入新的种植蔬菜面积:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("请输入新的种植蔬菜重量:");
            scanf("%f",&weight);getchar();
            flag=changePlant(id,year,s,weight);
            if(!flag) setLeft(100),printf("error:the plant cannot be found!\n");
            else setLeft(100),printf("success!\n");
        }
        else if(select==3){//删除蔬菜种植信息
            system("cls");setTop(10);setLeft(100);
            printf("请输入要删除的蔬菜编号:");
            getchar();scanf("%d",&id);getchar();
            setLeft(100);printf("请输入要删除的种植蔬菜年份:");
            scanf("%d",&year);getchar();
            flag=delPlant(id,year);
            if(flag) setLeft(100),printf("success!\n");
            else setLeft(100),printf("error:the plant cannot be found!\n");
        }
        else if(select==4) showMenu(1);
        else if(select==5) showMenu(0);
        else if(select==6) exit(0);
        break;
    case 5://数据查询界面
        drawMenu(title_query,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){
            system("cls");setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜种类编号:");
            getchar();scanf("%c",&k);getchar();
            flag=qKind(k);
            if(!flag) setLeft(100),printf("error:the kind %c cannot be found!\n",k);//蔬菜种类未找到
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
    case 6://蔬菜基本信息查询
        drawMenu(title_query_info,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//蔬菜名称索引
            system("cls");setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜名称:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            flag=qInfoA(name);
            if(!flag) setLeft(100),printf("error:the vegetables with name %s cannot be found!\n",name);
        }
        else if(select==2){//蔬菜分类码及营养成分索引
            system("cls");setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜种类编号:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("请输入要查询的蔬菜营养成分:");
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
    case 7://蔬菜种植信息查询
        drawMenu(title_query_plant,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//蔬菜名称及种植年份索引
            system("cls");setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜名称:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜年份:");
            scanf("%d",&year);getchar();
            flag=qPlantA(name,year);
            if(!flag) setLeft(100),printf("error:the vegetables cannot be found!\n");
        }
        else if(select==2){//蔬菜名称索引
            system("cls");setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜名称:");
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
    case 8://数据统计界面
        drawMenu(title_count,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//某年各类蔬菜收获统计
            setLeft(100);printf("请输入要查询的种植蔬菜年份:");
            getchar();scanf("%d",&year);getchar();
            countA(year);
        }
        else if(select==2){//各种蔬菜收获统计
            setLeft(100);printf("请输入要查询的种植蔬菜起始年份:");
            getchar();scanf("%d",&year);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜终止年份:");
            scanf("%d",&year1);getchar();
            countB(year,year1);
        }
        else if(select==3) countC();//某类蔬菜数量统计
        else if(select==4){//包含某营养成分的蔬菜统计
            setLeft(100);printf("请输入要查询的蔬菜营养成分:");
            memset(nut,0,50);
            getchar();scanf("%s",nut);getchar();
            countD(nut);
        }
        else if(select==5){//某年收获量达到标准的蔬菜统计
            setLeft(100);printf("请输入要查询的种植蔬菜年份:");
            getchar();scanf("%d",&year);getchar();
            setLeft(100);printf("请输入要满足的种植面积:");
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
    case 9://导入导出界面
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
    case 10://数据导入
        drawMenu(title_load,100,10,2,1);
        select=Scanf(100,0);
        if(select==1){//蔬菜种类信息导入
            setLeft(100);printf("请输入导入文件的绝对路径:");
            memset(filename,0,50);
            getchar();scanf("%s",filename);getchar();
            loadKind(filename);
        }
        else if(select==2){//蔬菜基本信息导入
            setLeft(100);printf("请输入导入文件的绝对路径:");
            memset(filename,0,50);
            getchar();scanf("%s",filename);getchar();
            loadVeg(filename);
        }
        else if(select==3){//蔬菜种植信息导入
            setLeft(100);printf("请输入导入文件的绝对路径:");
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
    case 11://数据导出
        drawMenu(title_export,100,10,2,1);
        select=Scanf(100,0);
        if(select==1) exportA();//按年份各类蔬菜信息统计表
        else if(select==2){//按蔬菜名称统计表
            setTop(10);setLeft(100);
            printf("请输入要查询的蔬菜名称:");
            memset(name,0,20);
            getchar();scanf("%s",name);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜终止年份:");
            scanf("%d",&year);getchar();
            exportB(name,year);
        }
        else if(select==3){//自由查询信息表
            system("cls");setTop(10);
            setLeft(100);printf("请输入要查询的蔬菜种类编号（左边界）:");
            getchar();scanf("%c",&k);getchar();
            setLeft(100);printf("请输入要查询的蔬菜种类编号（右边界）:");
            scanf("%c",&k1);getchar();
            setLeft(100);printf("请输入要查询的蔬菜种类名称:");
            memset(str,0,sizeof(str));
            scanf("%s",str);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜编号（左边界）:");
            scanf("%d",&id);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜编号（右边界）:");
            scanf("%d",&id1);getchar();
            setLeft(100);printf("请输入要查询的蔬菜名称:");
            memset(name,0,20);
            scanf("%s",name);getchar();
            setLeft(100);printf("请输入要查询的蔬菜营养成分:");
            memset(nut,0,50);
            scanf("%s",nut);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜面积（左边界）:");
            scanf("%d",&s);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜面积（右边界）:");
            scanf("%d",&s1);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜重量（左边界）:");
            scanf("%f",&weight);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜重量（右边界）:");
            scanf("%f",&weight1);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜年份（左边界）:");
            scanf("%d",&year);getchar();
            setLeft(100);printf("请输入要查询的种植蔬菜年份（右边界）:");
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
            if(year1>0) flag|=a[7];//由用户选择的搜索条件确定状态码
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

int drawMenu(char *str[],int left,int top,int line_height,int line_flag){//入口参数为界面中的选项，左间距，上间距，行高，行标志，输出界面内容
	int i=0,k,count=1,max=0,maxStrLength=0;
	while(strcmp(str[i],"")!=0){
		max=strlen(str[i]);
		if(max>maxStrLength) maxStrLength = max;
		i++;
	}
	i=0;
	system("cls");
	setTop(top);//控制上间距
	while(strcmp(str[i],"")!=0){
		setLeft(left);//控制左间距
		if(i==0){
			for(k=1;k<=maxStrLength/2+1;k++){
				if(k==1) printf("┌");
				printf("——");
				if(k==maxStrLength/2+1) printf("┐\n\n\n\n");
			}
			setLeft(left);
		}
		if(line_flag) printf("¤     %d.",count);
		printf("%s",str[i++]);
		count++;
		setTop(line_height);//控制行高
	}
	printf("\n\n\n\n");
	setLeft(left);
	for(k=1;k<=maxStrLength/2+1;k++){
		if(k==1) printf("└");
		printf("——");
		if(k==maxStrLength/2+1) printf("┘\n");
	}
	return count-1;
}

int setLeft(int left){//控制左间距
    int i;
	for(i=0;i<left;i++) printf(" ");
	return left;
}

int setTop(int top){//控制上间距
    int i;
	for(i=0;i<top;i++) printf("\n");
	return top;
}

void loadKind(char *filename){//载入种类信息，输入参数为文件的绝对路径
    char cr;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        setLeft(100);
        printf("open failed!\n");//无法打开指定文件
        return;
    }
    do{
        cr=fgetc(fp);
    }while(cr!='\n');
    hkind=(pvegkind)malloc(sizeof(vegkind));
    hkind->next=NULL;
    while((cr=fgetc(fp))!=EOF){//提取信息
        fscanf(fp,"%[^\n]",str+1);
        str[0]=cr;
        addKind(str);
        cr=fgetc(fp);
        memset(str,0,sizeof(str));
    }
    fclose(fp);
}

int addKind(char *str){//添加种类信息
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
    while(i<len){//提取每一个蔬菜名称，添加蔬菜信息
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

int delKind(char k){//删除种类信息，入口参数为蔬菜种类编号
    pvegkind now=hkind->next,pre=hkind;
    while(now!=NULL){
        if(now->k==k) break;
        pre=now;
        now=now->next;
    }
    if(now==NULL) return 0;
    pveginfo x=now->hinfo->next,y;
    while(x!=NULL){//递归释放所有相关内存空间
        y=x;
        x=x->next;
        free(y);
    }
    free(now->hinfo);
    pre->next=now->next;
    free(now);
    return 1;
}

int changeKind(char k,char *kind){//修改种类信息，入口参数为蔬菜种类编号，和种类的名称
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

void printKind(pvegkind now){//输出种类信息，入口参数为指定输出的结构体成员
    setLeft(100);printf("%c.%s:\n",now->k,now->kind);
    pveginfo x=now->hinfo->next;
    while(x!=NULL){
        printVeg(x);
        x=x->next;
    }
}

void exportKind(char *filename){//导出种类信息，输入参数为文件的绝对路径，以csv的格式输出相关信息
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"分类编号,分类名称,蔬菜名称\n");
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

void loadVeg(char *filename){//导入蔬菜基本信息，输入参数为文件的绝对路径
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
        fscanf(fp,"%[^,]",name);//读取蔬菜名称
        cr=fgetc(fp);
        k=fgetc(fp);
        cr=fgetc(fp);
        memset(nut,0,50);
        fscanf(fp,"%[^\n]",nut);//读取蔬菜营养成分
        cr=fgetc(fp);
        //printf("id:%d name:%s nut:%s kind:%c\n",id,name,nut,k);
        addVeg(id,name,k,nut,NULL);
    }
    fclose(fp);
}

int addVeg(int id,char *name,char k,char *nut,pvegkind now){//添加蔬菜信息，输入参数为蔬菜编号，蔬菜名称，蔬菜种类编号，蔬菜营养成分，蔬菜从属的种类结构体成员
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
        if(veg->id==0) veg->id=id;//如果蔬菜编号为初始状态，则修改为当前的编号
        else if(veg->id!=id) return 1;
        if(!strlen(veg->nut)&&nut!=NULL) strcpy(veg->nut,nut);
    }
    return 3;
}

int delVeg(char *name){//删除蔬菜信息，输入参数为蔬菜名称
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

int changeVeg(char *name,char *name1,char *nut1){//修改蔬菜信息，入口参数为蔬菜名称，新的蔬菜名称，新的营养成分
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

void printVeg(pveginfo now){//输出蔬菜信息，入口参数为指定输出的蔬菜基本信息结构体成员
    setLeft(100);printf("    id:%d name:%s kind:%c nutrition:%s\n",now->id,now->name,now->k,now->nut);
    pplantinfo x=now->hplant->next;
    while(x!=NULL){
        setLeft(100);printf("        square:%d weight:%f year:%d\n",x->s,x->weight,x->year);
        x=x->next;
    }
}

void exportVeg(char *filename){//导出蔬菜基本信息，输入参数为文件的绝对路径
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"蔬菜编号,蔬菜名称,分类码,营养成分\n");
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

void loadPlant(char *filename){//导入蔬菜种植信息，输入参数为文件的绝对路径
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
        fscanf(fp,"%d,%d,%f,%d",&id,&s,&weight,&year);//依次读入相关信息
        cr=fgetc(fp);
        //printf("name:%s nut:%s kind:%c\n",name,nut,k);
        addPlant(id,s,weight,year);
    }
    fclose(fp);
}

int addPlant(int id,int s,float weight,int year){//添加蔬菜种植信息，输入参数为蔬菜编号，种植面积，收获重量，种植年份
    pvegkind now=hkind->next;
    pveginfo veg;
    pplantinfo tmp;
    while(now!=NULL){
        veg=now->hinfo->next;
        while(veg!=NULL){
            if(veg->id==id) break;//寻找指定蔬菜编号的蔬菜
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

int delPlant(int id,int year){//删除蔬菜种植信息，入口参数为蔬菜编号和种植年份
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

int changePlant(int id,int year,int s,float weight){//修改蔬菜种植信息，入口参数为蔬菜编号，新的种植年份，种植面积，收获重量
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

void exportPlant(char *filename){//导出蔬菜种植信息，入口参数为文件的绝对路径
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"编号,蔬菜编号,种植面积,收获重量,种植年份\n");
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

int qKind(char k){//蔬菜种类查询，入口参数为种类编号，输出该种蔬菜所有的相关信息
    pvegkind now=hkind->next;
    while(now!=NULL){
        if(now->k==k) break;
        now=now->next;
    }
    if(now==NULL) return 0;
    else system("cls"),printKind(now);
    return 1;
}

int qInfoA(char *name){//蔬菜基本信息查询，入口参数为蔬菜名称，根据名称找到相对应的蔬菜，输出相关信息
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

int qInfoB(char k,char *nut){//蔬菜基本信息查询，入口参数为蔬菜种类编号和蔬菜营养成分
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

int qPlantA(char *name,int year){//蔬菜种植信息查询，入口参数为蔬菜名称和种植年份
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

int qPlantB(char *name){//蔬菜种植信息查询，入口参数为蔬菜名称
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

void exportA(){//数据导出
    FILE *fp;
    fp=fopen("按年份各类蔬菜信息统计表.csv","w");
    fprintf(fp,"年份,分类名称,种植面积（分）,收获总重量（kg）\n");
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

void exportB(char *name,int Y){//数据导出，入口参数为蔬菜名称和截止年份
    FILE *fp;
    fp=fopen("按蔬菜名称统计信息表.csv","w");
    fprintf(fp,"年份,蔬菜名称,分类名称,种植面积（分）,收获重量（kg）\n");
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

//自由查询导出，入口参数为所有可以搜索的参数，flag记录哪些参数被用来索引
void exportC(char k1,char k2,char *kind,int id1,int id2,char *name,char *nut,int s1,int s2,float weight1,float weight2,int year1,int year2,int flag){
    FILE *fp;
    fp=fopen("自由统计信息表.csv","w");
    fprintf(fp,"种类编号,种类名称,蔬菜编号,蔬菜名称,营养成分,种植面积（分）,收获重量（kg）,种植年份\n");
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

int countA(int Y){//某年各类蔬菜收获统计，遍历所有蔬菜种类，统计信息并排序，用代替柱状图
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

int countB(int Ys,int Yt){//各种蔬菜收获统计，入口参数为开始年份和截止年份
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

int countC(){//某类蔬菜数量统计，统计每种蔬菜中已记录的蔬菜数量
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

int countD(char *nut){//包含某营养成分的蔬菜统计，入口参数为营养成分表
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

int countE(int Y,int S){//某年收获量达到标准的蔬菜统计，入口参数为种植年份和种植面积标准
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
