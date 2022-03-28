/*	<<<...RESTAURANT MANAGEMENT SYSTEM....>>>

	SUBMITTED TO : DR. VAIBHAV VYAS
	
	SUBMITTED BY : 
					1) SAMRIDHI SETHI - 1913087
					2) SANIYA ASTHANA - 1913088
*/


#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<cstdio>
#include<stdlib.h>
#include<iomanip>

using namespace std;

class restaurant
{	
	public:
		char dish[50];
    	int key;
    	float price;
	    void create();
	    void Search();
	    void display();
	    void update();
	    void del();
	    void admin();
}r;

//customer class inheriting restaurant class publicly in single inheritance 
class customer : public restaurant
{
	public :
		char d[50];
		float p,amount;
		int qty;
	    void bill();
	    void showbill();
	    void dish_menu();
}rd;


//To create or add new dish in the list
void restaurant :: create()
{
	char a;
	int k;	
	fstream obj;
	
	top:
	do 
	{
		obj.open("restaurant.txt", ios::in | ios::binary);
		
		cout<<"ENTER THE DISH KEY : ";
		cin>>k;
		
		while(obj.read((char*)&r, sizeof(r)))
	    {
	        if(r.key==k)
	        {
	            cout<<"Key already exists"<<endl;
	            obj.close();
	        	goto top;
	        }
	    }
	    
		obj.close();
		
		obj.open("restaurant.txt", ios::app | ios::binary);
		
		r.key=k;
		
		cin.ignore();
		cout<<"ENTER THE DISH NAME : ";
		gets(r.dish);
		cout<<"ENTER THE DISH PRICE : ";
		cin>>r.price;
		
		obj.write((char*)&r, sizeof(r));
		
		cout<<endl<<"Do you want to add an other [y/n] : ";
		cin>>a;
		cout<<endl;
		
		obj.close();
		
	}while(a!='n');
}

//To display all dishes in our menu list
void restaurant :: display()
{
	int c = 0;
	fstream obj;
	
	obj.open("restaurant.txt", ios::in | ios::binary);
	
	cout<<setw(100)<<"----------------------------------------------------------------------------"<<endl;
	cout<<setw(57)<<"\tKey\t\tDISH NAME\t\tPRICE"<<endl;
	
	while(obj.read((char*)&r, sizeof(r)))
	{
	    cout<<setw(42)<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
	    c++;
	}
	cout<<setw(100)<<"-----------------------------------------------------------------------------"<<endl;
	
	if(c==0)
	{
		cout<<setw(70)<<"List is empty"<<endl;
	}
	
	obj.close();
}


//To search any dish from file 
void restaurant::Search()
{
	int a, c = 0;
	char ar[50];
	fstream obj;
	
	obj.open("restaurant.txt", ios::in);
	
	cout<<"Enter the dish name : ";
	cin>>ar;
	
	while(obj.read((char*)&r, sizeof(r)))
	{
	   if(strcmp(r.dish,ar)==0)
	   {
			cout<<endl;
			cout<<setw(70)<<"Dish is Available\n\n";
			cout<<setw(40)<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
			c++;
		}
	}
	
	/*cout<<"Enter the dish key:";
	cin>>a;
	
	while(obj.read((char*)&r,sizeof(r)))
	{
	   if(r.key==a)
	   {
		    cout<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
		    c++;
		}
	}*/
	
	if(c==0)
	{
		cout<<setw(70)<<"Dish Not Available"<<endl;
	}
	
	obj.close();
}


//To update a dish record in in file
void restaurant :: update()
{
	int a, p, c = 0;
	fstream obj;
	
	obj.open("restaurant.txt", ios::in | ios::out | ios::binary);
	
	cout<<"Enter the dish key : ";
	cin>>a;
	cout<<endl<<endl;
	
	obj.seekg(0);
	while(obj.read((char*)&r, sizeof(r)))
	{
		if(r.key==a)
		{
			cout<<endl;
			cout<<setw(70)<<"Destination record : \n"<<endl;
			cout<<setw(40)<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
			
			p = int(obj.tellg())-(sizeof(r));
			obj.seekp(p);
			
			cout<<"\n\nENTER THE NEW DETAILS :- \n\n";
			
			cout<<"ENTER THE DISH KEY : ";
			cin>>r.key;
			cin.ignore();
			cout<<"ENTER THE DISH NAME : ";
			gets(r.dish);
			cout<<"ENTER THE DISH PRICE : ";
			cin>>r.price;
			
			obj.write((char*)&r, sizeof(r));
			c++;
		}
		
	}
	
	if(c==0)
	{
		cout<<setw(70)<<"Dish Not Available"<<endl;
	}
	obj.close();
}


//Any dish can b deleted from file if you press delete option and then key/code of dish.
void restaurant :: del()
{
	int a, c;
	fstream obj, obj1;
	
	obj.open("restaurant.txt", ios::in | ios::binary);
	obj1.open("temp.txt", ios::app | ios::binary);
	
	cout<<"Enter the dish key : ";
	cin>>a;
	
	while(obj.read((char*)&r, sizeof(r)))
	{
		if(r.key==a)
		{
		    c++;
		    cout<<setw(40)<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl<<endl;
		    cout<<setw(73)<<"Destination record is deleted"<<endl<<endl;
		}
		
		if(r.key!=a)
		{
		    obj1.write((char*)&r, sizeof(r));
		}
	}
	
	obj.close();
	obj1.close();
	
	if(c==0)
	{
		cout<<setw(70)<<"Dish Not Found"<<endl;
	}
	
	remove("restaurant.txt");
	rename("temp.txt","restaurant.txt");
}


