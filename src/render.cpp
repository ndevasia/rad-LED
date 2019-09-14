#include "render.h"
#include <unistd.h>
#include <fcntl.h>

void sendBytes(uint8_t * byte, int n)
{
    int fd = open("/dev/ttyACM0", O_WRONLY);
    if (fd == -1)
    {
        perror("Couldn't open arduino serial port\n");
    }

    printf("Writing %d bytes to serial\n", n);
    write(fd, byte, n);

    close(fd);
}

void renderFrame(const Frame & frame)
{
    uint8_t msg[frame.size() * sizeof frame[0]];

    uint8_t * p = msg;
    for (const auto pixel : frame)
    {
        p[0] = pixel.r;
        p[1] = pixel.g;
        p[2] = pixel.b;

        p += 3;
    }

    sendBytes(msg, sizeof msg);
}
