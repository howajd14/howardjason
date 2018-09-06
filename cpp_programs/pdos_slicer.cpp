#include "../classes/coordinates_class/coordinates.hpp"
#include "../classes/file_class/file.hpp"
using namespace std;

int get_atom_num(string filename); /// function definition for obtaining atom number from pdos file name

int get_num_atoms_grps(double lower_bound,double upper_bound,string atm_name_given, string  slicing_axis, string coords_file, string out_files);

int main()
{
	string coords_file;
	string out_files;
	string info_files;
	int num_regions;
	int slice_axis_int;
	double lwr_bound;
	double upr_bound;
	vector<string> atom_names;
	

	cout << "\n\nwhat is the name of the coordinate file?     ";
	cin >> coords_file;

	coord coordinates(coords_file);   //make coordinate object with the coordinates
	
	cout << "\n\nWhat is the name of the file with output data file names?     ";
	cin >> out_files;

	file pdos_files(out_files);      //make file object with the file of containing the pdos out file names 

	cout << "\n\nWhat is the name of the file with desired slicing  of PDOS data?     ";

	cin >> info_files;		

	file  slicing_info(info_files); //make file object with the file containing the slicing info 

					// slicing info will have the coordinates for the slicing boundary on seperate lines
				       /*
					as an example
					1     this top line is the coordinate the slices are made perpendicular to
					0
					0.25
					0.5
					0.75
					1
					*/

	//*** initialize the slicing axis*******************
	string slice; slice = slicing_info.get_line(1); 
	stringstream slc(slice.c_str());
	slc >> slice_axis_int;
	

	//**************************************************



	num_regions=slicing_info.num_lines()-2;  // intialize the number of regions to slice 

//***********  Populate atom_names with the name of all atom types found  ******************************************************
	/*
	string holder_11; string holder_22;
	for(int x=1; x<=coordinates.get_num_atoms();x++)
	{
		
		if(x==1){holder_11 = coordinates.get_name(x); atom_names.push_back(holder_11);}
		if(x>1)
		{
		   	holder_22 = coordinates.get_name(x); 
			if(holder_11.compare(holder_22)!=0){atom_names.push_back(holder_22);  }
			 holder_11=holder_22;
		}		
	}
	*/
	string atom_names_file;
	cout << "\nEnter the file with your atom names:  "; 
	cin >> atom_names_file;
	file   atom_names_file_ob(atom_names_file);
	
	for(int x = 1; x<= atom_names_file_ob.num_lines(); x++)
	{
		string holder88; holder88 = atom_names_file_ob.get_line(x);
		atom_names.push_back(holder88);
		
	}
	
//************************************************************************************************************

			
//******** loop over # regions and add up data to fill ************************************************************
	for(int x=1; x<=num_regions; x++)
	{	
		cout << "\nregion:   " << x;   	
		vector<double> first_column;
		vector<double> second_column;
		
		//****** initialize the upper and lower bounds of the region************************************************
			for(int ll=1; ll<=2; ll++)
			{
				string here; 
				if(ll==1)
					{here = slicing_info.get_line(x+1);  istringstream tt(here); tt>>lwr_bound;   }
				if(ll==2)
					{here = slicing_info.get_line(x+2); istringstream ot(here);  ot>> upr_bound;   }
			}

		/// end initializing the upper and lower bounds of the region**********************************************
		

	       //*** intialize the first column of the output to the correct values and the second column to zeros**************
		
			file temp_pdos(pdos_files.get_line(1));
			for(int jj=2; jj<=temp_pdos.num_lines();jj++)
			{
				string temp; temp = temp_pdos.get_line(jj);
				stringstream  st(temp.c_str());
				double temp_double; st >> temp_double; first_column.push_back(temp_double);
				second_column.push_back(0);
			}   
			 
		
		//*** end initializing first and second columns**************************************************************

		
		for(unsigned int y=1; y<=atom_names.size(); y++)
		{
			
			file region;
			int holder1;  int num_atoms_in_group;
			string atm_name; string atm_name_given; atm_name_given=atom_names[y-1];
			
			num_atoms_in_group = get_num_atoms_grps(lwr_bound,upr_bound,atm_name_given, slicing_info.get_line(1),coords_file,out_files);
			
			cout << "\n" << atm_name_given << "\t" << num_atoms_in_group;
			
			if(num_atoms_in_group>0)
			{
			
			for(int bb=1; bb<=pdos_files.num_lines(); bb++)
			{
				//******* if the slicing is desired along the x axis ********************************************
				
				if(slice_axis_int==1)
				{
							
						holder1 = get_atom_num(pdos_files.get_line(bb));
						
						atm_name = coordinates.get_name(holder1);
						 						
						if(coordinates.get_ycoord(holder1)<0)
						{double ii; ii = coordinates.get_ycoord(holder1)+1;coordinates.set_ycoord(holder1,ii);}
															                        
							if(atm_name==atm_name_given&&(coordinates.get_ycoord(holder1)>lwr_bound&&coordinates.get_ycoord(holder1)<upr_bound))
							{								 
								file temp_atom_2(pdos_files.get_line(bb));
								string temp; double temp_double = 0.0; 
								
								for(int jj=2; jj<=temp_atom_2.num_lines(); jj++)
								{
									temp= temp_atom_2.get_line(jj); 
									stringstream svs(temp.c_str());
								        svs >> temp_double;  svs >>  temp_double;  
									second_column[jj-2] = second_column[jj-2] + temp_double;
								}							
							}
				}
				
			
				//******* end slicing along the x axis**********************************************************
				
				
				//******* if the slicing is desired along the y axis**********************************************
				
				if(slice_axis_int==2)
				{
							
						holder1 = get_atom_num(pdos_files.get_line(bb));
						
						atm_name = coordinates.get_name(holder1);
						 						
						if(coordinates.get_ycoord(holder1)<0)
						{double ii; ii = coordinates.get_ycoord(holder1)+1;coordinates.set_ycoord(holder1,ii);}
															                        
							if(atm_name==atm_name_given&&(coordinates.get_ycoord(holder1)>lwr_bound&&coordinates.get_ycoord(holder1)<upr_bound))
							{
								 
								file temp_atom_2(pdos_files.get_line(bb));
								string temp; double temp_double = 0.0; 
								
								for(int jj=2; jj<=temp_atom_2.num_lines(); jj++)
								{
									temp= temp_atom_2.get_line(jj); 
									stringstream svs(temp.c_str());
								        svs >> temp_double;  svs >>  temp_double;  
									second_column[jj-2] = second_column[jj-2] + temp_double;
								}							
							}
				}
				
			

				//******** end slicing along the y axis *********************************************************
				
				//****** if the slicing is desired along the z axis 
				if(slice_axis_int==3)
				{
							
						holder1 = get_atom_num(pdos_files.get_line(bb));
						
						atm_name = coordinates.get_name(holder1);
						 						
						if(coordinates.get_zcoord(holder1)<0)
						{double ii; ii = coordinates.get_zcoord(holder1)+1;coordinates.set_zcoord(holder1,ii);}
															                        
							if(atm_name==atm_name_given&&(coordinates.get_zcoord(holder1)>lwr_bound&&coordinates.get_zcoord(holder1)<upr_bound))
							{
				
								 
								file temp_atom_2(pdos_files.get_line(bb));
								string temp; double temp_double = 0.0; 
								
								for(int jj=2; jj<=temp_atom_2.num_lines(); jj++)
								{
									temp= temp_atom_2.get_line(jj); 
									stringstream svs(temp.c_str());
								        svs >> temp_double;  svs >>  temp_double;  
									second_column[jj-2] = second_column[jj-2] + temp_double;
								}							
							}
				}
				//****   end if the slicing is desired along the z-axis *****************************************************************************
			
			
			}
			 //******** now write the results out to files *********************************************************************************************
			
				for(unsigned int hh=1; hh<=first_column.size();hh++)
				{
				   string temp_1; string temp_2; 
				   stringstream yy;   yy << first_column[hh-1]; yy>> temp_1; yy.clear();yy.str(""); yy.precision(5); 
				  yy << scientific <<  second_column[hh-1]/num_atoms_in_group; 
					second_column[hh-1]=0;                                 // reset the vector to zero before the next loop
				   yy >> fixed >> temp_2; temp_1 = temp_1 + "      " + temp_2;
				    
				   region.add_line(temp_1);

					

				}
				stringstream out; out << x; 
				string file_name; string temp_file_name;
				file_name = "region"; out >> temp_file_name; 
				file_name = file_name + "_" + temp_file_name + "_" + atm_name_given;
				region.make_file(file_name);
			}

			  //********** end writing results out to files ***********************************************************************************************
				
		}
		
	}
	
return 0;
}


