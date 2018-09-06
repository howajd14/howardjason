#include <math.h>
#include "../file_class/file.hpp"
using namespace std;

/*
	This is the Cluster classes it is meant for providing a convient  means of  performing of dealing with the complexties of a cluster expansion by
	organizing the information needed in a cluster expansion in a convienient manner. 

	The basic constructor  for this class  is to simply read in  the dimensions of an array provided as input and a file name containing the information for this array. 
	This  array simply provides the configuration variables for each site of your grid repersenting the lattice in question. 
	The format for this array is as follows  
	Say you have a 2X2X2 grid  in  iXjXk  notation. (ijk) will denote the indices in the following example 

		
	line1:    (212)  (222)
	line2     (112)  (122)

	line3     (211)  (221)   
        line4     (111)  (121)

 	This grid  will then be stored  in a one dimensional  vector  in the order  (111) (121) (121) (222) (112) (212) (122) (222) 

	to access the ith, jth, kth  element   simplie acess the  (i-1)*j_sze + (k-1)*i_sze*j_sze + j -1   element of this vector. 

	Note:  Determining clusters from this grid will require periodic boundary conditions and it is the users responsibility to  ensure the grid representation is large enough that
		clusters are not linked farther than the adjoining periodic arrays. 

	This representation of the grid of configuration variables is the defining feature of the class. From here functions can be defined to perform the desired mathematics of the 
	cluster expansion. The mathmatics performed should be keep to the most basic but general forms. 

*/


class cluster
{
	public: 
		cluster(int a, int b , int c,  string cluster_array);
		~cluster();
		int sigM_p(int i2, int j2, int k2) const; // funtions to count sum over ijk the product of the spin variables  sigma(ijk)*simga{(i+i2)(j+j2)(k+k2)}
		int sigM_q(int i2,int j2,int k2,int i3,int j3,int k3,int i4,int j4,int k4) const; // sigma product sums of quadruplets
		int getC(string type_clust, int clust_type) const;  //total sum of specific cluster
		int getS(int i, int j, int k) const                 // get sigma at a specific index 
		{ 
			int index = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
			return config_vec[index];
		}
		int sigMs_p(int i, int j, int k, int i2, int j2, int k2) const; // sigma product for a pair a specific index 
		int spC(int i, int j, int k, int clust_type) const;             // cluster pair sum at specific index 

		//modifier  methods
		void setS(int i, int j, int k, int spin_val)
		{
			int index = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
			config_vec[index]=spin_val;
		}
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
		int          i_sze;
		int          j_sze;
		int          k_sze;

};
//this is the general constructor for the cluster class.  It reads in the  representation of the array specifing the occupation variables of your system
// the prescribed representation needed is described at the top of this file 

cluster::cluster(int a, int b, int c, string cluster_array_name)
{
	i_sze = a; j_sze = b; k_sze = c; 
	file cluster_file(cluster_array_name);
	if(cluster_file.num_lines()!=b*c){cout << "\ncheck the dimensions of b and c (j and k)\n";}
	if(cluster_file.num_lines()==b*c)
	{
		for(int x = 0 ; x <= cluster_file.num_lines()-1; x++)
		{
			stringstream ss; 
			string line = cluster_file.get_line(b*c - x);   ss << line; 
			for(int y = 1; y <= a; y++)
			{
				int holder;  ss >> holder;  config_vec.push_back(holder);
			}
		}
	}
}
//////////////////////////////////////  end basic  constructor ///////////////////////////////////////////////////////////////////

// the following is the member function to perform the sum over ijk  of the product sigma(ijk)*simga{(i+i2)(j+j2)(k+k2) where sigma are the 
// configuration variables for the specified indices 

