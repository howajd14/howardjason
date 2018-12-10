#include "classes/file.hpp"
#include "classes/coordinates_withvasp.hpp"
using namespace std; 

int main()
{
  string intpos_name; 
  cout << "\nWhat is the file name with the initial positions?\n";
  cin >> intpos_name; 
  coord  initpos(intpos_name,"vasp"); 
  string xcar_name; 
  cout << "\nWhat is the file name of the XDATCAR file?\n"; 
  cin >> xcar_name; 
  file   xdat(xcar_name); 
  string a_name; 
  cout << "\nWhat is the file name of the atom you are interested in?\n";
  cin >> a_name; 
  string atom_positions_line = "ATOMIC_POSITIONS (crystal)"; 
  file outfile; 
for(int x=1; x<=xdat.num_lines(); x++)
{
	stringstream ss; ss << xdat.get_line(x); 	
	string  direct; ss >> direct; 
	if(direct == "Direct")
	{
		outfile.add_line(atom_positions_line); 
		for(int y=1; y<=initpos.get_num_atoms(); y++)
		{
			if(initpos.get_name(y)==a_name)
			{
				string outline = a_name + "\t" + xdat.get_line(x+y); 
				outfile.add_line(outline); 
			}
		}
		outfile.add_line("--"); 
	}

}
outfile.make_file("atompos"); 


return 0; 
}
