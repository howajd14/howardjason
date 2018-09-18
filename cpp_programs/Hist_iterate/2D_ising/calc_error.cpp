#include "../../classes/file.hpp"
#include <math.h>

using namespace std; 

int main()
{
file sim("fileHist.dat"); 
file exact("Exact_logGE.dat"); 

double sum=0; 
for(int x=1; x<=sim.num_lines(); x++)
{
	stringstream ss; ss << sim.get_line(x); string burner; double simval; double exactval; 
	ss >> burner; ss >> simval; 
	ss.clear(); ss.str(""); 
	ss << exact.get_line(x); ss >> burner; ss >> exactval; 
	sum = sum + sqrt( (exactval - simval)*(exactval-simval) /(exactval*exactval) );
}

cout << "\n\n" << sum/(sim.num_lines()) << "\n\n" ;
return 0;
}