int cluster::sigM_p(int i2, int j2, int k2) const
{
	int sigma_sum = 0; 
	for(int i =1 ; i<=i_sze; i++)
	{
		for(int j=1; j<=j_sze; j++)
		{
			for(int k=1; k<=k_sze; k++)
			{
				int i_i2, j_j2, k_k2;  // these variables hold the sum of i + i2 , j + j2, k + k2
						       // the following statements take care of the periodic boundary conditions
				if((i+i2)<=0){i_i2 = i_sze + (i+i2);}
				if((i+i2)>i_sze){i_i2 = (i+i2)-i_sze;} 
				if((i+i2)>=1&&(i+i2)<=i_sze){i_i2 = i + i2;}

				if((j+j2)<=0){j_j2 = j_sze + (j+j2);}
				if((j+j2)>j_sze){j_j2 = (j+j2)-j_sze;} 
				if((j+j2)>=1&&(j+j2)<=j_sze){j_j2 = j + j2;}

				if((k+k2)<=0){k_k2 = k_sze + (k+k2);}
				if((k+k2)>k_sze){k_k2 = (k+k2)-k_sze;} 
				if((k+k2)>=1&&(k+k2)<=k_sze){k_k2 = k + k2;}
	
				int index1, index2; //variables to hold the index of the vector(representation of the array) that corresponds to the
						    // desired index of the actuall array
				index1 = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
				index2 = (j_j2-1)*i_sze + (k_k2-1)*i_sze*j_sze + i_i2 -1;
			
			        sigma_sum = sigma_sum + config_vec[index1]*config_vec[index2];

			}
		}
	}
		return sigma_sum; 

}
/////////////////////////////////////end  2nd order sigma product sum///////////////////////////////////////////////////////////////////////


///  sigMs_p  calculates the sigma product of a single specified set of indices //////////////////////////////////////////////////////////
int cluster::sigMs_p(int i, int j, int k , int i2, int j2, int k2) const 
{
	int sigma_sum = 0; 
	
				int i_i2, j_j2, k_k2;  // these variables hold the sum of i + i2 , j + j2, k + k2
						       // the following statements take care of the periodic boundary conditions
				if((i+i2)<=0){i_i2 = i_sze + (i+i2);}
				if((i+i2)>i_sze){i_i2 = (i+i2)-i_sze;} 
				if((i+i2)>=1&&(i+i2)<=i_sze){i_i2 = i + i2;}

				if((j+j2)<=0){j_j2 = j_sze + (j+j2);}
				if((j+j2)>j_sze){j_j2 = (j+j2)-j_sze;} 
				if((j+j2)>=1&&(j+j2)<=j_sze){j_j2 = j + j2;}

				if((k+k2)<=0){k_k2 = k_sze + (k+k2);}
				if((k+k2)>k_sze){k_k2 = (k+k2)-k_sze;} 
				if((k+k2)>=1&&(k+k2)<=k_sze){k_k2 = k + k2;}
	
				int index1, index2; //variables to hold the index of the vector(representation of the array) that corresponds to the
						    // desired index of the actuall array
				index1 = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
				index2 = (j_j2-1)*i_sze + (k_k2-1)*i_sze*j_sze + i_i2 -1;
			
			        sigma_sum = sigma_sum + config_vec[index1]*config_vec[index2];

		
		return sigma_sum; 

}
/////////////////////////////////////end  2nd order single sigma products///////////////////////////////////////////////////////////////////////



// the following memeber function is to calculate the sum of the quadruplet(4th order) sigma products //////////////////////////////////////

