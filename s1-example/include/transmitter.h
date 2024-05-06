
#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void tx_send(uint8_t **buffer, ssize_t *len);

#endif