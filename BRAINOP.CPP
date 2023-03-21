 #include <conio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <fstream.h>
 #include <process.h>
 #include <dos.h>
 #define L_MAX 500

 int dis=0,a=0;
 const char Srec[]="S_REC.txt";
 const char Trec[]= "T_REC.txt";
 const char Qlist[]= "Q_LIST.dat" ;
 char ch_nam[50],chnam[50];
 fstream nrec;
 const int max_classes =2         ;

 void align(char *str,int x,int& y,int w=60)
 { int i;
  while((*str)!='\0')
   {
     gotoxy(x,y++);
      for(i=0;i<w; i++)
      { if((*str)!='\n')
        cout<<(*str);
        str++;
      }
   }
 }

 void echo(char ch, int t)     // to repeatedly print a particular character several times
 {
 for (int i=1;i<=t;i++)
 cout<<ch;
 }

 void input_pas(char pas[])
 {
 int i=0;
 do
 {
 pas[i]=getch();
 if(pas[i]==13)
 {pas[i]='\0';
 break;
 }
 if (pas[i]==8)  //For the case when user enter a backspace
 {cout<< (char)8<<" "<<(char)8;
 i--;
 continue;
 }
 else{ cout<<'*';
 i++;
 }
 } 
 while(1);//Until user presses enter key (ASCII CODE FOR ENTER: 13)
 }
 const int X=80;  // max value
 const int Y=25;  // max value


 /*======= CLASS "BOX" FOR BORDER ======*/

 class box
 {
 private:
 int left,right,top,bottom;
 char str[L_MAX];
 int color;
 public:
 box()
 { 
 left=5;
 top=3;
 right=76;
 bottom=23;
 color=WHITE;
 }
 box(int l, int t, int r, int b, int c=WHITE)
 {
 left=l;
 top=t;
 right=r;
 bottom=b;
 color=c;
 strcpy(str,"  ");
 }
 void text(char s[])
 {strcpy(str,s);
 }
 void draw(int);
 void erase()
 {
 window(left,top,right,bottom);
 clrscr();
 } 
 } b(2,2,X-1,Y-1);
 

 void box::draw(int hold=1)
 {
 erase();
 window(left,top,right,bottom+1);
 int width=right-left+1;
 int height=bottom-top+1;
 textcolor(color);
 for(int j=1;j<=width; j++)
 {
 gotoxy(j,1); putch(char(205));   //top
 gotoxy(j,height); putch(char(205));    //bottom
 }
 for(j=1;j<=height; j++)
 {
 gotoxy(1,j); putch(char(186));                //left
 gotoxy(width,j); putch(char(186));             //right
 }
 gotoxy(1,1); putch(char(201));
 gotoxy(width,1); putch(char(187));
 gotoxy(1,height); putch(char(200));
 gotoxy(width,height); putch(char(188));
 window(left+2,top+1,right-2,bottom-3); //text window
 cputs(str);
 window(left,top,right,bottom+1);
 gotoxy(3,height-1);
 if(hold==1)
 cputs("..Press any key to continue..") ;
 textcolor(WHITE);
 }


 void intro()
 {
 int bg=1; // for blue
 textbackground(bg);
 int key=0;
 clrscr();
 int i;
 char str1[]="WELCOME TO THE 'BRAIN OPENER' E-LEARNING PORTAL";
 char str2[]=" DEVELOPED BY: ";
 char str3[]="CHIRAG JAIN";

 for(i=0;str1[i]!='\0';i++)
 {
 if(i%16!=bg&&i%16!=0)
 textcolor(i);
 else if(i%16==0) textcolor(6);
 else textcolor(4);
 gotoxy(13+i,5);
 putch(str1[i]);
  if(str1[i]!=' ')
  {
  gotoxy(13+i,6);
  cprintf("^");
  }
 delay(150);
 if(kbhit()) key=1;
 }
 gotoxy(15,13);
 for(i=0;str2[i]!='\0';i++)
 {
  putch(str2[i]);
 delay(80);
 if(key==1) {
 for(; str2[i]!='\0';i++) putch(str2[i]);
 break;}
 }
 textcolor(2);
 for(i=0;str3[i]!='\0';i++)
 {
 gotoxy(35+i,15);
 putch(str3[i]);
 gotoxy(35+i,16);
 putch('-');
 delay(150);
 if(key==1) {
 for(; str3[i]!='\0';i++) {
 gotoxy(35+i,15);
 putch(str3[i]);
 gotoxy(35+i,16);
 putch('-'); } break;}
 }
 strcpy(str2," UNDER THE GUIDANCE OF:");
 strcpy(str3,"SHEKHAR SIR");
 textcolor(YELLOW);
 gotoxy(15,18);
 for(i=0;str2[i]!='\0';i++)
 {
  putch(str2[i]);
 delay(80);
 if(key==1) {
 for(; str2[i]!='\0';i++) putch(str2[i]);
 break;}
 }
 textcolor(2);
 for(i=0;str3[i]!='\0';i++)
 {
 gotoxy(35+i,20);
 putch(str3[i]);
 gotoxy(35+i,21);
 putch('-');
 delay(150);
 if(key==1) {
 for(; str3[i]!='\0';i++) {
 gotoxy(35+i,20);
 putch(str3[i]);
 gotoxy(35+i,21);
 putch('-'); } break;}
 }
 gotoxy(15,24);
 textcolor(10);
 cprintf("Press any key to continue...........");

 // to flush extra characters in 'cin'

 while(kbhit()) {getch();};

 getch();
 }

 /*========  AN ABSTRACT CLASS "USER"  =========*/

 class user
 {   
 protected:
 char fname[15];
 char lname[15];
 char pass[16]; // 1 for '\0'
 public:
 char* re_fname() {
 return fname;
 }
 char* re_pass() {
 return pass;
 }
 virtual void input()=0;
 virtual void disp()=0;
 virtual void modify()=0;
 };
 class st:public user
 {
 protected:
 char cl[5];   // class in roman numerals
 char dob[11];
 public:
 void input()
 {
 b.draw(0);
 gotoxy(X/2-15,4);
 cprintf("Enter your details one by one: ");
 gotoxy(10,8);
 cprintf("First name : ");cout<<"\t \t" ;
 gets(fname);
 strupr(fname);
 gotoxy(10,10);
 cprintf("Last name : ");cout<<"\t \t" ;
 gets(lname);
 strupr(lname);
 gotoxy(10,12);
 cprintf("Class (in Roman Numerals) :     ");
 cin>>cl;
 gotoxy(10,14);
 cprintf("Date of birth (dd.mm.yyyy):     ");
 gets(dob);
 gotoxy(10,16);
 cprintf("Password (max. 15 characters) : ");
 input_pas(pass);
 gotoxy(X/2-20,20);
 cprintf("......Account created successfully......");
 gotoxy(X/2-14,21);
 cprintf("..Press any key to continue..");
 getch();
 }
 void modify()
 {
 char FNAME[15];
 char LNAME[15];
 char PASS[16]; // 1 for '\0'
 char CL[5];
 char DOB[11];
 b.draw(0);
 gotoxy(X/2-15,4);
 cprintf("Enter your details one by one:");
 gotoxy(X/2-18,5);
 cprintf(" (Press \".\" to retain old information)");
 gotoxy(10,8);
 cprintf("First name : ");cout<<"\t \t" ;
 gets(FNAME);
 strupr(FNAME);
 if(strcmp(".",FNAME)!=0) strcpy(fname,FNAME);
 gotoxy(10,10);
 cprintf("Last name : ");cout<<"\t \t" ;
 gets(LNAME);
 strupr(LNAME);
 if(strcmp(".",LNAME)!=0) strcpy(lname,LNAME);
 gotoxy(10,12);
 cprintf("Class (in Roman Numerals) :     ");
 cin>>CL;
 if(strcmp(".",CL)!=0) strcpy(cl,CL);
 gotoxy(10,14);
 cprintf("Date of birth (dd.mm.yyyy):     ");
 gets(DOB);
 if(strcmp(".",DOB)!=0) strcpy(dob,DOB);
 gotoxy(10,16);
 cprintf("Password (max. 15 characters) : ");
 input_pas(PASS);
 if(strcmp(".",PASS)!=0) strcpy(pass,PASS);
 gotoxy(X/2-20,19);
 cprintf("......Profile modified successfully......");
 gotoxy(X/2-14,20);
 cprintf("..Press any key to continue..");
 getch();
 }

 void disp()
 {
 clrscr();
 b.draw(0);
 textcolor(12);
 gotoxy(X/2-6,4);
 cprintf("MY PROFILE: ");
 gotoxy(X/2-10,5);
 echo('=',18);
 gotoxy(10,8);
 cprintf("First name : ");cout<<"\t \t" ;cprintf(fname);
 gotoxy(10,10);
 cprintf("Last name : ");cout<<"\t \t" ;cprintf(lname);
 gotoxy(10,12);
 cprintf("Class (in Roman Numerals) :     ");cprintf(cl);
 gotoxy(10,14);
 cprintf("Date of birth (dd.mm.yyyy):     ");cprintf(dob);
 gotoxy(10,16);
 cprintf("Password  : ");cout<<" \t \t";cprintf(pass);
 gotoxy(X/2-22,19);
 cprintf("..........Press any key to continue.........");
 getch();
 } 

 };

 /*=====  Class "TEACHER" derived from "USER" =====*/

 class teach:public user
 {
 protected:
 char cl[max_classes][5];
 char sub[20];
 public:
 char* re_sub() {
 return sub;     }
 char* re_cl()
 {
 	 return cl[0];
 }
 void input();
 void disp();
 void modify();
 };

 void teach::modify()
 { 
 char FNAME[15]; 
 char LNAME[15];
 char PASS[16]; // 1 for '\0'
 char CL[max_classes][5];
 char SUB[20];
 b.draw(0);
 gotoxy(X/2-15,4);
 cprintf("Enter your details one by one: ");
 gotoxy(X/2-18,4);
 cprintf("(Press \".\" to retain old information) ");
 gotoxy(10,8);
 cprintf("First name : ");cout<<"\t  \t" ;
 gets(FNAME);strupr(FNAME);
 if(strcmp(".",FNAME)!=0) strcpy(fname,FNAME);
 gotoxy(10,10);
 cprintf("Last name  : ");cout<<"\t  \t";
 gets(LNAME);
 strupr(LNAME);
 if(strcmp(".",LNAME)!=0) strcpy(lname,LNAME);
 gotoxy(10,12);
 cprintf("Subject    : ");cout<<"\t  \t";
 gets(SUB);
 if(strcmp(".",SUB)!=0) strcpy(sub,SUB);
 gotoxy(10,14);
 cprintf("Classes (in Roman Numeral) :  ");
 for(int i=0; i<max_classes; i++)
 {
 gotoxy(40,14+i);
 cin>>CL[i];
 if(strcmp(".",CL[i])!=0) strcpy(cl[i],CL[i]);
 }

 gotoxy(10,15+i);
 cprintf("Password (max. 15 characters) : ");
 input_pas(PASS);
 if(strcmp(".",PASS)!=0) strcpy(pass,PASS);
 gotoxy(X/2-20,18);                                       // changed
 cprintf(".......Profile modified successfully......");
 gotoxy(X/2-14,19);
 cprintf("..Press any key to continue..");
 getch();
 }
 void teach::disp()
 {
 b.draw(0);
 gotoxy(X/2-6,3);
 cprintf(" MY PROFILE ");
 gotoxy(X/2-10,4);
 echo('=',18);

 gotoxy(10,6);
 cprintf("First name : ");cout<<"\t  \t" ;cprintf(fname);
 gotoxy(10,10);
 cprintf("Last name  : ");cout<<"\t  \t";
 cprintf(lname);
 gotoxy(10,12);
 cprintf("Subject    : ");cout<<"\t  \t";
 cprintf(sub);
 gotoxy(10,14);
 cprintf("Classes (in Roman Numeral) :  ");
 for(int i=0; i<max_classes; i++)
 {
 gotoxy(40,14+i);
 cprintf(cl[i]);
 }
 gotoxy(10,15+i);
 cprintf("Password  : "); cout<<"\t \t";
 cprintf(pass);
 gotoxy(X/2-17,19);
 cprintf(".....Press any key to continue.....");
 getch();
 }

 void teach::input()
 {
 b.draw(0);
 gotoxy(X/2-15,4);
 cprintf("Enter your details one by one: ");
 gotoxy(10,8);
 cprintf("First name : ");cout<<"\t  \t" ;
 gets(fname);
 strupr(fname);
 gotoxy(10,10);
 cprintf("Last name  : ");cout<<"\t  \t";
 gets(lname);
 strupr(lname);
 gotoxy(10,12);
 cprintf("Subject    : ");cout<<"\t  \t";
 gets(sub);
 gotoxy(10,14);
 cprintf("Classes (in Roman Numeral) :  ");
 for(int i=0; i<max_classes; i++)
 {
 gotoxy(40,14+i);
 cin>>cl[i];
 } 

 gotoxy(10,15+i);
 cprintf("Password (max. 15 characters) : ");
 input_pas(pass);
 gotoxy(X/2-20,19);
 cprintf("......Account created successfully......");   
 gotoxy(X/2-14,20);
 cprintf("..Press any key to continue..");
 getch();
 }

 /*======= CLASS "QUESTION"  ========*/

 class question
 {
 char ques[120];
 char op_1[50],op_2[50],op_3[50],op_4[50];
 char ans; //'1' '2' '3' '4'
 char  expl[250];
 char diff;  // 'E' / 'M' / 'H' 
 public:
 void add_ques()
 {
  clrscr();
  b.draw(0);
  gotoxy(3,2);
  cout<<"Enter the question:      ";
  gotoxy(3,3);
  gets(ques);
  gotoxy(3,6);
  cout<<" Enter the first option :";
  gotoxy(3,7);
  gets(op_1);
  gotoxy(3,9);
  cout<<" Enter the second option :";
  gotoxy(3,10);
  gets(op_2);
  gotoxy(3,12);
  cout<<" Enter the third option :";
  gotoxy(3,13);
  gets(op_3);
  gotoxy(3,15);
  cout<<" Enter the fourth option :";
  gotoxy(3,16);
  gets(op_4);
  gotoxy(3,18);
  cout<<" Enter which option is correct :(1/2/3/4) \t";
  cin>>ans;
  gotoxy(3,20);
  clrscr();  
  b.draw(0);
  gotoxy(3,2);
  cout<<" Enter the explanation to question : ";
  gotoxy(3,3);
  gets(expl);
  gotoxy(3,7);
  cout<<"  Enter the difficulty level E(easy) or M(medium) or H(hard)\t ";
  cin>>diff;
  }
 void disp_ques(int qno );
 char * re_answer();            // to return correct answer
 char  re_diff(){return diff;}
 char re_coropt(){ return ans;}; // to return correct option
 char * re_exp()
 {
	return expl;}
 };


 void question::disp_ques(int qno )
 {
 char *q=ques;
 int len=strlen(ques);
 gotoxy(7,3);
 cout<<qno<<")  ";

  for(int i=0; i<63&&i<len;i++,q++) cout<<*q;
    gotoxy(7,4);

  for(i=0; i<63&&i+63<len;i++,q++) cout<<*q;
 gotoxy(6,6);
 cout<<"1. "<<op_1;
 gotoxy(6,7);
 cout<<"2. "<<op_2;
 gotoxy(6,8);
 cout<<"3. "<<op_3;
 gotoxy(6,9);
 cout<<"4. "<<op_4;
 }

 char * question:: re_answer()
 {
 if(ans=='1')
 return op_1;
 else if(ans=='2')
 return op_2;
 else if(ans=='3')
 return op_3;
 else if(ans=='4')
 return op_4;
 else return '\0'; 
 }


  int main()
  {

  char anss,ch_no,note[200];
  char NOTE[200];
  box q(3,2,78,23);
  int log=0,pos=0,y,i=0;
  char FNAME[15],PASS[16];
  fstream fstd(Srec,ios::binary|ios::in|ios::out);
  fstream easy,hard;
  ifstream quiz;
  fstream fteach(Trec,ios::binary|ios::in|ios::out);
  fstream fques;
  int temp; // used to store random value generated
  int sz_es,sz_hd;
  char res;
  int score=0;
  char expl[250];
  if(!fstd||!fteach) {
  cout<<"\n File not found";
  getch();
  exit(0); 
  }
  st s1;
  teach t1;
  question q1;
  char op;  // for main-menu
  char ch;  // for inner options (after login)
  clrscr();
  intro();
  clrscr();
  gotoxy(33,4);
  textcolor(RED);
  cputs("BRAIN OPENER");
  textcolor(YELLOW);
  gotoxy(33,5);
  cputs("^^^^^ ^^^^^^");
  box a(21,11,53,19,GREEN);
  a.text("This is a portal to provide E-learning facilities for the students of classes VI to XII");
  a.draw();
  sound(3000); delay(200); nosound();
  while(kbhit())
  {
  getch(); // to flush extra characters in 'cin'
  }  
  getch();

  do
  {
  textcolor(YELLOW);
  clrscr();  
  b.draw(0);
  gotoxy(34,2);
  cout<<" MAIN MENU ";
  gotoxy(28,3);
  echo('=',23);
  gotoxy(20,7);
  cout<<"1. Login as a student ";
  gotoxy(20,9);
  cout<<"2. Login as a teacher ";
  gotoxy(20,11);
  cout<<"3. Create a new student account ";
  gotoxy(20,13);
  cout<<"4. Create a new teacher's account ";
  gotoxy(20,15);
  cout<<"5. Instructions";
  gotoxy(20,17);
  cout<<"6. Exit";
  gotoxy(20,19);
  cout<<"Enter your choice here: \t  ";
  while(kbhit())
  {
  getch();}  // to flush extra characters in 'cin'
  op=getche();

  switch(op)
  {
  case '1':
  log=0;
  do
  {
  textcolor(13);
  clrscr();
  b.draw(0);gotoxy(25,21);
  cprintf("(Type 'Back' in first name to go back)") ;
  gotoxy(15,4);
  cprintf("Enter your first name: ");cout<<'\t';
  gets(FNAME);
  gotoxy(15,7);
  cprintf("Enter your password: ");cout<<'\t';
  input_pas(PASS);
  if(strcmpi(FNAME,"back")==0) {log=-1;
  break;
  }

  fstd.clear(); // to reset all the error flags
  // (otherwise it appears as if eof is reached)
  fstd.seekg(0,ios::beg);
  while(fstd.read((char*)&s1,sizeof(s1)))
  {
  if((strcmpi(FNAME,s1.re_fname())==0)&&(strcmp(s1.re_pass(),PASS)==0))
  { pos=fstd.tellg()-sizeof (s1);
  log=1;
  break;
  }
  }

// OPTIONS FOR STUDENT

  if(log==1)
  {
  	do
  {
  clrscr();
  textcolor(GREEN);
  b.draw(0);
  gotoxy(31,2);
  cout<<" WELCOME "<<s1.re_fname();
  gotoxy(28,3);
  echo('=',23);
  gotoxy(20,7);
  cprintf("1. LEARN A SUBJECT ");
  gotoxy(20,10);
  cprintf("2. TEST YOURSELF ");
  gotoxy(20,13);
  cprintf("3. VIEW YOUR PROFILE  ");
  gotoxy(20,16);
  cprintf("4. MODIFY  YOUR PROFILE ");
  gotoxy(20,19);
  cprintf("5. LOGOUT");
  gotoxy(20,21);
  cprintf(" PLEASE Enter your choice here : " );
  ch=getche();
  switch(ch)
  {
  case '1':
  int x;
  x=5;
  y=4;
   clrscr();
   q.draw(0);
      gotoxy(5,4);
      cout<<"The Chapters available are: "  ;
      gotoxy(5,8);
      cout<<"1. C++";
      gotoxy(5,10);
      cout<<"2. Networking";
      gotoxy(5,15);
      cout<<"Enter your choice here (1/2): ";
      gotoxy(5,17);
      ch_no=getche();  
      switch(ch_no)
      {
      case '1': strcpy(ch_nam,"C++.txt");
       break;
      case '2': strcpy(ch_nam,"Netw.txt");
       break;
      default: gotoxy(5,19);
       cout<<" Invalid Choice ! Try Again !! ";
       strcpy(ch_nam,"invalid");
       break;
      }
      gotoxy(21,21);
      cout<<".....Press any key to continue....";
      getch();
      if(strcmp(ch_nam,"invalid")==0)
	  {
		break;
	  }
      clrscr();
      q.draw(0);
	    nrec.clear();
      nrec.open(ch_nam,ios::in);
      nrec.seekg(0);
      if(!nrec)
	{
	  cout<<" Sorry File not available." ;
	  getch();
	  break;
	}
	    while(!nrec.eof())
	    {

       nrec.getline(NOTE,200,'\n');
	     if(nrec.eof())
       {
	gotoxy(25,21);
	cout<<"Press any key to continue...." ;
	while(kbhit()) {getch();};
	getch();
	break;
       }
       if(y>=17) {
		  gotoxy(25,21);
		  cout<<"Press any key to continue...." ;
		  y=4 ;
		  while(kbhit()) {getch();};
	getch();
		  clrscr();
      q.draw(0);
		  }
	      align(NOTE,x,y,68);
	for(int ctr=0; NOTE[ctr]!='\0'; ctr++) NOTE[ctr]='\0';
       ++y;
	     cout<<"\n \n ";
	     getch();
	     }
	    nrec.close();
	      break;

  case '2':

       // A random quiz of 5 questions
       // Each having 3 Easy and 2 difficult questions
      i=0;
      textcolor(YELLOW);
      clrscr();
      q.draw(0);
  gotoxy(6,5);
  cout<<"Welcome to the  Quiz prepared by the teachers of 'BRAIN OPENER'" ;
  gotoxy(4,8);
  cout<<"The rules are as follows: ";
  gotoxy(4,11);

  cout<<"1. Each Question has 4 choices out of which only one is correct.";
  gotoxy(4,13);

  cout<<"2. For each correct answer,(+4) marks will be awarded.";
  gotoxy(4,15);

  cout<<"3. For each wrong answer (-1) mark will be awarded.";
  gotoxy(4,17);

  cout<<"4. Entering wrong information may cause any discrepancies.";
  gotoxy(4,19);

  cout<<"5. The format will be as follows : 3 easy and 2 difficult questions";
  getch();
  easy.open("Easy.dat",ios::binary|ios::out);
  hard.open("Hard.dat",ios::binary|ios::out);
  fques.clear();
  fques.open(Qlist,ios::in|ios::binary);
  fques.seekg(0,ios::beg);
  sz_es=0;
  sz_hd=0;
  while(fques.read((char*)&q1,sizeof(q1)))
  {
  if(q1.re_diff()=='E')
  {
    easy.write((char*)&q1,sizeof(q1));
    sz_es++;
   }
  else if(q1.re_diff()=='H')
  {
   hard.write((char*)&q1,sizeof(q1));
   sz_hd++;
  }
  }
  if(sz_es<3||sz_hd<2)
  {cout<<"Not Enough Questions !! Try Again Later!!";
  getch();
  break;
  }
  hard.close();
  easy.close();

  randomize();   // to generate different random values everytime
	    char res;
	    score=0;
	    int flag;

  // For 3 Easy Questions

	   for(i=1; i<=3;i++)    
  {
  quiz.open("Easy.dat",ios::binary|ios::in);
  quiz.clear(); // to reset all the error flags 
  quiz.seekg(0);
  temp=random((sz_es)-i+1)*sizeof(q1);
  quiz.seekg(temp);
  quiz.read((char*)&q1,sizeof(q1));
  clrscr();
  q.draw(0);
  q1.disp_ques(i);
  gotoxy(7,13);
  cout<<" Enter your answer here: " ;
  gotoxy(36,13);
  cin>>res;
  if(res==q1.re_coropt()) {score+=4;
  gotoxy(5,15);
  cout<<" Keep it up! ";
  }
  else if(res=='1'||res=='2'||res=='3'||res=='4') {
  gotoxy(5,15);
  cout<<" Sorry, Wrong Answer ";
  score--;}
  else {
  gotoxy(5,15);
  cout<<" Invalid Choice !! ";
   }
  cout<<"The correct answer is "<<q1.re_answer();
  strcpy(expl,q1.re_exp());
  gotoxy(3,17);
  cout<<"Explanation-";
  int len=strlen(expl);
   for(int i=0; i<60&&i<len;i++) cout<<expl[i];
    gotoxy(3,18);
  for(i=0; i<70&&(i+60)<len;i++) cout<<expl[i+60];
    gotoxy(3,19);
  for(i=0; i<70&&(i+60+70)<len;i++) cout<<expl[i+60+70];
  gotoxy(25,21);
  cout<<"...Press any key to continue...";
  getch();
	  quiz.seekg(0);
	  flag=1;
  ofstream fin("temp.dat",ios::binary|ios::out);
  if(quiz.tellg()==temp) flag=0;
  while(quiz.read((char*)&q1,sizeof(q1)))
  {

  if(flag==1) fin.write((char*)&q1,sizeof(q1));
  if(quiz.tellg()==temp) flag=0; else flag=1;
  }
  quiz.close();
  fin.close();
  remove("Easy.dat");
  rename("temp.dat","Easy.dat");

  }

  // For 2 Hard Questions

     for(i=1; i<=2;i++)
	  {quiz.open("Hard.dat",ios::binary|ios::in);
	   quiz.clear(); // to reset all the error flags
     quiz.seekg(0);
     temp=random((sz_hd)-i+1)*sizeof(q1);
     quiz.seekg(temp);
     quiz.read((char*)&q1,sizeof(q1));
       clrscr();
      q.draw(0);
      q1.disp_ques(i+3);
  gotoxy(7,13);
  cout<<" Enter your answer here: " ;
  gotoxy(36,13);
  cin>>res;
  if(res==q1.re_coropt()) {score+=4;
  gotoxy(5,15);
  cout<<" Keep it up! ";
  }
  else if(res=='1'||res=='2'||res=='3'||res=='4') {
  gotoxy(5,15);
  cout<<" Sorry, Wrong Answer ";
  score--;}
  else {
  gotoxy(5,15);
  cout<<" Invalid Choice !! ";
  }
  cout<<"The correct answer is "<<q1.re_answer();
  strcpy(expl,q1.re_exp());
  gotoxy(3,17);
  cout<<"Explanation-";
  int len=strlen(expl);
   for(int i=0; i<60&&i<len;i++) cout<<expl[i];
    gotoxy(3,18);
  for(i=0; i<70&&(i+60)<len;i++) cout<<expl[i+60];
    gotoxy(3,19);
  for(i=0; i<70&&(i+60+70)<len;i++) cout<<expl[i+60+70];
  gotoxy(25,21);
  cout<<"...Press any key to continue...";
  getch();
  quiz.seekg(0);
  flag=1;
  ofstream fin("temp.dat",ios::binary|ios::out);
  if(quiz.tellg()==temp) flag=0;
  while(quiz.read((char*)&q1,sizeof(q1)))
  {
  
  if(flag==1) fin.write((char*)&q1,sizeof(q1));
  if(quiz.tellg()==temp) flag=0; else flag=1;
  }
  quiz.close();
  fin.close();
  remove("Hard.dat");
  rename("temp.dat","Hard.dat");
  }

  clrscr();
  gotoxy(25,16);
  cout<<"\a ********* Thank you*******";
  gotoxy(25,7);
  cout<<"Your score is  "<<score<<" out of 20";

  cout<<'\a';
  getch();
  fques.close();
  hard.close();
  quiz.close();
  easy.close();
	    break;
  case '3': s1.disp();
	     break;
  case '4': clrscr();
	    s1.modify();
	    fstd.clear();
	    fstd.seekp(pos);
	    fstd.write((char*)&s1,sizeof(s1));
	    break;
  case '5': ch='\0';
	     break;
  }
  }while(ch);
  }

  if(log==0)
  {
  gotoxy(30,11);
  cprintf("Sorry, Incorrect first name or password");
  gotoxy(30,13);
  cprintf(" Please try again!!");
  getch();
  }
  }while(log==0);
  break;
  case '2':
  log=0;
  do
  {
  textcolor(13);
  clrscr();
  b.draw(0);
  gotoxy(25,21);
  cprintf("(Type 'Back' in first name to go back)") ;
  gotoxy(15,4);
  cprintf("Enter your first name: ");cout<<'\t';
  gets(FNAME);
  gotoxy(15,7);
  cprintf("Enter your password: ");cout<<'\t';
  input_pas(PASS);
  if(strcmpi(FNAME,"back")==0) {log=-1;
  break;
  }
  fteach.clear(); // to reset all the error flags 
  fteach.seekg(0,ios::beg);
  while(fteach.read((char*)&t1,sizeof(t1)))
  {
  if((strcmpi(FNAME,t1.re_fname())==0)&&(strcmp(t1.re_pass(),PASS)==0))
  {
  pos=fteach.tellg()-sizeof(t1);
   log=1;
  break;
  }
  }

  // OPTIONS FOR TEACHER

  if(log==1)
  {
  do
  {
  clrscr();
  textcolor(GREEN);
  b.draw(0);
  gotoxy(31,2);
  cout<<" WELCOME "<<t1.re_fname();
  gotoxy(28,3);
  echo('=',23);
  gotoxy(20,7);
  cprintf("1. ADD NOTES FOR SUBJECT ");
  gotoxy(20,9);
  cprintf("2. ADD TEST QUESTIONS ");
  gotoxy(20,11);
  cprintf("3. VIEW TEST QUESTIONS");
  gotoxy(20,13);
  cprintf("4. MODIFY  YOUR PROFILE ");
  gotoxy(20,15);
  cprintf("5. VIEW YOUR PROFILE");
  gotoxy(20,17);
  cprintf("6. LOGOUT");
  gotoxy(20,20);
  cprintf(" PLEASE Enter your choice here : " );
  ch=getche();
  switch(ch)
  {
  case '1':
      clrscr();
      q.draw(0);
      gotoxy(5,4);
      cout<<"The Chapters available are: ";
      gotoxy(5,8);
      cout<<"1. C++";
      gotoxy(5,10);
      cout<<"2. Networking";
      gotoxy(5,15);
      cout<<"Enter your choice here (1/2): ";
      gotoxy(5,17);
      ch_no=getche();  
      switch(ch_no)
      {
      case '1': strcpy(ch_nam,"C++.txt");
       break;
      case '2': strcpy(ch_nam,"Netw.txt");
       break;
      default: gotoxy(5,19);
       cout<<" Invalid Choice ! Try Again !! ";
       strcpy(ch_nam,"invalid");
       break;
      }
      gotoxy(21,21);
      cout<<".....Press any key to continue....";
      getch();
      if(strcmp(ch_nam,"invalid")==0) {
	break;
      }
      clrscr();
	    nrec.open(ch_nam,ios::app|ios::out);
	    gotoxy(3,2);
	    cout<<"Enter the notes point wise (max 200 characters) ";
      cout<<" \n \t (add \"$\" to end a point )";
      cout<<"\n \n";
	    do
	    {
	    cin.getline(note,200,'$');
	    nrec<<'*'<<" "<<note<<'\n';
	    cout<<"  Do you want enter more (Y/N) \t ";
	    anss=getche();
	    cout<<"\n";
      }while(anss=='Y'||anss=='y');
	    nrec.close();
	      break;
  case '2': 
	    fques.open(Qlist,ios::ate|ios::binary|ios::out);
	       q1.add_ques();
	    fques.write((char*)&q1,sizeof(q1));
	       fques.close();
	      break;
  case '3':
	    fques.open(Qlist,ios::binary|ios::in);
	     fques.clear();
	    fques.seekg(0);
	    dis=1;
	    while(fques.read((char*)&q1,sizeof(q1)))
	    {
	    clrscr();
	    q.draw(0);
	    q1.disp_ques(dis); 
	    dis++;
	    gotoxy(25,21);
  cout<<"...Press any key to continue...";
	    while(kbhit()) getch();
      getch();
	    }
	    fques.close();
	    break;
  case '4': clrscr();
	    t1.modify();
	    fteach.clear();
	    fteach.seekp(pos);
	    fteach.write((char*)&t1,sizeof(t1));
	    break;
  case '5':  clrscr();
	     t1.disp();
	     break;
  case '6': ch='\0';
	     break;
   }
  fques.close();
  }while(ch);
  }
  if(log==0)
  {
  gotoxy(30,11);
  cprintf("Sorry, Incorrect first name or password");
  gotoxy(30,13);
  cprintf(" Please try again!!");
  getch();
  }
  }while(log==0);

  break;
  case '3':
  clrscr();
  textcolor(YELLOW);
  s1.input();
  fstd.clear();
  fstd.seekp(0,ios::end);
  fstd.write((char *)&s1,sizeof(s1));
  break;
  case '4':
  clrscr();
  textcolor(YELLOW);
  t1.input();
  fteach.clear();
  fteach.seekp(0,ios::end);
  fteach.write((char *)&t1,sizeof(t1));
  break;
  case '5':
  // Instructions
  clrscr();
  textcolor(YELLOW);
  b.draw(0);
  gotoxy(31,2);
  cout<<" INSTRUCTIONS ";
  gotoxy(24,3);
  echo('=',27);
  textcolor(WHITE);
  gotoxy(10,5);
  cout<<"1. The Portal works has a dual level structure - ";
  gotoxy(10,6);            // self-sustained
  cout<<"Teacher level and Student level ";
  gotoxy(10,8);
  cout<<"2. Only authorised teachers can log in, create the study";
  gotoxy(10,9);
  cout<<" material and create or modify the question bank for quiz .";
  //This ensures data security
  gotoxy(10,11);
  cout<<"3. Similarly, a student can also create an account,";
  gotoxy(10,12);
  cout<<" view the study material and take a quiz on whichever ";
  gotoxy(10,13);
  cout<<"chapters he desires.  ";
  gotoxy(10,15);
  cout<<"4. A special feature of the quiz is that the teacher  ";
  gotoxy(10,16);
  cout<<" can mark the difficulty level of a question as 'Easy'";
  gotoxy(10,17);
  cout<<" 'Medium' and 'Difficult' so that all the students get";
  gotoxy(10,18);
  cout<<" the same level of questions, though the questions being";
  gotoxy(10,19);
  cout<<" randomly selected.";
  gotoxy(10,22);
  cout<<"         ...Press any key to continue...";  

  getch();
  break;
  case '6':
  fteach.close();
  fstd.close();
  exit(0);
  break;
  default:
  gotoxy(47,22);
  cout<<"Invalid Choice, Try Again !!!";
  getch();
  }
  }while(1);
  }
