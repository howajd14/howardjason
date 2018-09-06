#include "../file_class/file.hpp"
#include <math.h>
using namespace std;

class group
{

	public:
	group();
	group(string group_name, int group_order);
	~group();
	string mult(string a, string b);
	string inv(string a);
	int size(){return group_lbs.size();}
	string get_label(int index){return group_lbs[index-1];}

	private:
	vector<string> group_lbs;
	vector<string> group_ops;
	int order;

};

group::group()
{
	order = 0;
}

group::group(string group_name, int group_order)
{
	file group_info(group_name);
	order = group_order;
	for(int x = 1; x<=group_info.num_lines(); x++)
	{
		stringstream ss; 
		string holder;
		string line = group_info.get_line(x); ss << line;
		ss >> holder; group_lbs.push_back(holder);
		string ops_line;
		for(int y =1; y <=group_order; y++)
		{
			ss >> holder; 
			if(y==1){ops_line = holder;}
			if(y>1){ops_line = ops_line + "\t" + holder;}
		}
		//cout << "\n" << ops_line;
		group_ops.push_back(ops_line);
		
	}
}

string group::mult(string a, string b)
{
	int i1, i2;
	string ops1, ops2, output; 
	vector<int> ops1_vec; vector<int> ops2_vec; vector<int> product_vec; 
	for(unsigned int x = 1; x<=group_lbs.size(); x++)
	{
		if(a == group_lbs[x-1]){i1=x;}
		if(b == group_lbs[x-1]){i2=x;}
	}
		string i1_ops = group_ops[i1-1];
		string i2_ops = group_ops[i2-1];
		stringstream ssi1; ssi1 << i1_ops;
		stringstream ssi2; ssi2 << i2_ops;
	for(int x =1; x<=order; x++)
	{
		int holder1; ssi1 >> holder1;
		int holder2; ssi2 >> holder2; 
		ops1_vec.push_back(holder1);
		ops2_vec.push_back(holder2);
		
	}
	for(int x=1; x<=order; x++)
	{
		int multiplier =  ops1_vec[x-1]/sqrt(ops1_vec[x-1]*ops1_vec[x-1]);
		int index      =  sqrt(ops1_vec[x-1]*ops1_vec[x-1]);
		product_vec.push_back(multiplier*ops2_vec[index -1]);
	}
	
	for(unsigned int x =1; x<=group_ops.size(); x++)
	{
		int truth = 1;
		int holderhere; stringstream jk;
		vector<int> temp_ops;
		string linehere = group_ops[x-1]; jk << linehere;
		for(int y = 1; y <= order; y++)
		{
			jk >> holderhere;  
			if(product_vec[y-1]!= holderhere){truth=0;}
		}
		if(truth == 1){output = group_lbs[x-1]; }
	}
	return output; 
}

string group:: inv(string a)
{
	string inverse;
	for(unsigned int x =1; x<=group_lbs.size(); x++)
	{
		if(group_lbs[0]==mult(a,group_lbs[x-1])){inverse=group_lbs[x-1];}

	}
	return inverse;
}

group::~group()
{}

/*
test stuff 
#include "groups.hpp"
using namespace std;

int main()
{

group P("group_rep",3);

cout << "\n" << P.inv("a") << "\n";
cout << "\n" << P.inv("b") << "\n";

return 0;
}

group rep file

e  1 2 3
a -1 -2 3
b -2 1 3
c 2 -1 3
d -1 2 -3
f 1 -2 -3
g 2 1 -3
h -2 -1 -3



*/
