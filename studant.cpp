#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
 
////////////////////////////////////////////////////////// STRUCTURE /////////////////////////////////////////////////////////////////////////////////////////////

struct study
{
	char subject[20];										//NAME SUBJECT + DIFFICULTY
	int hardness;      
	int slot;
	float mslot;    
	char alpha;                               
};


struct naming
{
	char first[10];											// NAME = LAST + FIRST
	char last[10];
};


struct student
{
	
	naming name;                                            //STUDENT PROFILE
	char mmode[20];
	study course[];
	int numsubject;
	char mode;
	
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////// FUNCTION DECLARATION ////////////////////////////////////////////////////////////////////////////////////

void input(student&,int&);                          		//INPUT DETAIL OF STUDENT --->USE POINTER,STRUCT
void slotcalculation(student&,int);                  		//CALCULATION TOTAL SLOT FOR EACH SUBJECT BASED ON DIFFICULTY
void scheduler(char[],student&,int);						//ARRANGE SUBJECT INTO A SCHEDULE BASED ON NUMBER OF SLOT ALLOCATED
void saveschedule(char[],student&,int&,ofstream&,int&);		//SAVE SCHEDULE AND DETAILS USING I/O FILE
void readdata(int& ,student& ,ifstream& ,char[][3],int&);	//READ SAVED SCHEDULE AND DETAILS FROM I/O FILE
void viewschedule(char[][3],int,student&); 					//VIEW SCHEDULE
void searchschedule(int ,student& ,char[][3]);				//SEARCH SCHEDULE SLOT
void minmax(int,student&);									//VIEW HARDEST AND EASIEST SUBJECT
void averagediff(int,student&);								//CALCULATE AND VIEW AVERAGE DIFFICULTY OF ALL SUBJECT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////// MAIN BODY ///////////////////////////////////////////////////////////////////////////////////////
 
int main()
{
	int numexecute;
	int totalstudent;
	int numsubject;
	char schedule[21];
	char Schedule[7][3];
	char service;
	student pupil;	
	ifstream reader("filebaru.h");
	char find[10];
	reader>>numexecute;                  //GET HOW MANY TIMES PROGRAM EXECUTED
	reader.close();
	
    
if(numexecute==0)                        // CONDITION IF FIRST TIME PROGRAM EXECUTED
{


	input(pupil,numsubject);	                    //INPUT DETAILS + CALCULATE SLOT + ARRANGE SCHEDULE + SAVE SCHEDULE
	slotcalculation(pupil,numsubject);
	scheduler(schedule,pupil,numsubject);
	numexecute+=1;	
	ofstream writer("filebaru.h");
	saveschedule(schedule,pupil,numexecute,	writer,numsubject);
	 writer.close();
	 
    cout<<"YOUR SCHEDULE HAS BEEN SAVED , RE-EXECUTE TO VIEW YOUR SCHEDULE"<<endl;
	 
	return 0;
}

else                     									 //CONDITION IF IT IS NOT FIRST TIME PROGRAM BEING EXECUTED
{  	
	ifstream reader("filebaru.h");           
	readdata(numsubject,pupil,reader,Schedule,numexecute);
	reader.close();
															//  READ FILE + VIEW SCHEDULE + VIEW MIN MAX + VIEW AVERAGE HARDNESS
	

     
    viewschedule(Schedule,numsubject,pupil);
   
	minmax(numsubject,pupil);
	
	averagediff(numsubject,pupil);
	


   
cout<<"any service you wish to proceed ?(R-reset // S-Search schedule // Else-quit) :";	 //CHECK IF USER WANT TO "EXIT" OR "SEARCH SCHEDULE" OR "RESET ALL DATA"
	cin>>service;
		if (service=='R')
			{
				numexecute=0;
				ofstream writer("filebaru.h");            
				writer<<numexecute<<endl;               //save file to folder	
	
			}
		if (service=='S')
			{
				searchschedule(numsubject,pupil,Schedule);
			}
		
	
	
			
	}
			
			 



}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////// INPUT DATA ////////////////////////////////////////////////////////////////////////////////////////////

void input(student &pupil,int &numsub) 
{   char alph[10]={'a','b','c','d','e','f','g','h','i','j'};
	char mode;
	cout<<"WELCOME TO STUDENT FINAL EXAM PREPARATION SCHEDULING SYSTEM "<<endl;
	cout<<"THIS SYSTEM IS DESIGNED TO ARRANGE STUDY SCHEDULE FOR THE UPCOMING STUDY WEEK "<<endl;
	cout<<"THE SCHEDULE ARRANGED BY THIS SYSTEM IS BASED ON THE DIFFICULTY OF THE PARTICULAR SUBJECT THAT YOU INSERT"<<endl<<endl;
	cout<<"PLEASE FILL IN THE DETAILS BELOW :\n____________________________________________________________________"<<endl;

	cout<<"enter your first name :";
	cin>>pupil.name.first;
	cout<<"enter your last name :";                               //input of student details
	cin>>pupil.name.last;	
	cout<<"Are you an early bird or a night owl ? (B/O): ";
	cin>>pupil.mode;

	cout<<"How many subject you pursue this semester (max = 10): ";     //get and return number of subject 
	cin>>numsub;
 
    cout<<endl;   
	for (int x=0;x<numsub;x++)
		{   cin.ignore();
			cout<<"Subject Code (max 6 char):";
			cin.getline(pupil.course[x].subject,20);
			pupil.course[x].alpha=alph[x];
			cout<<"Difficulty (1 to 10):";
			cin>>pupil.course[x].hardness;
			cout<<endl;   
		}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////// CALCULATE SLOT FOR EACH SUBJECT ////////////////////////////////////////////////////////////////////

void slotcalculation(student &pupil,int numsub)     
{	

	int holdm;
	float holdn;
	float total=0;
	int totalslot=0;
	char hold[20],holdA;
	int arr[numsub];

	for(int y=0;y<numsub;y++)
	{ 		
		
		total+=1+y;
			for (int x=0;x<numsub-1;x++)
			{
	
	
			if(pupil.course[x].hardness>pupil.course[x+1].hardness)         //21 slots ; 50% evenly for all subject ; 50% be divided based on the difficulty
				{ 
		 			strcpy(hold,pupil.course[x].subject);
						strcpy(pupil.course[x].subject,pupil.course[x+1].subject);
							strcpy(pupil.course[x+1].subject,hold);
					
					holdm = pupil.course[x].hardness;
			  			pupil.course[x].hardness= pupil.course[x+1].hardness;
			   				pupil.course[x+1].hardness=holdm;
			   				
			   		holdA = pupil.course[x].alpha;
			  			pupil.course[x].alpha= pupil.course[x+1].alpha;
			   				pupil.course[x+1].alpha=holdA;
					
				}
					
	
		
			}
			
	}
	
	

	

    for(int x=0;x<numsub;x++)
	{
		  	
		pupil.course[x].slot = (10.5/numsub)+((x+1)/total*10.5);
			pupil.course[x].mslot = ((10.5*(x+1)/total)-int(10.5*(x+1)/total))*10;
			totalslot+=pupil.course[x].slot;
					
    }
         
   	
    if(totalslot<21)
    {	
    	
    	for (int x=0;x<numsub;x++)
    	{
    		arr[x]=x;
    		
		}
		
		
	for (int y=0;y<numsub;y++)
	{

		for (int x=0;x<numsub-1;x++)
		{
			if(pupil.course[x].mslot<pupil.course[x+1].mslot)
			{
			   
			  holdn = arr[x];
			  	arr[x]= arr[x+1];
			   		arr[x+1]=holdn;
			}
			
		}
    }
    int lim=totalslot;
	    for(int x=0;x<(21-lim);x++)
	    {
	    	pupil.course[arr[x]].slot+=1;
	    		
	    	
	    	totalslot+=1;
	    	
		}
    	
	
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////// ARRANGE SUBJECT INTO SCHEDULE //////////////////////////////////////////////////////////////////////////////

void scheduler(char schedule[],student &pupil,int numsub)  								//arrange schedule
{
		
		int num=numsub;                           
		              											       
		for(int x=0;x<21;x++)								   
	{    													  		
		if(x%numsub==0 && x>=numsub*2)						 
		{	num=num+numsub;
		}
		
		if (x>=numsub)
		{
			int holdd=x-num;
			while(pupil.course[holdd].slot==0)
			{
				
				if(holdd==numsub-1)
				{
					holdd-=numsub-1;
					holdd++;
					
				}
				else
				holdd++;
				
			
			}
			schedule[x]=pupil.course[holdd].alpha;
			pupil.course[holdd].slot--;
		}
		else 
		 {  
		 int holdd=x;
			while(pupil.course[holdd].slot==0)
			{
			
				if(holdd>=numsub-1)
				{
					holdd-=numsub-1;
					holdd++;
				}
				else
					holdd++;
				
			}
		 	schedule[x]=pupil.course[holdd].alpha;
		 	pupil.course[holdd].slot--;
		 }
		
		
		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////// SAVE SCHEDULE INTO I/O FILE ////////////////////////////////////////////////////////////////////////////
 
void saveschedule(char schedule[],student &pupil,int &numexecute,ofstream &writer,int &numsub)  		//save schedule to file
{   
    writer<<numexecute<<endl;	
	writer<<pupil.name.first<<endl;
	writer<<pupil.name.last<<endl;
	writer<<numsub<<endl;

		for(int x=0;x<21;x++)
	{   
         	
	 	if(x%3==0 && x!=0)
		{
		writer<<endl;
		}
		writer<<schedule[x]<<"\t\t";
	
		
		
	}
	writer<<endl<<endl;
	for(int x=0;x<numsub;x++)
	{
		writer<<pupil.course[x].subject<<" "<<pupil.course[x].alpha<<" "<<pupil.course[x].hardness<<endl;	
	}
	
	
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////// READ DATA FROM I/O FILE //////////////////////////////////////////////////////////////////////////////////////

void readdata(int &numsub,student &pupil,ifstream &reader,char Schedule[][3],int &numexecute) ///read data from file
{

	reader>>numexecute; 
	reader.ignore();
	reader.get(pupil.name.first,10);
	reader.ignore();
	reader.get(pupil.name.last,10);
	reader>>numsub;
	
	for(int y=0;y<7;y++)
    {
    	for(int x=0;x<3;x++)
    	{
    	
    		reader>>Schedule[y][x];
    		
		}
    	
    	
	}

	for(int y=0;y<numsub;y++)
	{   
	
		reader>>pupil.course[y].subject;
		reader>>pupil.course[y].alpha;
		reader>>pupil.course[y].hardness;
		
	}
	
	
	
	
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////// VIEW SCHEDULE /////////////////////////////////////////////////////////////////////////////////////

void viewschedule(char schedule[][3],int numsub,student &pupil)  //function to view schedule
{   
    cout<<"\nName : "<<pupil.name.first<<" "<<pupil.name.last<<endl;
	cout<<"\n---------------------------------------------------------"<<endl;
    cout<<"                     Your Study Week Schedule           |\n---------------------------------------------------------"<<endl;
	if(pupil.mode=='B')
	cout<<"\t |  8.00-10.00\t|   2.00-4.00\t|   8.00-10.00 |"<<endl;
	else
	cout<<"\t|   2.00-4.00\t|   8.00-10.00\t|   10.00-12.00 |"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	for(int y=0;y<7;y++)
	{   
	    cout<<"Day :"<<y+1<<"\t|\t";
		for(int x=0;x<3;x++)
		
		{   
		     for(int z=0;z<numsub;z++)
		     {
		    	if(schedule[y][x]==pupil.course[z].alpha)
		     	{
		     		cout<<pupil.course[z].subject<<"\t|\t";
				}
			 }
		
		}
			
			cout<<endl<<"\t|\t\t|\t\t|\t\t|"<<endl;
	
		
	}
	cout<<"---------------------------------------------------------"<<endl;

cout<<"\n-------------------------------------------------------------------------------"<<endl;
cout<<"List Of Subjects\n-------------------------------------------------------------------------------"<<endl;
cout<<"Subject \tDifficulty"<<endl<<endl;
for(int x=0;x<numsub;x++)
{
	cout<<pupil.course[x].subject<<" \t\t"<<pupil.course[x].hardness<<endl;
		
}

cout<<"-------------------------------------------------------------------------------"<<endl;
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////// SEARCH SCHEDULE ////////////////////////////////////////////////////////////////////////////////////////

	void searchschedule(int numsub,student &pupil,char schedule[][3])
	{	
	
		cout<<"\n\nEnter the detail of Schedule that you want to search\n----------------------------------------------------\n";
		int searchday; 
		int searchslot;
	
		cout<<"Enter Day (1 to 7) :";
		cin>>searchday;
		
		cout<<"Enter Slot (1 to 3) :";
		cin>>searchslot;
		 
		for (int x=0;x<7;x++)
		{
			
			for(int y=0;y<3;y++)
			{   
			    if(y+1==searchslot && x+1==searchday)
			    for(int z=0;z<numsub;z++)
				if(schedule[x][y]==pupil.course[z].alpha)
		     	{
		     		cout<<"\nSubject that you should study on day "<<x+1<<" and slot "<<y+1<<" is : "<<pupil.course[z].subject<<endl;
				}
			}
		}
		
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////// FIND MIN MAX ///////////////////////////////////////////////////////////////////////////////////////////

	void minmax(int numsub,student &pupil)
	{
		int min=99;
		int positionmin;
		int max=0;
		int positionmax;
		


		
		for(int x=0;x<numsub;x++)
		{
			if(pupil.course[x].hardness<min)
			{
				min=pupil.course[x].hardness;
				positionmin=x;
			}
		
			if(pupil.course[x].hardness>max)
			{
				max=pupil.course[x].hardness;
				positionmax=x;
			}
		
		} 
	
		
		cout<<"\n\nMin and Max Hardness of Subject \n-------------------------------"<<endl;
		cout<<"Hardest subject is "<<pupil.course[positionmax].subject<<endl;
		cout<<"Easiest subject is "<<pupil.course[positionmin].subject<<endl;
		cout<<"-------------------------------\n"<<endl;
		
		
		
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////// AVERAGE DIFFICULTY OF SUBJECTS ////////////////////////////////////////////////////////////////////

void averagediff(int numsub,student &pupil)
{   float total=0;
	for(int x=0;x<numsub;x++)
	{ 
		total+=pupil.course[x].hardness;		
	}
	
	cout<<"Average Difficulty of Subject : "<<total/numsub<<endl<<endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




