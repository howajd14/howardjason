#include "classes/file.hpp"
#include "classes/coordinates.hpp"
#include <math.h>
using namespace std; 

int main()
{

string pos_file_name; 
cout << "\nWhat is the name of the coordinate file?\n"; 
cin >> pos_file_name; 
file   Li_positions(pos_file_name); 
string atompos_line = "ATOMIC_POSITIONS (crystal)"; 
int num_atoms; 
cout << "\nHow many atoms?\n" ; 
cin >> num_atoms; 
int num_iterations = Li_positions.num_lines()/(num_atoms+2);
file outfile;  
vector<double> xa,ya,za; 
for(int y=1; y <= num_iterations - 1.0;y++)
{
        coord first_coords;
	for(int ll = 1; ll <= num_atoms; ll++)
	{
		string line2;
		int line_num2 = ll + 1 + (y-1)*(num_atoms+2); 
		line2 = Li_positions.get_line(line_num2); //cout << "\n" << line2;
		stringstream ii;
		ii << line2; string name; double crds2;
		ii >> name; first_coords.add_atom_name(name); 
		
		ii >> crds2; first_coords.add_atom_xcoord(crds2);
		ii >> crds2; first_coords.add_atom_ycoord(crds2);
		ii >> crds2; first_coords.add_atom_zcoord(crds2);
	}
	coord second_coords;
	for(int ll = 1; ll <= num_atoms; ll++)
	{
		string line2;
		int line_num2 = ll + 1 + y*(num_atoms+2); 
		line2 = Li_positions.get_line(line_num2); //cout << "\n" << line2;
		stringstream ii;
		ii << line2; string name; double crds2;
		ii >> name; second_coords.add_atom_name(name); 
		
		ii >> crds2; second_coords.add_atom_xcoord(crds2);
		ii >> crds2; second_coords.add_atom_ycoord(crds2);
		ii >> crds2; second_coords.add_atom_zcoord(crds2);
	}
	if(y==1)
	{
		
		outfile.add_line(atompos_line); 
		for(int xx=1; xx<=num_atoms; xx++)
		{
			string outline; 
			outline = first_coords.get_name(xx); 
			stringstream ss; ss << first_coords.get_xcoord(xx); 
			string holder; ss >> holder; outline  = outline + "\t" + holder; 
			ss.clear(); ss.str("") ; ss << first_coords.get_ycoord(xx); 
			ss >> holder; outline = outline + "\t" + holder; 
			ss.clear(); ss.str(""); ss << first_coords.get_zcoord(xx); 
			ss >> holder; outline = outline + "\t" + holder; 
			outfile.add_line(outline); 
			xa.push_back(first_coords.get_xcoord(xx)); 
			ya.push_back(first_coords.get_ycoord(xx)); 
			za.push_back(first_coords.get_zcoord(xx)); 
		}
		outfile.add_line("--"); 
	}
	outfile.add_line(atompos_line); 
	for(int xx=1; xx<=num_atoms; xx++)
	{
		
		double delx,dely,delz; 
		delx = round(first_coords.get_xcoord(xx) - second_coords.get_xcoord(xx)) + second_coords.get_xcoord(xx); 
		delx = delx - first_coords.get_xcoord(xx); 
		dely= round(first_coords.get_ycoord(xx) - second_coords.get_ycoord(xx)) + second_coords.get_ycoord(xx); 
		dely = dely - first_coords.get_ycoord(xx); 
		delz= round(first_coords.get_zcoord(xx) - second_coords.get_zcoord(xx)) + second_coords.get_zcoord(xx); 
		delz= delz - first_coords.get_zcoord(xx); 
		xa[xx-1]=xa[xx-1] + delx; 
		ya[xx-1]=ya[xx-1] + dely; 
		za[xx-1]=za[xx-1] + delz; 
		string outline; outline = second_coords.get_name(xx); 
		stringstream ss; ss << xa[xx-1]; string holder; ss >> holder; outline = outline + "\t" + holder; 
		ss.clear(); ss.str(""); ss << ya[xx-1]; ss >> holder; outline = outline + "\t" + holder; 
		ss.clear(); ss.str(""); ss << za[xx-1]; ss >> holder; outline = outline + "\t" + holder; 
		outfile.add_line(outline); 
	}
	outfile.add_line("--");
}



outfile.make_file("unwrapped_atompos"); 

return 0; 
}
