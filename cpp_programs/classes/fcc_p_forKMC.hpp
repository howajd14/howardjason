#include <math.h>
#include "../file_class/file.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;



class fcc_p
{
	public: 
		fcc_p(int a, int b , int c, double percent_vac);
		fcc_p(int a, int b , int c, double percent_vac,int seed_prime);
		~fcc_p();
		
		int getS(int i, int j, int k) const                 // get sigma at a specific index 
		{ 
				if(i < 1){i = i_sze+i;}
				if(i>i_sze){i=i-i_sze;}
				if(j <1){j=j_sze+j;}
				if(j>j_sze){j =j-i_sze;}
				if(k<1){k= k_sze+k;}
				if(k>k_sze){k=k-k_sze;}
			int index = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
			return config_vec[index];
		}
		int get_nocc(){return nocc;}
		int get_nion(){ return  nion;}
		int get_nvac(){return   nvac;}
		int get_ionx(int ion_num){ return ixpos[ion_num-1];}
		int get_iony(int ion_num){return iypos[ion_num-1];}
		int get_ionz(int ion_num){return izpos[ion_num-1];}
		int get_vacx(int vac_num){ return vxpos[vac_num-1];}
		int get_vacy(int vac_num){return vypos[vac_num-1];}
		int get_vacz(int vac_num){return vzpos[vac_num-1];}
		int get_occx(int occ_num){return xocc[occ_num-1];}
		int get_occy(int occ_num){return yocc[occ_num-1];}
		int get_occz(int occ_num){return zocc[occ_num-1];}
		int get_ion_num(int x, int y, int z)
		{
			int number=0; 
			for( int ii=1; ii<=nion; ii++)
			{
				if(((ixpos[ii-1]==x)&&(iypos[ii-1]==y))&&izpos[ii-1]==z){number=ii;}
			
			}
			return number;
		}
		int get_vac_num(int x, int y, int z)
		{
			int number=0; 
			for( int ii=1; ii<=nvac; ii++)
			{
				if(((vxpos[ii-1]==x)&&(vypos[ii-1]==y))&&vzpos[ii-1]==z){number=ii;}
			
			}
			return number;
		}
		double get_hprob(int xi, int yi, int zi);
		double get_ddot(int xd, int yd,int zd, int xi, int yi, int zi);
		double get_ddotH(int xd, int yd,int zd, int xi, int yi, int zi);
		int get_num_n(int xi, int yi, int zi);
		int get_num_nion(int xi, int yi, int zi);
		string get_neighs(int xi, int yi, int zi);
		string get_all_neighs(int xi, int yi, int zi);
		string get_ion_neighs(int xi, int yi, int zi);
		string get_neigh(int neigh, int xi, int yi, int zi); 
		string get_vac_neigh(int neigh, int xi, int yi, int zi); 
		void populate(); 
		void setS(int i, int j, int k, int spin_val)
		{
			int index = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
			config_vec[index]=spin_val;
		}
		void set_ionx(int ion_num,int index){ixpos[ion_num-1]=index;}
		void set_iony(int ion_num,int index){iypos[ion_num-1]=index;}
		void set_ionz(int ion_num,int index){izpos[ion_num-1]=index;}
		void set_vacx(int vac_num,int index){vxpos[vac_num-1]=index;}
		void set_vacy(int vac_num,int index){vypos[vac_num-1]=index;}
		void set_vacz(int vac_num,int index){vzpos[vac_num-1]=index;}
		
		void make_array_file( string filename)
		{
			file array_file; 
			int count = 0;
			int num_lines = j_sze*k_sze;
			for(int h =1; h<= num_lines; h++){array_file.add_line("");}
				for (int ii = 1; ii<= num_lines; ii++)
				{
					string outline=""; 
					stringstream sj; 
					for(int jj =1; jj<=i_sze; jj++)
					{
						count = count +1; //cout << "\n" << num_lines;
						string holder;  
						sj << config_vec[count-1]; sj >> holder;
						if(jj==1){outline = holder;}
						if(jj>1){outline = outline + " " + holder;}
						sj.clear();sj.str("");
						//cout << "\ngot here  " << outline << "\t" << jj;
					}
					
					array_file.set_line(num_lines-ii+1,outline);
				}
			array_file.make_file(filename);
		}
		
	private:
		vector<int>  config_vec;
		vector<int>  xocc;
		vector<int>  yocc;
		vector<int>  zocc;
		vector<int>  ixpos;
		vector<int>  iypos;
		vector<int>  izpos;
		vector<int>  vxpos;
		vector<int>  vypos;
		vector<int> vzpos;
		
