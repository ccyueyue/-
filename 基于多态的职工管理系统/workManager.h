#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include<fstream>
#define FILENAME "empFile.txt"
//ͷ�ļ�д��Ľṹ�������еĺ�������
class WorkManager
{
public:

	//���캯��
	WorkManager();

	//���û���ͨ�Ľ���
	void Show_Menu();

	//�˳�ϵͳ
	void exitsystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_isEmpty;

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��������Ϣ
	void init_Emp();

	//��ʾְ��
	void show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//����ְ���ı���ж�ְ���Ƿ����
	int Is_Exist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~WorkManager();

};