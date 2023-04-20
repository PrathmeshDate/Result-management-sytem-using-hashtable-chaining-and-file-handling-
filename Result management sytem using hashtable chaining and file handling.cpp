//Result management system using Hashtable chaining and file handling.

#include<iostream>
#include<iomanip>
#include<fstream>
#define MAX 1000
using namespace std;

struct node
{
	int roll_no;
	string subject;
	int marks;			//Creating the node 
	
	node *next;
};
//End of struct node
class Hashtable
{
	node *ht[MAX];
	public:
		Hashtable()
			{
				for(int i=0;i<MAX;i++)
					{
						ht[i]=new node;
						ht[i]->next=NULL;
					}
			}
			int hash(int roll);//Function to generate index .
			void insert(int roll,string sub,int Marks);//Function to insert values in hashtable from file.
			void find(int roll);
			int sumOfNodes(int roll);//Function to find total marks obtained.
			void wrighttofile();//Function to store data in file.
			void readfromfile();//Function to read data from file.	
			void display();		
};
//End of class hashtable.

int n;//Declaring n (total number of students) globally to access from any function.

int Hashtable::hash(int roll)
{
	int pos = (roll%MAX);
	return pos;
}//Hash function to generate hash value
void Hashtable::insert(int roll,string sub,int Marks)
{
	int pos;
	pos=hash(roll);
	node *current;
	current = new node;
	current->roll_no=roll;		
	current->subject=sub;
	current->marks=Marks;
	current->next=ht[pos]->next;
	ht[pos]->next=current;
}//Insert function to insert data in hashtable
void Hashtable::readfromfile()
{
	int roll,mm3,mmp,mdsa,mse,mppl;
	string sub1="M3";
	string sub2="MP";
	string sub3="DSA";
	string sub4="SE";
	string sub5="PPL";
	ifstream ROLL1;
	ROLL1.open("rollno.txt");
 	ifstream M31;
	M31.open("m3.txt");
	ifstream MP1;
	MP1.open("mp.txt");
	ifstream DSA1;
	DSA1.open("dsa.txt");
	ifstream SE1;
	SE1.open("se.txt");
	ifstream PPL1;
	PPL1.open("ppl.txt");
	ifstream noOfStudents("noOfstudents.txt");	
	noOfStudents>>n;

	for(int i=0;i<n;i++)
	{
		ROLL1>>roll;
		M31>>mm3;
		MP1>>mmp;
		DSA1>>mdsa;
		SE1>>mse;
		PPL1>>mppl;
		insert(roll,sub1,mm3);
		insert(roll,sub2,mmp);
		insert(roll,sub3,mdsa);//Calling insert function to store data which is read from file.
		insert(roll,sub4,mse);
		insert(roll,sub5,mppl);

	}
	ROLL1.close();
	M31.close();
	MP1.close();
	DSA1.close();//Closing all opened files.
	SE1.close();
	PPL1.close();
	
}//Function to read data from file.
void Hashtable::wrighttofile()
{
  // Create and open a text file
	int roll,mm3,mmp,mdsa,mse,mppl;
	
	ofstream ROLL("rollno.txt");
	ofstream M3("m3.txt");
	ofstream MP("mp.txt");
	ofstream DSA("dsa.txt");
	ofstream SE("se.txt");
	ofstream PPL("ppl.txt");
	for(int i=0;i<n;i++)
	{
		cout<<"Enter roll number of student "<<i+1<<":"<<endl;
		cin>>roll;
	
		ROLL <<roll<<endl;
		
		cout<<"Enter marks of M3 of roll no "<<roll<<":"<<endl;
		cin>>mm3;
		M3 <<mm3<<endl;

		cout<<"Enter marks of MP of roll no "<<roll<<":"<<endl;
		cin>>mmp;
		MP <<mmp<<endl;

		cout<<"Enter marks of DSA of roll no "<<roll<<":"<<endl;
		cin>>mdsa;
		DSA <<mdsa<<endl;

		cout<<"Enter marks of SE of roll no "<<roll<<":"<<endl;
		cin>>mse;
		SE <<mse<<endl;

		cout<<"Enter marks of PPL of roll no "<<roll<<":"<<endl;
		cin>>mppl;
		PPL <<mppl<<endl;
	}
	ROLL.close();
	M3.close();
	MP.close();
	DSA.close();//Closing all files after writing.
	SE.close();
	PPL.close();
}//Function to write data to file.
int Hashtable::sumOfNodes(int roll)
{
    int pos;
	int sum;
	node *current;
	pos = hash(roll);
	current = ht[pos]->next;
    while (current != NULL)
	{ 
        sum += current->marks;
        current = current->next;
    }
  
    return sum;
}//Function to calculate total marks obtained out of 500
void Hashtable::display()
{
	cout<<"Displaying entire database."<<endl;
	cout<<"\nRoll No|Subject|Marks Obtained|"<<endl;
    for(int i=0;i<MAX;i++)
    {
      
        node *temp;
        temp = ht[i]->next;
        while(temp!=NULL)
        {
            cout<<"  "<<temp->roll_no<<"  :  "<<temp->subject<<"  :  "<<temp->marks<<endl;
            temp = temp->next;
        }
    }
}//Display function to display entire stored record
void Hashtable::find(int roll)
{
	int pos;
	node *current;
	pos = hash(roll);
	current = ht[pos]->next;
	if(current==NULL)
	{
		cout<<"No records found for entered roll number."<<endl<<endl;
	}//If roll number not found in record
	else
	{
		cout<<"\n--------------------------------------------------"<<endl;
		cout<<"Displaying result for Seat Number: "<<roll;
		cout<<"\n--------------------------------------------------"<<endl;
		cout<<"\nSubject"<<" | "<<"Marks Obtained";
		cout<<"\n--------------------------------------------------"<<endl;
		while(current != NULL)
			{
				cout<<"   "<<left<<setw(5)<<current->subject<<"|";
				cout<<right<<setw(7)<<current->marks<<endl;	
				current = current->next;
			}
		cout<<"\n--------------------------------------------------"<<endl;
		float per=sumOfNodes(roll);
		cout<<"Total marks obtained out of 500 : "<<per<<endl;
		cout<<"Percentage obtained: "<<per/5<<"%"<<" ";
		if(per>=200)
		{
			cout<<"Result:PASS.";
		}
		else
		{
			cout<<"Result:FAIL.";
		}
		cout<<"\n--------------------------------------------------"<<endl;
	}//If number found in record.
}//End of find function.
int main()
{	
	Hashtable H;
	int choice;
	int ROLL;
	string Sub;
	int MARKS;
	int choice1;
	H.readfromfile();//When program runs second time to read data from existing record files.
	cout<<"\t\t\t ****Welcome to Result management system****"<<endl;
	cout<<"Enter 1 for administrator login."<<endl;
	cout<<"Enter 2 to view student result."<<endl;
	cout<<"Enter your choice:";
	cin>>choice1;
	if(choice1==1)
	{
		string usernm;
		int choice;
		cout<<"Enter your username:"<<endl;
		cin>>usernm;
		if(usernm == "prd2002" || usernm == "rmg2002" || usernm == "ddl2002" || usernm == "kmp2002" || usernm == "pml2002")
		{	string pass;
			cout<<"Enter your password: "<<endl;
			cin>>pass;
			if(pass=="admin")
			{
				cout<<"Permission Granted!"<<endl;
				while(true)
				{
					cout<<"## Administrator Menu ##"<<endl;
					cout<<"(1)Insert students Data"<<endl;
					cout<<"(2)Store data from file to hashtable."<<endl;
					cout<<"(3)View student result for verification."<<endl;
					cout<<"(4)Display entire record."<<endl;
					cout<<"(5)Go back to main menu."<<endl;
					cout<<"(6)Exit result system."<<endl;
					cout<<"Enter your choice:"<<endl;
					cin>>choice;
					if(choice==1)
					{	
						ofstream noOfStudents("noOfstudents.txt");
						cout<<"How many students data do you want to add? "<<endl;
						cin>>n;
						noOfStudents <<n<<endl;
						noOfStudents.close();
						H.wrighttofile();					
					}
					else if (choice==2)
					{
						H.readfromfile();
						cout<<"Data stored successfully in hashtable."<<endl;
					}
					
					else if(choice==3)
					{
						int roll;
						cout<<"Enter roll number to find result:"<<endl;
						cin>>roll;
						H.find(roll);
					}
					else if(choice==4)
					{
						H.display();
					}
					else if(choice==5)
					{
						cout<<"Returning back to main menu."<<endl;
						main();//Calling main function to returning back to main function.
					}
					else if(choice==6)
					{
						exit(0);
					}
					else
					{
						cout<<"Wrong choice entered.Enter correct choice again!!"<<endl;
					}
				}
			}
		}
		else
		{
			cout<<"Wrong username or password!!!Terminating session."<<endl;
			exit(0);
		}
	}
	else if(choice1==2)
	{
			
		int choice;
		while(true)
		{
			cout<<"## Result Dashboard Menu ##"<<endl;
			cout<<"(1)View your result"<<endl;
			cout<<"(2)Go back to main menu."<<endl;
			cout<<"(3)Exit result system"<<endl;
			cout<<"Enter your choice:"<<endl;
			cin>>choice;
			if(choice==1)
			{
				int roll;
				cout<<"Enter roll number to find result:"<<endl;
				cin>>roll;

				

				H.find(roll);
			}
			else if(choice==2)
			{
				main();//Calling main function to return back to main menu.
			}
			else if(choice==3)
			{
				exit(0);
			}
			else
			{
				cout<<"Wrong choice entered.Enter correct choice again!!"<<endl;
			}
		}

	}
}//End of main function.