//Displays Admin submenu and calls other functions
void restaurant :: admin()
{
	char a;
	
	do
	{
		cout<<"\n\n\t\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"\t\t\t\t\t\t                       "<<endl;
		cout<<"\t\t\t\t\t\t  1) ADD DISH          "<<endl;
		cout<<"\t\t\t\t\t\t  2) DISPLAY           "<<endl;
		cout<<"\t\t\t\t\t\t  3) SEARCH A DISH     "<<endl;
		cout<<"\t\t\t\t\t\t  4) UPDATE            "<<endl;
		cout<<"\t\t\t\t\t\t  5) DELETE            "<<endl;
		cout<<"\t\t\t\t\t\t  0) EXIT TO MAIN MENU "<<endl;
		cout<<"\t\t\t\t\t\t                       "<<endl;
		cout<<"\t\t\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		
		cout<<"\t\t\t\t\t\tEnter Your Choice : ";
		cin>>a;
		cout<<endl<<endl;
		
		switch(a)
		{
			case '0':break;
			
			case '1':create();
					break;
					
			case '2':display();
			    	break;
			    
			case '3':Search();
					break;
			    
			case '4':update();
			    	break;
			    
			case '5':del();
			    	break;
	    }
	    
	}while(a!='0');
}


//To take order from the customer
void customer :: bill()
{
	int a, c = 0;
	char ch;
	float total = 0;
	fstream obj, obj1;


	dish_menu();
	cout<<"\n\nENTER YOUR ORDER: \n";
	
	obj1.open("bill.txt", ios::out | ios::binary);
	
	do
	{
		obj.open("restaurant.txt", ios::in | ios::binary);
		cout<<endl;
		
		cout<<"Enter the dish key : ";
		cin>>a;
		
		while(obj.read((char*)&r, sizeof(r)))
		{
			if(r.key==a)
			{
				c++;
				
				cout<<"Enter the quantity : ";
				cin>>rd.qty;
				
				rd.amount=rd.qty*r.price;
				
				cout<<setw(45)<<r.dish<<"\t\t"<<r.price<<"*"<<rd.qty<<"\t\t"<<rd.amount<<endl;
				strcpy(rd.d,r.dish);
				rd.p=r.price;
				
				obj1.write((char*)&rd,sizeof(rd));
				total=total+rd.amount;
			}
		}
		
		if(c==0)
		{
			cout<<setw(70)<<"Dish Not Available"<<endl;
		}
		
		cout<<"\nDo you want to order more [y/n] : ";
		cin>>ch;
		
		obj.close();
		
	}while(ch!='n');
	
	obj1.close();
	
	cout<<endl<<endl;
	cout<<"***************************************************************************************************************************************"<<endl;
	cout<<"                                                       BILL                                                        "<<endl;
	cout<<"***************************************************************************************************************************************"<<endl;
	
	showbill();
	
	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t   TOTAL="<<total<<"\t\t\t\t\t\t      "<<endl;
	cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}


//To display bill of customer's order
void customer :: showbill()
{
    fstream obj;
    
    obj.open("bill.txt",ios::in|ios::binary);
    
    cout<<"\t\t\tDISH NAME\t\tPRICE\t\tQTY\t\tAMOUNT"<<endl;
    
    while(obj.read((char*)&rd,sizeof(rd)))
    {
        cout<<"\t\t\t"<<rd.d<<"\t\t\t"<<rd.p<<"\t\t"<<rd.qty<<"\t\t"<<rd.amount<<endl;
    }
    
    obj.close();
}

//Displays menu to the customer - ( By Default)
void customer::dish_menu()
{
	fstream obj;
	
	obj.open("restaurant.txt",ios::in|ios::binary);
	
	cout<<endl<<endl;
	cout<<setw(100)<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<setw(62)<<"MENU \n\n";
	while(obj.read((char*)&r,sizeof(r)))
	{
	    cout<<setw(48)<<r.key<<") "<<r.dish<<"-------RS  "<<r.price<<endl;                         
	}
	cout<<setw(100)<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	
	obj.close();
}

int main()
{
    char a;
    customer obj;
    
    cout<<"\t\t\t\t   ..........WELCOME TO SAMSAN RESTAURANT.........."<<endl<<endl;
    
    do
    {
        cout<<"\n\t\t\t\t\t\t-------------------"<<endl;
        cout<<"\t\t\t\t\t\t|                  |"<<endl;
        cout<<"\t\t\t\t\t\t|    1)Admin       |"<<endl;
        cout<<"\t\t\t\t\t\t|    2)Customer    |"<<endl;
        cout<<"\t\t\t\t\t\t|    0)Exit        |"<<endl;
        cout<<"\t\t\t\t\t\t|                  |"<<endl;
        cout<<"\t\t\t\t\t\t--------------------"<<endl;
        
        cout<<"\t\t\t\t\t\tSelect a Menu Option : ";
        cin>>a;
        
        switch(a)
        {
	        case '0':
	            break;
	        case '1':obj.admin();
	            	break;
	            	
	        case '2':obj.bill();
	            	break;
        }
        
    }while(a!='0');
    
    return 0;
}