int cluster::sigM_q(int i2,int j2,int k2,int i3,int j3,int k3,int i4,int j4,int k4) const
{
	int sigma_sum = 0; 
	for(int i =1 ; i<=i_sze; i++)
	{
		for(int j=1; j<=j_sze; j++)
		{
			for(int k=1; k<=k_sze; k++)
			{
				int i_i2, j_j2, k_k2, i_i3, j_j3 , k_k3, i_i4, j_j4, k_k4; // these variables hold the sum of i + i2 , j + j2, k + k2 ext 
							
						       // the following statements take care of the periodic boundary conditions
				if((i+i2)<=0){i_i2 = i_sze + (i+i2);}
				if((i+i2)>i_sze){i_i2 = (i+i2)-i_sze;} 
				if((i+i2)>=1&&(i+i2)<=i_sze){i_i2 = i + i2;}

				if((j+j2)<=0){j_j2 = j_sze + (j+j2);}
				if((j+j2)>j_sze){j_j2 = (j+j2)-j_sze;} 
				if((j+j2)>=1&&(j+j2)<=j_sze){j_j2 = j + j2;}

				if((k+k2)<=0){k_k2 = k_sze + (k+k2);}
				if((k+k2)>k_sze){k_k2 = (k+k2)-k_sze;} 
				if((k+k2)>=1&&(k+k2)<=k_sze){k_k2 = k + k2;}

				if((i+i3)<=0){i_i3 = i_sze + (i+i3);}
				if((i+i3)>i_sze){i_i3 = (i+i3)-i_sze;} 
				if((i+i3)>=1&&(i+i3)<=i_sze){i_i3 = i + i3;}

				if((j+j3)<=0){j_j3 = j_sze + (j+j3);}
				if((j+j3)>j_sze){j_j3 = (j+j3)-j_sze;} 
				if((j+j3)>=1&&(j+j3)<=j_sze){j_j3 = j + j3;}

				if((k+k3)<=0){k_k3 = k_sze + (k+k3);}
				if((k+k3)>k_sze){k_k3 = (k+k3)-k_sze;} 
				if((k+k3)>=1&&(k+k3)<=k_sze){k_k3 = k + k3;}

				if((i+i4)<=0){i_i4 = i_sze + (i+i4);}
				if((i+i4)>i_sze){i_i4 = (i+i4)-i_sze;} 
				if((i+i4)>=1&&(i+i4)<=i_sze){i_i4 = i + i4;}

				if((j+j4)<=0){j_j4 = j_sze + (j+j4);}
				if((j+j4)>j_sze){j_j4 = (j+j4)-j_sze;} 
				if((j+j4)>=1&&(j+j4)<=j_sze){j_j4 = j + j4;}

				if((k+k4)<=0){k_k4 = k_sze + (k+k4);}
				if((k+k4)>k_sze){k_k4 = (k+k4)-k_sze;} 
				if((k+k4)>=1&&(k+k4)<=k_sze){k_k4 = k + k4;}

	
				int index1, index2, index3, index4; //variables to hold the index of the vector(representation of the array) that corresponds to the
						    		   // desired index of the actual array
				index1 = (j-1)*i_sze + (k-1)*i_sze*j_sze + i -1;
				index2 = (j_j2-1)*i_sze + (k_k2-1)*i_sze*j_sze + i_i2 -1;
				index3 = (j_j3-1)*i_sze + (k_k3-1)*i_sze*j_sze + i_i3 -1;
				index4 = (j_j4-1)*i_sze + (k_k4-1)*i_sze*j_sze + i_i4 -1;
			
			        sigma_sum = sigma_sum + config_vec[index1]*config_vec[index2]*config_vec[index3]*config_vec[index4];

			}
		}
	}
		return sigma_sum; 
}
//////////////////////////////////// end 4th order clusters sigma product sum /////////////////////////////////////////////////////////////////

///////////////////////  the following function retrieves the sigma product sums for  every cluster of  specified type in the grid 
/*
			the following labels  give what each cluster represents 

			for  pair interactions  (string "p" as input)
			1 - nearest neighbor  pair  i-axis  i and i+/-1  type 
			2 - nearest neighbor  pair  j-axis  j and  j+/-1 type
			3 - nearest neighbor  pair  k-axis  k and k+/-1  type
			4 - next nearest neighbor in the  i-j  plane   ij and i+/-1 j+/-1 type
			5 - next nearest neighbor in the  i-k plane    ik  and i+/-1 , k+/-1  type
			6 - next nearest neighbor in the  j-k plane    jk  and j+/-1 , k+/-1 type
			7 - next next nearest neigbor     ijk and i+/-1, j+/-1 , k+/-1 type
			8 - n-n-n nearest                 ijk     i+/-2 , j, k 
			9 - n-n-n nearest                 ijk     i, j+/-2, k
			10- n-n-n nearest                 ijk     i, j, k+/-2
			11  n-n-n-n nearest 		  ijk     i+/-1,j+/-2,k
			12 n-n-n-n nearest                ijk     i+/-2 , j+/-1, k
			13 n-n-n-n nearest 		  ijk    i+/-1, j, k+/-2
			14 n-n-n-n nearest                ijk    i+/-2, j, k+/-1
			15 n-n-n-n nearest                ijk    i j+/-1 , k+/-2
			16 n-n-n-n nearest                ijk    i j+/-2 , k+/-1
			17 n-n-n-n-n nearest              ijk    i+/-2, j+/-1, k+/-1
			18 n-n-n-n-n nearest              ijk    i+/-1, j+/-2 , k+/-1
			19 n-n-n-n-n nearest              ijk    i+/-1, j+/-1,  k+/-2
			20 n-n-n-n-n-n nearest            ijk    i+/-3, j , k
                        21 ""                             ijk    i , j+/-3 , k
                        22 ""                             ijk    i, j, k+/-3

			for 4th order quadruaplets  (string "q" as input)
			1 - nearest neighbor squares in   i-j plane         {ijk}, {i+/-1 j k}, {i j+/-1 k}, {i+/-1 j+/-1 k} type
			2 - nearest neighbor squares  in   i-k plane        {ijk}, {i+/-1 j k}, {i j k+/-1}, {i+/-1 j k+/-1} type 
			3 - nearest neighbor squares in  j-k plane          {ijk}, {i j+/-1 k}, {i j k+/-1}, {i j+/-1 k+/-1}
			4 - nn squares        perpendicular k-axis          {ijk}, {i+/-1 j+/-1 k} {i j k+/-1} {i+/-1 j+/-1 k+/-1}
			5 - nn squares        perpendicular j-axis          {ijk}, {i+/-1 j k+/-1} , {i j+/-1 k} , {i+/-1 j+/-1 k+/-1}
			6 - nn squares        perpendicular i-axis          {ijk}, {i j+/-1 k+/1},   {i+/-1 j k} , {i+/-1 j+/-1 k+/-1}
*/

