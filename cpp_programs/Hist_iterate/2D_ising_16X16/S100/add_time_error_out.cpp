#include "../../../classes/2D_ising.hpp"
using namespace std; 

int main()
{

file err("error_out"); 

file outfile; 
for(int x=1; x<=err.num_lines(); x++)
{
stringstream ss; ss << x; string outline; ss >> outline; 
ss.clear(); ss.str(""); 
ss << err.get_line(x); string hold; ss >> hold; 
outline = outline + "\t" + hold; 
outfile.add_line(outline); 

}

outfile.make_file("error_out.dat"); 
return 0; 
}
