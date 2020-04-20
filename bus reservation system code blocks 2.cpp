#include <conio.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

static int p = 0;
static int pnr_store=0;

class bus_travel
{
public:
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];
    int wt,cargowt;
public:
    void install();
    void allotment();
    void empty();
    void show();
    void avail();
    void position(int i);
    void cargo(const char *);
    void dispatch();
    virtual void info_init()=0;
    virtual void get_info()=0;
};

class bus_manu:virtual public bus_travel
{
protected:
    char manu_name[90],engine[90],ec[90];
    float speed,torque;
    int num_seats,manu_num,count1;
public:
    bus_manu(){count1=0;}
    virtual void info_init();
    virtual void get_info();
};

class bus_pass:virtual public bus_travel
{
protected:
    char name[90],address[90];
    int age,count2;
    long int pnr;
public:
    bus_pass(){count2=0;}
    virtual void info_init();
    virtual void get_info();
};

class get_details:public bus_manu,public bus_pass
{
public:
    virtual void info_init();
    virtual void get_info();
}bus[100];

void bus_manu::info_init()
{
    char str[90];
    cout<<"Enter bus make details:\n";
    cout<<"Manufacturer: ";
    cin>>bus[count1].manu_name;
    cout<<"Manufacture number: ";
    cin>>bus[count1].manu_num;
    cout<<"Engine: ";
    cin>>bus[count1].engine;
    cout<<"Emission class: ";
    cin>>bus[count1].ec;
    cout<<"Speed: ";
    cin>>bus[count1].speed;
    cout<<"Torque: ";
    cin>>bus[count1].torque;
    cout<<"Number of seats: ";
    cin>>bus[count1].num_seats;
    count1++;
}

void bus_manu::get_info()
{
    int num,count;
    cout<<"\nEnter bus manufature number: ";
    cin>>num;
    for(int i=0;i<count1;i++){
        if(bus[i].manu_num==num){count=i; break;}
    }
    cout<<"\nBUS MAKE INFORMATION\n";
    cout<<"\nManufacturer   : "<<bus[count].manu_name;
    cout<<"\nEngine         : "<<bus[count].engine;
    cout<<"\nEmission class : "<<bus[count].ec;
    cout<<"\nSpeed          : "<<bus[count].speed;
    cout<<"\nTorque         : "<<bus[count].torque;
    cout<<"\nNumber of Seats: "<<bus[count].num_seats;
}

void bus_pass::info_init()
{
    cout<<"\nEnter passenger details\n";
    cout<<"Name: ";
    cin>>bus[count2].name;
    cout<<"Address: ";
    cin>>bus[count2].address;
    cout<<"Age: ";
    cin>>bus[count2].age;
    bus[count2].pnr=pnr_store;
    count2++;
}

void bus_pass::get_info()
{
    int num,count;
    cout<<"Enter customer PNR: ";
    cin>>num;
    for(int i=0;i<count2;i++){
        if(bus[i].pnr==num){count=i; break;}
    }
    cout<<"\nPASSENGER INFORMATION\n";
    cout<<"\nName   : "<<bus[count].name;
    cout<<"\nAddress: "<<bus[count].address;
    cout<<"\nAge    : "<<bus[count].age;
    cout<<"\nPNR    : "<<bus[count].pnr;
}

void get_details::info_init()
{
    int choice;
    cout<<"\nTo enter bus manufacturing details, enter 1";
    cout<<"\nTo enter bus passenger details, enter 2\n";
    cin>>choice;
    switch(choice){
        case 1: bus_manu::info_init(); break;
        case 2: bus_pass::info_init(); break;
        default: cout<<"INVALID CHOICE"; get_details::info_init();
    }
}

