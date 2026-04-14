#include <iostream>

/* Eliminate duplicates from the array and print the unique numbers.
   The order of the unique numbers should be the same as their first occurrence
   in the input array.

   *** Use own array in exercise. Do not use STL containers!!! ****  
*/
void unique_numbers( int numbers[], unsigned int collection_size){
  int output[20];
  int unic_ctr = 0;

  for (unsigned int i = 0; i<collection_size; ++i) {
      bool repeat = false;
      
      for (unsigned int j = 0; j<unic_ctr; ++j) {
        if (output[j] == numbers[i]) {
          repeat = true;
          std::cout<<" Duplicate found, BREAKING J LOOP "<<" I:"<<i<<" value:"<<numbers[i]<< std::endl;
          break;
        }
      }
      if (!repeat) {
        std::cout<<" OUTPUT ADDING index:"<<unic_ctr<< " output: "<<numbers[i]<< std::endl;
        output[unic_ctr++] = numbers[i];
      }
  }
  
  std::cout<<" Unique Outputs:  ";
  for (int k= 0; k<unic_ctr;  ++k)
    std::cout<<output[k]<<" ";
  std::cout<< std::endl;
}

int main () {
    int numbers[] = {1, 1, 2, 3, 4, 5, 1, 2, 2};
    unsigned int collection_size = std::size(numbers);
    unique_numbers(numbers, collection_size);
    return 0;
}
