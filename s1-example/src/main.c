
#include <stdio.h>
#include <sys/types.h>

#include <coder.h>
#include <transmitter.h>


int main() {

    uint8_t *buffer = "hello";
    ssize_t len = 6;

    UEContextReleaseRequest_coder(&buffer, &len);
    tx_send(&buffer, &len);

    return 0;

}