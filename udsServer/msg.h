//#include <hal_types.h>

#undef pal_mem_cpy
#define pal_mem_cpy memcpy

typedef unsigned int hal_cindex_t;
#define CINDEX_SIZE                    32

#define HAL_IFNAME_LEN  20
/* MAC address length. */
#define HAL_HW_LENGTH   6

#define HAL_MSG_IF_SIZE                                 (HAL_IFNAME_LEN + 1 + 4)
#define HAL_MSG_CINDEX_IF_FLAGS                          0
#define HAL_MSG_CINDEX_IF_METRIC                         1
#define HAL_MSG_CINDEX_IF_MTU                            2
#define HAL_MSG_CINDEX_IF_HW                             3
#define HAL_MSG_CINDEX_IF_BANDWIDTH                      4
#define HAL_MSG_CINDEX_IF_DUPLEX                         5
#define HAL_MSG_CINDEX_IF_AUTONEGO                       6
#define HAL_MSG_CINDEX_IF_ARP_AGEING_TIMEOUT             7
#define HAL_MSG_CINDEX_IF_SEC_HW_ADDRESSES               8
#define HAL_MSG_CINDEX_IF_IF_FLAGS                       9

#define HAL_MSG_LACP_PSC_SIZE  (8)


/* 
   Interface manager messages. 
*/
#define HAL_MSG_IF_BASE                             600
#define HAL_MSG_IF_MSG(n)                           (HAL_MSG_IF_BASE + (n))
#define HAL_MSG_IF_NEWLINK                          HAL_MSG_IF_MSG(1)
#define HAL_MSG_IF_DELLINK                          HAL_MSG_IF_MSG(2)
#define HAL_MSG_IF_GETLINK                          HAL_MSG_IF_MSG(3)
#define HAL_MSG_IF_GET_METRIC                       HAL_MSG_IF_MSG(4)
#define HAL_MSG_IF_GET_MTU                          HAL_MSG_IF_MSG(5)
#define HAL_MSG_IF_SET_MTU                          HAL_MSG_IF_MSG(6)
#define HAL_MSG_IF_GET_HWADDR                       HAL_MSG_IF_MSG(7)
#define HAL_MSG_IF_SET_HWADDR                       HAL_MSG_IF_MSG(8)
#define HAL_MSG_IF_SET_SEC_HWADDRS                  HAL_MSG_IF_MSG(9)
#define HAL_MSG_IF_ADD_SEC_HWADDRS                  HAL_MSG_IF_MSG(10)
#define HAL_MSG_IF_DELETE_SEC_HWADDRS               HAL_MSG_IF_MSG(11)
#define HAL_MSG_IF_GET_FLAGS                        HAL_MSG_IF_MSG(12)
#define HAL_MSG_IF_SET_FLAGS                        HAL_MSG_IF_MSG(13)
#define HAL_MSG_IF_UNSET_FLAGS                      HAL_MSG_IF_MSG(14)
#define HAL_MSG_IF_GET_BW                           HAL_MSG_IF_MSG(15)
#define HAL_MSG_IF_SET_BW                           HAL_MSG_IF_MSG(16)
#define HAL_MSG_IF_IPV4_NEWADDR                     HAL_MSG_IF_MSG(17)
#define HAL_MSG_IF_IPV4_DELADDR                     HAL_MSG_IF_MSG(18)
#define HAL_MSG_IF_SET_PORT_TYPE                    HAL_MSG_IF_MSG(19)
#define HAL_MSG_IF_CREATE_SVI                       HAL_MSG_IF_MSG(20)
#define HAL_MSG_IF_DELETE_SVI                       HAL_MSG_IF_MSG(21)
#define HAL_MSG_IF_COUNTERS_GET                     HAL_MSG_IF_MSG(22)
#define HAL_MSG_IF_L3_INIT                          HAL_MSG_IF_MSG(23) 
#define HAL_MSG_IF_L2_INIT                          HAL_MSG_IF_MSG(24) 
#define HAL_MSG_IF_GET_DUPLEX                       HAL_MSG_IF_MSG(25)
#define HAL_MSG_IF_SET_DUPLEX                       HAL_MSG_IF_MSG(26)
#define HAL_MSG_IF_SET_AUTONEGO                     HAL_MSG_IF_MSG(27)
#define HAL_MSG_IF_GET_ARP_AGEING_TIMEOUT           HAL_MSG_IF_MSG(28)
#define HAL_MSG_IF_SET_ARP_AGEING_TIMEOUT           HAL_MSG_IF_MSG(29)
#ifdef HAVE_IPV6
#define HAL_MSG_IF_IPV6_NEWADDR                     HAL_MSG_IF_MSG(30)
#define HAL_MSG_IF_IPV6_DELADDR                     HAL_MSG_IF_MSG(31)
#endif /* HAVE_IPV6 */
#define HAL_MSG_IF_STP_REFRESH                      HAL_MSG_IF_MSG(32)
#define HAL_MSG_IF_UPDATE                           HAL_MSG_IF_MSG(33)
#define HAL_MSG_IF_CLEANUP_DONE                     HAL_MSG_IF_MSG(33)
#define HAL_MSG_IF_FIB_BIND                         HAL_MSG_IF_MSG(34)
#define HAL_MSG_IF_FIB_UNBIND                       HAL_MSG_IF_MSG(35)
#define HAL_MSG_IF_STATS_FLUSH                      HAL_MSG_IF_MSG(36)
#define HAL_MSG_IF_SET_MDIX                         HAL_MSG_IF_MSG(37)
#define HAL_MSG_IF_PORTBASED_VLAN                   HAL_MSG_IF_MSG(38) 
#define HAL_MSG_IF_PORT_EGRESS                      HAL_MSG_IF_MSG(39)
#define HAL_MSG_IF_CPU_DEFAULT_VLAN                 HAL_MSG_IF_MSG(40)
#define HAL_MSG_IF_SET_FORCE_VLAN                   HAL_MSG_IF_MSG(41)
#define HAL_MSG_IF_SET_ETHER_TYPE                   HAL_MSG_IF_MSG(42)
#define HAL_MSG_IF_SET_LEARN_DISABLE                HAL_MSG_IF_MSG(43)
#define HAL_MSG_IF_GET_LEARN_DISABLE                HAL_MSG_IF_MSG(44)         
#define HAL_MSG_IF_SET_SW_RESET                     HAL_MSG_IF_MSG(45)
#define HAL_MSG_IF_WAYSIDE_DEFAULT_VLAN             HAL_MSG_IF_MSG(46)
#define HAL_MSG_IF_PRESERVE_CE_COS                  HAL_MSG_IF_MSG(47) 
#define HAL_MSG_IF_L3_DEINIT                        HAL_MSG_IF_MSG(48)
#define HAL_MSG_IF_DEBUG_HSL                        HAL_MSG_IF_MSG(49) 
#define HAL_MSG_VRRP_UPDATE                         HAL_MSG_IF_MSG(50) 
#define HAL_MSG_IF_CLEAR_COUNTERS                   HAL_MSG_IF_MSG(51)  
#ifdef HAVE_BVI
#define HAL_MSG_IF_CREATE_BVI                       HAL_MSG_IF_MSG(52)
#define HAL_MSG_IF_DELETE_BVI                       HAL_MSG_IF_MSG(53)
#define HAL_MSG_IF_DHCP_SET_ACTION                  HAL_MSG_IF_MSG(54)
#endif /* HAVE_BVI */
#define HAL_MSG_SYSTEM_TIME_UPDATE                  HAL_MSG_IF_MSG(55)

