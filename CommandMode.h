//ISHAN TYAGI 
//ROLLNO- 2018201017



#include <bits/stdc++.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "remove_dir.h"
using namespace std;
#define BUFF_SIZE 1024

string current_path;

void copy_file(vector<string> g){
       string path=g[g.size()-1];
       string temp;
       int srcFD,destFD,nbread,nbwrite;
       char *buff[BUFF_SIZE];
       for(int i=1;i<g.size()-1;i++){
       srcFD = open(g[i].c_str(),O_RDONLY);
       temp=path +"/"+g[i];
       destFD = open(temp.c_str(),O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
 
	if(destFD == -1)
	{
		printf("\nError opening file %s errno = %d\n",temp,errno);
		exit(EXIT_FAILURE);
	}
 
	/*Start data transfer from src file to dest file till it reaches EOF*/
	while((nbread = read(srcFD,buff,BUFF_SIZE)) > 0)
	{
		if(write(destFD,buff,nbread) != nbread)
			printf("\nError in writing data to %s\n",temp);
	}
       }
}
void copy(vector<string> g){
	   string name=g[g.size()-1];
       string temp;
       int srcFD,destFD,nbread,nbwrite;
       char *buff[BUFF_SIZE];
       //for(int i=0;i<g.size()-1;i++){
       srcFD = open(g[1].c_str(),O_RDONLY);
       temp=name+g[0];
       destFD = open(temp.c_str(),O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
 
	if(destFD == -1)
	{
		printf("\nError opening file %s errno = %d\n",temp,errno);
		exit(EXIT_FAILURE);
	}
 
	/*Start data transfer from src file to dest file till it reaches EOF*/
	while((nbread = read(srcFD,buff,BUFF_SIZE)) > 0)
	{
		if(write(destFD,buff,nbread) != nbread)
			printf("\nError in writing data to %s\n",temp);
	}
	   }


void copy_dir(vector<string> d){
	//cout << "in copy dir "<< endl ; 
	DIR *dir_ptr;
    struct stat fileInfo;
    struct dirent *direntp;
    string source=d[1];
    string destination=d[2];
    if(source =="." && source =="..")
    	return ;
	if( (dir_ptr = opendir(source.c_str())) == NULL )
   {
      printf(" cannot open %s for copying\n", source);
      return ;
   }
   else
   {
   	//cout << "source and directory "<< source << " " << destination << endl ;
      while( (direntp = readdir(dir_ptr)))
      { 
       if(strcmp(direntp -> d_name , ".") && strcmp(direntp -> d_name,  ".."))
       {     
       stat(direntp->d_name,&fileInfo);
        //cout << direntp ->d_name << endl ;
        char tempDest[1000];
        //char tempD[1000];
        //char tempS[1000];
        strcpy(tempDest, destination.c_str()); 
        strcat(tempDest , "/");
        strcat(tempDest, direntp->d_name); 
        //strcat(tempD, direntp->d_name);
        char tempSrc[1000];
        strcpy(tempSrc, source.c_str()); 
        strcat(tempSrc , "/");
        strcat(tempSrc, direntp->d_name); 
        //cout << tempSrc << " "<<tempDest << endl ;
          if(stat(tempSrc, &fileInfo) >=0)
          if(S_ISREG(fileInfo.st_mode)) 
          {
          	vector<string> s;
          	s.push_back(direntp ->d_name);
          	s.push_back(tempSrc);
          	s.push_back(tempDest);
          	copy(s);
          }
          
          if(S_ISDIR(fileInfo.st_mode))
          {
            mkdir(tempDest,0777);
            vector<string> s;
          	s.push_back("1");
          	s.push_back(tempSrc);
          	s.push_back(tempDest);
            copy_dir(s);
          }  
       }
   		}
      }
      closedir(dir_ptr);

}

void snap_shot(string pat,string name,string file_name){
  FILE *d;
  struct dirent **r;
  d =fopen(file_name.c_str(),"a");
  int n=scandir(pat.c_str(),&r,NULL,alphasort);
  fprintf(d, "%s\n",name );
  if(n==2){
  	return ;
  }
  for(int i=2;i<n;i++)
  	fprintf(d, "%s\t",r[i]->d_name );

  for(int i=2;i<n;i++){
  	if(r[i]->d_type==DT_DIR)
  		snap_shot(pat+"/"+r[i]->d_name,r[i]->d_name,file_name);
  }
  fclose(d);

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CommandMode(){
	printf("\033[30;1H");
	printf("===========================================================================================================================================\n");
	printf("Command Mode:\n");
	label:
	string input="";
	vector<string> input_token;
	printf("\033[32;1H");
	printf("Enter the Command >>");
	while(1){
		char g=getchar();
		if(g==27)
			return ;
		cout << g;
        if(g==10)
        {	input_token.push_back(input);
        	break;
        }
		if(g !=' ')
		{
            input += g;
		}
		else
		{	input_token.push_back(input);
            input="";
		}


	}
	
	//cout<< current_path<<endl;
	
	string a="copy_file";
	string b="move";
	string c="rename";
	string d="create_file";
	string e="create_dir";
	string f="delete_file";
	string g="search";
	string h="snapshot";
	string i="delete_dir";
	string j="goto";
	string k="copy_dir";
 
	if(input_token[0]==a)
	{
		
		copy_file(input_token);
	}
	
	else
		if(input_token[0]==b)
			{   
				int n=static_cast<int>(input_token.size());
				//cout << n;
				/*string mo=input_token[2] + "/" + input_token[1];
				rename(input_token[1].c_str(), mo.c_str());*/
				//move(v);
                string  pad=input_token[n-1];
                for(int i=1;i<input_token.size()-1;i++)
               {
               		string g=current_path +"/"+input_token[i];

    				string mo=current_path +"/"+pad + "/" + input_token[i];
    			//cout << "Path created is : " << s << endl;
    		    rename(g.c_str(), mo.c_str());
    }
				
    }			
	else
		if(input_token[0]==c)
			{	
				//cout <<"rename";
				string b= current_path +"/"+input_token[1];
				string s=current_path + "/"+input_token[2];
    	        rename(b.c_str(), s.c_str());
		    }
	else
		if(input_token[0]==d)
			{
			//makeFile(input_token[1],input_token[2]);
			if(f=="."){
		         
		         std::ofstream o(current_path.c_str());
	       }
			else{
			string a=input_token[2] + "/" +input_token[1];
       			std::ofstream o(a.c_str());
			}
	}	
	else
		if(input_token[0]==e)
			{
				//make_dir(input_token[1],input_token[2]);   
				 if(d == "."){
                 mkdir(current_path.c_str(), (S_IRWXG | S_IRWXU));
             }
    
     	else 
    		if(1){
     	string s=input_token[2];
     	string a=input_token[1];
     	s=s + "/"+a;
    	if(mkdir(s.c_str(),(S_IRWXG | S_IRWXU))){
     //int_error(argv[0], argv[1]);
     }
 		}
	}	
	else
		if(input_token[0]==f)
			{
				//delete_file();
				string s=input_token[2] +"/"+input_token[1];
				remove(s.c_str());
	}	
	else
		if(input_token[0]==g)
			{
				//search();
		}

	else
		if(input_token[0]==h){
		 FILE * d;
		 char a[1024];
		 cout << current_path << endl;
		 string q=getcwd(a,sizeof(a));
		 d=fopen((q+"/"+current_path+"/"+input_token[2]).c_str(),"w");
		 snap_shot(current_path+"/"+input_token[1],input_token[2],q+"/"+current_path+"/"+input_token[2]);
		 fclose(d);

			
		}
	else
		if(input_token[0]==i){
			//delete_dir(input_token[1],input_token[2]);
			string g=input_token[2]+"/"+input_token[1];
			delete_dir(g.c_str());
		}

	else
		if(input_token[0]==j){
			//goto;
		if(input_token[1]=="/")
				{
					current_path=".";
					return ;
				}
			else
			{
				current_path=current_path + "/" +input_token[1];
			    return;
		}
		}

	else
		if(input_token[0]==k){
			copy_dir(input_token);

		}

		else{
			printf("Command Not found\n");
		}
goto label;
}
