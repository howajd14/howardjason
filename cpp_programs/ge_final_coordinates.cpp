#include "../../../../../cpp_programs/classes/file_class/file.hpp"
#include "../../../../../cpp_programs/classes/coordinates_class/coordinates.hpp"
using namespace std; 

int main()
{

int num_files; cout << "\nHow many run files?\n"; cin >> num_files; 
int num_atoms; cout << "\nHow many atoms?\n" ;  cin >> num_atoms; 
int  count_start=0; cout << "\nWhere does the count start?"; 
cin >> count_start; 
for(int x=1; x<=num_files; x++)
{
	stringstream ss; ss << x; 
	string holder; ss >> holder; 
	string filename = "run" + holder + "/LiClOH.out"; 
	file  data(filename); 
	int find_not_find =0; 
	for(int y=1; y<=data.num_lines(); y++)
	{
		string atline = data.get_line(y); 
		if(atline == "Begin final coordinates")
		{
		find_not_find=1; 
			coord outcoords; 
			for(int z=1; z<=num_atoms; z++)
			{
				ss.clear();ss.str("");
				ss << data.get_line(y+2+z); 
				string atomname; double cds; 
				ss >> atomname; outcoords.add_atom_name(atomname);
				ss >> cds; outcoords.add_atom_xcoord(cds);
				ss >> cds; outcoords.add_atom_ycoord(cds); 
				ss >> cds; outcoords.add_atom_zcoord(cds);
				ss.clear();ss.str("");
			}
			stringstream jh; jh << (count_start+(x-1)); string addstring; jh >> addstring; 
			string coordsname = "coords" + addstring; 
			outcoords.make_file(coordsname);
		}
		
	}
	if(find_not_find==0){cout << "\nNo final coordinates for file:   " << x << "\n" ; }
}	

return 0; 
}
