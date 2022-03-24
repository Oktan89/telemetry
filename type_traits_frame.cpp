#include "type_traits_frame.h"

    uint32_t swap_uint32(uint32_t in)
    {
        uint32_t swapped = ((in >> 24) & 0xff) |
                ((in << 8) & 0xff0000) |
                ((in >> 8) & 0xff00) |
                ((in << 24) & 0xff000000);
        return(swapped);
    }

    uint32_lsb_t uint32_to_lsb(uint32_t in) 
    {
        return((uint32_lsb_t)swap_uint32(in));
    }

    uint32_t lsb_to_uint32(uint32_lsb_t in) {
        return(swap_uint32((uint32_t)in));
    }