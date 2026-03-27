/* SPDX-License-Identifier: GPL-2.0 */
/* MauNux Kernel-Only Intel PRO/1000 Ethernet Driver Header */ 
/*

#ifndef _MAUNUX_E1000_H_
#define _MAUNUX_E1000_H_

#include <linux/stddef.h>
#include <linux/module.h>
#include <linux/types.h>
#include <asm/byteorder.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/string.h>
#include <linux/pagemap.h>
#include <linux/dma-mapping.h>
#include <linux/bitops.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/capability.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <net/pkt_sched.h>
#include <linux/list.h>
#include <linux/reboot.h>
#include <net/checksum.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/if_vlan.h>

/* Base Address Registers */
#define MAUNUX_BAR_0 0
#define MAUNUX_BAR_1 1

/* Macro para declarar dispositivos Intel PRO/1000 */
#define MAUNUX_E1000_DEVICE(device_id) { \
    PCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id) \
}

struct maunux_e1000_adapter;  /* forward declaration */

#include "maunux_e1000_hw.h"  /* Hardware-specific estructuras y defines */

/* Máximo número de interrupciones */
#define MAUNUX_MAX_INTR 10

/* Contador para reset polling */
#define MAUNUX_CHECK_RESET_COUNT 50

/* TX/RX Descriptor defines */
#define MAUNUX_DEFAULT_TXD 256
#define MAUNUX_MAX_TXD     256
#define MAUNUX_MIN_TXD      48
#define MAUNUX_DEFAULT_RXD 256
#define MAUNUX_MAX_RXD     256
#define MAUNUX_MIN_RXD      48

/* Tamaño máximo de VLAN */
#define MAUNUX_MAX_ETH_VLAN_SIZE 1522

/* Rx buffer sizes soportados */
#define MAUNUX_RXBUF_128   128
#define MAUNUX_RXBUF_256   256
#define MAUNUX_RXBUF_512   512
#define MAUNUX_RXBUF_1024  1024
#define MAUNUX_RXBUF_2048  2048
#define MAUNUX_RXBUF_4096  4096
#define MAUNUX_RXBUF_8192  8192
#define MAUNUX_RXBUF_16384 16384

/* SmartSpeed */
#define MAUNUX_SMARTSPEED_DOWNSHIFT 3
#define MAUNUX_SMARTSPEED_MAX       15

/* Flow Control Watermarks */
#define MAUNUX_FC_HIGH_DIFF 0x1638
#define MAUNUX_FC_LOW_DIFF  0x1640
#define MAUNUX_FC_PAUSE_TIME 0xFFFF

/* TX queue wake threshold */
#define MAUNUX_TX_QUEUE_WAKE 16
/* RX buffer write bundle */
#define MAUNUX_RX_BUFFER_WRITE 16  /* must be power of 2 */

/* EEPROM flags */
#define MAUNUX_EEPROM_APME 0x0400

#ifndef MAUNUX_MASTER_SLAVE
#define MAUNUX_MASTER_SLAVE maunux_ms_hw_default
#endif

#define MAUNUX_MNG_VLAN_NONE 0xFFFF

/* Estructura TX buffer */
struct maunux_tx_buffer {
    struct sk_buff *skb;
    dma_addr_t dma;
    unsigned long time_stamp;
    u16 length;
    u16 next_to_watch;
    bool mapped_as_page;
    unsigned short segs;
    unsigned int bytecount;
};

/* RX function pointers y estructuras */
struct maunux_rx_ops {
    bool (*clean_rx)(struct maunux_e1000_adapter *adapter,
                     struct maunux_rx_ring *rx_ring,
                     int *work_done, int work_to_do);
    void (*alloc_rx_buf)(struct maunux_e1000_adapter *adapter,
                         struct maunux_rx_ring *rx_ring,
                         int cleaned_count);
};

#endif /* _MAUNUX_E1000_H_ */
