#include <iostream>
#include <string>
#include <map>

using namespace std ;
     
    struct Key
    {
      public:
        /** Rule name. */
        char name[64];
        /**
        * Constructor.
        */
        Key(const std::string &name);

        /** < operaror. */
        bool operator < (const Key &k) const;

        private:
            /** No need for default constructor. */
            Key();
    };

Key::Key(const std::string &name)
{
    size_t i;
    for (i = 0;
        (i < sizeof(this->name) - 1) && (i < name.size());
        ++i)
    {
        this->name[i] = name[i];
    }
    for ( ; i < sizeof(this->name); ++i)
    {
        this->name[i] = '\0';
    }
}


typedef std::map<Key,std::string> KeyStringType ;

bool Key::operator < (const Key &k) const
{
    return (memcmp(this, &k, sizeof(*this)) == -1);

}


   int main()
   {
   std::cout<<"PRINT IN MAIN PROGRAM"<<std::endl ;
   Key key_1("FTIPSERule039") ;
   Key key_2("Rule01") ;
   std::cout<<"First key : "<<key_1.name<<std::endl ;
    
   KeyStringType Keys ;
   
   Keys.insert(std::pair<Key, std::string>(key_1,"My first  string") )  ; 
   Keys.insert(std::pair<Key, std::string>(key_2,"My second string") )  ; 
   
   Keys.erase(key_2 )  ; 
   Keys.erase(key_1 )  ; 

   Keys.insert(std::pair<Key, std::string>(key_1,"My first  string") )  ; 
//   Keys.insert(std::pair<Key, std::string>(key_2,"My second string") )  ; 

   /*
      
    KeyStringType::iterator it = Keys.find(key_1);
    if (it != Keys.end())
    {
     std::cout<< "Found key :: string "<<it->first.name<<" :  "<<it->second<<std::endl;
    }
    else
    {
     std::cout<< "Required key not found "<<std::endl;
    }
    
    */
    
    
    KeyStringType::iterator it1 = Keys.find(key_2);
    if (it1 != Keys.end())
    {
     std::cout<< "Found key :: string "<<it1->first.name<<" :  "<<it1->second<<std::endl;
    }
    else
    {
     std::cout<< "Required key not found "<<std::endl;
    }

    
    return 0 ; 
   }