		int          i_sze;
		int          j_sze;
		int          k_sze;
		int          nocc;
		int          nion; 
		int          nvac;

};
//this is the general constructor for the cluster class.  It reads in the  representation of the array specifing the occupation variables of your system
// the prescribed representation needed is described at the top of this file 

fcc_p::fcc_p(int a, int b, int c, double precent_vac)
{
	i_sze = 2*a; j_sze = 2*b; k_sze = 2*c; 
	for(int x =1; x<=i_sze; x++)
	{
		for(int y =1; y<=j_sze; y++)
		{
			for(int z =1; z<=k_sze; z++)
			{
				config_vec.push_back(1);
			}
		}
	}
	for(int x =1; x<=i_sze; x++)
	{
		for(int y =1; y<=j_sze; y++)
		{
			for(int z =1; z<=k_sze; z++)
			{
				if(z%2!=0)
				{
					if(x%2!=0&&y%2==0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
					if(x%2==0&&y%2!=0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
				}
				if(z%2==0)
				{
					if(x%2!=0&&y%2!=0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
					
				}
			}
		}
	}
	nocc = xocc.size();
	srand(time(NULL));
	double pvac =0;
	int num_vac =0;
	while(pvac<precent_vac)
	{
		int rnb = rand()%nocc + 1;
		if(getS(xocc[rnb-1],yocc[rnb-1],zocc[rnb-1])==2)
		{
			setS(xocc[rnb-1],yocc[rnb-1],zocc[rnb-1],0);
			num_vac = num_vac +1; 
		}
		pvac = 1.0*num_vac/(1.0*nocc);
	}
	for(int x =1; x<=nocc; x++)
	{
		if(getS(xocc[x-1],yocc[x-1],zocc[x-1])==2)
		{
			ixpos.push_back(xocc[x-1]);
			iypos.push_back(yocc[x-1]);
			izpos.push_back(zocc[x-1]); 
		}
		if(getS(xocc[x-1],yocc[x-1],zocc[x-1])==0)
		{
			vxpos.push_back(xocc[x-1]);
			vypos.push_back(yocc[x-1]);
			vzpos.push_back(zocc[x-1]); 
		}
	}
	nion = ixpos.size();
	nvac = vxpos.size();

	
 //       cout << "\n" << nion;	
}
//////////////////////////////////////  end basic  constructor ///////////////////////////////////////////////////////////////////

//begin basic constructor two
fcc_p::fcc_p(int a, int b, int c, double precent_vac, int seed_prime)
{
	i_sze = 2*a; j_sze = 2*b; k_sze = 2*c; 
	for(int x =1; x<=i_sze; x++)
	{
		for(int y =1; y<=j_sze; y++)
		{
			for(int z =1; z<=k_sze; z++)
			{
				config_vec.push_back(1);
			}
		}
	}
	for(int x =1; x<=i_sze; x++)
	{
		for(int y =1; y<=j_sze; y++)
		{
			for(int z =1; z<=k_sze; z++)
			{
				if(z%2!=0)
				{
					if(x%2!=0&&y%2==0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
					if(x%2==0&&y%2!=0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
				}
				if(z%2==0)
				{
					if(x%2!=0&&y%2!=0)
					{
						setS(x,y,z,2);
						xocc.push_back(x);yocc.push_back(y);zocc.push_back(z);
					}
					
				}
			}
		}
	}
	nocc = xocc.size();
	srand(time(NULL)+seed_prime);
	double pvac =0;
	int num_vac =0;
	while(pvac<precent_vac)
	{
		int rnb = rand()%nocc + 1;
		if(getS(xocc[rnb-1],yocc[rnb-1],zocc[rnb-1])==2)
		{
			setS(xocc[rnb-1],yocc[rnb-1],zocc[rnb-1],0);
			num_vac = num_vac +1; 
		}
		pvac = 1.0*num_vac/(1.0*nocc);
	}
	for(int x =1; x<=nocc; x++)
	{
		if(getS(xocc[x-1],yocc[x-1],zocc[x-1])==2)
		{
			ixpos.push_back(xocc[x-1]);
			iypos.push_back(yocc[x-1]);
			izpos.push_back(zocc[x-1]); 
		}
	}
	nion = ixpos.size();
 //       cout << "\n" << nion;	
}
//////////////////////////////////////  end basic  constructor ///////////////////////////////////////////////////////////////////


///    gets the number of neighboring vacancies
int fcc_p::get_num_n(int xp, int yp, int zp)
{
	 int xi, yi, zi; 
	int num_neighs =0;
	

	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				
				int  tf =0; //recent change
                                if((x==0&&y==0)&&z==0){tf=1;}


				if(tf==0&&config_vec[index]==0)
				{
					num_neighs = num_neighs +1; 
				}
			}
		}
	}
  //      cout << "\n" << num_neighs;
	return num_neighs;
}

//get the number of neighboring ions
int fcc_p::get_num_nion(int xp, int yp, int zp)
{
	 int xi, yi, zi; 
	int num_neighs =0;
	

	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
								
				int  tf =0; //recent change
				if((x==0&&y==0)&&z==0){tf=1;}

				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				
				if(tf==0&&config_vec[index]==2)
				{
					num_neighs = num_neighs +1; 
				}
			}
		}
	}
	return num_neighs;
}

