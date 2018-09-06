#include "../classes/coordinates_class/coordinates.hpp"
#include "../classes/file_class/file.hpp"

using namespace std;


int main()
{

string file_name;

cout << "\nenter the name of your coordinates file\n";
cin >> file_name;

coord my_coords(file_name);
file out_file;

int  a, b, c;

cout << "\nenter how much to expand  the a coords\n";
cin >> a;
cout << "\nenter how much to expand  the b coords\n";
cin >> b;
cout << "\nenter how much to expand the  c coords\n";
cin >> c;

int num_atoms_initial = my_coords.get_num_atoms();


for(int x= 1; x<=num_atoms_initial; x++)
{
    if(my_coords.get_xcoord(x)<0.0){my_coords.set_xcoord(x,my_coords.get_xcoord(x)+1.0);}
    if(my_coords.get_ycoord(x)<0.0){my_coords.set_ycoord(x,my_coords.get_ycoord(x)+1.0);}
    if(my_coords.get_zcoord(x)<0.0){my_coords.set_zcoord(x,my_coords.get_zcoord(x) +1.0);}
   
    if(a!=0){ my_coords.set_xcoord(x,my_coords.get_xcoord(x)/(a*1.0+1.0));}
    if(b!=0){my_coords.set_ycoord(x,my_coords.get_ycoord(x)/(b*1.0+1.0));}
    if(c!=0){my_coords.set_zcoord(x,my_coords.get_zcoord(x)/(c*1.0+1.0));}

}



for(int x=1; x<=num_atoms_initial; x++)

{


   	for(int aa=1; aa<=a;aa++)
   	{
      
		
		my_coords.add_atom_name(my_coords.get_name(x));
                my_coords.add_atom_xcoord(my_coords.get_xcoord(x) + (aa*1.0)/(1.0 + a*1.0));
                my_coords.add_atom_ycoord(my_coords.get_ycoord(x));
                my_coords.add_atom_zcoord(my_coords.get_zcoord(x));
		
  	 }
	
	for(int bb=1; bb <= b; bb++)
	{
		
		my_coords.add_atom_name(my_coords.get_name(x));
                my_coords.add_atom_xcoord(my_coords.get_xcoord(x));
                my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                my_coords.add_atom_zcoord(my_coords.get_zcoord(x));
		
	}
		
	
	for(int cc=1; cc <=c; cc++)
        {
		
		my_coords.add_atom_name(my_coords.get_name(x));
               	my_coords.add_atom_xcoord(my_coords.get_xcoord(x));
               	my_coords.add_atom_ycoord(my_coords.get_ycoord(x));
                my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
		

	 }

	for(int aa=1; aa<=a; aa++)
	{
		for(int bb=1; bb <=b; bb++)
		{
		 my_coords.add_atom_name(my_coords.get_name(x));
                my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
                my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                my_coords.add_atom_zcoord(my_coords.get_zcoord(x));	
		}

	}

	for(int aa=1; aa<=a; aa++)
	{
		for(int cc=1; cc <=c; cc++)
		{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));	
		}
	}

	for(int bb=1; bb<=b; bb++)
	{
		for(int cc=1; cc<=c; cc++)
		{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
		}
	}

	for(int aa=1; aa<=a; aa++)
	{
		for(int bb=1; bb<=b; bb++)
		{
			for(int cc=1; cc<=c; cc++)
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}
		}
	}

}
//  close loop over coords 
		
/*
	if((c!=0&&cc!=0)&&(b!=0&&bb!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

			if((c!=0&&cc!=0)&&(a!=0&&aa!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

			if(((c!=0&&cc!=0)&&(a!=0&&aa!=0))&&(b!=0&&bb!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

		if((b!=0&&bb!=0)&&(a!=0&&aa!=0))
		{
		my_coords.add_atom_name(my_coords.get_name(x));
                my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
                my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                my_coords.add_atom_zcoord(my_coords.get_zcoord(x));


		}

		if((c!=0&&cc!=0)&&(b!=0&&bb!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

			if((c!=0&&cc!=0)&&(a!=0&&aa!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

			if(((c!=0&&cc!=0)&&(a!=0&&aa!=0))&&(b!=0&&bb!=0))
			{
			my_coords.add_atom_name(my_coords.get_name(x));
               		my_coords.add_atom_xcoord(my_coords.get_xcoord(x)+ (aa*1.0)/(1.0 + a*1.0));
               		my_coords.add_atom_ycoord(my_coords.get_ycoord(x)+ (bb*1.0)/(1.0 + b*1.0));
                	my_coords.add_atom_zcoord(my_coords.get_zcoord(x)+ (cc*1.0)/(1.0 + c*1.0));
			}

*/


for(int x=1; x <=my_coords.get_num_atoms();x++)
{
	string line_holder, line_out;
	stringstream ss;
	
	ss.precision(10); ss.width(10);
	ss << my_coords.get_name(x) << "\n" << my_coords.get_xcoord(x) << "\n" << my_coords.get_ycoord(x) << "\n"  << my_coords.get_zcoord(x);

	ss >> line_holder; line_out = line_holder; ss >> line_holder; line_out = line_out + "\t" + line_holder; ss >> line_holder; line_out = line_out + "\t" + line_holder;
	ss >> line_holder; line_out = line_out + "\t"+ line_holder; 
	out_file.add_line(line_out);
	ss.clear(); ss.str("");


}


out_file.make_file("new_super_cell");



return 0;
}
