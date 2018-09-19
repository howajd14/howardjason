#include "../../classes/file.hpp"
#include <math.h>
using namespace std; 

int main()
{
string filename;
cout << "\nWhat is the filename with your data\n"; 
cin >> filename; 

file dat(filename); 
file hist("fileHist.dat"); 
file outfile; 
for(int x=1; x<=dat.num_lines(); x++)
{
stringstream ss; ss<<dat.get_line(x); 
double holder; ss >> holder; 
double xval; ss.clear();ss.str(""); 
ss << hist.get_line(x); ss >> xval; 
string outline; 
ss.clear();ss.str(""); ss << xval; ss>> outline; ss.clear();ss.str("");
ss << log(holder);  string linehold; ss >> linehold; 
outline = outline + "\t" + linehold; 
outfile.add_line(outline); 
} 
outfile.make_file("Exact_logGE.dat"); 
return 0; 
}
