#include<iostream>
#include<string>

using namespace std;

void quickQurt(int arr[],int left,int right)
{
	if(left>=right)return;
	int i=left;
	int j=right;
	int key=arr[left];
	while(i<j)
	{
		while(i<j&&arr[j]>=key)j--;
		if(i<j)
		{
			arr[i]=arr[j];
			i++;
		}
		while(i<j&&arr[i]<key)i++;
		if(i<j)
		{
			arr[j]=arr[i];
			j--;
		}
	}
	arr[i]=key;
	quickQurt(arr,left,i-1);
	quickQurt(arr,i+1,right);
}

int main()
{
	int arr[10];
	for(int i=0;i<10;i++)
	{
		cin>>arr[i];
	}
	for(int i=0;i<10;i++)
	{
		cout<<arr[i];
		if(i!=9)cout<<" ";
	}
	cout<<endl;
	quickQurt(arr,0,9);
	for(int i=0;i<10;i++)
	{
		cout<<arr[i];
		if(i!=9)cout<<" ";
	}
	cout<<endl;
	return 0;
}