int cluster::getC(string cluster_type, int which_clust) const
{
	 int cluster_sum = 0; 
	if(cluster_type == "p") /////   second order clusters ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		if(which_clust==1)
		{	
		 cluster_sum = sigM_p(1,0,0) + sigM_p(-1,0,0);
		}
		else if(which_clust==2)
		{
		 cluster_sum = sigM_p(0,1,0) + sigM_p(0,-1,0);
		}
		else if(which_clust==3)
		{
		 cluster_sum = sigM_p(0,0,1) + sigM_p(0,0,-1);
		}
		else if(which_clust==4)
		{
		 cluster_sum = sigM_p(1,1,0) + sigM_p(-1,1,0) + sigM_p(1,-1,0) + sigM_p(-1,-1,0);
		}
		else if(which_clust==5)
		{
		 cluster_sum = sigM_p(1,0,1) + sigM_p(-1,0,1) + sigM_p(1,0,-1) + sigM_p(-1,0,-1);
		}
		else if(which_clust==6)
		{
		 cluster_sum = sigM_p(0,1,1) + sigM_p(0,-1,1) + sigM_p(0,1,-1) + sigM_p(0,-1,-1);
		}
		else if(which_clust==7)
		{
		cluster_sum = sigM_p(1,1,1)+sigM_p(-1,1,1)+sigM_p(1,-1,1)+sigM_p(1,1,-1)+sigM_p(-1,-1,1)+sigM_p(-1,1,-1)+sigM_p(1,-1,-1)+sigM_p(-1,-1,-1);
		}
		else if(which_clust==8)
		{
		cluster_sum = sigM_p(2,0,0)+sigM_p(-2,0,0);
		}
		else if(which_clust==9)
		{
		cluster_sum = sigM_p(0,2,0)+sigM_p(0,-2,0);
		}
		else if(which_clust==10)
		{
		cluster_sum = sigM_p(0,0,2)+sigM_p(0,0,-2);
		}
		else if(which_clust==11)
		{
		cluster_sum = sigM_p(1,2,0)+sigM_p(-1,2,0)+sigM_p(1,-2,0)+sigM_p(-1,-2,0);
		}
		else if(which_clust==12)
		{
		cluster_sum = sigM_p(2,1,0)+sigM_p(-2,1,0)+sigM_p(2,-1,0)+sigM_p(-2,-1,0);
		}
		else if(which_clust==13)
		{
		cluster_sum = sigM_p(1,0,2)+sigM_p(-1,0,2)+sigM_p(1,0,-2)+sigM_p(-1,0,-2);
		}
		else if(which_clust==14)
		{
		cluster_sum =sigM_p(2,0,1)+sigM_p(-2,0,1)+sigM_p(2,0,-1)+sigM_p(-2,0,-1);
		}
		else if(which_clust==15)
		{
		cluster_sum=sigM_p(0,1,2)+sigM_p(0,-1,2)+sigM_p(0,1,-2)+sigM_p(0,-1,-2);
		}
		else if(which_clust==16)
		{
		cluster_sum=sigM_p(0,2,1)+sigM_p(0,-2,1)+sigM_p(0,2,-1)+sigM_p(0,-2,-1);
		}
		else if(which_clust==17)
		{
			for(int x = -2; x<=2; x=x+4)
			{
				for(int y=-1; y<=1; y=y+2)
				{
					for(int z=-1; z<=1; z=z+2)
					{
					cluster_sum=cluster_sum + sigM_p(x,y,z);
					}
				}
			}
		}
		else if(which_clust==18)
		{
			for(int x = -1; x<=1; x=x+2)
			{
				for(int y=-2; y<=2; y=y+4)
				{
					for(int z=-1; z<=1; z=z+2)
					{
					cluster_sum=cluster_sum + sigM_p(x,y,z);
					}
				}
			}
		}
		else if(which_clust==19)
		{
			for(int x = -1; x<=1; x=x+2)
			{
				for(int y=-1; y<=1; y=y+2)
				{
					for(int z=-2; z<=2; z=z+4)
					{
					cluster_sum=cluster_sum + sigM_p(x,y,z);
					}
				}
			}
		}
		else if(which_clust==20)
		{
		cluster_sum = sigM_p(3,0,0)+sigM_p(-3,0,0);
		}
		else if(which_clust==21)
		{
		cluster_sum = sigM_p(0,3,0)+sigM_p(0,-3,0);
		}
		else if(which_clust==22)
		{
		cluster_sum = sigM_p(0,0,3)+sigM_p(0,0,-3);
		}

		else {cout << "\nYou did not enter a valid pair cluster"; } // end second order clusters //////////////////////////////////////////////////////////////////////////////
	}
	else if (cluster_type == "t")/// third order clusters ////////////////////////////////////////////////////////////////////////////////////////////////
	{
	}////////////////////////////end third order clusters ////////////////////////////////////////////////////////////////////////////////////////////////
	else if (cluster_type == "q")/////////////////////////// begin fourth order clusters  ///////////////////////////////////////////////////////////////////////
	{
		if(which_clust ==1)
		{
		    for(int x=-1; x<=1; x=x+2)
		    {
			for(int y=-1; y<=1; y=y+2)
			{
				cluster_sum = cluster_sum + sigM_q(x,0,0,0,y,0,x,y,0);
			}
		    }
		}
		else if(which_clust==2)
		{
			for(int x=-1; x<=1; x=x+2)
		    	{
				for(int y=-1; y<=1; y=y+2)
				{
					cluster_sum = cluster_sum + sigM_q(x,0,0,0,0,y,x,0,y);
				}
		    	}
		}
		else if(which_clust==3)
		{
			for(int x=-1; x<=1; x=x+2)
		    	{
				for(int y=-1; y<=1; y=y+2)
				{
					cluster_sum = cluster_sum + sigM_q(0,x,0,0,0,y,0,x,y);
				}
		    	}
			
		}
		else if(which_clust==4)
		{
			for(int x=-1; x<=1; x=x+2)
			{
				for(int y =-1; y<=1; y=y+2)
				{
					for(int z = -1; z<=1; z=z+2)
					{
					cluster_sum = cluster_sum + sigM_q(x,y,0,0,0,z,x,y,z);
					}
				}
			}
		}
		else if(which_clust==5)
		{
			for(int x=-1; x<=1; x=x+2)
			{
				for(int y =-1; y<=1; y=y+2)
				{
					for(int z = -1; z<=1; z=z+2)
					{
					cluster_sum = cluster_sum + sigM_q(x,0,z,0,y,0,x,y,z);
					}
				}
			}
		}
		else if(which_clust==6)
		{
			for(int x=-1; x<=1; x=x+2)
			{
				for(int y =-1; y<=1; y=y+2)
				{
					for(int z = -1; z<=1; z=z+2)
					{
					cluster_sum = cluster_sum + sigM_q(0,y,z,x,0,0,x,y,z);
					}
				}
			}
		}
		else{cout << "\nYou did not enter a valid  fourth order cluster type\n";}// end fourth order clusters /////////////////////////////////////////////////////////////
	}
	else
	{ cout << "\nYou did not enter a valid cluster type";}
	return cluster_sum; 
}

