#include"workManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
WorkManager::WorkManager()
{
	//文件不存在
	ifstream ifs(FILENAME,ios::in);
	//ifs.open(FILENAME,ios::in);
	if (!ifs.is_open())
	{
		//cout<<"文件不存在"<<endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_isEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，没有数据
	char ch;
	ifs >>ch;
	if (ifs.eof())
	{
		//cout<<"文件为空！"<<endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_isEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，不为空
	this->m_isEmpty = false;
	int num = this->get_EmpNum();
	//cout<<  "职工个数为: "<< num<<endl;
	this->m_EmpNum = num;//更新成员属性
	//开辟空间
	this->m_EmpArray = new Worker *[this->m_EmpNum];
	//将文件中的数据，存放到数组
	this->init_Emp();

	//for(int i = 0; i<this->m_EmpNum; i++)
	//{
	//	cout<<"职工编号"<<this->m_EmpArray[i]->m_Id
	//		<<"职工姓名"<<this->m_EmpArray[i]->m_Name
	//		<<"部门编号"<<this->m_EmpArray[i]->m_DepId
	//		<<endl;
	//}
}
//展示菜单
void WorkManager::Show_Menu()
{
	cout<<"***********************************************"<<endl;
	cout<<"************* 欢迎使用职工管理系统 ************"<<endl;
	cout<<endl;
	cout<<"**************** 0.退出管理程序 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 1.增加职工信息 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 2.显示职工信息 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 3.删除职工信息 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 4.修改职工信息 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 5.查找职工信息 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 6.按照编号排序 ***************"<<endl;
	cout<<endl;
	cout<<"**************** 7.清空所有信息 ***************"<<endl;
	cout<<"***********************************************"<<endl;
	cout<<endl;
}
void WorkManager::exitsystem()
{
	cout<<"欢迎下次使用"<<endl;
	system("pause");
	exit(0);
}
void WorkManager::add_Emp() 
{
	cout<<"请输入添加职工的数量"<<endl;

	int addNum = 0;
	cin >> addNum;
	if(addNum > 0)
	{
		//计算添加新空间的大小
		int newsize = this->m_EmpNum+addNum;//新空间人数 = 原来记录的人数+新增人数
		//开辟新空间
		Worker**newSpace = new Worker *[newsize];
		//将原来空间的数据，拷贝到新空间
		if(this->m_EmpNum > 0)
		{
			for(int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for(int i = 0; i<addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout<<"请输入第 "<<i+1<<" 个新职工编号： "<<endl;
			cin>>id;
			cout<<"请输入第 "<<i+1<<" 个新职工姓名： "<<endl;
			cin>>name;
			cout<<"请选择该职工的岗位： "<<endl;
			cout<<"1.普通职工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>dSelect;
			Worker * worker = NULL;
			switch(dSelect)
			{
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id,name,2);
				break;
			case 3:
				worker = new Boss(id,name,3);
				break;
			default:
				break;
			}
			//将创建的职工职责，保存到数组中
			newSpace[this->m_EmpNum+i] = worker;
		}
		//释放原有空间
		delete [] this->m_EmpArray;

		//更新新空间的指向
		this->m_EmpArray = newSpace;

		//更新职工人数
		this->m_EmpNum = newsize;

		this->m_isEmpty = false;
		
		//成功添加后保存到文件中
		save();
		 
		//提示添加成功
		cout<<"成功添加"<<addNum<<"名新职工"<<endl;

	}
	else
	{
		cout<<"输入数据有误，请重新输入"<<endl;
	}
	system("pause");
	system("cls");
}
void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);
	for (int i = 0; i < this->m_EmpNum; i ++)
	{
		ofs<<this->m_EmpArray[i]->m_Id<<"  "
			<<this->m_EmpArray[i]->m_Name<<"  "
			<<this->m_EmpArray[i]->m_DepId<<endl;
	}
	ofs.close();
}
int WorkManager::get_EmpNum()
{
	ifstream ifs(FILENAME,ios::in);
	//ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while(ifs>>id && ifs >>name && ifs >>dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}
void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker *worker = NULL;
		//根据不同的部门ID创建不同的对象
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else 
		{
			worker = new Boss(id, name, dId);
		}
		//存放到数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkManager::show_Emp()
{
	if(this->m_isEmpty)
	{
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::Del_Emp()
{
	if (this->m_isEmpty)
	{
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else
	{
		//按照职工编号删除
		cout<<"请输入想要删除的职工编号："<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re == -1)
		{
			cout<<"该员工不存在"<<endl;
		}
		else
		{
			for(int i = re;i < m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			//数据同步更新至文件中
			this->save();
			cout<<"删除成功！"<<endl;
		}
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}
int WorkManager::Is_Exist(int id)
{
	int index = -1;
	for (int i = 0; i <this->m_EmpNum; i++)
	{
		if(this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void WorkManager::Mod_Emp()
{
	if (this->m_isEmpty)
	{
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else
	{
		//按职工编号修改职工信息
		cout<<"请输入要修改的职工编号："<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re != -1)
		{
			delete this->m_EmpArray[re];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout<<"查到"<<id <<"号职工，请输入新职工工号： "<<endl;
			cin >> newId;
			cout<<"请输入姓名： "<<endl;
			cin >> newName;
			cout<<"请输入职工岗位： "<<endl;
			cout<<"1、普通职工"<<endl;
			cout<<"2、经理"<<endl;
			cout<<"3、老板"<<endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch(dSelect)
			{
			case 1:
				worker = new Employee(newId,newName,dSelect);
				break;
			case 2:
				worker = new Manager(newId,newName,dSelect);
				break;
			case 3:
				worker = new Boss(newId,newName,dSelect);
				break;
			default:
				break;
			}
			//更改数据 到数组中
			this->m_EmpArray[re] = worker;
			cout<<"修改成功！"<<endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout<<"该员工不存在！"<<endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::find_Emp()
{
	if (this->m_isEmpty)
	{
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else
	{
		//按职工编号修改职工信息
		cout<<"请输入要修改的职工编号："<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re == -1)
		{
			cout<<"该员工不存在！"<<endl;
		}
		else
		{
			this->m_EmpArray[re]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::Sort_Emp()
{
	if (this->m_isEmpty)
	{
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else
	{
		cout<<"请选择排序方式： "<<endl;
		cout<<"1、按职工工号进行升序"<<endl;
		cout<<"2、按职工工号进行降序"<<endl;

		int select = 0;
		cin >>select;

		for(int i = 0 ;i < m_EmpNum; i++)
		{
			int minOrMax= i;
			for (int j = i+1; j < m_EmpNum; j++)
			{
				if(select == 1)//升序
				{
					if(m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//降序
				{
					if(m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
	cout<<"排序成功，排序结果为：  "<<endl;	
	this->save();
	this->show_Emp();
	}
	system("pause");
	system("cls");
}
void WorkManager::Clean_File()
{
	cout<<"确认清空？"<<endl;
	cout<<"1、确认"<<endl;
	cout<<"2、返回"<<endl;

	int select = 0;
	cin >>select;
	if(select == 1)
	{
		//打开模式ios::trunc 如果存在文件，则删除文件并重新创建一个空文件
		ofstream ofs;
		ofs.open(FILENAME,ios::trunc);
		ofs.close();

		if(this->m_isEmpty != NULL)
			for(int i = 0; i < m_EmpNum; i++)
			{
				if(this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete [] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_isEmpty = true;
	}
	cout<<"清空成功！"<<endl;
	system("pause");
	system("cls");
}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
	delete [] this->m_EmpArray;
	this->m_EmpArray = NULL;
	}
	
}