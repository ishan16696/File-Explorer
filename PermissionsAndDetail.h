//ISHAN TYAGI 
//ROLLNO- 2018201017




#include <bits/stdc++.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
using namespace std;
std::vector<string> v;
struct stat filestatus; // to print the details of files and dir

void permission(string b){

    struct passwd *p;
    struct group *g;
        
    struct dirent **namelist;
        v.clear();
        int n;
        n=scandir(b.c_str(),&namelist,NULL,alphasort);

        if(n < 0)
        {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        else
        {
            while (n--)
            {
                
                    v.push_back(namelist[n]->d_name);
                
            }
            
        }
        
      sort(v.begin(),v.end());
      printf("\033c");// to clear the screen
      for(int i=0;i<v.size();i++)
        {

        cout << v[i] << "       "; 
         stat (namelist[i]->d_name,&filestatus);
              

    
    printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
    printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
    printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
    printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
    printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
    printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
    printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
    printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
    printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
    printf( (filestatus.st_mode & S_IXOTH) ? "x" : "-");
    p=getpwuid(filestatus.st_uid);
    g=getgrgid(filestatus.st_gid);
    printf("%s",p->pw_name );
    printf("%s",g->gr_name);
    printf(" %ldKB",filestatus.st_size/1024);
    printf("%s",ctime(&filestatus.st_ctime));//Print the date and time of last modified
    

        }

}
