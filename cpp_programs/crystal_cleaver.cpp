/*
This program is for cleaving a set of coordinates above a certain cut off provided by the user

the inputs are a file containing the coordinates at which to perform the cleave and a file containing
the coordinates to cleave

the format for the  file containing the coordinates to cleave is

x-cleave coordinate
y-cleave coordinate
z-cleave coordinate

the format for the input file of coordinates to cleave is

atom name x-coordinate y-coordinate z-coordinate
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {

string line;

vector<double> x_cleave;   //will hold x coordinate cleave
vector<double> y_cleave;   //will hold y coordinate cleave
vector<double> z_cleave;   //will hold z coordinate cleave
vector<string> s;

string  cleave_file_tmp,coord_file, name;   //used for getting info from user on name of file containing the cleave coordinates

cout << "\n\nWhat is the name of the file containing your cleave coordinates file?\n\n";
	cin >> name;
	istringstream cleave_name(name);
	cleave_name >> cleave_file_tmp;

/*
This first block of code opens the file containing the cleave coordinates it then checks to make sure it is open. Then the file is read and
the cleave coordinates are placed in the appropriate vectors. Vectors are used in case the program is desired to be used for more complex purposes
and more inputs will be included. 
*/


ifstream  cleave_file (cleave_file_tmp.c_str());

if (cleave_file.is_open())
{      
	int count_1 = 1;
	while (getline (cleave_file,line))
	{
		istringstream iss(line);
		double holder;
			while(iss>>holder)
				{
				if (count_1==1)
					{x_cleave.push_back(holder);}
				if (count_1==2)
					{y_cleave.push_back(holder);}
				if (count_1==3)
					{z_cleave.push_back(holder);}
				}
        
	count_1 = count_1 + 1;
	}
}
else 
{ cout << "\n cleave coordinates file failed to open";}	//let the user know if the file did not open


cleave_file.close();

/*
This next block code gets the name of the coordinate file to be cleaved from the user then opens it. 
After opening it, it reads through line by line checking if whether to ommit the coordinate or not then writing
the coordinates not omit out line by line to a file "cleaved_coordinates.txt"
*/


cout << "\n\nWhat is the name of the file containing the coordinates you want cleaved?\n\n";
	cin >> name;
	istringstream coordinates_file(name);
	coordinates_file >> coord_file;

ifstream myfile (coord_file.c_str());

ofstream anotherfile ("cleaved_coordinates.txt");

if(myfile.is_open()&& anotherfile.is_open()) {

int counter_2=0;
while ( getline (myfile,line)) 
{ 
	istringstream iss(line); 
	double n;  vector<double> v; string string_holder; int bool_var=0; 
	
		for(int ii=0; ii<4; ii++)
		{
			if(ii==0)
				{iss>>string_holder;  s.push_back(string_holder);}
			if(ii>0)
			{
				iss>>n;		
				
				if(ii==1&&(n>x_cleave[0]))
					{ bool_var=1;}
				if(ii==2&&(n>y_cleave[0]))
					{bool_var=1;}
				if(ii==3&&(n>z_cleave[0]))
					{bool_var=1;}
			
			v.push_back(n);
                	
			}
		
		}
       if(bool_var==0)
	{
		for(int ii=0;ii<4;ii++)
		{
			if(ii==0)
			{anotherfile<<s[counter_2]<<"\t";}
			if(ii>0)
			{
			anotherfile.setf(ios::showpoint);
 			anotherfile.width(11);
			
			anotherfile<<v[ii-1] ; anotherfile << "\t" ; 
			}
		}
	anotherfile<< "\n";
	}

	counter_2=counter_2 +1;

	
}

	
	myfile.close();
	anotherfile.close();

}

else cout<<"unable to open either your coordinates file or the oput cleaved_coordinates file ";

cout << "\n\nThe name of your cleaved coordinates file is cleaved_coordinates.txt\n\n";

return 0;
}
