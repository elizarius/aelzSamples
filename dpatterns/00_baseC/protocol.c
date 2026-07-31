/*
    Write a decoder for the given protocol. The protocol is operating
    on top of TCP/IP.

    A packet has fixed header and one or many data fields.
    ID: Running sequence number
    Flags: 
        If the first bit is set FOO is used
        If the second bit is set BAR is used
        Other bits are undefined.

    Total length: Total length of the packet (header + data) in bytes
    Timestamp: Timestamp in seconds since 1970-01-01 00:00:00 UTC

     0                   1                   2                   3   
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | ID            | Flags         | Total length                  |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Time stamp                                                    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Data length                   | Data                          |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               \
    \                                                               \
    |                                                               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Data length                   | Data                          |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               \
    \                                                               \
    |                                                               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                                               |
                          ...
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct Data {
    uint16_t length;
    uint8_t *buffer;
    struct Data *next;
} Data_t;

typedef struct protocol_s {
    uint8_t id;
    uint8_t flags;
    uint16_t length;
    uint32_t timestamp;
    Data_t *data;
} protocol_t;

protocol_t *decode(uint8_t *packet)
{
    protocol_t *proto = malloc(sizeof(protocol_t));
    proto->id = packet[0];
    proto->flags = packet[1];
    proto->length = (packet[2] << 8) | packet[3];

    proto->timestamp = (packet[4] << 24) | (packet[5] << 16) |
                      (packet[6] << 8) | packet[7];

    proto->data = malloc(sizeof(Data_t));
    proto->data->length = (packet[8] << 8) | packet[9];
    proto->data->buffer = malloc(proto->data->length);
    if (proto->data->buffer != NULL)
        for (int i = 0; i < proto->data->length; i++)
            proto->data->buffer[i] = packet[10 + i];
    proto->data->next = NULL;

    return proto;
}

void free_protocol(protocol_t *proto)
{
    if (proto == NULL)
        return;
    if (proto->data != NULL) {
        if (proto->data->buffer != NULL)
            free(proto->data->buffer);
        free(proto->data);
    }
    free(proto);
}

int main(void)
{
    /* Create a sample packet */
    uint8_t packet[] = {
        0x01,           /* ID */
        0x03,           /* Flags (bits 0 and 1 set) */
        0x00, 0x14,     /* Length: 20 bytes */
        0x00, 0x00, 0x00, 0x00,  /* Timestamp: 0 */
        0x00, 0x05,     /* Data length: 5 bytes */
        'H', 'e', 'l', 'l', 'o'  /* Data: "Hello" */
    };

    protocol_t *proto = decode(packet);

    printf("Decoded packet:\n");
    printf("ID: %d\n", proto->id);
    printf("Flags: 0x%02x\n", proto->flags);
    printf("Length: %d\n", proto->length);
    printf("Timestamp: %u\n", proto->timestamp);
    printf("Data length: %d\n", proto->data->length);
    printf("Data: ");
    for (int i = 0; i < proto->data->length; i++)
        printf("%c", proto->data->buffer[i]);
    printf("\n");

    free_protocol(proto);
    return 0;
}