//get a string with information on neighboring vacancies; 
string fcc_p::get_neighs(int xp, int yp, int zp)
{
	int xi, yi, zi; 
	stringstream nene ; 
	string neighbors=""; 
	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				int  tf =0; //recent change
                               if(((x==0&&y==0)||(z==0&&y==0))||(x==0&&z==0)){tf=1;}


				if(tf==0&&config_vec[index]==0)
				{
					string holdernene; nene << x; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << y; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << z; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					nene << xi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << yi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << zi ; nene >>  holdernene; neighbors = neighbors + holdernene + "  "; 
					nene.clear();nene.str("");
				}
			}
		}
	}
	return neighbors; 
}

// get a string with information on all neighbors
string fcc_p::get_all_neighs(int xp, int yp, int zp)
{
	int xi, yi, zi; 
	stringstream nene ; 
	string neighbors=""; 
	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				int  tf =0; //recent change
                                if(((x==0&&y==0)||(z==0&&y==0))||(x==0&&z==0)){tf=1;}

				
				if(tf==0&&(config_vec[index]==0||config_vec[index]==2))
				{
					string holdernene; nene << x; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << y; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << z; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					nene << xi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << yi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << zi ; nene >>  holdernene; neighbors = neighbors + holdernene + "  "; 
					nene.clear();nene.str("");
				}
				
			}
		}
	}
	return neighbors; 
}

// get a string with information on the ion neighbors
string fcc_p::get_ion_neighs(int xp, int yp, int zp)
{
	int xi, yi, zi; 
	stringstream nene ; 
	string neighbors=""; 
	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				int  tf =0; //recent change
                                if(((x==0&&y==0)||(z==0&&y==0))||(x==0&&z==0)){tf=1;}


				if(tf==0&&config_vec[index]==2)
				{
					string holdernene; nene << x; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << y; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << z; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					nene << xi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << yi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << zi ; nene >>  holdernene; neighbors = neighbors + holdernene + "  "; 
					nene.clear();nene.str("");
				}
			}
		}
	}
	return neighbors; 
}

//get information on a particular neigbor 
string fcc_p::get_neigh(int neigh, int xp, int yp, int zp)
{
	int xi, yi, zi; 
	stringstream nene ; 
	string neighbors=""; 
	int count = 0; 
	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				int  tf =0; //recent change
                                if(((x==0&&y==0)||(z==0&&y==0))||(x==0&&z==0)){tf=1;}

				
				if(tf==0&&(config_vec[index]==0||config_vec[index]==2)){count = count +1;}
				if(count == neigh)
				{
					string holdernene; nene << x; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << y; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << z; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					nene << xi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << yi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << zi ; nene >>  holdernene; neighbors = neighbors + holdernene + "  "; 
					nene.clear();nene.str("");
					count = count + 1; 
				}
				
			}
		}
	}
	return neighbors; 	
	
}
//

//get information on a particular neigbor 
string fcc_p::get_vac_neigh(int neigh, int xp, int yp, int zp)
{
	int xi, yi, zi; 
	stringstream nene ; 
	string neighbors=""; 
	int count = 0; 
	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				int  tf =0; //recent change
                                if(((x==0&&y==0)||(z==0&&y==0))||(x==0&&z==0)){tf=1;}

				
				if(tf==0&&(config_vec[index]==0)){count = count +1;}
				if(count == neigh)
				{
					string holdernene; nene << x; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << y; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					 nene << z; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear(); nene.str("");
					nene << xi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << yi; nene >> holdernene; neighbors = neighbors + holdernene + "  ";
					nene.clear();nene.str("");
					nene << zi ; nene >>  holdernene; neighbors = neighbors + holdernene + "  "; 
					nene.clear();nene.str("");
					count = count + 1; 
				}
				
			}
		}
	}
	return neighbors; 	
	
}
//
double fcc_p::get_ddotH(int xd, int yd,int zd, int xp, int yp, int zp)
{
	int xi, yi, zi; 
	double xv=0; double yv=0; double zv=0;
	double dot =0; 
	 
				
							for(int x =-1; x<=1; x++)
							{
								for(int y=-1; y<=1; y++)
								{
									for(int z=-1; z<=1; z++)
									{
				
										xi = xp + x;
										yi = yp + y;
										zi = zp + z;
								
										int  tf =0; //recent change
										if((x==0&&y==0)&&z==0){tf=1;}

										if(xi <1){xi = i_sze;}
										if(xi>i_sze){xi=1;}
										if(yi <1){yi=j_sze;}
										if(yi>j_sze){yi =1;}
										if(zi<1){zi= k_sze;}
										if(zi>k_sze){zi=1;}
										int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				
										if(tf==0&&config_vec[index]==0)
										{
											xv = xv + x; yv=yv+y; zv=zv+z; 
										}
									}
								}
							} 
						
				if(sqrt(xv*xv +yv*yv +zv*zv)!=0) {xv=xv/sqrt(xv*xv + yv*yv + zv*zv); yv=yv/sqrt(xv*xv + yv*yv + zv*zv);zv=zv/sqrt(xv*xv + yv*yv + zv*zv);} 
	dot = (-1)*xd*xv + (-1)*yd*yv + (-1)*zd*zv;
	return dot; 
}