void get_details::get_info()
{
    int choice;
    cout<<"\nTo display bus manufacturing details, enter 1";
    cout<<"\nTo display bus passenger details, enter 2\n";
    cin>>choice;
    switch(choice){
        case 1: bus_manu::get_info(); break;
        case 2: bus_pass::get_info(); break;
        default: cout<<"INVALID CHOICE"; get_details::get_info();
    }
}

void vline(char ch)
{
    for (int i=80;i>0;i--)
        cout<<ch;
}

long int pnr_gen()
{
    long int num;
    num=rand()%50000+10000;
    return num;
}

void bus_travel::install()
{
    cout<<"Enter bus no: ";
    cin>>bus[p].busn;
    cout<<"\nEnter Driver's name: ";
    cin>>bus[p].driver;
    cout<<"\nArrival time: ";
    cin>>bus[p].arrival;
    cout<<"\nDeparture: ";
    cin>>bus[p].depart;
    cout<<"\nFrom: \t\t\t";
    cin>>bus[p].from;
    cout<<"\nTo: \t\t\t";
    cin>>bus[p].to;
    bus[p].empty();
    p++;
}

void bus_travel::allotment()
{
    int seat,seat1;
    char number[5];
    top:
    cout<<"Bus no: ";
    cin>>number;
    int n;
    char str[10];
    for(n=0;n<=p;n++){
        if(strcmp(bus[n].busn,number)==0)
        break;
      }
    if(n<=p)
      {
        cout<<"\nSeat Number: ";
        cin>>seat1;
        seat=seat1-1;
        if(seat1>32){
            cout<<"\nThere are only 32 seats available in this bus.";
        }
        else{
            if (strcmp(bus[n].seat[seat/4][(seat%4)],"Empty")==0){
                pnr_store=pnr_gen();
                sprintf(str,"%ld",pnr_store);
                bus[p].info_init();
                strcpy(bus[n].seat[seat/4][(seat%4)],str);
            }
            else
            cout<<"The seat no. is already reserved.\n";
          }
        }
    if(n>p){
        cout<<"Enter correct bus no.\n";
        goto top;
    }
  }

void bus_travel::empty()
{
    for(int i=0; i<8;i++){
        for(int j=0;j<4;j++){
            strcpy(bus[p].seat[i][j], "Empty");
        }
      }
    bus[p].cargowt=0;
}

void bus_travel::show()
{
    int n;
    char number[5];
    cout<<"Enter bus no: ";
    cin>>number;
    for(n=0;n<=p;n++){
        if(strcmp(bus[n].busn, number)==0)
        break;
    }
    while(n<=p){
    vline('*');
    cout<<"Bus no: \t"<<bus[n].busn
    <<"\nDriver: \t"<<bus[n].driver<<"\t\tArrival time: \t"
    <<bus[n].arrival<<"\tDeparturetime:"<<bus[n].depart
    <<"\nFrom: \t\t"<<bus[n].from<<"\t\tTo: \t\t"<<
    bus[n].to<<"\n";
    vline('*');
    bus[0].position(n);
    int a=1;
    for (int i=0; i<8; i++){
        for(int j=0;j<4;j++){
            a++;
            if(strcmp(bus[n].seat[i][j],"Empty")!=0)
            cout<<"\nThe seat no "<<(a-1)<<" is reserved for "<<bus[n].seat[i][j]<<".";
        }
    }
    break;
    }
    if(n>p)
        cout<<"Enter correct bus no: ";
}

void bus_travel::position(int l)
{
    int s=0;p=0;
    for (int i =0; i<8;i++){
        cout<<"\n";
        for (int j = 0;j<4; j++){
            s++;
            if(strcmp(bus[l].seat[i][j], "Empty")==0){
                cout.width(5);
                cout.fill(' ');
                cout<<s<<".";
                cout.width(10);
                cout.fill(' ');
                cout<<bus[l].seat[i][j];
                p++;
            }
            else{
                cout.width(5);
                cout.fill(' ');
                cout<<s<<".";
                cout.width(10);
                cout.fill(' ');
                cout<<bus[l].seat[i][j];
            }
        }
    }
    cout<<"\n\nThere are "<<p<<" seats empty in Bus No: "<<bus[l].busn;
}

