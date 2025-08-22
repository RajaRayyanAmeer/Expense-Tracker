#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<limits>
using namespace std;
void record_expense();
void display_expense();
float summarize_expense();
int main()
{
 int choice;
 cout<<"\n\n\t\t\t\t\t\tWELCOME TO YOUR EXPENSE TRACKER! KINDLY CHOSSE AN OPTION: \n";
 cout<<"\n\t\t\t1. Record Expense \n";
 cout<<"\t\t\t2. Display Expense \n";
 cout<<"\t\t\t3. Summarize Expense \n";
 cout<<"\t\t\t4. Exit \n";
 cout<<"\t\t\t Choose an Option: ";
 cin>>choice;
 cout<<endl;
 switch (choice)
 {
  case 1:  record_expense();      break;
  case 2:  display_expense();     break;
  case 3:  summarize_expense();   break;
  case 4:  return 0;              default:
  cout<<"\t\t\tERROR...\n";
 }
 return 0;
}
void record_expense()
{
 char description[100];
 float amount;
 cout<<"\n\t\t\tEnter Expense Description: ";
 cin.ignore();                              // Ignore any newline characters or spacewhite in the input buffer
 cin.getline(description, 100);             // Read a line of input from the text file for the description                      
 cout<<"\n\t\t\tEnter Expense Amount: ";      
 cin>>amount;
 cout<<endl;
 if (amount < 0)
    {
     cout<<"\t\t\tERROR... Invalid Input!!!\n\t\t\tEnter Expense Amount: ";
     cin>>amount;
     cout<<endl;
	}
 else if (amount > 0)
         {
          cout<<"\t\t\tExpense Record Successfully!!! \n";
		 }
 ofstream data;  
 if (!data)   
    {
     cout<<"\t\tERRROR FILE OPENING...\n";
     return;
	}
 data.open("expenses.txt",ios::app);       // Open the expenses file in append mode
 time_t now = time(0);                     // Get the current time and format it as a string
 string formatted_time = string(ctime(&now));
 data<<endl<<formatted_time<<" - "<<description<<":  $"<<amount<<endl;         // Write the expense record to the file
 data.close(); 
}       
void display_expense()
{
 ifstream data ("expenses.txt");                    // Open the expenses file for reading
 if (!data)
    {
     cout<<"\t\tERRROR FILE OPENING...\n";
     return;
	}
 string line;
 while (getline(data, line))
       {
       	cout<<line<<endl;    
	   }
 data.close();
}
float summarize_expense()    
{
    ifstream data ("expenses.txt");                // Open the expenses file for reading
    if (!data)
    {
        cout<<"\t\tERRROR FILE OPENING...\n";
        return 0.0f;
    }
    string line;
    float total = 0.0f;
    while (getline(data, line))
    {
        size_t found = line.rfind('$');             // Find the position of the '$' character in the line
        if (found != string::npos)
        {
            string amount_str = line.substr(found + 1);       // Extract the amount string from the line
             try
            {
                float amount = stof(amount_str);             // Convert the amount string to a float
                total = total + amount;
            }
            catch (const invalid_argument& ia)
            {
                cout<<"\t\t"<<amount_str<<"\n";
            }
        }
    }
    data.close();
    cout<<"\t\t\tTotal Expenses: "<<total<<" $"<<endl;
    return total;
}                          