int cluster::spC(int i, int j , int k, int which_clust) const ///// function to return the cluster product of specific pairs at a given index 
{
	 int cluster_sum = 0; 
	
		if(which_clust==1)
		{	
		 cluster_sum = sigMs_p(i,j,k,1,0,0) + sigMs_p(i,j,k,-1,0,0);
		}
		else if(which_clust==2)
		{
		 cluster_sum = sigMs_p(i,j,k,0,1,0) + sigMs_p(i,j,k,0,-1,0);
		}
		else if(which_clust==3)
		{
		 cluster_sum = sigMs_p(i,j,k,0,0,1) + sigMs_p(i,j,k,0,0,-1);
		}
		else if(which_clust==4)
		{
		 cluster_sum = sigMs_p(i,j,k,1,1,0) + sigMs_p(i,j,k,-1,1,0) + sigMs_p(i,j,k,1,-1,0) + sigMs_p(i,j,k,-1,-1,0);
		}
		else if(which_clust==5)
		{
		 cluster_sum = sigMs_p(i,j,k,1,0,1) + sigMs_p(i,j,k,-1,0,1) + sigMs_p(i,j,k,1,0,-1) + sigMs_p(i,j,k,-1,0,-1);
		}
		else if(which_clust==6)
		{
		 cluster_sum = sigMs_p(i,j,k,0,1,1) + sigMs_p(i,j,k,0,-1,1) + sigMs_p(i,j,k,0,1,-1) + sigMs_p(i,j,k,0,-1,-1);
		}
		else if(which_clust==7)
		{
		cluster_sum = sigMs_p(i,j,k,1,1,1)+sigMs_p(i,j,k,-1,1,1)+sigMs_p(i,j,k,1,-1,1)+sigMs_p(i,j,k,1,1,-1)+sigMs_p(i,j,k,-1,-1,1)+sigMs_p(i,j,k,-1,1,-1)+sigMs_p(i,j,k,1,-1,-1)+sigMs_p(i,j,k,-1,-1,-1);
		}
		else if(which_clust==8)
		{
		cluster_sum = sigMs_p(i,j,k,2,0,0)+sigMs_p(i,j,k,-2,0,0);
		}
		else if(which_clust==9)
		{
		cluster_sum = sigMs_p(i,j,k,0,2,0)+sigMs_p(i,j,k,0,-2,0);
		}
		else if(which_clust==10)
		{
		cluster_sum = sigMs_p(i,j,k,0,0,2)+sigMs_p(i,j,k,0,0,-2);
		}
		else if(which_clust==11)
		{
		cluster_sum = sigMs_p(i,j,k,1,2,0)+sigMs_p(i,j,k,-1,2,0)+sigMs_p(i,j,k,1,-2,0)+sigMs_p(i,j,k,-1,-2,0);
		}
		else if(which_clust==12)
		{
		cluster_sum = sigMs_p(i,j,k,2,1,0)+sigMs_p(i,j,k,-2,1,0)+sigMs_p(i,j,k,2,-1,0)+sigMs_p(i,j,k,-2,-1,0);
		}
		else if(which_clust==13)
		{
		cluster_sum = sigMs_p(i,j,k,1,0,2)+sigMs_p(i,j,k,-1,0,2)+sigMs_p(i,j,k,1,0,-2)+sigMs_p(i,j,k,-1,0,-2);
		}
		else if(which_clust==14)
		{
		cluster_sum =sigMs_p(i,j,k,2,0,1)+sigMs_p(i,j,k,-2,0,1)+sigMs_p(i,j,k,2,0,-1)+sigMs_p(i,j,k,-2,0,-1);
		}
		else if(which_clust==15)
		{
		cluster_sum=sigMs_p(i,j,k,0,1,2)+sigMs_p(i,j,k,0,-1,2)+sigMs_p(i,j,k,0,1,-2)+sigMs_p(i,j,k,0,-1,-2);
		}
		else if(which_clust==16)
		{
		cluster_sum=sigMs_p(i,j,k,0,2,1)+sigMs_p(i,j,k,0,-2,1)+sigMs_p(i,j,k,0,2,-1)+sigMs_p(i,j,k,0,-2,-1);
		}
		else if(which_clust==17)
		{
			for(int x = -2; x<=2; x=x+4)
			{
				for(int y=-1; y<=1; y=y+2)
				{
					for(int z=-1; z<=1; z=z+2)
					{
					cluster_sum=cluster_sum + sigMs_p(i,j,k,x,y,z);
					}
				}
			}
		}
		else if(which_clust==18)
		{
			for(int x = -1; x<=1; x=x+2)
			{
				for(int y=-2; y<=2; y=y+4)
				{
					for(int z=-1; z<=1; z=z+2)
					{
					cluster_sum=cluster_sum + sigMs_p(i,j,k,x,y,z);
					}
				}
			}
		}
		else if(which_clust==19)
		{
			for(int x = -1; x<=1; x=x+2)
			{
				for(int y=-1; y<=1; y=y+2)
				{
					for(int z=-2; z<=2; z=z+4)
					{
					cluster_sum=cluster_sum + sigMs_p(i,j,k,x,y,z);
					}
				}
			}
		}
		else {cout << "\nYou did not enter a valid pair cluster"; } 
		return cluster_sum;
} //////// end  function to return the cluster product of specific pairs at a given index ///////////////////////////////////////


//    destructor
cluster::~cluster()
{
}

