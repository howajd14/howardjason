#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <chrono>
#include <ctime>
#include <ratio>
using namespace std::chrono;

class rand_num
{


public: 

	 rand_num();
	~rand_num();
	
	int get_rand_int(int range)
	{
	      
                chrono::high_resolution_clock::time_point  t2 = chrono::high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2-t1); 
		double time_gap = time_span.count(); 
		
			while(time_gap==0||time_gap==old_gap)
			{
			        chrono::high_resolution_clock::time_point  t3 = chrono::high_resolution_clock::now();
				duration<double> time_span_2 = duration_cast<duration<double>>(t3-t1); 
				time_gap = time_span_2.count(); 
			}
			for(int xx = 1; xx <=1000000; xx++){xx = xx;}
		
		//cout << "\n" << time_gap; 
		 int seed =  int (time_gap*1000000);
		srand(seed + time(NULL));
		old_gap = time_gap; 
		int holder = range + 1;
		random_int = rand()%holder;
                return random_int;
	}

private:

int random_int; 
int clock_time; 
double old_gap; 

chrono::high_resolution_clock::time_point t1; 



};

rand_num::rand_num()
{
   
    t1 = chrono::high_resolution_clock::now();
    random_int = 1;
    old_gap = 0; 
   
}

rand_num::~rand_num()
{}


