#include "../NN_fixed_hist.hpp"
//#include "/home/howard/cpp_programs/classes/histogram.hpp"
#include "../random.hpp"
using namespace std; 

 

int main()
{
//   dataset   myds("Dataset",458,5,3); 
  // vector<NN>     myNN; 
   //srand(time(NULL)); 
  // int S = 1; for(int x=1; x<=S; x++){myNN.push_back(NN(1,40,1,5));}
  NN  myNN(3,2,1,5); 
  cout <<"\n\n" << myNN.get_hW(3,2,2)<<"\n"; 

return 0; 
   
}

