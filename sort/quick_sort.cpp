#include <iostream>
#include<vector>
#include<thread>

using namespace std;
vector<int> arr(10);
int pivot=0;



void display(vector<int> &vec)
{
 cout<<"\narray:";
 for(int i=0;i<vec.size();i++)
 {
  cout<<"\t"<<vec[i];
 }
}

void swap(vector<int> &vec,int low,int high){
 int temp=vec[low];
 vec[low]=vec[high];
 vec[high]=temp;
}

int partation(vector<int> &vec,int low,int high){
	pivot=low;
	swap(vec,low,high);
	for(int i=low;i<high;i++){
		if(vec[i]<=vec[high]){
			swap(vec,i,low);
			low+=1;
		}
	}
	swap(vec,low,high);
    return low;

}

void quicksort(vector<int> &vec,int low,int high)
{
 if (low<high){
  pivot=partation(vec,low,high);
  thread t1([&]{
            quicksort(vec,low,pivot-1);
        });
  thread t2([&] {
            quicksort(vec,pivot+1,high);
        });
   t1.join();
   t2.join();

  /*quicksort(vec,low,pivot-1);
  quicksort(vec,pivot+1,high);*/
}
}






int main() {
    std::cout << "Enter the size of the array: ";
    int size;
    std::cin >> size;

    std::cout << "Enter the elements of the array: ";
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
	display(arr);
	quicksort(arr,0,arr.size()-1);
	cout<<"\n After sorting:";
	display(arr);
	return 0;
}
// the output of the code
// Enter the size of the array: 3
// Enter the elements of the array: 
// 4
// 1
// 6

// array:  4       1       6        
//  After sorting:
// array:  1       4       6  