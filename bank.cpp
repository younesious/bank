#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

class Customer
{
	private :
		char Name[];
		int AccountNumber;
		int Situation;
		int Balance;
		
	public :
		Customer(int = 0,int = 0,int = 0,string n = "");
		void SetName(string );
		void SetAccountNumber(int );
		void SetSituation(int );
		void SetBalance(int );
		string getName();
		int getAccountNumber();
		int getSituation();
		int getBalance();
};

Customer::Customer(int an,int s,int b,string n)
{
	SetAccountNumber(an);
	SetSituation(s);
	SetBalance(b);
	SetName(n);
}
void Customer::SetName(string n)
{
	int l = sizeof(n) / sizeof(n[0]);
	if(l > 17)
		cout<<"Please enter string with fewer char...\n";
	n.copy(Name,l);
	Name[l] = '\0';
}
void Customer::SetAccountNumber(int an)
{
	AccountNumber = an;
}
void Customer::SetSituation(int s)
{
	Situation = s;
}
void Customer::SetBalance(int b)
{
	Balance = b;
}
string Customer::getName()
{
	return Name;
}
int Customer::getAccountNumber()
{
	return AccountNumber;
}
int Customer::getSituation()
{
	return Situation;
}
int Customer::getBalance()
{
	return Balance;
}

