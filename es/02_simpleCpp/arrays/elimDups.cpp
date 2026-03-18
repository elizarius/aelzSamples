#include <iostream>

/* Eliminate duplicates from the array and print the unique numbers.
   The order of the unique numbers should be the same as their first occurrence
   in the input array.

   *** Use own array in exercise. Do not use STL containers!!! ****  
*/
void unique_numbers( int numbers[], unsigned int collection_size){
  int output[] ={};
  output[0] = numbers[0];
  bool repeat = false;
  int j;

  for (unsigned int i = 0; i<collection_size; i++) {
    std::cout<<numbers[i]<<std::endl;
      repeat = false;
      
      for (j = 0; j<=i; j++) {
        std::cout<<" ou: "<<output[j]<< " num: " << numbers[i] << std::endl;
        if (output[j] == numbers[i]) {
          repeat = true;
          break;
        }
      if (!repeat) {
        output[j+1] = numbers[i];
        std::cout<<" OU ADDED index:"<<j+1<<" "<<output[j]<< std::endl;
      }


      // else {
      //   std::cout<<" no match "<<std::endl;
      //   output[j] = numbers[i];
      //   repeat = false;
      // }
      
    }
    // if (!repeat)
    //   output[++i] = numbers[i];

  }

  // for (int j= 0; j< sizeof(output)/sizeof(output[0]);  ++j)
  //   std::cout<<std::endl<<output[j];
    
}

int main () {
    int numbers[] = {1, 2, 3, 4, 5, 1, 2, 3};
    unsigned int collection_size = sizeof(numbers) / sizeof(numbers[0]);
    unique_numbers(numbers, collection_size);
    return 0;
}
