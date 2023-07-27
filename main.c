
#include<iomanip.h>

#include<fstream.h>

#include<conio.h>

#include<stdio.h>

#include<process.h>

#include<string.h>

class book
{
	char bno[6];
	char book_name[50];
	char author_name[20];
  public:
	
    void modifybookfunc()
    {
        cout<<"\nBook no--> "<<bno;

        cout<<"\nModify Book Name-------->";

        gets(book_name);

        cout<<"\nModify author's Name of Book-------->";

        gets(author_name);
    }


    void showthebook()
    {
        cout<<"\nbook no-------->"<<bno;

        cout<<"\nbook name -------->";

        puts(book_name);

        cout<<"author name-------->";

        puts(author_name);

    }

    

    char* retbno()

    {
        return bno;
    }

    void report()
    {
        cout<<bno<<setw(30)<<book_name<<setw(30)<<author_name<<endl;

    }
     

     void createthebook()
	{

        cout<<"\nthe new book entry-------->\n";

        
        cout<<"\nEnter the book no-------->";

        cin>>bno;

        cout<<"\n\nEnter the Name of The Book--------> ";

        gets(book_name);

        cout<<"\n\nEnter the Author's Name -------->";

        gets(author_name);

        cout<<"\n\n\nBook Created!!!!!!!!11";

    }



};         




class student
{

    char admno[6];

    char name[20];

    char stbno[6];

    int token;
public:
    void createthestudent()
    {
        clrscr();
         cout<<"\nnew student entry\n";

        cout<<"\nEnter the admission no---------------------------------------------->";

        cin>>admno;

        cout<<"\n\nEnter The name of The student ---------------------------------------->";

        gets(name);


        token=0;

        stbno[0]='/0';

        cout<<"\n\nStudent Record Created";
    }

    void showthestudent()
    {
        cout<<"\nAdmission no---> "<<admno;

        cout<<"\nStudent Name---> ";

        puts(name);

        cout<<"\nNo of Book issued--->"<<token;

        if(token==1)


            cout<<"\nBook No--------------->"<<stbno;
    }

    void modifythestudent()

    {
        cout<<"\nAdmission no--->"<<admno;

        cout<<"\nModify Student Name--->";

        gets(name);
    }


    char* returnadmin_number()
    {
        return admno;
    }

    char* retst_bno()
    {
        return stbno;
    }

    int ret_token()
    {
        return token;
    }

    void add__the__token()
    {token=1;}

    void reset_token()
    {token=0;}

    void get__st__bno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};       



fstream fp,fp1;
book bk;
student st;

void writethebookfunc()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        clrscr();
        bk.createthebook();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\nAre you sure you want to add more record????????????(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void writestudentfunc()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.createthestudent();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\ndo you want to add more record?????????????(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}


void displaythespbfunc(char n[])
{
    cout<<"\nbook details\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.showthebook();
             flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
        cout<<"\n\nbook does not exist";
    getch();
}

void displaythesps(char n[])
{
    cout<<"\nstudent details\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.returnadmin_number(),n)==0))
        {
            st.showthestudent();
            flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
            cout<<"\n\nStudent does not exist";
     getch();
}


void modifybookfunc()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\n\t                                      modify book record----->";
    cout<<"\n\n\t                                      Enter the book no.--->";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.showthebook();
            cout<<"\n                     Enter The new Details of book----->"<<endl;
            bk.modifybookfunc();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t record updated!";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n record not found!! ";
        getch();
}


void modifythestudent()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\n\t modify student record----> ";
    cout<<"\n\n\t Enter the admission no. of The student-------->";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.returnadmin_number(),n)==0)
        {
            st.showthestudent();
            cout<<"\nEnter the new details of student-------->"<<endl;
            st.modifythestudent();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t record updated";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n\n record not found !!!!";
    getch();
}



void deletestudentfunc()
{
    char n[6];
    int flag=0;    
    clrscr();
        cout<<"\n\n\n\t delete student";
        cout<<"\n\n     Enter The admission no. of the Student You Want To Delete---> ";
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.returnadmin_number(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
        
    fp2.close();
        fp.close();
        remove("student.dat");
        rename("Temp.dat","student.dat");
        if(flag==1)
             cout<<"\n\n\t record deleted";
        else
             cout<<"\n\nrecord not found";
        getch();
}


void deletethebookfunc()
{
    char n[6];
    clrscr();
    cout<<"\n\n\n\t  delete book";
    cout<<"\n\nEnter The Book no. of the Book you want To delete-------->";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)  
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
        
    fp2.close();

        fp.close();

        remove("book.dat");

        rename("Temp.dat","book.dat");

        cout<<"\n\n\t        record deleted";

        getch();
}




void displayallfunc()
{
    clrscr();
         fp.open("student.dat",ios::in);

         if(!fp)
         {
               cout<<"Oops!!file can't open";

               getch();

               return;
         }

    cout<<"\n\n\t\tstudent list------\n\n";
   
    cout<<"\tadmission No.----->"<<setw(10)<<"Name-------->"<<setw(20)<<"book issued------->\n";
    
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
         
    fp.close();
    getch();
}


