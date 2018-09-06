#include "../../../../../cpp_programs/classes/file_class/file.hpp"
#include "../../../../../cpp_programs/classes/coordinates_class/coordinates.hpp"
using namepsace std; 
int main()
{
int nf =0;
cout << "\nhow many files?\n";
cin >> nf; 
coord Lipos("Lipos");
coord Clpos("Clpos"); 
double cmx, cmy, cmz;cmx=0;cmy=0;cmz=0; 
for(int x =1 ; x<= Clpos.get_num_atoms(); x++)
{
cmx = cmx+Clpos.get_xcoord(x); cmy=cmy+Clpos.get_ycoord(x); cmz=cmz+Clpos.get_zcoord(x); 
}
for(int x=1; x<=nf; x++)
{
    string filename = "coords"; stringstream ss; ss << x; 
    string holdit; ss >> holdit; filename = filename + holdit; 
    coord  Licoordso(filename); 
    coords Licoords; 
    coords Clcoords; 
    for(int pp =1; pp<=Licoordso.get_num_atoms(); pp++)
    {
	if(Licoordso.get_name(pp)=="Li")
	{
		Licoords.add_atom_name(Licoordso.get_name(pp));
		Licoords.add_atom_xcoord(Licoordso.get_xcoord(pp));
		Licoords.add_atom_ycoord(Licoordso.get_ycoord(pp)); 
		Licoords.add_atom_zcoord(Licoordso.get_zcoord(pp)); 
		
	}
	if(Licoordso.get_name(pp)="Cl")
	{
		Clcoords.add_atom_name(Licoordso.get_name(pp));
		Clcoords.add_atom_xcoord(Licoordso.get_xcoord(pp));
		Clcoords.add_atom_ycoord(Licoordso.get_ycoord(pp)); 
		Clcoords.add_atom_zcoord(Licoordso.get_zcoord(pp)); 
		
	}
	
	
    }
    double cmx2=0;double cmy2=0; double cmz2=0;
	for(int x =1 ; x<= Clcoords.get_num_atoms(); x++)
	{
	cmx2 = cmx2+Clcoords.get_xcoord(x); cmy2=cmy+Clcoords.get_ycoord(x); cmz2=cmz2+Clcoords.get_zcoord(x); 
	}
	double delcmx=cmx-cmx2; double delcmy=cmy-cmy2; double delcmz=cmz-cmz2; 
    for(int pp=1; pp <=Licoords.get_num_atoms(); pp++)
    {
		if(Licoords.get_xcoord(pp)<0){Licoords.set_xcoord(pp,Licoords.get_xcoord(pp)+1);}
		if(Licoords.get_xcoord(pp)>1){Licoords.set_xcoord(pp,Licoords.get_xcoord(pp)-1);}
		if(Licoords.get_ycoord(pp)<0){Licoords.set_ycoord(pp,Licoords.get_ycoord(pp)+1);}
		if(Licoords.get_ycoord(pp)>1){Licoords.set_ycoord(pp,Licoords.get_ycoord(pp)-1);}
		if(Licoords.get_zcoord(pp)<0){Licoords.set_zcoord(pp,Licoords.get_zcoord(pp)+1);}
		if(Licoords.get_zcoord(pp)>1){Licoords.set_zcoord(pp,Licoords.get_zcoord(pp)-1);}
    }
    vector<int> vec; for(int x=1; x<=24; x++){vec.push_back(0);}
    for(int y=1; y<=Licoords.get_num_atoms(); y++)
    {
		double Rmin = 1000; 
		int   index = 0; 
		for( int z = 1; z<=Lipos.get_num_atoms(); z++)
		{
			double rmin = 1000; 
			for(int ii=1; ii<=3; ii++)
			{	
				for(int jj=1; jj<=3; jj++)
				{
					for(int kk=1; kk<=3; kk++)
					{
						int id = ii-2; int jd = jj-2; int kd=kk-2; 
						double delx = (Licoords.get_xcoord(y)+id+delcmx)-(Lipos.get_xcoord(z));
						double dely = (Licoords.get_ycoord(y)+jd+delcmy)-(Lipos.get_ycoord(z));
						double delz = (Licoords.get_zcoord(y)+kd+delcmz)-(Lipos.get_zcoord(z));
                                                double Rhere = delx*delx + dely*dely + delz*delz; 
						if(Rhere < rmin){rmin=Rhere;}
					}
				}
			}
			if(rmin < Rmin){Rmin = rmin; index =z;}
		}
		vec[index-1]=1;
    }
	file configvec; 
	file outname = "vec" + holdit; ss.clear();ss.str(""); 
	for(unsigned int oo=1; oo<=vec.siz(); oo++)
	{
		string outline; ss << vec[oo-1] ; ss >> outline; 
		configvec.add_line(outline);
		ss.clear();ss.str("");
	}
	configvec.make_file(outname); 

}
return 0;
}
