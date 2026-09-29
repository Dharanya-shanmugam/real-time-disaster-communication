#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "hal_data.h"
#include "network/ether_link.h"
#include "priority_mailbox.h"


EXPORT INT usermain(void)
{
    ER err;
    disaster_message_t msg;


    tm_putstring((UB *)"\r\n");
    tm_putstring(
        (UB *)"========================================\r\n"
    );
    tm_putstring(
        (UB *)" Disaster Communication System\r\n"
    );
    tm_putstring(
        (UB *)" Ethernet + Priority Mailbox Test\r\n"
    );
    tm_putstring(
        (UB *)"========================================\r\n"
    );


    /* =====================================================
     * 1. Initialize Ethernet
     * ===================================================== */

    tm_putstring(
        (UB *)"Initializing Ethernet...\r\n"
    );

    err = ether_link_init();

    if (err != E_OK)
    {
        tm_printf(
            (UB *)"Ethernet initialization FAILED: %d\r\n",
            err
        );

        while (1)
        {
            tk_dly_tsk(1000);
        }
    }

    tm_putstring(
        (UB *)"Ethernet initialization SUCCESS\r\n"
    );


    /* =====================================================
     * 2. Initialize Priority Mailbox
     * ===================================================== */

    tm_putstring(
        (UB *)"Initializing Priority Mailbox...\r\n"
    );

    err = priority_mailbox_init();

    if (err != E_OK)
    {
        tm_printf(
            (UB *)"Priority Mailbox initialization FAILED: %d\r\n",
            err
        );

        while (1)
        {
            tk_dly_tsk(1000);
        }
    }

    tm_putstring(
        (UB *)"Priority Mailbox initialization SUCCESS\r\n"
    );


    /* =====================================================
     * 3. Start Ethernet RX Task
     * ===================================================== */

    tm_putstring(
        (UB *)"Starting Ethernet RX task...\r\n"
    );

    err = ether_link_start();

    if (err != E_OK)
    {
        tm_printf(
            (UB *)"Ethernet RX task start FAILED: %d\r\n",
            err
        );

        while (1)
        {
            tk_dly_tsk(1000);
        }
    }

    tm_putstring(
        (UB *)"Ethernet RX task started\r\n"
    );


    /* =====================================================
     * 4. Receive messages from Priority Mailbox
     * ===================================================== */

    tm_putstring(
        (UB *)"\r\n"
        "Waiting for priority messages...\r\n"
    );


    while (1)
    {
        err = priority_mailbox_receive(&msg);

        if (err == E_OK)
        {
            tm_printf(
                (UB *)"\r\n"
                "========================================\r\n"
                " MESSAGE RECEIVED\r\n"
                " Priority : %d\r\n"
                " Message  : %s\r\n"
                "========================================\r\n",
                msg.priority,
                msg.message
            );
        }
        else
        {
            tm_printf(
                (UB *)"Mailbox receive FAILED: %d\r\n",
                err
            );

            tk_dly_tsk(1000);
        }
    }


    return 0;
}
