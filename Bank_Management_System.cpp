#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

class account_query
{
    private:
    char account_number[20];
    char first_name[10];
    char last_name[10];
    float total_balance;

    public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void account_query::read_data()
{
    cout<<"\nEnter Account Number: ";
    cin>>account_number;
    cout<<"\nEnter First Name: ";
    cin>>first_name;
    cout<<"\nEnter Last Name: ";
    cin>>last_name;
    cout<<"\nEnter Balance: ";
    cin>>total_balance;
    cout<<endl;
}
void account_query::show_data()
{
    cout<<"--------------------------------------------------------------"<<endl;
    cout<<account_number<<"\t\t"<<first_name<<" "<<last_name<<"\t\t"<<total_balance<<endl;
}
void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.bank",ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this),  sizeof(*this));
    outfile.close();
}
void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile)
    {
       cout<<"Error in Opening! File Not Found.!!"<<endl;
       return;
    }
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this),sizeof(*this)))
        {
            show_data();
        }
    }
    infile.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile)
    {
        cout<<"\nError in Opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count=infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record in file";
    cout<<"\nEnter record number to search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.bank",ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in Opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0,ios::end);
    int count= iofile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record in file.";
    cout<<"\n Enter record number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to modify"<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in Opening! File Not Found!!";
        return;
    }
    infile.seekg(0,ios::end);
    int count=infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<count<<" record in the file";
    cout<<"Enter record number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0;i<count;i++)
    {
        infile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank","record.bank");
}


int main()
{
    account_query A;
    int choice;
    cout<<"*Account Information System*"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add Record to file";
        cout<<"\n\t2-->Show Record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        cout<<"\n";
        switch(choice)
        {
        case 1: A.write_rec();
                break;
        case 2: cout<<"Acc No.\t\t"<<"Name\t\t\t"<<"Balance"<<endl;
                A.read_rec();
                cout<<"--------------------------------------------------------------\n"<<endl;
                break;
        case 3: A.search_rec();
                break;
        case 4: A.edit_rec();
                break;
        case 5: A.delete_rec();
                break;
        case 6: exit(0);
                break;
        default :cout<<"\nEnter Correct Choice";
                 exit(0);
        }
    }
    system("pause");
    return 0;
}