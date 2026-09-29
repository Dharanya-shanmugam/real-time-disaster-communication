#include "ether_link.h"
#include "../priority_mailbox.h"
#include <tm/tmonitor.h>
#include "hal_data.h"

#define ETHER_RX_BUFFER_SIZE 1536U

static uint8_t g_rx_buffer[ETHER_RX_BUFFER_SIZE]
__attribute__((aligned(32)));


/* =========================================================
 * Ethernet Initialization
 * ========================================================= */

ER ether_link_init(void)
{
    fsp_err_t err;

    tm_putstring((UB *)"\r\n");
    tm_putstring((UB *)"========================================\r\n");
    tm_putstring((UB *)" Ethernet Link Layer\r\n");
    tm_putstring((UB *)"========================================\r\n");
    tm_putstring((UB *)"Opening Ethernet RMAC...\r\n");

    err = R_RMAC_Open(
        &g_ether0_ctrl,
        &g_ether0_cfg
    );

    if (err != FSP_SUCCESS)
    {
        tm_printf(
            (UB *)"R_RMAC_Open FAILED: %d\r\n",
            err
        );

        return E_SYS;
    }

    tm_putstring(
        (UB *)"R_RMAC_Open SUCCESS\r\n"
    );

    return E_OK;
}


/* =========================================================
 * Ethernet Frame Processing
 * ========================================================= */

static void process_ethernet_frame(
    uint8_t *buffer,
    uint32_t length
)
{
    uint8_t *payload;
    uint32_t payload_length;

    /* Minimum Ethernet frame */

    if (length < 14U)
    {
        return;
    }


    /* -----------------------------------------------------
     * Check Destination MAC
     *
     * Our RA8P1 board MAC:
     * 00:11:22:33:44:55
     *
     * Ignore all other traffic such as:
     * ARP, IPv6, broadcast, multicast, etc.
     * ----------------------------------------------------- */

    if (!(buffer[0] == 0x00 &&
          buffer[1] == 0x11 &&
          buffer[2] == 0x22 &&
          buffer[3] == 0x33 &&
          buffer[4] == 0x44 &&
          buffer[5] == 0x55))
    {
        return;
    }


    /* -----------------------------------------------------
     * Check EtherType
     *
     * 0x0800 = IPv4
     * ----------------------------------------------------- */

    if (!(buffer[12] == 0x08 &&
          buffer[13] == 0x00))
    {
        return;
    }


    /* -----------------------------------------------------
     * Get Ethernet payload
     * ----------------------------------------------------- */

    payload = &buffer[14];
    payload_length = length - 14U;


    tm_printf(
        (UB *)"\r\nReceived Disaster Ethernet frame: %lu bytes\r\n",
        (unsigned long)length
    );


    tm_printf(
        (UB *)"Destination MAC: "
        "%02X:%02X:%02X:%02X:%02X:%02X\r\n",
        buffer[0],
        buffer[1],
        buffer[2],
        buffer[3],
        buffer[4],
        buffer[5]
    );


    tm_printf(
        (UB *)"Source MAC: "
        "%02X:%02X:%02X:%02X:%02X:%02X\r\n",
        buffer[6],
        buffer[7],
        buffer[8],
        buffer[9],
        buffer[10],
        buffer[11]
    );


    tm_printf(
        (UB *)"EtherType: 0x%02X%02X\r\n",
        buffer[12],
        buffer[13]
    );


    tm_printf(
        (UB *)"Payload length: %lu\r\n",
        (unsigned long)payload_length
    );


    /* =====================================================
     * FIRE
     *
     * Priority = 1
     * ===================================================== */

    if (payload_length >= 4U &&
        payload[0] == 'F' &&
        payload[1] == 'I' &&
        payload[2] == 'R' &&
        payload[3] == 'E')
    {
        tm_putstring(
            (UB *)"FIRE detected!\r\n"
        );

        if (priority_mailbox_send(
                PRIORITY_FIRE,
                "FIRE ALERT") == E_OK)
        {
            tm_putstring(
                (UB *)"FIRE -> Priority Mailbox\r\n"
            );
        }
        else
        {
            tm_putstring(
                (UB *)"FIRE -> Priority Mailbox FAILED\r\n"
            );
        }
    }


    /* =====================================================
     * MEDICAL
     *
     * Priority = 2
     * ===================================================== */

    else if (payload_length >= 7U &&
             payload[0] == 'M' &&
             payload[1] == 'E' &&
             payload[2] == 'D' &&
             payload[3] == 'I' &&
             payload[4] == 'C' &&
             payload[5] == 'A' &&
             payload[6] == 'L')
    {
        tm_putstring(
            (UB *)"MEDICAL detected!\r\n"
        );

        if (priority_mailbox_send(
                PRIORITY_MEDICAL,
                "MEDICAL EMERGENCY") == E_OK)
        {
            tm_putstring(
                (UB *)"MEDICAL -> Priority Mailbox\r\n"
            );
        }
        else
        {
            tm_putstring(
                (UB *)"MEDICAL -> Priority Mailbox FAILED\r\n"
            );
        }
    }


    /* =====================================================
     * ROAD
     *
     * Priority = 3
     * ===================================================== */

    else if (payload_length >= 4U &&
             payload[0] == 'R' &&
             payload[1] == 'O' &&
             payload[2] == 'A' &&
             payload[3] == 'D')
    {
        tm_putstring(
            (UB *)"ROAD detected!\r\n"
        );

        if (priority_mailbox_send(
                PRIORITY_ROAD,
                "ROAD BLOCK") == E_OK)
        {
            tm_putstring(
                (UB *)"ROAD -> Priority Mailbox\r\n"
            );
        }
        else
        {
            tm_putstring(
                (UB *)"ROAD -> Priority Mailbox FAILED\r\n"
            );
        }
    }


    /* =====================================================
     * NORMAL
     *
     * Priority = 4
     * ===================================================== */

    else if (payload_length >= 6U &&
             payload[0] == 'N' &&
             payload[1] == 'O' &&
             payload[2] == 'R' &&
             payload[3] == 'M' &&
             payload[4] == 'A' &&
             payload[5] == 'L')
    {
        tm_putstring(
            (UB *)"NORMAL detected!\r\n"
        );

        if (priority_mailbox_send(
                PRIORITY_NORMAL,
                "NORMAL MESSAGE") == E_OK)
        {
            tm_putstring(
                (UB *)"NORMAL -> Priority Mailbox\r\n"
            );
        }
        else
        {
            tm_putstring(
                (UB *)"NORMAL -> Priority Mailbox FAILED\r\n"
            );
        }
    }


    /* =====================================================
     * Unknown Disaster Message
     *
     * This will ONLY execute for packets addressed to our
     * board with EtherType 0x0800 but whose payload is not
     * FIRE / MEDICAL / ROAD / NORMAL.
     * ===================================================== */

    else
    {
        tm_putstring(
            (UB *)"Unknown Disaster Payload\r\n"
        );
    }
}


