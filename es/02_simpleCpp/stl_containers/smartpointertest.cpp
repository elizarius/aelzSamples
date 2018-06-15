#include "I_COPSServer/stack/internal/Sptr.hxx"

int main() {
  Sptr<int> p1(new int(3));
  Sptr<int> p2(new int(4));
  Sptr<int> p3(new int(5)); // this is freed
  
  p1.release();
  p2.release();
  
  p2 = p1;
  p1 = p3;
  // when checking with valgrind, it shows that the releasing works, and the "released" memory is not freed      
}