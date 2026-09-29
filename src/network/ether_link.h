#ifndef ETHER_LINK_H
#define ETHER_LINK_H

#include <tk/tkernel.h>

/* Ethernet initialization */
ER ether_link_init(void);

/* Ethernet receive task */
void ether_link_rx_task(INT stacd, void *exinf);

/* Start Ethernet receive task */
ER ether_link_start(void);

#endif /* ETHER_LINK_H */