// get prob a H points towards a site 
double fcc_p::get_hprob(int xp, int yp, int zp)
{
	int xi, yi, zi; 
	double tot_dot = 0; 
	 
				if(zp%2==0)
				{
					for(int zz =-1; zz<=1; zz=zz+2)
					{
						xi = xp ;
						yi = yp ;
						zi = zp + zz;
						if(xi <1){xi = i_sze;}
						if(xi>i_sze){xi=1;}
						if(yi <1){yi=j_sze;}
						if(yi>j_sze){yi =1;}
						if(zi<1){zi= k_sze;}
						if(zi>k_sze){zi=1;}
						int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
						
						if(config_vec[index]==1)
						{
							double dot = get_ddotH(0,0,zz,xi,yi,zi);
							if(dot==0){dot = ((rand()%500 +1)-1000)/1000.0;}
							tot_dot = tot_dot + dot;  
						}
					}
				}
	
				if(xp%2==0)
				{
				  for(int xx=-1; xx<=1; xx=xx+2)
				  {
					xi = xp + xx;
					yi = yp ;
					zi = zp ;
					if(xi <1){xi = i_sze;}
					if(xi>i_sze){xi=1;}
					if(yi <1){yi=j_sze;}
					if(yi>j_sze){yi =1;}
					if(zi<1){zi= k_sze;}
					if(zi>k_sze){zi=1;}
					int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
					
		                        
					if(config_vec[index]==1)
					{
							double dot = get_ddotH(xx,0,0,xi,yi,zi);
							if(dot==0){dot = ((rand()%500 +1)-1000)/1000.0;}
							tot_dot = tot_dot + dot;  
					}
				  }
				}
				
				if(yp%2==0)
				{
				  for(int yy=-1; yy<=1; yy=yy+2)
				  {
					xi = xp ;
					yi = yp +yy;
					zi = zp ;
					if(xi <1){xi = i_sze;}
					if(xi>i_sze){xi=1;}
					if(yi <1){yi=j_sze;}
					if(yi>j_sze){yi =1;}
					if(zi<1){zi= k_sze;}
					if(zi>k_sze){zi=1;}
					int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
					
					if(config_vec[index]==1)
					{
						double dot = get_ddotH(0,yy,0,xi,yi,zi);
							if(dot==0){dot = ((rand()%500 +1)-1000)/1000.0;}
							tot_dot = tot_dot + dot;  
					}
				  }
				}
		
	
	return tot_dot; 
}

//get the sum of displacement vector dotted with vectors to neighbors
double fcc_p::get_ddot(int xd, int yd, int zd, int xp, int yp, int zp)
{
	 int xi, yi, zi; 
	double dot =0;
	

	for(int x =-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			for(int z=-1; z<=1; z++)
			{
				
				xi = xp + x;
				yi = yp + y;
				zi = zp + z;
								
				int  tf =0; //recent change
				if((x==0&&y==0)&&z==0){tf=1;}

				if(xi <1){xi = i_sze;}
				if(xi>i_sze){xi=1;}
				if(yi <1){yi=j_sze;}
				if(yi>j_sze){yi =1;}
				if(zi<1){zi= k_sze;}
				if(zi>k_sze){zi=1;}
				int index = (yi-1)*i_sze + (zi-1)*i_sze*j_sze + xi -1;
				
				if(tf==0&&config_vec[index]==2)
				{
					dot = dot + x*xd + y*yd + z*zd; 
				}
			}
		}
	}
	return dot;
}




//    destructor
fcc_p::~fcc_p()
{
}