void displayallbfunc()
{
    clrscr();
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"Oops!!file can't open";
               getch();
               return;
         }

    cout<<"\n\n\t\tBook list----\n\n";
   
    cout<<"book number---"<<setw(20)<<"Book name----"<<setw(25)<<"author---\n";
    

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}


void bookissuefunc()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    clrscr();
    cout<<"\n\nbook isuue";

    cout<<"\n\n\tEnter The student's admission no---->";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.returnadmin_number(),sn)==0)
        {
            found=1;
            if(st.ret_token()==0)
            {
                      cout<<"\n\n\tEnter the book no-------->";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.showthebook();
                        flag=1;
                        st.add__the__token();
                        st.get__st__bno(bk.retbno());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t and the Book issued is successfull\n\nPlease Write current date 
                        in backside of book and submit within 15 days else there is fine Rs. 1 for each day     
                        after 15 days period.Be Careful !!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                    }
                    }
                  if(flag==0)
                        cout<<"book no does not exist";
            }
                else
                  cout<<"you have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"student record not exist--------->";
    getch();
      fp.close();
      fp1.close();
}



void bookdeposifunct()
{
    char sn[6],bn[6];

    int found=0,flag=0,day,fine;

    clrscr();

    cout<<"\n\nBook deposit";


    cout<<"\n\n\t             enter The student's admission no--------->";

    cin>>sn;

    fp.open("student.dat",ios::in|ios::out);

    fp1.open("book.dat",ios::in|ios::out);
    
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.returnadmin_number(),sn)==0)
        {
            found=1;

            if(st.ret_token()==1)

            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retbno(),st.retst_bno())==0)
            {
                bk.showthebook();
                flag=1;
                cout<<"\n\n             book deposited in no. of days------------->";
                cin>>day;

                if(day>15)


                {

                   fine=(day-15)*1;

                   cout<<"\n\n             fine has to deposited Rs. "<<fine;

                }
                    st.reset_token();

                    int pos=-1*sizeof(st);


                    fp.seekp(pos,ios::cur);

                    fp.write((char*)&st,sizeof(student));

                    cout<<"\n\n\t           book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"              book no. does not exist!!!!!";
              }
         else
            cout<<"                no book is issued..please check!!!!!!";
        }
       }
      if(found==0)
    cout<<"              Student record not exist";
    getch();
  fp.close();
  fp1.close();
  }





void intro()
{
    clrscr();

    gotoxy(35,11);

    cout<<"library";

    gotoxy(35,14);

    cout<<"management";

    gotoxy(35,17);

    cout<<"system";

 

    getch();
}




void adminmenufunc()
{
    clrscr();
    int ch2;
    cout<<"\n\n\n\t                             administrator menu----------------------->>";
    cout<<"\n\n\t                               1.create student record                ";
    cout<<"\n\n\t                               2.display all students record             ";
    cout<<"\n\n\t                               3.DISPLAY SPECIFIC STUDENT RECORD           ";
    cout<<"\n\n\t                               4.modify student record           ";
    cout<<"\n\n\t                               5.delete student record          ";
    cout<<"\n\n\t                               6.create book            ";
    cout<<"\n\n\t                               7.display all books              ";
    cout<<"\n\n\t                               8.display specific book            ";
    cout<<"\n\n\t                               9.modify book              ";
    cout<<"\n\n\t                               10.delete book              ";
    cout<<"\n\n\t                               11.back to main menu              ";
    cout<<"\n\n\t                               Please Enter Your Choice (1-11)          ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: clrscr();

                writestudentfunc();
                break;

            case 2: displayallfunc();
            break;

            case 3:

                   char num[6];
                   clrscr();

                   cout<<"\n\n\tPlease Enter The Admission No--------------------------------->";

                   cin>>num;

                   displaythesps(num);
                   break;

              case 4: modifythestudent();
              break;

              case 5: deletestudentfunc();
              break;

        case 6: clrscr();

            writethebookfunc();
            break;

        case 7: displayallbfunc();
        break;

        case 8: {
                   char num[6];

                   clrscr();

                   cout<<"\n\tPlease Enter The book no--------------------------------->";

                   cin>>num;

                   displaythespbfunc(num);

                   break;
            }
              case 9: modifybookfunc();
              break;

              case 10: deletethebookfunc();
              break;

             case 11: return;

              default:cout<<"\a";
       }
       adminmenufunc();
}






void main()
{
    char ch;
    intro();
    do
    {
         clrscr();
        cout<<"\n\n\n\t                         main menu ";
        cout<<"\n\n\t                           01. book issue ";
        cout<<"\n\n\t                           02. book deposit";
          cout<<"\n\n\t                         03. administrator menu";
          cout<<"\n\n\t                         04. exit";
          cout<<"\n\n\t                         please select your option (1-4) ";
          ch=getche();
          switch(ch)
          {

            case '1':
            
            
            clrscr();
                 
                 
                 bookissuefunc();


                    break;
              case '2':
              
              
              bookdeposifunct();


                     break;



              case '3':
              
              
              adminmenufunc();
                 break;


              case '4':
              
              exit(0);


              default :
              
              
              cout<<"\a";
        }
        }
        while(ch!='4');
}
