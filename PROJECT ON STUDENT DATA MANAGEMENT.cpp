// STUDENT RECORD MANAGEMENT SYSTEM
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int main()
{
    // considering the max length of data entered (name) to be 15
    char data[15];
    int n = 0 , option = 0 , count_n = 0 ;

    //initial mark allotted on subject
    string empty = "00";
    string proctor = "";

    //name of the file in which db is stored
    ifstream f("db.txt");
    string line;

    //the following for loop count the number of lines in the file
    for(int i=0; std::getline(f,line);++i)
    {
        count_n++;
    }

    while(option != 6)
    {
        //this prints out all the available options int the db
        cout<<"\n Available options : \n 1.Add new students"
            <<"\n 2. students login \n 3. Faculty login"
              "\n 4. Proctor login \n 5. Admin view\n "
            <<" 6. Exit\n Enter option: ";
        cin>> option;

        if(option == 1)
        {
            cout<<"Enter the number of students:";
            cin>>n;

            count_n = count_n + n;
            for(int i=0; i<n;i++)
            {
                ofstream outfile;
                outfile.open("db.txt", ios::app);
                //the entire data of a single student is stored line by line
                cout<<" Enter your registration number: ";
                cin>>data;
                outfile <<data <<"\t";

                cout<<"Enter your name";
                cin>>data;
                int len = strlen(data);

                while(len<15)
                {
                    data[len]= ' ';
                    len= len+1;
                }
                outfile << data<<"\t";
                //inserting empty data initially into the file
                outfile<< empty<<"\t";
                outfile<<empty<<"\t";

                cout<<"Enter your proctor ID:";
                cin>>proctor;

                outfile<< proctor <<endl;
            }
        }
        else if(option == 2)
        {
            char regno[9];
            cout<<"Enter your registration number";
            cin>> regno;
            ifstream infile;
            int check = 0;
            infile.open("db.txt",ios::in);

            //this loop prints out the data according to the registration number specified
            while(infile >> data)
            {
                if(strcmp(data,regno)==0)
                {
                    cout<<"\n Registration Number: "<<data<<endl;
                    infile>> data;
                    cout<<"Name : "<<data<<endl;

                    infile >> data;
                    cout<<"MI20102 mark :"<<data<<endl;

                    infile>>data;
                    cout<<"MI21202 mark:"<<data<<endl;

                    infile>>data;
                    cout<<"PROCTOR ID "<<data<<endl;

                    infile.close();
                    check=1;
                }
            }
            if(check == 0)
            {
                cout<<"NO SUCH REGISTRATION NUMBER IS FOUND !"<<endl;
            }
        }

        //this loop is used to view  and add marks to the database of a student
        else if (option == 3)
        {
            char subcode[7];
            cout<<" Enter your subject code: ";
            cin>>subcode;
            string code1 = "MI20102", code2 = "MI21202", mark = "";
            ifstream infile;
            int check =0;

            cout<<"\n Available operations: \n 1. Add data about marks\n"
                <<"2. View data\n Enter option:";
            cin>> option;

            if(option ==1 )
            {
                cout<<"Warning! You need to add mark details"
                    <<"for all the students !"<<endl;
                for(int i=0;i<count_n;i++)
                {
                    fstream file("db.txt");
                    // the seek int the file has been done according to the length
                    //of the data being inserted. It needs to adjusted accordingly for different
                    //lengths of data.
                   if(strcmp(subcode,code1.c_str())==0)
                   {
                       file.seekp(26+ 37*i, std::ios_base::beg);
                       cout<<"Enter the mark of student#"<<(i+1)<<":";
                       cin>>mark;
                       file.write(mark.c_str(),2);
                   }
                   if(strcmp(subcode,code2.c_str())==0)
                   {
                       file.seekp(29+ 37*i,std::ios_base::beg);
                       cout<<"Enter the mark of student#"<<(i+1)<<":";
                       cin>>mark;
                       file.write(mark.c_str(),2);
                   }
                }
            }

            //this loop is used to view marks of a student.
            //the extra infile commands have been used to get a specific
            //mark only since the data has been separated by a tab space
            else if(option == 2)
            {
                infile.open("db.txt",ios::in);
                if(strcmp(subcode,code1.c_str())==0)
                {
                    cout<<"Registration number - marks\n"<<endl;
                    while(infile >> data)
                    {
                        cout<<data;
                        infile>>data;
                        infile>>data;
                        cout<<"-"<<data<<endl;
                        infile>>data;
                        infile>>data;
                        check = 1;
                    }
                }
                infile.close();
                infile.open("db.txt",ios::in);
                if(strcmp(subcode,code2.c_str())==0)
                {
                    cout<<"Registration number - marks\n"<<endl;
                    while(infile >> data)
                    {
                        cout<< data;
                        infile >> data;
                        infile>> data;
                        infile>>data;
                        cout<<"-"<<data<<endl;
                        infile>>data;
                        check = 1;
                    }
                }

            }
            infile.close();
            if(check == 0)
            {
                cout<<"No such subject code found !"<<endl;
            }

        }
        //this loop displays all the details of students under the same proctor id

        else if(option == 4)
        {
            char procid[7];
            cout<<"Enter your proctor id :";
            cin>>procid;
            int check =0;
            char temp1[100],temp2[100],temp3[100],temp4[100];
            char id[100];
            ifstream infile;
            infile.open("db.txt",ios::in);

            while( infile>> temp1)
            {
                infile>>temp2;
                infile>>temp3;
                infile>>temp4;
                infile>>id;;

                if(strcmp(id,procid)==0)
                {
                    cout<<"\n Registration Number:"<<temp1<<endl;
                    cout<<"\n Name: "<<temp2<<endl;
                    cout<<"\n MI21202 Mark : "<<temp3<<endl;
                    cout<<"\n MI20102 Mark : "<<temp4<<endl;
                    check = 1;

                }
            }
            if(check ==0)
            {
                cout<<"No such proctor id found !"<<endl;

            }
        }
        // This loop acts as an admin view to see all the data in the file

        else if (option == 5)
        {
            char password[25];
            cout<<"Enter the Admin password :";
            cin>> password;

            //this variable value can be changed according to your
            //requirement of the administrator password.

            string admin_pass = "Admin";

            if(strcmp(password,admin_pass.c_str())== 0)
            {
                cout<<"Reg No.        "
                      "\tName\tMI20102\tMI21202\tProctor ID"<<endl;
                ifstream infile;
                infile.open("db.txt",ios::in);
                char data[20];
                while(infile>>data)
                {
                    cout<<data<<"\t";
                    infile>>data;
                    cout<<data<<"\t";
                    infile>>data;
                    cout<<data<<"\t";
                    infile>>data;
                    cout<<data<<"\t";
                    infile>>data;
                    cout<<data<<endl;
                }
            }
        }
    }
}
























