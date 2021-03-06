/* 
   LICENCE TO BE APPENDED
*/

#ifndef _STACK_ITF_H_
#define _STACK_ITF_H_

#include <component.h>
#include <interface.h>
#include <network_stack/protocol.h>

using namespace Exokernel;

/**
 * Stack component state type.
 */
enum { 
  STACK_INIT_STATE = 0,   /**< The init state. */
  STACK_READY_STATE = 1,  /**< The state when stack component is up running. */
};

/**
 * The stack component type.
 */
typedef enum {
  exo_UDP = 0,    /**< The exo UDP stack type. */
  exo_TCP = 1,    /**< The exo TCP/UCP stack type. */
  LWIP = 2,       /**< The LWIP stack type. */
} stack_type_t;

/**
 * The supporting app type.
 */
typedef enum {
  TERA_CACHE = 0,    /**< The server-side app. */
  TRAFGEN    = 1,    /**< The client-side traffic generator. */
} app_type_t;

/**
 * The statck component init argument struct. 
 */
typedef struct {
  stack_type_t st;           /**< The stack type ID. */
  app_type_t app;            /**< The app type ID. */
  params_config_t params;    /**< The params config struct */
	params_config_t app_params;
} stack_arg_t;

/** 
 * Interface definition for IStack.
 * 
 */
class IStack : public Exokernel::Interface_base
{
public:
  DECLARE_INTERFACE_UUID(0x00352b0d,0x81a0,0x4061,0x90e1,0x8ba7,0x5412,0x03fd);

  /**
   * To receive a single packet from NIC component.
   *
   * @param p Pointer to a packet buffer.
   * @param pktlen The length of received packet.
   * @param device The NIC identifier.
   * @param queue The RX queue where the packets are received.
   * @return The return status.
   */
  virtual status_t receive_packet(pkt_buffer_t p, size_t pktlen, unsigned device, unsigned queue) = 0;

  /**
   * To send an ARP requst.
   *
   * @param ipdst_addr Pointer to the destination IP address.
   * @param device The NIC identifier.
   */
  virtual void arp_output(ip_addr_t *ipdst_addr, unsigned device) = 0;

  /**
   * To send a UDP packet. This function supports IP fragments. The entire payload will be 
   * guaranteed to sent out when the function returns.
   *
   * @param vaddr UDP payload virtual address.
   * @param paddr UDP payload physical address.
   * @param udp_payload_len The size of UDP payload.
   * @param recycle The flag to indicate whether the sent out packet memory needs to be recycled.
   * @param allocator_id The allocator which allocates the packet memory.
   * @param device The NIC identifier.
   * @param queue The TX queue where the packets are sent.
   */
  virtual void udp_send_pkt(uint8_t *vaddr, addr_t paddr, unsigned udp_payload_len,
                            bool recycle, unsigned allocator_id, unsigned device, unsigned queue) = 0;

  /**
   * To get an ARP entry in arp table.
   *
   * @param ip_addr Pointer to the IP address.
   * @param device The NIC identifier.
   * @return The index in arp table which contains the arp record for this IP.
   */
  virtual int get_entry_in_arp_table(ip_addr_t* ip_addr, unsigned device) = 0;

  /**
   * To bind IP and port to UDP stack.
   *
   * @param ipaddr Pointer to the IP address.
   * @param port The UDP port.
   * @param device The NIC identifier.
   */
  virtual void udp_bind(ip_addr_t *ipaddr, uint16_t port, unsigned device) = 0;
  
};

#endif
