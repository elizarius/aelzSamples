#include <stdio.h>

void dump_memory(void* data, size_t len)
{
size_t i;
printf("Data in [%p..%p): \n",data,data+len);
for (i=0;i<len;i++)
printf("%02X ", ((unsigned char*)data)[i] );
printf("\n\n");
}


void dump_memory_1(void* data, size_t len)
{
size_t i;
char buffer [1000] ;
printf("Data in [%p..%p): \n",data,data+len);

for (i=0;i<len;i++)
 sprintf(buffer+(3*i), "%02X ", ((unsigned char*)data)[i] );
 
 printf("%s \n", buffer );
 printf("\n");
 
}




   int main(int argc, char **argv)
   {
   int x = 0x1234;
   dump_memory   (&x , 10 ) ; 
   dump_memory_1 (&x , 10 ) ; 
   return 0 ;
   
    
   }




