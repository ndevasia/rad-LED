#include "render.h"
#include <libserialport.h>

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
    
    const char * serialPort = "/dev/ttyACM0";
    sp_port * port;
    sp_return status = sp_get_port_by_name(serialPort, &port);
    if (sp_get_port_by_name(serialPort, &port) == SP_OK &&
        sp_open(port, SP_MODE_WRITE) == SP_OK)
    {
        sp_set_baudrate(port, 9600);

        constexpr unsigned ms = 1000;
        sp_blocking_write(port, msg, sizeof msg, ms);
    }
    else
    {
        fprintf(stderr, "Error opening: %s\n", serialPort);
    }
}
