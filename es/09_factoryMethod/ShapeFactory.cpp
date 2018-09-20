#include <iostream>
#include <fstream>


const  int
LINE     =  1 ,
POLYGON  =  2 ,
CIRCLE   =  3 ; 



class Shape 
{
 public :
  virtual  void  Draw () const              =  0 ;
  virtual  void  Rotate (double angle )     =  0 ;
  virtual  void  Zoom   (double zoomFactor) =  0 ;
  
  // Read something from object , virtual
  virtual  void  Read ( ) = 0 ;
  
 private :
 
} ;


    void  Shape::Draw () const  
    {
    
    cout<<" Shape::Draw  default implementation of pure abstract function"<<endl ;
    }




class Line : public Shape 
{
 public :
  void  Draw () const           {  cout<<" Line::Draw   called "<<endl ;}
  void  Rotate (double angle )     {}
  void  Zoom   (double zoomFactor) {}
 
 
  void  Read ( ) {cout<<" Line::Read called<<endl"<<endl ;} 
} ;


class Polygon : public Shape 
{
 public :
   void  Draw () const          {cout<<" Polygon::Draw   called "<<endl ;}
   void  Rotate (double angle )     {}
   void  Zoom   (double zoomFactor) {}

 
  void  Read ( ) {cout<<" Polygon::Read called<<endl"<<endl  ;} 
  
  
} ;


class Cyrcle : public Shape 
{
 public :
   void  Draw () const            {cout<<" Cyrcle::Draw   called "<<endl ;}
   void  Rotate (double angle )     {}
   void  Zoom   (double zoomFactor) {}
    
 
   void  Read ( ) {cout<<" Cyrcle::Read called<<endl"<<endl ;} 
} ;




class Drawing 
{
 public  :
 void Save (std::ofstream& outFile ) {}
 void Load (std::ifstream& inFile )  ;
 
 private :  
 //current element 
} ;


void Drawing::Load (std::ifstream& inFile )
{

 while (inFile )
 {
   // read object type 
   int drawingType     ;
   inFile>>drawingType ;
 
   // create empty object 
   Shape* pCurrentObject ;
 
   switch (drawingType)
   {
   case LINE  :
    pCurrentObject = new Line ;
    break ;
    
   case POLYGON :
    pCurrentObject = new Polygon ;
    break ;

   case CIRCLE :
    pCurrentObject = new Cyrcle ;
    break ;
    
   default :
   cout<<" Drawing::Load unknown type of Shape , error "<<endl ;


   
   }
   
   pCurrentObject->Read ; 
 
 
 } 
 
}



int main ()
{

 cout<<" ::ShapeFactory  testing "<<endl ;
 return 0 ;
}