/*
This program is for adding noisy to a set of coordinates it needs a input file in the format as follows

atom name   coordinate x    coordinate y  coordinate z

or more explicitly 

H  1 1 1 
S  1 1 1
O  1 1 1 

The program will ask the user for the amount of noise which should be given as a integer amount fraction of 1000
It is designed for fractional coordinates. 

For example if you want +/-0.5 maximal noise then  the user should enter 500

The 0.5 sets upper and lower limits on the noise and a random generator is used to distribute the noisy between 
+/- of this maximum.  Whether the noise is +/- is also determined by a random number generator
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int main() 
{

string line;        // used to pull lines out of the original coordinates file
string name;        // used to take input for name of original coordinates file
string  file_name;  // coordinates file name placed here using istringstream and then used in ifstream to open file
int  noise_amount;  
int count = 1;      // used while looping through input coordinate file to make to number to help seed srand to get a better random number

// here the user will first be asked for the noise amount and then the name of there original coordinates file both the input and output
// files are then opened 

cout << "\n\nEnter the amount of noise as a fraction of 1000 for example for 0.0025 in noise +/- (in fractional coordinates) enter 25\n";
	cin >> noise_amount;

cout << "\n\nEnter the name of the input file with the coordinates you want noisy\n\n The name of the noisy coordinates file will be noisy_coordinates.txt";
	cin >> name;
	istringstream filename(name);
	filename >> file_name;

double a, b, c;
cout << "\nadd noise to a axis? 0 for no 1 for yes\n"; cin >> a;
cout << "\nadd noise to b axis? 0 for no 1 for yes\n"; cin >> b;
cout << "\nadd noise to c axis? 0 for no 1 for yes\n"; cin >> c;

ifstream coordinates_file (file_name.c_str());
ofstream noisy_coordinates ("noisy_coordinates.txt");
srand(time(NULL));

if(coordinates_file.is_open()&&noisy_coordinates.is_open())  // make sure files are opened if they are not user will be told
{

while (getline(coordinates_file,line))                       // read input file line by line
	{

	istringstream iss(line);                            // stream the line from input file
	double  n;                                          // temporarily holds the input coordinate
	string  atom_type;                                  // holds name of atome
	double  random_bool;                                // used to determine wether to +/- the noise
	
	double  new_coordinates[3];                         // to hold the new and noisy coordinates

//loop to deal with each entry for each line
	for(int x=0; x<4 ; x++)
		{
		
			if(x==0){ iss >> atom_type; }                //first entry is the atom type name

			if(x>0){iss>>n; }  //if x the loop count is greater than one noise is going to be added seed srand well enough to produce reasonable
								     // random numbers 
		
			if(x==1)  // x=1 is the x or a cordinate  random_bool(not a true bool) is first assigned to determine wheter +/-
			          // srand is seeded again  to ensure the noise is also sufficiently random
			       {
					random_bool= (rand()%10000)/10000.0; 
						if(random_bool>0.5)
							{ 
								//srand(time(NULL)*n*count); 
								new_coordinates[0]= n + a*(rand()%noise_amount)/10000.0;
							}
						if(random_bool<=0.5)
							{      // srand(time(NULL)*n*count);
								new_coordinates[0]= n - a*(rand()%noise_amount)/10000.0;
							}
				}
			
			if(x==2)  // y or b coordinate same procedure as above
			       {
					random_bool= (rand()%10000)/10000.0; 
						if(random_bool>0.5)
							{ 
								//srand(time(NULL)*n*count); 
								new_coordinates[1]= n + b*(rand()%noise_amount)/10000.0;
							}
						if(random_bool<=0.5)
							{      // srand(time(NULL)*n*count);
								new_coordinates[1]= n - b*(rand()%noise_amount)/10000.0;
							}
				}


			
			if(x==3)  //  z or c coordinate same procedure as above
			       {
					random_bool= (rand()%10000)/10000.0; 
						if(random_bool>0.5)
							{ 
								//srand(time(NULL)*n*count); 
								new_coordinates[2]= n + c*(rand()%noise_amount)/10000.0;
							}
						if(random_bool<=0.5)
							{      // srand(time(NULL)*n*count);
								new_coordinates[2]= n - c*(rand()%noise_amount)/10000.0;
							}
				}
							
		

			
		}


	for(int x=0; x<4 ; x++)  // This loop takes the atom type and new noisy coordinates from the most recent line of the input file and writes it out to the
				//  noisy_coordinates.txt file
		{
			if(x==0)
				{ noisy_coordinates << atom_type << "\t";}
			if(x>0)
				{ noisy_coordinates.setf(ios::showpoint); noisy_coordinates.width(11); noisy_coordinates << new_coordinates[x-1]<< "\t";}
			
		}
	noisy_coordinates << "\n";
	
        count++;
	}
}
else {cout << "\nThe files failed to open\n";} // Let the user know if there was a problem opening the input and output files

coordinates_file.close();
noisy_coordinates.close();





return 0;
}
