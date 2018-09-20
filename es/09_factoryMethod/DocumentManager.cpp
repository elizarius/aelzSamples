#include <iostream>
#include <list>

class Document        ;        // forward declaration 
class GraphicDocument ;

class DocumentManager 
{
public  :
 Document *  NewDocument() ;
 
private :
 virtual Document *   CreateDocument () = 0 ;
 std::list<Document*> listOfDocs_ ;

} ;


 
Document * DocumentManager::NewDocument ()
{
 Document* pDoc = CreateDocument () ;
 listOfDocs_.push_back ( pDoc ) ;
 //.......... do something else 
 
 return pDoc ;

}	


/**
*
* Derived class declarations and definitions 
* 
*/


class GraphicDocumentManager : public DocumentManager  
{
public  :

Document *   CreateDocument () ;


private :


} ;


Document *   GraphicDocumentManager::CreateDocument () 
{

 //return  new GraphicDocument  ;
}


int main ()
{
 cout<<"::Main  Object Factory test "<<endl ;
 return 0;
}
