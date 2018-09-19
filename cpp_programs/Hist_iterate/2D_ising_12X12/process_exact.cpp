#include "../../classes/file.hpp"
using namespace std; 

int main()
{

file dat("12X12.dat"); 
file outfile; 
string line = dat.get_line(1); 
stringstream ss; ss << line; 
while(ss.eof()!=1)
{
string templine; ss >> templine; 
stringstream ll; 
ll << templine; string outline="";; 
char c; 

	while(ll.get(c))
	{
		 
		if((c!='{'&&c!=',')&&c!='}')
		{
		outline = outline + c; 
		}
	}
outfile.add_line(outline); 
}
outfile.make_file("Coefficients"); 

return 0; 
}