/* =========================================================
 * Ethernet RX Task
 * ========================================================= */

void ether_link_rx_task(
    INT stacd,
    void *exinf
)
{
    fsp_err_t err;
    uint32_t rx_length;

    (void)stacd;
    (void)exinf;


    tm_putstring(
        (UB *)"Ethernet RX task started\r\n"
    );

    tm_putstring(
        (UB *)"Processing Ethernet link...\r\n"
    );


    /* -----------------------------------------------------
     * Initial Link Processing
     * ----------------------------------------------------- */

    err = R_RMAC_LinkProcess(
        &g_ether0_ctrl
    );

    tm_printf(
        (UB *)"R_RMAC_LinkProcess result: %d\r\n",
        err
    );


    if (err == FSP_SUCCESS)
    {
        tm_putstring(
            (UB *)"Ethernet LINK UP\r\n"
        );
    }
    else
    {
        tm_putstring(
            (UB *)"Ethernet LINK PROCESS FAILED\r\n"
        );
    }


    tm_putstring(
        (UB *)"Ethernet RX ready\r\n"
    );


    /* -----------------------------------------------------
     * Continuous Receive Loop
     * ----------------------------------------------------- */

    while (1)
    {
        rx_length = 0U;

        err = R_RMAC_Read(
            &g_ether0_ctrl,
            g_rx_buffer,
            &rx_length
        );


        /* -------------------------------------------------
         * Ethernet Frame Received
         * ------------------------------------------------- */

        if (err == FSP_SUCCESS)
        {
            process_ethernet_frame(
                g_rx_buffer,
                rx_length
            );
        }


        /* -------------------------------------------------
         * No Ethernet Data
         * ------------------------------------------------- */

        else if (
            err == FSP_ERR_ETHER_ERROR_NO_DATA
        )
        {
            tk_dly_tsk(10);
        }


        /* -------------------------------------------------
         * Ethernet Link Down
         * ------------------------------------------------- */

        else if (
            err == FSP_ERR_ETHER_ERROR_LINK
        )
        {
            tm_putstring(
                (UB *)"Ethernet LINK DOWN\r\n"
            );


            err = R_RMAC_LinkProcess(
                &g_ether0_ctrl
            );


            if (err == FSP_SUCCESS)
            {
                tm_putstring(
                    (UB *)"Ethernet LINK UP\r\n"
                );
            }


            tk_dly_tsk(500);
        }


        /* -------------------------------------------------
         * Other RMAC Error
         * ------------------------------------------------- */

        else
        {
            tm_printf(
                (UB *)"R_RMAC_Read error: %d\r\n",
                err
            );

            tk_dly_tsk(100);
        }
    }
}


/* =========================================================
 * Start Ethernet RX Task
 * ========================================================= */

ER ether_link_start(void)
{
    T_CTSK ctsk;
    ID tskid;
    ER err;


    ctsk.tskatr = TA_HLNG | TA_RNG0;
    ctsk.task = ether_link_rx_task;
    ctsk.exinf = NULL;
    ctsk.itskpri = 10;
    ctsk.stksz = 2048;


    /* -----------------------------------------------------
     * Create RX Task
     * ----------------------------------------------------- */

    tskid = tk_cre_tsk(
        &ctsk
    );


    if (tskid < E_OK)
    {
        tm_printf(
            (UB *)"Ethernet RX task creation FAILED: %d\r\n",
            tskid
        );

        return (ER)tskid;
    }


    /* -----------------------------------------------------
     * Start RX Task
     * ----------------------------------------------------- */

    err = tk_sta_tsk(
        tskid,
        0
    );


    if (err != E_OK)
    {
        tm_printf(
            (UB *)"Ethernet RX task start FAILED: %d\r\n",
            err
        );

        return err;
    }


    tm_putstring(
        (UB *)"Ethernet RX task started successfully\r\n"
    );


    return E_OK;
}
