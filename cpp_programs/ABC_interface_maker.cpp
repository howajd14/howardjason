/*
This program is to make a solid single atom type interface that uses a AB stacking scheme.  It takes as arugments from and input file
the number of planes vertical and the length and width of the rows in atoms for each row. 
the AB stacking is staggard along the x direction
*/




#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int main() {


vector<string> interface_types;

vector<double> interface_dimension;
string line;
string atom_type;
int num_rows;
int length_rows;
int width_rows;




ifstream  interface_info ("interface_info.txt");

if (interface_info.is_open())
{

// the first line of the code is to get the atom type of the interface 
	getline(interface_info,line);
	atom_type=line;


//the second line gets the dimension of the interface
// the dimensions are put in order to a vector 
// 1st entry lower bound x,  2nd entry upper bound x direction
// so on in the same manner for y and z
// dimensions should be placed in order on the same line in the input file

	getline(interface_info,line);
	istringstream ass(line); 
	double holder;
	for(int x=0;x<6;x++)
	{ ass >> holder; interface_dimension.push_back(holder);  }



// the third line is how many rows  

	getline(interface_info,line);
	istringstream lss(line); lss >> num_rows;

//  the fourth line is the row length
	
	getline(interface_info,line);
	istringstream tss(line); tss >> length_rows;

// the fifth line is the row width 

	getline(interface_info,line);
	istringstream gss(line); gss >> width_rows;

	


    
interface_info.close();

}

else { cout << "\n inferface_info file failed to open" ;}




//the interface will now be created as a labeled text file "interface.txt" it is made in fractional coordinates


ofstream interface ("interface.txt");


if (interface.is_open())



{
    
	for(int kk=1; kk<=num_rows; kk++)
		{   
		
			for(int ii=0;ii<length_rows;ii++)
			{
				for(int jj=0;jj<width_rows;jj++)
				{
					interface << atom_type << "\t" ; 

					for (int y=0; y<3; y++)
					{
					  if(y==0)
						{
					        interface.setf(ios::showpoint);
	 				        interface.width(11);
                                                double  xx = (interface_dimension[1]-interface_dimension[0])/(length_rows);

						if((kk%2)==0)                                                               // this part of the code performs the AB stacking
						{                                                                           // along what could be considered the x direction
							interface << (xx*ii + xx/2 + interface_dimension[0])/1000.0 << "\t";       
						}
						else { interface << (xx*ii +interface_dimension[0])/1000.0 << "\t";}
					
						
						}
						
					if(y==1)
						{
				
						interface.setf(ios::showpoint);
	 				        interface.width(11);
						double yy = (interface_dimension[3]-interface_dimension[2])/(width_rows);

						if((kk%2)==0)
						{
						interface << (yy*jj + yy/2 + interface_dimension[2])/1000.0 << "\t";
						}
						else{ interface << ((yy*jj  + interface_dimension[2]))/1000.0;}
						}

					if(y==2)
						{
					        interface.setf(ios::showpoint);
	 				        interface.width(11);
						double zz = (interface_dimension[5]-interface_dimension[4])/(num_rows + 1);
				                interface << (zz*kk +  interface_dimension[4])/1000.0 << "\t";
						}
					}
					
					interface << "\n";
				}
				
					
			}		
						
		   }
			interface.close();
						


}

else { cout << "\n interface file failed to open" ;}

return 0; }
			



		