#define HAL_MSG_IF_SET_PTP_CONFIG                   HAL_MSG_IF_MSG(56)
#define HAL_MSG_IF_UNSET_PTP_CONFIG                 HAL_MSG_IF_MSG(57) 


/* 
   Interface message. 
*/
struct hal_msg_if
{
  hal_cindex_t cindex;

  /* Mandatory parameters start. */

  /* Name. */
  char name[HAL_IFNAME_LEN + 1];

  /* Ifindex. */
  unsigned int ifindex;

  /* Mandatory parameters end. */

  /* Flags TLV. */
  unsigned long flags;

  /* Metric TLV. */
  unsigned int metric;

  /* MTU TLV. */
  unsigned int mtu;

  /* DUPLEX TLV. */
  unsigned int duplex;

  /* AUTONEGO TLV, */
  unsigned int autonego;

  /* ARP AGEING TIMEOUT TLV. */
  unsigned int arp_ageing_timeout;

  /* HW Type, Address TLV. */
  unsigned short hw_type;
  unsigned short hw_addr_len;
  unsigned char hw_addr[HAL_HW_LENGTH];

  /* Number of secondary MAC addresses.*/
  unsigned char nAddrs;
  unsigned short sec_hw_addr_len;
  unsigned char **addresses;

  /* Bandwidth TLV. */
  unsigned int bandwidth;

  /* Interface type L3/L2 */
   unsigned char type;

  /* MDIX TLV */
   unsigned int mdix;

  /* Interface Properties */
#define HAL_IF_INTERNAL          (1 << 0)
  unsigned int if_flags;

};

