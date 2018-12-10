#include "classes/file.hpp"
using namespace std; 

int main()
{

string filename; 
cout << "\nWhat is the name of your file?\n"; 
cin >> filename; 
file myfile(filename); 

string anme; 
cout << "\nWhat is the name of your atom?\n";
cin >> anme; 
string find_name = "#"+anme; 
file outfile;

int nlines; 
cout << "\nHow many lines do you want to use?\n";
cin >> nlines; 

string lat_vec_file;
cout << "\nwhat is your lattice vectors file name\n";
cin >> lat_vec_file;
file lat_vecs(lat_vec_file);

double v1 [3];
double v2 [3];
double v3 [3];
double AA=0;

for(int x=1 ; x<=lat_vecs.num_lines() ; x++)
{
        if(x==1)
        {
                string lineHH = lat_vecs.get_line(x);
                stringstream jll; jll << lineHH; jll>>AA;
        }
        if(x==2)
        {
                string linell = lat_vecs.get_line(x);
                stringstream kjj; kjj << linell;
                double holder;
                kjj >> holder; v1[0]=holder*AA;
                kjj >> holder; v1[1]=holder*AA;
                kjj >> holder; v1[2]=holder*AA;
        }
        if(x==3)
        {
                string linell = lat_vecs.get_line(x);
                stringstream kjjj; kjjj << linell;
                double holder;
                kjjj >> holder; v2[0]=holder*AA;
                kjjj >> holder; v2[1]=holder*AA;
                kjjj >> holder; v2[2]=holder*AA;
        }
        if(x==4)
        {
                string linell = lat_vecs.get_line(x);
                stringstream kjjjj; kjjjj << linell;
                double holder;
                kjjjj >> holder; v3[0]=holder*AA;
                kjjjj >> holder; v3[1]=holder*AA;
                kjjjj >> holder; v3[2]=holder*AA;
        }
}


for(int x=1; x<=nlines; x++)
{
	stringstream ss; ss << myfile.get_line(x); 
	string hold; ss >> hold; 
       if(hold == find_name)
       {	double  xx,yy,zz; double xp,yp,zp;
	       string outline = anme; 
	       ss >> xx; ss >> yy ; ss >> zz; 
	       xp = xx*v1[0]+yy*v2[0]+zz*v3[0]; 
	       ss.clear();ss.str(""); ss << xp; ss >> hold; 
	       outline = outline + "\t" + hold; 
	       yp = xx*v1[1]+yy*v2[1]+zz*v3[1]; 
	       ss.clear(); ss.str(""); ss << yp; ss >> hold; 
	       ss >> hold; outline = outline + "\t" + hold; 
	       zp = xx*v1[2]+yy*v2[2]+zz*v3[2]; 
	       ss.clear(); ss.str(""); ss << zp; 
	       ss >> hold; outline = outline + "\t" + hold;  
	       outfile.add_line(outline);
	       ss.clear(); ss.str(""); 
	}	       
}
outfile.make_file("bunch_of_coords"); 
return 0; 
}
