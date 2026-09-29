#ifndef PRIORITY_MAILBOX_H
#define PRIORITY_MAILBOX_H

#include <tk/tkernel.h>

/* Message priorities */
#define PRIORITY_FIRE       1
#define PRIORITY_MEDICAL    2
#define PRIORITY_ROAD       3
#define PRIORITY_NORMAL     4

/* Message structure */
typedef struct
{
    INT priority;
    char message[64];
} disaster_message_t;

/* Mailbox initialization */
ER priority_mailbox_init(void);

/* Send message to mailbox */
ER priority_mailbox_send(INT priority, const char *message);

/* Receive message from mailbox */
ER priority_mailbox_receive(disaster_message_t *msg);

#endif /* PRIORITY_MAILBOX_H */
