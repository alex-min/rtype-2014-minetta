#ifndef CRC_H
#define CRC_H

#define POLY 0x8408

class CRC
{
public :
    static unsigned short getCRC16(const void *data_r, unsigned short length);
};

#endif // CRC_H
