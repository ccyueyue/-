#pragma once
#include<iostream>
#include<string>
using namespace std;

//职工抽象类
class Worker
{
public:

	//显示个人信息
	virtual void showInfo() = 0; //纯虚函数
	//获取岗位名称
	virtual string getDepName() = 0;


	int m_Id;
	string m_Name;
	int m_DepId;
};