//ISHAN TYAGI 
//ROLLNO- 2018201017





#include <bits/stdc++.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "PermissionsAndDetail.h"
#include "nonCanonical.h"
#include "CommandMode.h"
using namespace std;

//global variable
char cwd[10240];
 //string to_avoid;
//to_avoid=cwd;
stack<string> r;
stack<string> l;

string pathCalc(string cur){
      string s= current_path;
      l.push(s);
      while(!r.empty())
        r.pop();
      s=s+ "/" + cur;
      current_path=s;
      return s;
}


int main()
{       
	    getcwd(cwd, sizeof(cwd));
        current_path=cwd;
        
        //printf("%d\n",x );
       
        permission(cwd);
 printf("\033[1;1H");

init_keyboard();   
char ch;
int y=1; 
int x=1;
 printf("\033[1;1H");
while(1){
ch=getchar();

if(ch==65)
    {
    if(x>1)
      x--;
    printf("\033[%d;%dH",x,y);
   }

    if(ch==66)
{ if(x<25)
      x++;
printf("\033[%d;%dH",x,y);
}

    if(ch==10)
{
    string path = pathCalc(v[x-1]);
stat (v[x-1].c_str(),&filestatus);
if(!S_ISDIR(filestatus.st_mode)){
   // system(("xdg-open "+ v[x-1]).c_str());// to open the application
	pid_t pid=fork();
	if(pid==0){
		execl("/usr/bin/xdg-open","xdg-open",path.c_str(),(char*)0);
		exit(1);
		wait(NULL);
	}
}
//else{
printf("\033c");

permission(path);
x=1;y=1;
 printf("\033[1;1H");
//}
 
   }

    if(ch==67){
      //Right Arrow
   if(!r.empty())
   {
          string b=r.top();
          r.pop();
          l.push(current_path);
          permission(b);
          
   }

}

    if(ch==68){
//Left Arrow
    if(!l.empty())
       {
          string b=l.top();
          l.pop();
          r.push(current_path);
          permission(b);
          
       }

}

    if(ch==127){
       //Backspace ---> move to the parent directory
        string s=current_path;

         while(!r.empty())
             r.pop();

      int n=s.length();
      int i;
     for(i=n-1;i>=0;i--)
     {
      if(s[i]=='/')
         break;

    }
       s.resize(i);
      current_path=s;
       permission(s);
      x=1;y=1;
       printf("\033[1;1H");
        
    }


    if(ch=='h')
    {
        current_path=cwd;
        while(!r.empty())
             r.pop();
        permission(current_path);


    }

   	   if (ch==':')
   		{
   		CommandMode();
        permission(current_path);
   		}
}

close_keyboard();


    return 0;
}