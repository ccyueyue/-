#include<iostream> 
using namespace std;
#include"workManager.h"
#include"worker.h"
#include"employee.h"

int main()
{
	/*Worker *worker = new Employee(1,"张三",1);
	worker->showInfo();*/

	//实例化管理者对象
	WorkManager wm;
	int select =0;
	while(true)
	{
		wm.Show_Menu();
		cout<<"请输入您的选择"<<endl;
		cin>>select;
		switch(select)
		{
		case 0:
			wm.exitsystem();
		case 1:
			wm.add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			cout<<"您输入的选项不存在，请重新输入"<<endl;
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
