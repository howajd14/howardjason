#include "../file_class/file.hpp"
#include <math.h>
using namespace std;

class character_table
{

	public:
	character_table();
	character_table(string group_name, int num_classes_g, int group_order);
	character_table(string group_name1, int num_classes_g1,  string group_name2, int num_classes_g2);
	~character_table();

	int triple_p(string a, string b, string c); 
	double decomp(string rep_chars, string aj); 
	int num_members(){return members.size();}    
	int num_reps(){return representations.size();}
	string get_char(int index){return characters[index-1];}
	string rep_name(int index){return representations[index-1];}
	string member_name(int index){return members[index-1];}
	void make_table(string table_name);
	


	private:
	vector<string> representations;
	vector<string> members;
	vector<string> characters; 
	vector<int>    N_K; 
	int order; 
	int num_classes; 
	

};

character_table::character_table() //the null character table 
{	
	representations.push_back("");
	members.push_back("");
	characters.push_back("");
	N_K.push_back(0);
	order =0; 
	num_classes = 0;
}

character_table::character_table(string character_file,int num_classes_g, int group_order)
{
	file character_info(character_file);   string line;   line = character_info.get_line(1); 
	stringstream ss; ss << line; 
	order = group_order; 
	num_classes = num_classes_g; 
	for(int x = 1 ; x<=num_classes; x++)
	{
		string holder;  ss >> holder; representations.push_back(holder);
	}
	line = character_info.get_line(2);  ss.clear(); ss.str(""); ss << line; 
	for(int x = 1; x<= num_classes; x++)
	{
		int holder;   ss >> holder; N_K.push_back(holder);
	}
	for(int x = 3; x<= character_info.num_lines();x++)
	{
		ss.clear(); ss.str("");  line = character_info.get_line(x); ss << line;  string character_line = "";
		for(int y = 1; y<=num_classes+1; y++)
		{
			
			if(y==1){string holder; ss >> holder; members.push_back(holder);}
			if(y>1){string holder; ss >> holder;  character_line = character_line + holder + "\t"; }
			
		}
		characters.push_back(character_line);
	}
	
	
}


// constructor for a direct product group 
character_table::character_table(string character_file1, int num_classes_g1,  string character_file2, int num_classes_g2)
{
	//initialize first talbe 
	file character_info1(character_file1);    string line;   line = character_info1.get_line(1);  stringstream ss; ss << line;  vector<string> rep1; 
	for(int x = 1 ; x<=num_classes_g1; x++)
	{
		string holder;  	ss >> holder; rep1.push_back(holder);
	}
	line = character_info1.get_line(2);   ss.clear(); ss.str(""); ss << line;   vector<int>  N_K1;
	for(int x = 1; x<= num_classes_g1; x++)
	{
		int holder;    ss >> holder; N_K1.push_back(holder);
	}
	vector<string> members1;    vector<string> characters1; 
	for(int x = 3; x<= character_info1.num_lines();x++)
	{
		ss.clear(); ss.str("");   line = character_info1.get_line(x);  ss << line;   string character_line = "";
		for(int y = 1; y<=num_classes_g1+1; y++)
		{
			
			if(y==1){string holder; ss >> holder; members1.push_back(holder);} if(y>1){string holder; ss >> holder;  character_line = character_line + holder + "\t"; }
		}
		characters1.push_back(character_line);
	}
	// end intialize  first table  start second 
	file character_info2(character_file2);   line = character_info1.get_line(1);   ss.clear();ss.str(""); ss << line; vector<string> rep2; 
	for(int x = 1 ; x<=num_classes_g2; x++)
	{
		string holder;  ss >> holder; rep2.push_back(holder);
	}
	line = character_info2.get_line(2);  ss.clear(); ss.str(""); ss << line;   vector<int>  N_K2;
	for(int x = 1; x<= num_classes_g2; x++)
	{
		int holder;  ss >> holder; N_K2.push_back(holder);
	}
	vector<string> members2;  vector<string> characters2; 
	for(int x = 3; x<= character_info2.num_lines();x++)
	{
		ss.clear(); ss.str("");  line = character_info2.get_line(x);  ss << line;  string character_line = "";
		for(int y = 1; y<=num_classes_g2+1; y++)
		{
			
			if(y==1){string holder; ss >> holder; members2.push_back(holder);} if(y>1){string holder; ss >> holder;  character_line = character_line + holder + "\t"; }
			
		}
		characters2.push_back(character_line);
	}
	//end initialize  second table start intitalize  direct prodcut into private values 
	order = 0; 
	for(unsigned int x =1; x<=rep2.size(); x++)
	{
		for(unsigned int y=1; y<=rep1.size(); y++)
		{
			representations.push_back(rep1[y-1]+rep2[x-1]);   N_K.push_back(N_K1[y-1]*N_K2[x-1]);  order = order + N_K1[y-1]*N_K2[x-1];
			
		}
	}
	for(unsigned int x =1; x<= members2.size(); x++)
	{
		for(unsigned int y =1; y<=members1.size(); y++)
		{
			members.push_back(members1[y-1]+members2[x-1]);  string char1 = characters1[y-1];  string char2 = characters2[x-1];
			vector<double> Char1v; vector<double> Char2v;   	stringstream ty; ty << char1; 
			for(int ll =1; ll <= num_classes_g1; ll++)
			{
				double  holdnow;  ty >> holdnow; Char1v.push_back(holdnow);
			}
			ty.clear();ty.str(""); ty << char2; 
			for(int jh=1; jh<=num_classes_g2; jh++)
			{
				double holdnow;  ty >> holdnow; Char2v.push_back(holdnow);
			}
			string CharLine = "";
			for(unsigned int ik =1; ik <= Char2v.size(); ik++)
			{
				for(unsigned int op=1; op<= Char1v.size(); op++)
				{
					string holdstring1;  ty.clear(); ty.str("");  ty << (Char1v[op-1]*Char2v[ik-1]); ty >> holdstring1; 
					if(ik==Char2v.size()&&Char1v.size()==op)
					{
						CharLine = CharLine + holdstring1; 
					}
					else {CharLine = CharLine + holdstring1 + " ";}
				}
			}
			characters.push_back(CharLine);
		}
	}
	num_classes = members.size(); 
	// end  intitalize total direct product character table 
}

