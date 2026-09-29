#include "priority_mailbox.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <string.h>


/* =========================================================
 * Configuration
 * ========================================================= */

#define PRIORITY_MSG_POOL_SIZE    10


/* =========================================================
 * Priority message structure
 *
 * T_MSG_PRI contains:
 *      T_MSG msgque;
 *      PRI   msgpri;
 *
 * The T_MSG header must be at the beginning of the
 * message packet passed to tk_snd_mbx().
 * ========================================================= */

typedef struct
{
    T_MSG_PRI msg_header;
    disaster_message_t data;
    INT used;
} priority_message_packet_t;


/* =========================================================
 * Mailbox
 * ========================================================= */

static ID g_priority_mbx;


/* Message pool */
static priority_message_packet_t
    g_message_pool[PRIORITY_MSG_POOL_SIZE];


/* =========================================================
 * Initialize Priority Mailbox
 * ========================================================= */

ER priority_mailbox_init(void)
{
    T_CMBX cmbx;

    /* Message priority order */
    cmbx.mbxatr = TA_TPRI | TA_MPRI;

    /* Create mailbox */
    g_priority_mbx = tk_cre_mbx(&cmbx);

    if (g_priority_mbx < E_OK)
    {
        tm_printf(
            (UB *)"Priority mailbox creation FAILED: %d\r\n",
            g_priority_mbx
        );

        return (ER)g_priority_mbx;
    }

    /* Initialize message pool */
    for (INT i = 0; i < PRIORITY_MSG_POOL_SIZE; i++)
    {
        g_message_pool[i].used = 0;
        g_message_pool[i].msg_header.msgpri = 0;
        g_message_pool[i].data.priority = 0;
        g_message_pool[i].data.message[0] = '\0';
    }

    tm_printf(
        (UB *)"Priority mailbox created: ID = %d\r\n",
        g_priority_mbx
    );

    return E_OK;
}


/* =========================================================
 * Send message to Priority Mailbox
 * ========================================================= */

ER priority_mailbox_send(
    INT priority,
    const char *message
)
{
    INT index = -1;
    priority_message_packet_t *packet;

    /* Check priority */
    if ((priority < PRIORITY_FIRE) ||
        (priority > PRIORITY_NORMAL))
    {
        return E_PAR;
    }

    /* Check message pointer */
    if (message == NULL)
    {
        return E_PAR;
    }

    /* Find free packet */
    for (INT i = 0; i < PRIORITY_MSG_POOL_SIZE; i++)
    {
        if (g_message_pool[i].used == 0)
        {
            index = i;
            break;
        }
    }

    if (index < 0)
    {
        tm_putstring(
            (UB *)"Priority message pool FULL\r\n"
        );

        return E_NOMEM;
    }

    packet = &g_message_pool[index];

    /* Mark packet as used */
    packet->used = 1;

    /* Set message priority */
    packet->msg_header.msgpri = (PRI)priority;

    /* Store application data */
    packet->data.priority = priority;

    strncpy(
        packet->data.message,
        message,
        sizeof(packet->data.message) - 1
    );

    packet->data.message[
        sizeof(packet->data.message) - 1
    ] = '\0';


    tm_printf(
        (UB *)"Sending priority message: P=%d, %s\r\n",
        priority,
        packet->data.message
    );


    /*
     * T_MSG_PRI begins with T_MSG.
     *
     * Pass the address of msgque to tk_snd_mbx().
     */
    return tk_snd_mbx(
        g_priority_mbx,
        &packet->msg_header.msgque
    );
}


/* =========================================================
 * Receive message from Priority Mailbox
 * ========================================================= */

ER priority_mailbox_receive(
    disaster_message_t *msg
)
{
    T_MSG *mail_msg;
    priority_message_packet_t *packet;
    ER err;

    /* Validate output pointer */
    if (msg == NULL)
    {
        return E_PAR;
    }

    /* Wait indefinitely for a message */
    err = tk_rcv_mbx(
        g_priority_mbx,
        &mail_msg,
        TMO_FEVR
    );

    if (err != E_OK)
    {
        return err;
    }


    /*
     * T_MSG is the first member of T_MSG_PRI,
     * and T_MSG_PRI is the first member of our packet.
     *
     * Therefore the received T_MSG address is also
     * the beginning of priority_message_packet_t.
     */
    packet =
        (priority_message_packet_t *)mail_msg;


    /* Copy application message */
    msg->priority = packet->data.priority;

    strncpy(
        msg->message,
        packet->data.message,
        sizeof(msg->message) - 1
    );

    msg->message[
        sizeof(msg->message) - 1
    ] = '\0';


    /* Release packet */
    packet->used = 0;


    return E_OK;
}