void EnterData()
{
	Customer ob;
	int AccountNumber,Balance;
	string Name;

	fstream f1("bank.dat");
	if(!f1)
		exit(0);
		
	cout<<"Please enter AccountNumber(in form of(***)from 000 to 999).\n";
	cin>>AccountNumber;
	cout<<"Please enter (name/balance)...\n";
	cin>>Name>>Balance;
	ob.SetName(Name);
	ob.SetSituation(1);
	ob.SetBalance(Balance);
	ob.SetAccountNumber(AccountNumber);
	
	f1.seekp(sizeof(ob) * (ob.getAccountNumber()-1),ios::beg);
	f1.write((char *)&ob,sizeof(ob));
	
	f1.close();
}
void TransAction()
{
	int an,amount;
	char ans;
	Customer ob;
	
	cout<<"Please enter your AccountNumber:\n";
	cin>>an;
	cout<<"Do you want to withdraw your money?(w/d)\n";
	cin>>ans;
	
	fstream f2("bank.dat");
	if(!f2)
		exit(0);
	f2.seekg((an - 1) * sizeof(ob),ios::beg);
	f2.read((char *)&ob,sizeof(ob));
	
	if(ans == 'w')
	{
		cout<<"enter amount:\n";
		cin>>amount;
		if(amount <= ob.getBalance())
		{
		ob.SetBalance(ob.getBalance() - amount);
		f2.seekp((an - 1) * sizeof(ob),ios::beg);
		f2.write((char *)(&ob),sizeof(ob));
		cout<<"operation successfuly done.\n";
		}
		else
			cout<<"Not enough balance.\n";
	} else if(ans == 'd')
		{
			cout<<"enter amount:\n";
			cin>>amount;
			ob.SetBalance(ob.getBalance() + amount);
			f2.seekp((an - 1) * sizeof(ob),ios::beg);
			f2.write((char *)(&ob),sizeof(ob));
			cout<<"operation successfuly done.\n";
		}
		else
			cout<<"Invalid answer.\n";
			
		f2.close();	
}
/*
void MaxBalance()
{
	Customer ob;
	int max = 0;
	int flag = 0;
	
	fstream f3("bank.dat");
	if(!f3)
		exit(0);
		
	for(int i = 0;i < 1000;i++)
	{
	f3.seekg(sizeof(ob) * (i),ios::beg);
	f3.read((char *)&ob,sizeof(ob));
	
	if(ob.getBalance() > max)
		{
			max = ob.getBalance();
			flag = i;
		}
	}
	f3.seekg(sizeof(ob) * (flag - 1),ios::beg);
	f3.read((char *)& ob,sizeof(ob));
	
	cout<<"Information person have max balance:\n";
	cout<<"Name : "<<ob.getName()<<endl;
	cout<<"AccountNumber : "<<ob.getAccountNumber()<<endl;
	cout<<"Balance : "<<ob.getBalance()<<endl;
	cout<<"Situation : "<<ob.getSituation()<<endl<<endl;	
	
	f3.close();
}
*/
void MaxBalance()
{
	Customer ob;
	int max = 0,an = 1;
	
	fstream f3("bank.dat");
	if(!f3)
		exit(0);
	f3.read((char *)&ob,sizeof(ob));
		
	cout<<"Max balance information:\n";
	
	while(f3 && !f3.eof())
	{
		if(ob.getBalance() > max)
		{
			max = ob.getBalance();
			an = ob.getAccountNumber();			
		}
		f3.read((char *)&ob,sizeof(ob));
	}	
	
	f3.seekg((an - 1) * sizeof(ob),ios::beg);
	f3.read((char *)&ob,sizeof(ob));
	
	cout<<"Name : "<<ob.getName()<<endl;
	cout<<"AccountNumber : "<<ob.getAccountNumber()<<endl;
	cout<<"Situation : "<<ob.getSituation()<<endl;
	cout<<"Balance : "<<ob.getBalance()<<endl;
	
	f3.close();
}
void CloseAccount()
{
	int an;
	Customer ob;
	cout<<"Please enter AccountNumber should close their account.\n";
	cin>>an;
	
	fstream f4("bank.dat");
	if(!f4)
		exit(0);
	f4.seekg((an - 1) * sizeof(ob),ios::beg);
	f4.read((char *)&ob,sizeof(ob));
	
	ob.SetSituation(0);
	
	f4.seekp((an - 1) * sizeof(ob),ios::beg);
	f4.write((char *)&ob,sizeof(ob));
	f4.close();
}
void ReportData()
{
	Customer ob;
	
	cout<<"Name\t  AccountNumber\t    Situation\t      Balance";
	cout<<"\n-------------------------------------------------------------------\n";
	
	fstream f5("bank.dat");
	if(!f5)
		exit(0);
	f5.read((char *)&ob,sizeof(ob));
	
	while(f5 && !f5.eof())
	{
		if(ob.getSituation() == 1)
		{
			cout<<ob.getName()<<"\t\t";
			cout<<ob.getAccountNumber()<<"\t\t";
			cout<<ob.getSituation()<<"\t\t";
			cout<<ob.getBalance()<<endl;
		}
		f5.read((char *)&ob,sizeof(ob));
	}
	
	f5.close();
}
void ReportAccount()
{
	int an;
	Customer ob;
	cout<<"Please enter your AccountNumber:\n";
    cin>>an;
    
    fstream f6("bank.dat");
    if(!f6)
    	exit(0);
    	
    f6.seekg((an - 1) * sizeof(ob),ios::beg);
    f6.read((char *)&ob,sizeof(ob));
    
    cout<<"Name : "<<ob.getName()<<endl;
	cout<<"AccountNumber : "<<ob.getAccountNumber()<<endl;
	cout<<"Situation : "<<ob.getSituation()<<endl;
	cout<<"Balance : "<<ob.getBalance()<<endl;
	
	f6.close();	
}
void Exit()
{
	exit(0);
}

void Menu()
{
	while(true)
	{
		int op;
		cout<<"Hello,Good time.\nPlease choose your operations(enter number):\n";
		cout<<"(1)Enter date"<<"\t\t(2)Trans action\n";
		cout<<"(3)Max balance"<<"\t\t(4)Close account\n";
		cout<<"(5)Report data"<<"\t\t(6)Report account\n";
		cout<<"(7)Exit\n\n";
		cin>>op;
	
		switch(op)
		{
			system("cls");
			case 1 : EnterData();
			break;
			 
			case 2 : TransAction();
			break;
			
			case 3 : MaxBalance();
			break;
			
			case 4 : CloseAccount();
			break;
			
			case 5 : ReportData();
			break;
			
			case 6 : ReportAccount();
			break;
			
			case 7 : Exit();
			break;
			
			default : cout<<"Error\n";
			exit(0);
		}
		
	}
}

int main()
{
	
	Menu();
	
	return 0;
}
