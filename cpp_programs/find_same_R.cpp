#include "../../../../../cpp_programs/classes/file_class/file.hpp"
#include "../../../../../cpp_programs/classes/coordinates_class/coordinates.hpp"
#include <math.h>
using namespace std; 
int main()
{
string ensname; cout << "\nwhat is the name of the energy file?\n"; 
cin >> ensname; 
file ens(ensname); 
vector<double> energies; 
 
int count2=0; 
double tole =0; 
cout << "\nWhat is the tolerance for the coordinates check?\n"; 
cin >> tole;  
for(int x=1; x<= ens.num_lines(); x++)
{
	stringstream ss; ss << ens.get_line(x); double holder; ss >> holder; 
	energies.push_back(holder); 
}
file outfile1; 
for(unsigned int tt =1; tt <= ens.num_lines();  tt++)
{
//cout << "\n" << tt; 
	for(int x=1; x<=ens.num_lines(); x++)
	{
			double en1, en2; en1 = energies[tt-1]; en2 = energies[x-1]; 
				if(sqrt( (en1-en2)*(en1-en2))< 0.00001 && tt!=x)
				{
		cout << "\n" << tt << "\t" << x; 			
					stringstream ll; ll << tt; string holdit; ll >> holdit; string name1="coords" + holdit; 
					ll.clear(); ll.str(""); ll << x;ll >> holdit; string name2 = "coords" + holdit; 
					coord coords1(name1); 
					coord coords2(name2); 
					double avgdx=0; double avgdy=0; double avgdz=0; int ctt =0; 
					for(int op=1; op<=coords1.get_num_atoms(); op++)
					{
						if(coords1.get_name(op)!="Li")
						{
						ctt++; 
							avgdx = avgdx + coords1.get_xcoord(op) - coords2.get_xcoord(op); 
							avgdy = avgdy + coords1.get_ycoord(op) - coords2.get_ycoord(op); 
							avgdz = avgdz + coords1.get_zcoord(op)  - coords2.get_zcoord(op); 
						}
					}
					avgdx=avgdx/ctt; avgdy=avgdy/ctt; avgdz=avgdz/ctt; 
					double sqvx=0; double sqvy=0; double sqvz =0; 
					for(int op=1; op<=coords1.get_num_atoms(); op++)
					{
						if(coords1.get_name(op)!="Li")
						{
							double delx = coords1.get_xcoord(op) - coords2.get_xcoord(op);
							double dely = coords1.get_ycoord(op) - coords2.get_ycoord(op);
							double delz = coords1.get_zcoord(op)  - coords2.get_zcoord(op);
							sqvx = sqvx + sqrt( (delx - avgdx)*(delx - avgdx)); 
							sqvy = sqvy + sqrt((dely - avgdy)*(dely - avgdy));
							sqvz = sqvz + sqrt((delz - avgdz)*(delz - avgdz));
						}
					}
					sqvx = sqvx/ctt; sqvy = sqvy/ctt; sqvz=sqvz/ctt; 
					if((sqvx<tole&&sqvy<tole)&& sqvz<tole )
					{
						count2++; 
					}
			
				}
	}
}
cout << "\nThe number of degenerancies #D =  " << count2 << "\n\n" ;
return 0; 
}