void bus_travel::avail()
{
    for(int n=0;n<p;n++){
        vline('*');
        cout<<"Bus no: \t"<<bus[n].busn<<"\nDriver: \t"<<bus[n].driver
        <<"\t\tArrival time: \t"<<bus[n].arrival<<"\tDeparture Time: \t"
        <<bus[n].depart<<"\nFrom: \t\t"<<bus[n].from<<"\t\tTo: \t\t\t"
        <<bus[n].to<<"\n";
        vline('*');
        vline('_');
    }
}

void bus_travel::cargo(const char *name)
{
    int cwt,n;
    char number[10];
    int cargoid;
    ofstream cr(name,ios::app);
    cout<<"Bus no: ";
    cin>>number;
    for(n=0; n<=p; n++){
        if(strcmp(bus[n].busn, number)==0){
            cout<<"enter cargo id\n";
            cin>>cargoid;
            cout<<"enter weight of cargo\n";
            cin>>cwt;
            bus[n].cargowt+=cwt;
            if(bus[n].cargowt<bus[n].wt){
                cout<<"cargo added\n";
                cr<<endl<<"cargo id:  "<<cargoid<<"\t cargo weight:  "<<cwt<<endl;
            }
            else{
                cout<<"cargo cant be added\n";
                break;
            }
        }
    }
    if(n>p)
        cout<<"enter valid bus no"<<endl;
}

void a::dispatch()
{
    int driverID[n],nwaiting=0,rear=-1,front=0,terminate=0;
    char command;
    while(terminate==0){
        cout<<"enter d to accomodate\n c to dispatch \n x to exit"<<endl;
        cin>>command;
        switch(command){
            case 'd':
                if(nwaiting==n)
                    cout<<"queue is full.....no bus can be accommodated. try again later.\n";
                else{
                    rear=(rear+1)%n;
                    cout<<"enter driver id"<<endl;
                    cin>>driverID[rear];
                    nwaiting++;
                    cout<<"bus accomodated"<<endl;
                    int k=front;
                    cout<<"available :\n";
                    for(int j=0;j<nwaiting;j++){
                        cout<<driverID[k]<<"\t";
                        k=(k+1)%n;
                    }
                    cout<<endl;
                    }
                break;
            case 'c':
                if(nwaiting==0) cout<<"no bus is available .......try again later\n";
                else{
                    cout<<"Assigning: " << driverID[front]<<endl;
                    front=(front+1)%n;
                    nwaiting--;
                    int k=front;
                    cout<<"available :\n";
                    for(int j=0;j<nwaiting;j++)
                    {
                        cout<<driverID[k]<<"\t";
                        k=(k+1)%n;
                    }
                    cout<<endl;
                }
                break;
        case 'x':terminate=1;break;
        default: cout <<"illegal command \n";
        }
    }
}

int main()
{
    system("cls");
    int w;
    while(1)
    {
        //system("cls");
        cout<<"\n\n\n\n\n";
        cout<<"\t1.Install\n\t"
        <<"2.Reservation\n\t"
        <<"3.Show\n\t"
        <<"4.Buses Available. \n\t"
        <<"5.Enter bus manufacture details or bus passenger details.\n\t"
        <<"6.Search bus manufacture details or bus passenger details.\n\t"
        <<"7.Exit";
        cout<<"\n\tEnter your choice:->";
        cin>>w;
        switch(w)
          {
            case 1:bus[p].install();break;
            case 2:bus[p].allotment();break;
            case 3:bus[0].show();break;
            case 4:bus[0].avail();break;
            case 5:bus[0].info_init();break;
            case 6:bus[0].get_info();break;
            case 7:exit(0);
          }
    }
    return 0;
}
