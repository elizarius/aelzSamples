#include <iostream>

/* Eliminate duplicates from the array and print the unique numbers.
   The order of the unique numbers should be the same as their first occurrence
   in the input array.
   #  Use 
*/
void unique_numbers( int numbers[], unsigned int collection_size){
  int j = 0;
  int output[] ={};
  output[0] = numbers[0];
  bool repeat = false;
   
  for (int i = 0; i<collection_size; ++i) {
    bool repeat = false;

    for (int j = 0; j<numbers[i]; ++j)
      if (output[j] == numbers[i]) {
        repeat = true;
        break;
      }
  if (!repeat)
      output[++j] = numbers[i];
  }

  for (int j= 0; j< sizeof(output); j++)
  std::cout<<output[j];
    
}

int main () {
    int numbers[] = {1, 2, 3, 4, 5, 1, 2, 3};
    unsigned int collection_size = sizeof(numbers) / sizeof(numbers[0]);
    unique_numbers(numbers, collection_size);
    return 0;
}
