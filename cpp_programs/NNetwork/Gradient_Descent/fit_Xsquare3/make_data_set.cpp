#include "../../../classes/file.hpp"
#include "../../random.hpp"
using namespace std; 
int main()
{
           file DS; 
	   srand(time(NULL));
	   int ndp = 1000;
	   int range = 100;  
	   for(int x=1; x<=ndp; x++)
           {
		   string outline = "ds" ; 
		   string holder; stringstream ss; ss << x; ss >> holder; 
		   outline = outline + holder; 
		   double xcoord = (rand()%range+1);// - (range/2.0+1);  
		   double val = xcoord*xcoord/10000; 
		   ss.clear(); ss.str(""); ss << val ; ss >> holder; 
		   outline = outline + "\t" + holder; 
		   DS.add_line(outline); 
		   ss.clear(); ss.str(""); ss << xcoord; ss >> outline; 
		   DS.add_line(outline); 
           }
DS.make_file("Dataset_xsq"); 
}
