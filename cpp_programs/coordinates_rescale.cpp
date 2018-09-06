/*
This program is for taking a set of coordinates and scaling them axis by axis according
to scaling factors provided by an input file

the format of the input file is as follows

x-scaling factor
y-scaling factor
z-scaling factor

it requires a file whose name will be specified by the user at compile time that has a list of
the coordinates to be scaled. The format of these coordinates needs to be as follows

atom name  coordinate-x coordinate-y coordinate-z 

for example

Li 1  1  1 
Li .5 1  1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
 
string line;               //will hold lines drawn from the scaling factor file and coordinates to be scaled file

vector<double> x_scale;    //will hold x_coordinate scaling factor
vector<double> y_scale;    //will hold y_coordinate scaling factor
vector<double> z_scale;    //will hold z_coordinate scaling factor
string atom_name;          //will hold name of atom
string file_name, name;    //used for reading in name of scaling factors file and coordinates to be scaled file from user input

/*
This first section of code prompts the user for the name of the file containing the scaling factors and then opens the file to 
read in the scaling factors to x_scale y_scale and z_scale vectors. Vectors are used for these instead of doubles to allow for 
adapation for more complex operations to the coordinatess

don't forget to scale the vectors in your run file!
*/
cout << "\n\n Enter the name of the file that contains the scaling factors. If you have trouble the format is: \n";
cout << "\nx_coordinate scaling factor\ny_coordinate scaling factor\nz_coordinate scaling factor\n\n";
	cin >> name;
	istringstream scaling_name(name);
	scaling_name >> file_name;


ifstream  trans_file (file_name.c_str());

if (trans_file.is_open())
{      
	int count_1 = 1;
	while (getline (trans_file,line))
	{
		istringstream iss(line);
		double holder;
			while(iss>>holder)
				{
				if (count_1==1)
					{x_scale.push_back(holder);}
				if (count_1==2)
					{y_scale.push_back(holder);}
				if (count_1==3)
					{z_scale.push_back(holder);}
				}
        
	count_1 = count_1 + 1;
	}
}
else 
{ cout << "\n Scaling factors file failed to open";}	//let the user know if the scaling factors file falied to open


trans_file.close();

/*
The next section of code first prompts the user for the name of the file containing the list of coordinates to be scaled
it then opens this file and the output file where the scaled coordinates will be written to. 
It then reads throught the unscaled coordinates line be line while then scaling them and writting them back out line by line
to the new scaled coordinate file
*/

cout << "\nEnter the name of the file containing the list of coordinates to be scaled\n";
	cin >> name;
	istringstream unscaled_coords(name);
	unscaled_coords >> file_name;
	

ifstream myfile (file_name.c_str());

ofstream anotherfile ("scaled_coordinates.txt");

if(myfile.is_open()&& anotherfile.is_open())   //check if both input and output files are open before proceding 
{


while ( getline (myfile,line)) 
{ 
	istringstream iss(line); 
	double n;  vector<double> v;          //n temporarily holds coordinate to be scaled. v temporarily holds the scaled coordinates before the are written out
	
		for(int ii=0; ii<4; ii++)     // this loop takes care of reading in the atom name then coordinates to be scaled(while simultaneously scaling them)
		{
			if(ii==0)
				{iss>>atom_name;  }
			if(ii>0)
			{
				iss>>n;	if(n<0){n=n+1;}	
				
				if(ii==1)
					{n= (n*x_scale[0]);}
				if(ii==2)
					{n= (n*y_scale[0]);}
				if(ii==3)
					{n= (n*z_scale[0]);}
			
			v.push_back(n);
                	
			}
		
		}
		for(int ii=0;ii<4;ii++)    //this loop takes care of writing out the most recently scaled atomic coordinate
		{
			if(ii==0)
			{anotherfile<<atom_name<<"\t";}
			if(ii>0)
			{
			anotherfile.setf(ios::showpoint);
			anotherfile.width(11);
			anotherfile<<v[ii-1] ; anotherfile << "\t";
			}
		}
	

	anotherfile<< "\n";
}

	
	myfile.close();
	anotherfile.close();

}

else cout<<"unable to open either the input coordinate file or output scaled coordinate file ";

cout << "\n\nThe name of your scaled coordinate file is 'scaled_coordinates.txt'.\n\n";

return 0;
}



