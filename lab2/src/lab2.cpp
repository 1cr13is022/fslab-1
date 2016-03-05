#include <iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<string>
using namespace std;

class student{
	public:string usn;
	string name;
	int sem;
	string branch;
	public:string buffer;
	public:fstream f1;

	public:void pack()
	{
		string temp,sem1;
		stringstream out;
		out<<sem;
		sem1=out.str();
		temp.erase();
		temp=usn+'|'+name+'|'+sem1+'|'+branch;
		if(temp.length()<100)
		{
			for(int i=temp.length()+1;i<=100;i++)
			{
				temp+="$";
			}
		}
		buffer+=temp;
	}

	public:void datain()
		{
			cout<<"Enter USN: ";
			cin>>usn;
			cout<<"Enter Name: ";
			cin>>name;
			cout<<"Enter Semester: ";
			cin>>sem;
			cout<<"Enter Branch: ";
			cin>>branch;
		}

	void write()
		{
			f1.open("file.txt",ios::out|ios::app);
			f1<<buffer;
			f1.close();
		}

	public:int * unpack()
	{
		int i=0;
		int *p = new int[4];
		while(buffer[i]!='|')
		{
			usn=buffer[i];
			i++;
			p[0]=f1.tellp();
		}
		while(buffer[i]!='|')
		{
			name=buffer[i];
			i++;
			p[1]=f1.tellp();
		}
		while(buffer[i]!='|')
		{
			sem=buffer[i];
			i++;
			p[2]=f1.tellp();
		}
		while(buffer[i]!='$')
		{
			branch=buffer[i];
			i++;
			p[3]=f1.tellp();
		}
		return p;
	}




	void modify();
	void del();

	int search(string key)
	{
		int *p;
		string sem1;
		int flag=0,pos;
		char buffer[101];
		f1.open("file.txt",ios::in);
		while(!f1.eof())
		{
		  f1.read(buffer,100);
		  pos=f1.tellp();
		  p=unpack();
		  if(key==usn)
		  {
			  flag=1;
			  return p[0];
		  }
		  if(key==name)
		  {
			  flag=1;
			  return p[1];
		  }
		  stringstream out;
		  out<<sem;
		  sem1=out.str();
		  if(key==sem1) //convert sem to string
		  {
			  flag=1;
			  return p[2];
		  }
		  if(key==branch)
		  {
			  flag=1;
			  return p[3];
		  }

		}
		return pos;
	}

};

int main() {
	int choice,flag;
	string key;
	student s;
	while(1)
	{
		cout<<"Enter 1.Insert 2.search 3.modify 4.Delete 5.Exit";
		cin>>choice;
		switch(choice)
		{
		case 1:s.datain();
			   s.pack();
			   s.write();
			   break;

		case 2:cout<<"\nEnter key to be searched for: ";
				cin>>key;
				flag=s.search(key);
				break;

		/*case 3:s.modify();
			   break;
		case 4:s.del();
			   break; */

		case 5:exit(0);
				break;

		default:cout<<"\nWrong input!";
		}
	}
	return 0;
}
