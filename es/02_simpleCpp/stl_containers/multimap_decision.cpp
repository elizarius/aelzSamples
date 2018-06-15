void addMultiMapEmulator(const COPSStack::COPSDecision& obj, const COPSStack::COPSContext& cntxt)  
{

/*
 typedef multimap < COPSStack::COPSContext, vector <COPSStack::COPSDecision >  > DecisionMap;
 static DecisionMap _decisions;
 static vector <COPSStack::COPSDecision > tempDec ;
 static COPSStack::COPSContext& lastContext ; 
 
    assert(!obj.isLocalDecision());
    
    // If temp empty and first received object Dec flags , add it to temp
    if (obj.isFlagSet() && tempDec.empty() ) 
     tempDec.push_back(obj) ;
       
    if (!tempDec.empty()c &&  ) 
     tempDec.push_back(obj) ;
    
    
    
    if (obj.isFlagSet())
    {
        if (_decisions[cntxt].size())
        {
            std::cerr<<"AELZ trace point 01 ,ERROR  size = "<<_decisions[cntxt].size()<<endl ;	
            exit ( -1) ;           
            //Only one set of decision flags is allowed
            //for each context
        }
    }
    else
    {
        if (_decisions[cntxt].size() == 0)
        {
            std::cerr<<"AELZ trace point 02 exit from program  "<<endl ;	        	
            //The flags decision must precede any other
            //decision message, since the decision is not
            //flags throw exception
        }
    }
    _decisions[cntxt].push_back(obj);
     std::cerr<<" Member filled into DedMap tr_point 03 pass"<<endl ;	    
  
*/
	
}