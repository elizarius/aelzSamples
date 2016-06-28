#include <getopt.h>
#include <string.h>
#include <cstdlib>

#include "InterfaceHandler.h"
#include "HelpHandler.h"

extern "C"
{

#include <bits/sockaddr.h>
#include <linux/netlink.h>

#include <tlv.h>
#include "msg.h"
}


using namespace std;

int InterfaceHandler::processCli(int argc, char * argv[])
{
    struct option InterfaceOptions[]=
    {
        {"if-name", required_argument, 0, 'i'},
        {"if-index",required_argument, 0, 'n'},
        {"mtu",     required_argument, 0, 'm'},
        {"help",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int argMust= 0 ;
    int c;
    while(-1 != (c = getopt_long(argc, argv, "i:m:h", InterfaceOptions, NULL)))
    {
        char *tail=NULL;
        switch(c)
        {
            case 'i':
                ifaceName_ = optarg;
                argMust++;
                break ;

            case 'm':
                mtuSize_ = atoi(optarg);
                break ;

            case 'n':
                ifaceIndex_ = atoi(optarg);
                break ;

            case 'h':
                return helpMessage(hIface_.c_str());

            default:
                cout << "InterfaceManager : unrecognized argument "<<c<<endl;
                return 0 ;
        }
 
        if (tail && strlen(tail) > 0)
        {
            cout<< "garbage at: "<< tail<<endl;
            return 0;
        }
    
    } // END WHILE

    if (argMust < 1)
    {
        cout<< "ERR: if-name must present in command"<< endl;
        return 0;
    }

    return 1 ;
}


int InterfaceHandler::fillInterfaceMsg()
{

   struct hal_msg_if ifMsg ;

    // 1. fill msg_if structure with input data 
    //
    memset (&ifMsg,0 , sizeof (struct hal_msg_if) );
    strcpy(ifMsg.name, ifaceName_.c_str());
    ifMsg.ifindex = ifaceIndex_;
    ifMsg.mtu     = mtuSize_;

    // Set cindex bit = xxxx x1xx for set_mtu
    //
    // Do not ask me IPI logic behind : 
    //
    //  - HAL_MSG_CINDEX_IF_MTU = 2
    //  - left shift 1<< 2 --> x1xx
    //  - than bitwise | required field
    //
    ifMsg.cindex  = ifMsg.cindex |0x0004 ;

  
    // 2. create netlink structure, we use
    //    regular netlink header but not hal_netlink   
    //struct nlmsghdr *nlh;
    u_char *pnt;
    u_char *zz_pnt;
    int size, msgsz;

    struct 
    {
       struct nlmsghdr nlh;
       u_char buf[512];
    } req;

    /* Set message. */

    pnt = (u_char *)req.buf;
    size = sizeof (req.buf) ;

    // AELZ_103: fill buffer with data from ifMsg_ and calculate some size;  
     //msgsz = hal_msg_encode_if (&pnt, (u_int32_t *)&size, &ifMsg);

  /* Interface name. */
  //TLV_ENCODE_PUT (ifMsg.name, HAL_IFNAME_LEN + 1);
  memcpy ( (void *)(*pnt), (void *)(ifMsg.name),HAL_IFNAME_LEN + 1);
  pnt += (HAL_IFNAME_LEN +1);

  
  /* Interface index. */
  //TLV_ENCODE_PUTL (ifMsg.ifindex);
  *pnt       = (ifMsg.ifindex >> 24) & 0xFF;          
  *(pnt + 1) = (ifMsg.ifindex >> 16) & 0xFF;        
  *(pnt + 2) = (ifMsg.ifindex >> 8)  & 0xFF;
  *(pnt + 3) = (ifMsg.ifindex) & 0xFF;       
    pnt += 4;                      


  /* Interface type. L2/L3 */
  //TLV_ENCODE_PUTC (ifMsg.type);
      *pnt     = ifMsg.type & 0xFF;
       pnt++;

 
//          hal_msg_encode_tlv (pnt, size, i, 4);
//         (u_char **pnt, u_int32_t *size, u_int16_t type, u_int16_t length)

////            length += HAL_MSG_TLV_HEADER_SIZE;

////            TLV_ENCODE_PUTW (type);
////            TLV_ENCODE_PUTW (length);


//       TLV_ENCODE_PUTW (msg->mtu);
      *(pnt)     = (mtuSize_ >> 8) & 0xFF;    
      *(pnt + 1) = (mtuSize_) & 0xFF;         
       pnt += 2;                      
  

    /* Set header. */
    //nlh = &req.nlh;
    req.nlh.nlmsg_len = 20;	// AELZ_101 : add calculated value
    req.nlh.nlmsg_flags = NLM_F_CREATE | NLM_F_REQUEST | NLM_F_ACK;
    req.nlh.nlmsg_type =  HAL_MSG_IF_SET_MTU; 
    req.nlh.nlmsg_seq = 1;	// AELZ_102 : add calculated value but not hardcoded 

    // AELZ_104: send message , in this case just return req buffer 
    return 0 ;
}


