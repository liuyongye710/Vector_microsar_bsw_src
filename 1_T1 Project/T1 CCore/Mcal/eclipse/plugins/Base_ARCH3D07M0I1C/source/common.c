/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007PT
* DESCRIPTION : common code
* HISTORY     : Initial version
* @file     common.c
* @version  1.0
* @date     2023 - 01 - 01
* @brief    Initial version.
*
*****************************************************************************/

#include "common.h"

void cc_memcpy(uint8_t *dest, const uint8_t *src, const uint32_t bytes)
{
    uint32_t bytes_temp;
    uint8_t * dest_temp = NULL;
    uint8_t const * src_temp = NULL;

    bytes_temp = bytes;
    dest_temp = (uint8_t *)dest;
    src_temp = (uint8_t const *)src;

    while (bytes_temp > 0u)
    {
        *dest_temp = *src_temp;
        bytes_temp--;
        if (0u == bytes_temp)
        {
            break;
        }
        dest_temp++;
        src_temp++;
    }
}

void cc_memset(uint8_t *dest, const uint8_t val, const uint32_t bytes)
{
    uint32_t bytes_temp;
    uint8_t  * dest_temp = NULL;

    dest_temp = dest;
    bytes_temp = bytes;

    while (bytes_temp > 0u)
    {
        *dest_temp = val;
        bytes_temp--;
        if (0u == bytes_temp)
        {
            break;
        }
        dest_temp++;
    }
}

uint8_t cc_memcmp(const uint8_t *src1, const uint8_t *src2, uint32_t len)
{
    uint8_t const *p1 = NULL;
    uint8_t const *p2 = NULL;
    uint32_t len_temp = 0u;

    len_temp = len;
    p1 = src1;
    p2 = src2;

    do
    {
        if (*p1 != *p2)
        {
            return 1;
        }
        p1++;
        p2++;
        len_temp--;
    } while (len_temp != 0u);

    return 0;
}

uint32_t cc_strlen(const uint8_t * s)
{
    const uint8_t *sc;
    uint32_t temp = 0;
    for (sc = s; *sc != (uint8_t)'\0'; ++sc)
    {
    }
    temp = (uint32_t)(sc - s);
    return temp;
}

void delay(volatile uint32_t x)
{
    uint32_t x_temp = x;
    while (x_temp != 0u)
    {
        x_temp--;
    }
}

void delay_ms(uint32_t ms)
{
    uint32_t i;
    uint32_t temp = ms;
    do
    {
        temp--;
        i = 6400;
        do
        {
           i--;
        }while (i != 0u);
    }while (temp != 0u);
}