///********************* function for getting atom number *************************************
int get_atom_num(string file_name)
{

stringstream ss(file_name.c_str());  //the name of pdos out file  is  made into a string stream
char c;
vector<char> atm_num;
bool  truth=true;
int   at_atm_num=0;
int  past_atm_num=0;

while(ss.get(c)&&truth)  // this loop goes throught the pdos data file one char at a time name looking for the atom_num using a que for when it
			// it is before and right after the number to caputure one digit at a time in a vector
{
	
	if(c=='('){past_atm_num=1;truth=false;}
	if(at_atm_num==1&&past_atm_num==0)
	{
		
	    atm_num.push_back(c);
	}
	if(c=='#'){at_atm_num++;}

}

string make_int="";

for(unsigned int x=1; x<=atm_num.size();x++)
{
	
	make_int= make_int + atm_num[x-1];
}

stringstream ss4(make_int.c_str());     int atm_num2; ss4 >> atm_num2;   


return atm_num2;
}

///********************  end function for getting atom number *********************************



////***************** began function get num atoms in group  *********************************************
/*
		the # atoms in the group is the # of atoms for the given atom type in that region 
*/
int get_num_atoms_grps(double lower_bound,double upper_bound,string atm_name_given, string  slicing_axis, string coords_file, string out_files)
{

string filename1 = coords_file;
string filename2 = out_files;
string atom_name;
string atom_name_given = atm_name_given;

double    lwr_bound = lower_bound;
double    upr_bound = upper_bound;
int    count; count = 0;
int    num_atoms_in_grp;
int    holder1; int holder2;
string slice_axis = slicing_axis;
stringstream s;  s << slice_axis;
int slice_axis_int; s >> slice_axis_int;



coord  coordinates(filename1);
file   pdos_files(filename2);




for(int x=1; x<=pdos_files.num_lines();x++)
{
	
	
       /*
		below there are three if statements to decide which axis defines the groups 
		within each statement a counter named count adds up how many unique times the given
		atom type appears within the bounds (lwr_bound, upr_bound) of the group. It does this by disregarding 
		repeat atom# for that atom found in the group through the if statement 
		if(holder2!=holder1)

		its noted this code checks for negative coordinate values in the coordinate object if the are negative the are reset to that value plus 1
		to put all values in the 0 to 1 range. 
	*/    
	

	if(slice_axis_int==1)
	{
		
		if(x==1)
		{
			 holder1 = get_atom_num(pdos_files.get_line(x)); 
	                 atom_name = coordinates.get_name(holder1);
			if(coordinates.get_xcoord(holder1)<0){double ii; ii = coordinates.get_xcoord(holder1)+1;coordinates.set_xcoord(holder1,ii);}
			if((atom_name==atom_name_given)&&(coordinates.get_xcoord(holder1)>lwr_bound&&coordinates.get_xcoord(holder1)<upr_bound))
			{
				count++; 
			}
		}
		if(x>1)
		{
			holder2 = get_atom_num(pdos_files.get_line(x));
			atom_name = coordinates.get_name(holder2);
			if(coordinates.get_xcoord(holder2)<0){double ii; ii = coordinates.get_xcoord(holder2)+1;coordinates.set_xcoord(holder2,ii);}
			if(holder2!=holder1)
			{
				
				if((atom_name==atom_name_given)&&(coordinates.get_xcoord(holder2)>lwr_bound&&coordinates.get_xcoord(holder2)<upr_bound))
			{
				count++; holder1=holder2;
			}
				
			}
			
		}
	
	}

	
	if(slice_axis_int==2)
	{
		
		if(x==1)
		{
			 holder1 = get_atom_num(pdos_files.get_line(x)); 
	                 atom_name = coordinates.get_name(holder1);
			if(coordinates.get_ycoord(holder1)<0){double ii; ii=coordinates.get_ycoord(holder1)+1; coordinates.set_ycoord(holder1,ii);}
			if((atom_name==atom_name_given)&&(coordinates.get_ycoord(holder1)>lwr_bound&&coordinates.get_ycoord(holder1)<upr_bound))
			{
				count++; 
			}
		}
		if(x>1)
		{
			holder2 = get_atom_num(pdos_files.get_line(x));
			atom_name = coordinates.get_name(holder2);
			if(coordinates.get_ycoord(holder2)<0){double ii; ii=coordinates.get_ycoord(holder2)+1; coordinates.set_ycoord(holder2,ii);}
			if(holder2!=holder1)
			{
				if((atom_name==atom_name_given)&&(coordinates.get_ycoord(holder2)>lwr_bound&&coordinates.get_ycoord(holder2)<upr_bound))
			{
				count++; holder1=holder2;
			}
				
			}
			
		}
	
	}

	
	if(slice_axis_int==3)
	{
		
		if(x==1)
		{
			
			 holder1 = get_atom_num(pdos_files.get_line(x)); 
			
	                 atom_name = coordinates.get_name(holder1);
			if(coordinates.get_zcoord(holder1)<0){double ii; ii=coordinates.get_zcoord(holder1) + 1; coordinates.set_zcoord(holder1,ii);}
			if((atom_name==atom_name_given)&&(coordinates.get_zcoord(holder1)>lwr_bound&&coordinates.get_zcoord(holder1)<upr_bound))
			{
				count++; 
			}
		}
		if(x>1)
		{
			
			holder2 = get_atom_num(pdos_files.get_line(x));
			atom_name = coordinates.get_name(holder2);
			if(coordinates.get_zcoord(holder2)<0){double ii; ii=coordinates.get_zcoord(holder2) + 1; coordinates.set_zcoord(holder2,ii);}
			if(holder2!=holder1)
			{
				
				if((atom_name==atom_name_given)&&(coordinates.get_zcoord(holder2)>lwr_bound&&coordinates.get_zcoord(holder2)<upr_bound))
			{
				
				count++; holder1=holder2;
			}
				
			}			
		}	
	}
	
}

num_atoms_in_grp=count; 

return num_atoms_in_grp;
}


