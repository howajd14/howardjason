#include "../../../../../cpp_programs/classes/file_class/file.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using name space std; 

int main()
{
int ne = 700000;
int  vec_array[ne][24]; 
srand(time(NULL)); 
for(int x=1; x<=ne; x++)
{
for(int y=1; y<=24; y++){vec_array[x-1][y-1]=0;}
}

for(int x=1; x<=ne; x++)
{
	int count =0; 
        while(count < 16)
	{
		ri = rand()%24+1; 
		if(vec_array[x-1][ri-1]==0){vec_array[x-1][ri-1]=1; count = count +1; }
	}
}

int cnt_degen; 
for(int x=1; x<=ne; x++)
{
	for(int y=1; y<=ne; y++)
	{
		int dot =0
		for (int ii=1; ii<=24; ii++)
		{
			dot = dot + vec_array[x-1][ii-1]*vec_array[y-1][ii-1]; 
		}
		if(dot == 16){cnt_degen++;}
	}
}
cout <<"\n\n" << (cnt_degen - ne) << "\n\n"; 
return 0;
}
