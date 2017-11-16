/*!
 *   @brief M4 Utilities Implementation
 *   @author Gus Grubba <mavlink@grubba.com>
 */

#include "m4util.h"
#include <sstream>

//-----------------------------------------------------------------------------
static const unsigned char CRC8T[] = {
    0, 7, 14, 9, 28, 27, 18, 21, 56, 63, 54, 49, 36, 35, 42, 45, 112, 119, 126, 121, 108, 107,
    98, 101, 72, 79, 70, 65, 84, 83, 90, 93, 224, 231, 238, 233, 252, 251, 242, 245, 216, 223, 214, 209, 196,
    195, 202, 205, 144, 151, 158, 153, 140, 139, 130, 133, 168, 175, 166, 161, 180, 179, 186, 189, 199, 192,
    201, 206, 219, 220, 213, 210, 255, 248, 241, 246, 227, 228, 237, 234, 183, 176, 185, 190, 171, 172, 165,
    162, 143, 136, 129, 134, 147, 148, 157, 154, 39, 32, 41, 46, 59, 60, 53, 50, 31, 24, 17, 22, 3, 4, 13, 10,
    87, 80, 89, 94, 75, 76, 69, 66, 111, 104, 97, 102, 115, 116, 125, 122, 137, 142, 135, 128, 149, 146, 155,
    156, 177, 182, 191, 184, 173, 170, 163, 164, 249, 254, 247, 240, 229, 226, 235, 236, 193, 198, 207, 200,
    221, 218, 211, 212, 105, 110, 103, 96, 117, 114, 123, 124, 81, 86, 95, 88, 77, 74, 67, 68, 25, 30, 23, 16,
    5, 2, 11, 12, 33, 38, 47, 40, 61, 58, 51, 52, 78, 73, 64, 71, 82, 85, 92, 91, 118, 113, 120, 127, 106, 109,
    100, 99, 62, 57, 48, 55, 34, 37, 44, 43, 6, 1, 8, 15, 26, 29, 20, 19, 174, 169, 160, 167, 178, 181, 188,
    187, 150, 145, 152, 159, 138, 141, 132, 131, 222, 217, 208, 215, 194, 197, 204, 203, 230, 225, 232, 239,
    250, 253, 244, 243
};

//-----------------------------------------------------------------------------
/** x^8 + x^2 + x + 1 */
uint8_t
crc8(uint8_t* buffer, int len)
{
    uint8_t ret = 0;
    for(int i = 0; i < len; ++i) {
        ret = CRC8T[ret ^ buffer[i]];
    }
    return ret;
}

//-----------------------------------------------------------------------------
RxBindInfo::RxBindInfo()
{
    clear();
}

//-----------------------------------------------------------------------------
void
RxBindInfo::clear()
{
    mode        = 0;
    panId       = 0;
    nodeId      = 0;
    aNum        = 0;
    aBit        = 0;
    trNum       = 0;
    trBit       = 0;
    swNum       = 0;
    swBit       = 0;
    monitNum    = 0;
    monitBit    = 0;
    extraNum    = 0;
    extraBit    = 0;
    txAddr      = 0;
    achName.clear();
    trName.clear();
    swName.clear();
    monitName.clear();
    extraName.clear();
}


//-----------------------------------------------------------------------------
std::string
RxBindInfo::getName() {

    std::stringstream nodeSs;
    nodeSs << nodeId;

    switch (mode) {
        case TYPE_SR12S:
            return std::string("SR12S_") + nodeSs.str();
        case TYPE_SR12E:
            return std::string("SR12E_") + nodeSs.str();
        case TYPE_SR24S:
            return std::string("SR24S_") + nodeSs.str() + std::string(" v1.03");
        case TYPE_RX24:
            return std::string("RX24_") + nodeSs.str();
        case TYPE_SR19P:
            return std::string("SR19P_") + nodeSs.str();
        default:
            if (mode >= 105) {
                std::stringstream modeSs;
                modeSs << (float)mode / 100.0f;
                return std::string("SR24S_") + nodeSs.str() + std::string("v") + modeSs.str();
            } else {
                return nodeSs.str();
            }
    }
}


