#include"employee.h"


Employee::Employee(int id ,string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepId = dId;
}
void Employee::showInfo()
{
	cout<<"职工编号"<<this->m_Id
		<<"\t职工姓名"<<this->m_Name
		<<"\t岗位"<<this->getDepName()
		<<"\t职工职责：完成经理交待的任务"<<endl;
}

string Employee::getDepName()
{
	return string("员工");
}
