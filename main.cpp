#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

const char* hostname    = "localhost";
const char* username    = "admin";
const char* password    = "admin";
const char* database    = "bank";
unsigned int port       = 3306;
const char* unixsocket  = NULL;
unsigned long clientflag = 0;

MYSQL* connectdatabase()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if(conn){
        cout<<"connected to database "<<endl;
        return conn;
    }
    else{
        cout<<"Failed to connect to database"<<endl;
        return conn;
    }
}

create_account(MYSQL* conn){
    int qstate;

    string name,age,dob,position,gender;

        cout <<" Enter your full name"<<endl;
        cin >> name;


        cout<<" Enter your age:"<<endl;
        cin>> age;

        cout <<" Enter your date of birth"<<endl;
        cin >> dob;


        cout<<" Enter your position"<<endl;
        cin>> position;


        cout<<"Enter your gender"<<endl;
        cin>>gender;

        stringstream  ss;
        ss << "INSERT INTO `accounts`(`id`, `name`, `age`, `date_of_birth`, `position`, `gender`) VALUES  ('" "','" << name<<"','" <<age <<"','"  << dob<<"','" <<position<<"', '" <<gender<<"')";

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0)
    {
        cout<<"Record inserted...~~~ \n";
    }
    else
    {
        cout<<"failed to insert...~~~ \n";
    }

}

show_account(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;

    if(conn)
    {
        int qstate = mysql_query(conn, "SELECT * FROM accounts ");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row = mysql_fetch_row(res))
            {
                    for(int i=0;i<count;i++)
                    {
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;

            }
        }

    }
    else{
        cout<<"Failed to fetch ";


    }

}



/*show_account_sp(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;

    string id;

    cout <<" Enter id number"<<endl;
    cin >> id;



    if(conn)
    {
        int qstate = mysql_query(conn, "SELECT `name` FROM `accounts` WHERE 1 ");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row = mysql_fetch_row(res))
            {
                    for(int i=0;i<count;i++)
                    {
                        cout<<"\t"<<row[i];
                    }
                    cout<<endl;

            }
        }

    }
    else{
        cout<<"Failed to fetch ";


    }

}*/




deletedb(MYSQL* conn)
{
    string name;
    stringstream ss;
    cout<<"Enter the name. of record ";
    cin>>name;


    ss  << "DELETE FROM accounts WHERE name = '"+name+"' ";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(qstate == 0)
        {
        cout<<"~~~~~Record deleted...~~~ \n";
        }
    else
        {
        cout<<"~~~~~failed to delete...~~~ \n";
        }

}




int main()
{
    int c;
    MYSQL* conn = connectdatabase();
    op:
    if(conn){

        cout<<"\t\t\t=================================================================="<<endl;
        cout<<"\t\t\t                        WELCOME TO misba clinic                   "<<endl;
        cout<<"\t\t\t                                                                  "<<endl;
        cout<<"\t\t\t                               created by                         "<<endl;
        cout<<"\t\t\t                         name    = misba banedar                  "<<endl;
        cout<<"\t\t\t                         college = Abeda inamdar                  "<<endl;
        cout<<"\t\t\t=================================================================="<<endl<<endl<<endl;


        cout<<"Enter numbers for operations "<<endl;
        cout<<"1 Input record \n2 print all record \n3 delete one record \n4 for exit ";
        cin>>c;
        switch(c){
            case 1:
            create_account(conn);
            goto op;
            break;
            case 2:
            show_account(conn);
            goto op;
            case 3:
            deletedb(conn);
            goto op;
            case 4:
            exit(0);
            break;
            default:
                cout<<"Wrong input   ......exiting.....\n\n";
               goto op;
        }

    }
    else{
        exit(0);
    }

    return 0;
}
