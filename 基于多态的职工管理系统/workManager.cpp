#include"workManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
WorkManager::WorkManager()
{
	//�ļ�������
	ifstream ifs(FILENAME,ios::in);
	//ifs.open(FILENAME,ios::in);
	if (!ifs.is_open())
	{
		//cout<<"�ļ�������"<<endl;

		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_isEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ�û������
	char ch;
	ifs >>ch;
	if (ifs.eof())
	{
		//cout<<"�ļ�Ϊ�գ�"<<endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_isEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ���Ϊ��
	this->m_isEmpty = false;
	int num = this->get_EmpNum();
	//cout<<  "ְ������Ϊ: "<< num<<endl;
	this->m_EmpNum = num;//���³�Ա����
	//���ٿռ�
	this->m_EmpArray = new Worker *[this->m_EmpNum];
	//���ļ��е����ݣ���ŵ�����
	this->init_Emp();

	//for(int i = 0; i<this->m_EmpNum; i++)
	//{
	//	cout<<"ְ�����"<<this->m_EmpArray[i]->m_Id
	//		<<"ְ������"<<this->m_EmpArray[i]->m_Name
	//		<<"���ű��"<<this->m_EmpArray[i]->m_DepId
	//		<<endl;
	//}
}
//չʾ�˵�
void WorkManager::Show_Menu()
{
	cout<<"***********************************************"<<endl;
	cout<<"************* ��ӭʹ��ְ������ϵͳ ************"<<endl;
	cout<<endl;
	cout<<"**************** 0.�˳�������� ***************"<<endl;
	cout<<endl;
	cout<<"**************** 1.����ְ����Ϣ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 2.��ʾְ����Ϣ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 3.ɾ��ְ����Ϣ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 4.�޸�ְ����Ϣ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 5.����ְ����Ϣ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 6.���ձ������ ***************"<<endl;
	cout<<endl;
	cout<<"**************** 7.���������Ϣ ***************"<<endl;
	cout<<"***********************************************"<<endl;
	cout<<endl;
}
void WorkManager::exitsystem()
{
	cout<<"��ӭ�´�ʹ��"<<endl;
	system("pause");
	exit(0);
}
void WorkManager::add_Emp() 
{
	cout<<"���������ְ��������"<<endl;

	int addNum = 0;
	cin >> addNum;
	if(addNum > 0)
	{
		//��������¿ռ�Ĵ�С
		int newsize = this->m_EmpNum+addNum;//�¿ռ����� = ԭ����¼������+��������
		//�����¿ռ�
		Worker**newSpace = new Worker *[newsize];
		//��ԭ���ռ�����ݣ��������¿ռ�
		if(this->m_EmpNum > 0)
		{
			for(int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for(int i = 0; i<addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout<<"������� "<<i+1<<" ����ְ����ţ� "<<endl;
			cin>>id;
			cout<<"������� "<<i+1<<" ����ְ�������� "<<endl;
			cin>>name;
			cout<<"��ѡ���ְ���ĸ�λ�� "<<endl;
			cout<<"1.��ְͨ��"<<endl;
			cout<<"2.����"<<endl;
			cout<<"3.�ϰ�"<<endl;
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
			//��������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum+i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete [] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//����ְ������
		this->m_EmpNum = newsize;

		this->m_isEmpty = false;
		
		//�ɹ���Ӻ󱣴浽�ļ���
		save();
		 
		//��ʾ��ӳɹ�
		cout<<"�ɹ����"<<addNum<<"����ְ��"<<endl;

	}
	else
	{
		cout<<"����������������������"<<endl;
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
		//��¼����
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
		//���ݲ�ͬ�Ĳ���ID������ͬ�Ķ���
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
		//��ŵ�������
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkManager::show_Emp()
{
	if(this->m_isEmpty)
	{
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬�ӿ�
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
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout<<"��������Ҫɾ����ְ����ţ�"<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re == -1)
		{
			cout<<"��Ա��������"<<endl;
		}
		else
		{
			for(int i = re;i < m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			//����ͬ���������ļ���
			this->save();
			cout<<"ɾ���ɹ���"<<endl;
		}
	}
	//�����������������
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
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else
	{
		//��ְ������޸�ְ����Ϣ
		cout<<"������Ҫ�޸ĵ�ְ����ţ�"<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re != -1)
		{
			delete this->m_EmpArray[re];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout<<"�鵽"<<id <<"��ְ������������ְ�����ţ� "<<endl;
			cin >> newId;
			cout<<"������������ "<<endl;
			cin >> newName;
			cout<<"������ְ����λ�� "<<endl;
			cout<<"1����ְͨ��"<<endl;
			cout<<"2������"<<endl;
			cout<<"3���ϰ�"<<endl;
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
			//�������� ��������
			this->m_EmpArray[re] = worker;
			cout<<"�޸ĳɹ���"<<endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout<<"��Ա�������ڣ�"<<endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::find_Emp()
{
	if (this->m_isEmpty)
	{
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else
	{
		//��ְ������޸�ְ����Ϣ
		cout<<"������Ҫ�޸ĵ�ְ����ţ�"<<endl;
		int id = 0;
		cin >> id;
		int re = Is_Exist(id);
		if (re == -1)
		{
			cout<<"��Ա�������ڣ�"<<endl;
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
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else
	{
		cout<<"��ѡ������ʽ�� "<<endl;
		cout<<"1����ְ�����Ž�������"<<endl;
		cout<<"2����ְ�����Ž��н���"<<endl;

		int select = 0;
		cin >>select;

		for(int i = 0 ;i < m_EmpNum; i++)
		{
			int minOrMax= i;
			for (int j = i+1; j < m_EmpNum; j++)
			{
				if(select == 1)//����
				{
					if(m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//����
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
	cout<<"����ɹ���������Ϊ��  "<<endl;	
	this->save();
	this->show_Emp();
	}
	system("pause");
	system("cls");
}
void WorkManager::Clean_File()
{
	cout<<"ȷ����գ�"<<endl;
	cout<<"1��ȷ��"<<endl;
	cout<<"2������"<<endl;

	int select = 0;
	cin >>select;
	if(select == 1)
	{
		//��ģʽios::trunc ��������ļ�����ɾ���ļ������´���һ�����ļ�
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
	cout<<"��ճɹ���"<<endl;
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