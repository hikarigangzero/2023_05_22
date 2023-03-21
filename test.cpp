#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct roommess
{
	char id[11];
	int price;
	bool booked=false;
	char cname[21];
	char cid[21];
	bool gone=false;
};

class room//假设共3层每层5间 
{
	public:
		static void menu(room rooms[][5]);
		static void addmessage(room rooms[][5]);
		static void book(room rooms[][5]);
		void rcmessage(room rooms);
		room();
		static void priceset(room rooms[][5]);
		void delemessage(room &a,int record,room rooms[][5]);
		static void show(room rooms[][5]);
		static void finding(char arr[],room rooms[][5]);
		static void count(room rooms[][5]); 
	private:
		struct roommess mesa;
};

room::room()//构造函数 
{
	strcpy(mesa.cname,"N");
	strcpy(mesa.cid,"N");
	strcpy(mesa.id,"N");
}

void room::menu(room rooms[][5])//菜单 
{
	int a=0;
	do
	{
		cout<<"  欢迎使用酒店客房管理系统  "<<endl
		<<"----------------------------"<<endl
		<<"*****增加客房信息——1******"<<endl
		<<"*****删除客房信息——2******"<<endl
		<<"*****显示客房信息——3******"<<endl
		<<"*****预订客房————4******"<<endl
		<<"*****办理入住————5******"<<endl
		<<"*****查找住户————6******"<<endl
		<<"*****办理退房————7******"<<endl
		<<"*****总统计—————8******"<<endl
		<<"*****退出——————9******"<<endl
		<<"----------------------------"<<endl;
		cin>>a;
		switch(a)
		{
			case 1:
				{
					room::addmessage(rooms);
					break;
				}
			case 7:
			case 2:
				{
					cout<<"请输入需要删除的房间号："<<endl;
					int nn;
					cin>>nn;
					int x, y;
					x=nn/100;
					y=nn%100;
					rooms[x-1][y-1].delemessage(rooms[x-1][y-1],nn,rooms);
					break;
				}
			case 3:
				{
					room::show(rooms);
					break;
				}
			case 4:
				{
					room::book(rooms);
					break;
				}
			case 5:
				{
					cout<<"请输入入住的房号："<<endl;
					int nn;
					cin>>nn;
					int x, y;
					x=nn/100;
					y=nn%100;
					rooms[x-1][y-1].mesa.gone=true;
					break;//5办理入住 
				}
			case 6:
				{
					cout<<"请输入姓名："<<endl;
					char arr[21];
					cin>>arr;
					room::finding(arr,rooms);
					break;
				}
			case 8:
				{
					room::count(rooms);
					break;
				}
			case 9:
				{
					exit(0);
					break;
				}
			default: break;
		}
	}while(true);
}

void room::addmessage(room rooms[][5])//1增加用户信息 
{
	ofstream file;
	file.open("message",ios::out|ios::binary);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			file.write((char*)&rooms[i][j].mesa,sizeof(rooms[i][j].mesa));
		}
	}
	file.close();
}

void room::priceset(room rooms[][5])//设置房间价格 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			rooms[i][j].mesa.price=(i+1)*100+(j+1)*10;
		}
	}
}

void room::rcmessage(room rooms)//输入住户信息
{
	cout<<"请输入姓名："<<endl;
	cin>>mesa.cname;
	cout<<"请输入身份证号码："<<endl;
	cin>>mesa.cid;
	cout<<"请输入房间号："<<endl;
	cin>>mesa.id;
}

void room::book(room rooms[][5])//4预订客房
{
	cout<<"请输入要预定的房间号（共三层，每层五间）："<<endl;
	int record=0;
	int a=0;
	int b=0;
	cin>>record;
	a=record/100;
	b=record%100;
	rooms[a-1][b-1].rcmessage(rooms[a-1][b-1]);
	rooms[a-1][b-1].mesa.booked=true;
}

void room::delemessage(room &a,int record,room rooms[][5])//2,7退房与删除客房信息 
{
	int x, y;
	x=record/100;
	y=record%100;
	ofstream file;
	file.open("message",ios::out|ios::binary);
	a.mesa.booked=false;
	a.mesa.gone=false; 
	strcpy(a.mesa.cid,"N");
	strcpy(a.mesa.cname,"N");
	strcpy(a.mesa.id,"N");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			file.write((char*)&rooms[i][j].mesa,sizeof(rooms[i][j].mesa));
		}
	}
	file.close();
}

void room::show(room rooms[][5])//3显示客房信息 
{
	ifstream file;
	file.open("message",ios::in|ios::binary);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			file.read((char*)&rooms[i][j].mesa,sizeof(rooms[i][j].mesa));
			if(strcmp(rooms[i][j].mesa.cname,"N")!=0)
			{
				cout<<"房间号："<<rooms[i][j].mesa.id<<endl
				<<"价格："<<rooms[i][j].mesa.price<<endl
				<<"住户姓名："<<rooms[i][j].mesa.cname<<endl
				<<"住户身份证号码："<<rooms[i][j].mesa.cid<<endl;
				if(rooms[i][j].mesa.booked)
				{
					cout<<"已预定"<<endl; 
				}
				else if(!rooms[i][j].mesa.booked)
				{
					cout<<"未预定"<<endl;
				}
				if(rooms[i][j].mesa.gone)
				{
					cout<<"已入住"<<endl;
				}
				else if(!(rooms[i][j].mesa.gone))
				{
					cout<<"未入住"<<endl;
				}
			}
		}
	}
	file.close();
}

void room::finding(char arr[],room rooms[][5])//6用姓名查找房号 
{
	ifstream file;
	file.open("message",ios::in|ios::binary);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			file.read((char*)&rooms[i][j].mesa,sizeof(rooms[i][j].mesa));
		}
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(strcmp(rooms[i][j].mesa.cname,arr)==0)
			{
				cout<<"对应房间号为："<<rooms[i][j].mesa.id<<endl;
			}
		}
	}
	file.close();
}

void room::count(room rooms[][5])
{
	int a=0;
	int b=0;
	cout<<"共有15个房间"<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			if((rooms[i][j].mesa.booked)&&(!rooms[i][j].mesa.gone))
			{
				a++;
			}
			else if((rooms[i][j].mesa.booked)&&(rooms[i][j].mesa.gone))
			{
				b++;
			}
		}
	}
	cout<<"有"<<a<<"个房间被预定但未入住"<<endl
	<<"有"<<b<<"个房间已入住"<<endl; 
}

int main()
{
	room rooms[3][5];
	room::priceset(rooms);
	room::menu(rooms);
	return 0;
}
