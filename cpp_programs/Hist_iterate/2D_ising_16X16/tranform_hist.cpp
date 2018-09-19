#include "../../classes/file.hpp"
#include <math.h>
using namespace std; 

int main()
{

file hist("fileHist.dat");
file outfile; 
for(int x=1; x<=hist.num_lines(); x++)
{
	stringstream ss; ss << hist.get_line(x); 
	string holder; string outline;  double val; double val2; ss>> val2; 
	ss >> val;  ss.clear(); ss.str("");
	ss << (val2/(16*16*0.001)); ss >> outline; ss.clear(); ss.str(""); 
	ss << val; ss >> holder; outline = outline + "\t" + holder; 
	outfile.add_line(outline); 
}


outfile.make_file("fileHist_ln.dat"); 
return 0;
}
