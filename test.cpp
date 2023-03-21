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

class room//���蹲3��ÿ��5�� 
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

room::room()//���캯�� 
{
	strcpy(mesa.cname,"N");
	strcpy(mesa.cid,"N");
	strcpy(mesa.id,"N");
}

void room::menu(room rooms[][5])//�˵� 
{
	int a=0;
	do
	{
		cout<<"  ��ӭʹ�þƵ�ͷ�����ϵͳ  "<<endl
		<<"----------------------------"<<endl
		<<"*****���ӿͷ���Ϣ����1******"<<endl
		<<"*****ɾ���ͷ���Ϣ����2******"<<endl
		<<"*****��ʾ�ͷ���Ϣ����3******"<<endl
		<<"*****Ԥ���ͷ���������4******"<<endl
		<<"*****������ס��������5******"<<endl
		<<"*****����ס����������6******"<<endl
		<<"*****�����˷���������7******"<<endl
		<<"*****��ͳ�ơ���������8******"<<endl
		<<"*****�˳�������������9******"<<endl
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
					cout<<"��������Ҫɾ���ķ���ţ�"<<endl;
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
					cout<<"��������ס�ķ��ţ�"<<endl;
					int nn;
					cin>>nn;
					int x, y;
					x=nn/100;
					y=nn%100;
					rooms[x-1][y-1].mesa.gone=true;
					break;//5������ס 
				}
			case 6:
				{
					cout<<"������������"<<endl;
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

void room::addmessage(room rooms[][5])//1�����û���Ϣ 
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

void room::priceset(room rooms[][5])//���÷���۸� 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			rooms[i][j].mesa.price=(i+1)*100+(j+1)*10;
		}
	}
}

void room::rcmessage(room rooms)//����ס����Ϣ
{
	cout<<"������������"<<endl;
	cin>>mesa.cname;
	cout<<"���������֤���룺"<<endl;
	cin>>mesa.cid;
	cout<<"�����뷿��ţ�"<<endl;
	cin>>mesa.id;
}

void room::book(room rooms[][5])//4Ԥ���ͷ�
{
	cout<<"������ҪԤ���ķ���ţ������㣬ÿ����䣩��"<<endl;
	int record=0;
	int a=0;
	int b=0;
	cin>>record;
	a=record/100;
	b=record%100;
	rooms[a-1][b-1].rcmessage(rooms[a-1][b-1]);
	rooms[a-1][b-1].mesa.booked=true;
}

void room::delemessage(room &a,int record,room rooms[][5])//2,7�˷���ɾ���ͷ���Ϣ 
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

void room::show(room rooms[][5])//3��ʾ�ͷ���Ϣ 
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
				cout<<"����ţ�"<<rooms[i][j].mesa.id<<endl
				<<"�۸�"<<rooms[i][j].mesa.price<<endl
				<<"ס��������"<<rooms[i][j].mesa.cname<<endl
				<<"ס�����֤���룺"<<rooms[i][j].mesa.cid<<endl;
				if(rooms[i][j].mesa.booked)
				{
					cout<<"��Ԥ��"<<endl; 
				}
				else if(!rooms[i][j].mesa.booked)
				{
					cout<<"δԤ��"<<endl;
				}
				if(rooms[i][j].mesa.gone)
				{
					cout<<"����ס"<<endl;
				}
				else if(!(rooms[i][j].mesa.gone))
				{
					cout<<"δ��ס"<<endl;
				}
			}
		}
	}
	file.close();
}

void room::finding(char arr[],room rooms[][5])//6���������ҷ��� 
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
				cout<<"��Ӧ�����Ϊ��"<<rooms[i][j].mesa.id<<endl;
			}
		}
	}
	file.close();
}

void room::count(room rooms[][5])
{
	int a=0;
	int b=0;
	cout<<"����15������"<<endl;
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
	cout<<"��"<<a<<"�����䱻Ԥ����δ��ס"<<endl
	<<"��"<<b<<"����������ס"<<endl; 
}

int main()
{
	room rooms[3][5];
	room::priceset(rooms);
	room::menu(rooms);
	return 0;
}
