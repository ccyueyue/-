#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include<fstream>
#define FILENAME "empFile.txt"
//头文件写类的结构，和类中的函数声明
class WorkManager
{
public:

	//构造函数
	WorkManager();

	//与用户沟通的界面
	void Show_Menu();

	//退出系统
	void exitsystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker ** m_EmpArray;

	//添加职工
	void add_Emp();

	//保存文件
	void save();

	//判断文件是否为空 标志
	bool m_isEmpty;

	//统计人数
	int get_EmpNum();

	//初始化员工人数信息
	void init_Emp();

	//显示职工
	void show_Emp();

	//删除职工
	void Del_Emp();

	//按照职工的编号判断职工是否存在
	int Is_Exist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();

	//析构函数
	~WorkManager();

};