#ifndef IRQ_H
#define IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mcu32_memory_map.h>
#include <epic.h>
#include <csr.h>
#include <scr1_csr_encoding.h>

#include <gpio.h>
#include <timer32.h>

#include "hal.h"


void trap_handler();

void EnableInterrupts();

void DisableInterrupts();


#ifdef __cplusplus
}
#endif

#endif