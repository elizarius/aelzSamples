#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
class Path
{
public:
    Path(std::string path)
    {
        currentPath = path;
    }

    std::string getPath() const
    {
        return currentPath;
    }

    void cd(std::string newPath)
    {
            
        size_t last_dir_pos = currentPath.size()-1;

        // 1. Check whether change directory in beginnig 
         size_t posit = newPath.find("../");
         if  (posit == 0) {
            std::cout<< "AELZ step 1 "<<endl;
            currentPath.replace(last_dir_pos, 2, newPath.substr(3));
            return;
        }
        
          //3. Select parent directory.
          posit = newPath.find("..");
          if  (posit != std::string::npos) {
          
              posit = currentPath.find_last_of("/\\");
              std::cout<< "AELZ step 3 "<<endl;
              currentPath = currentPath.substr(0, posit);
              return;
          } 

        
         //2. Select child directory.
          posit = newPath.find("/\\");
          if  (posit == std::string::npos) {
              std::cout<< "AELZ step 2- "<<endl;
              currentPath = currentPath + "/"+ newPath;
              return;
          } 
        
        
    }

private:
    std::string currentPath;
};

#ifndef RunTests
int main()    
{
    Path path("/a/b/c/d");
    path.cd("../x");
    std::cout << path.getPath()<<endl;
    
    path.cd("x");
    std::cout << path.getPath()<<endl;

    // Parent dir 
    path.cd("..");
    std::cout << path.getPath()<<endl;
    
}
#endif
