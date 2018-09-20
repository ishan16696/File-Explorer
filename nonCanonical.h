//ISHAN TYAGI 
//ROLLNO- 2018201017



#include <bits/stdc++.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

static struct termios initial_settings, new_settings;

//to initiate the non-canonical mode
void init_keyboard()
{
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
tcsetattr(0, TCSANOW, &new_settings);

}

//to close the non-canonical mode
void close_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}

//#endif