int character_table::triple_p(string a, string b, string c)
{
	int index_a, index_b, index_c; 
	for(unsigned int x = 1; x<= members.size();  x++)
	{
		if(a == members[x-1]){index_a = x;}
		if(b == members[x-1]){index_b = x;}
		if(c == members[x-1]){index_c = x;}
	}

	vector<int> a_character, b_character, c_character; 
	
	stringstream sa, sb, sc; 
	sa << characters[index_a-1]; sb << characters[index_b-1]; sc << characters[index_c-1];
	for(int x = 1; x<= num_classes; x++)
	{
		int holder; 
		sa >> holder; a_character.push_back(holder);
		sb >> holder; b_character.push_back(holder);
		sc >> holder; c_character.push_back(holder); 
	}
	int sum = 0; 
	for(int x = 1; x<=num_classes; x++)
	{
		sum = sum + N_K[x-1]*a_character[x-1]*b_character[x-1]*c_character[x-1];
		
	}
return sum; 
}

void character_table::make_table(string table_name)
	{
		file  outfile; string outline=""; string holder; 
		stringstream ss; 
		for(unsigned int x=1; x<=representations.size(); x++)
		{
				if(x<representations.size())
				{
				ss << representations[x-1]; ss >> holder; outline = outline + holder + "   ";
				}
				else
				{
				ss << representations[x-1]; ss >> holder; outline = outline + holder;
				}
				ss.clear();ss.str("");
		}
		outfile.add_line(outline);
		ss.clear();ss.str("");outline = "";
		for(unsigned int x=1; x<=N_K.size(); x++)
		{
				if(x<representations.size())
				{
				ss << N_K[x-1]; ss >> holder; outline = outline + holder + "   ";
				}
				else
				{
				ss << N_K[x-1]; ss >> holder; outline = outline + holder;
				}
				ss.clear(); ss.str("");
		}
		outfile.add_line(outline);
		ss.clear();ss.str("");outline = "";
		for(unsigned int x=1; x<=members.size(); x++)
		{
				outline = members[x-1]; 
				outline = outline + "  " + characters[x-1]; 
				outfile.add_line(outline);
		}
		outfile.make_file(table_name);

}	

double character_table::decomp(string rep_chars, string aj)
{
     vector<int> rep_char; stringstream hh; hh << rep_chars; 
      int sum=0;
      int aj_index;  vector<int> aj_char; 
     for(int x =1; x<=num_classes; x++)
     {
	int holder; hh >> holder;  rep_char.push_back(holder); 
     }
     for(unsigned x =1; x<= members.size(); x++)
     {
	if(aj==members[x-1]){aj_index = x;}
     }
     hh.clear(); hh.str(""); hh << characters[aj_index-1]; //cout << "\n" << characters[aj_index-1];
     for(int x =1; x<= num_classes; x++)
     {
	int holder;  hh >> holder; aj_char.push_back(holder); 
     }
     for(int x =1 ; x<=num_classes; x++)
     {
	sum = sum + N_K[x-1]*aj_char[x-1]*rep_char[x-1];
     }
    
return (1.0*sum)/(1.0*order);  

}

	
/*
string character_table:: inv(string a)
{
	
}
*/
character_table::~character_table()
{}

/*
test stuff 

TD table 
e c3 c2 od s4
1 8 8 6 6
a1 1 1 1 1 1
a2 1 1 1 -1 -1
e 2 -1 2 0 0 
t1 3 0 -1 -1 1
t2 3 0 -1 1 -1

Itable 
E i
1 1
r1 1 1
r2 1 -1

#include "character_table_2.0.hpp"
using namespace std;

int main()
{

character_table DP_TDi("TD_table", 5,"Itable",2);


DP_TDi.make_table("TD_DP_I");



return 0;
}

#include "character_table_2.0.hpp"
using namespace std;
int main()
{
        
character_table  TD("TD_table",5);

string l1 = "3 0 -1 3 3"; 

cout << "\n" << TD.decomp(l1,"e") <<"\n";

return 0;
}






*/
