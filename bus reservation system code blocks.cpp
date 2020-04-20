/*This one works*/

#include <conio.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

static int p = 0;
static int q=0;

class a
{
protected:
        char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];
    public:
        void install();
        void allotment();
        void empty();
        void show();
        void avail();
        void position(int i);
};

class d:public a
  {
    protected:
        char manu_name[90],engine[90],ec[90];
        float speed,torque;
        int num_seats;

    public:
      void get()
          {
           cout<<"\nEnter details for bus "<<q+1<<".";
           gets(busn);
           cout<<"Company name: ";
           gets(manu_name);
           cout<<"Type of Engine: ";
           gets(engine);
           cout<<"Torque: ";
           cin>>torque;
           cout<<"Emission Class: ";
           cin.getline(ec,90);
           cout<<"Max Speed(Recommended): ";
           cin>>speed;
           cout<<"Number of seats: ";
           cin>>num_seats;
           q++;
          }
      void put()
          {
           cout<<"\nCompany Name          : "<<manu_name;
           cout<<"\tType of Engine        : "<<engine;
           cout<<"\nTorque                : "<<torque;
           cout<<"\nEmission Class        : "<<ec;
           cout<<"\nMax Speed(Recommended): "<<speed;
           cout<<"\nNumber of Seats       : "<<num_seats;
          }
}bus[10];

void vline(char ch)
{
    for (int i=80;i>0;i--)
        cout<<ch;
}

void a::install()
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

void a::allotment()
{
    int seat,seat1;
    char number[5];
    top:
    cout<<"Bus no: ";
    cin>>number;
    int n;
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
                cout<<"Enter passanger's name: ";
                cin>>bus[n].seat[seat/4][(seat%4)];
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

void a::empty()
{
    for(int i=0; i<8;i++){
        for(int j=0;j<4;j++){
            strcpy(bus[p].seat[i][j], "Empty");
        }
      }
}

void a::show()
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

void a::position(int l)
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

void a::avail()
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
int main()
{
    system("cls");
    int w,w2;
    while(1)
    {
        //system("cls");
        cout<<"\n\n\n\n\n";
        cout<<"\t\t\t1.Install\n\t\t\t"
        <<"2.Reservation\n\t\t\t"
        <<"3.Show\n\t\t\t"
        <<"4.Buses Available. \n\t\t\t"
        <<"5.Exit";
        cout<<"\n\t\t\tEnter your choice:->";
        cin>>w;
        switch(w)
          {
            case 1:  cout<<"For installing bus travel details press 8\nFor installing bus manufaturing details press 9: ";
                    cin>>w2;
                    switch(w2)
                    {
                        case 8:bus[p].install(); break;
                        case 9:bus[q].get();break;
                    };
            break;
            case 2:  bus[p].allotment();
            break;
            case 3:  cout<<"For bus travel details press 8\n For bus manufacturing details press 9: ";
                    cin>>w2;
                    switch(w2)
                    {
                        case 8:bus[p].show(); break;
                        case 9:bus[q].put(); break;
                    };
            break;
            case 4:  bus[0].avail();
            break;
            case 5:  exit(0);
          }
    }
    return 0;
}
