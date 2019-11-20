//
// Created by annika on 07.11.19.
//

#include "unity.h"
#include "test/header_replacements/EmbeddedUtilities/MockBitManipulation.h"
#include "elasticnodemiddleware/elasticNodeMiddleware_internal.h"
#include "elasticnodemiddleware/fpgaPins.h"
#include "elasticnodemiddleware/xmem.h"

uint8_t port_fpga_program_b;
uint8_t ddr_fpga_program_b;

uint8_t port_fpga_power_sram;
uint8_t ddr_fpga_power_sram;
uint8_t port_fpga_power_aux;
uint8_t ddr_fpga_power_aux;
uint8_t port_fpga_power_io;
uint8_t ddr_fpga_power_io;
uint8_t port_fpga_power_int;
uint8_t ddr_fpga_power_int;

uint8_t ddr_fpga_cclk;

uint8_t port_fpga_init_b;
uint8_t ddr_fpga_init_b;

uint8_t port_fpga_done;
uint8_t ddr_fpga_done;

uint8_t* DDR_FPGA_PROGRAM_B = &ddr_fpga_program_b;
uint8_t* PORT_FPGA_PROGRAM_B = &port_fpga_program_b;

uint8_t* DDR_FPGA_POWER_SRAM =&ddr_fpga_power_sram;
uint8_t* PORT_FPGA_POWER_SRAM =&port_fpga_power_sram;
uint8_t* DDR_FPGA_POWER_AUX = &ddr_fpga_power_aux;
uint8_t* PORT_FPGA_POWER_AUX = &port_fpga_power_aux;
uint8_t* DDR_FPGA_POWER_IO = &ddr_fpga_power_io;
uint8_t* PORT_FPGA_POWER_IO = &port_fpga_power_io;
uint8_t* DDR_FPGA_POWER_INT = &ddr_fpga_power_int;
uint8_t* PORT_FPGA_POWER_INT = &port_fpga_power_int;

uint8_t* DDR_FPGA_CCLK = &ddr_fpga_cclk;

uint8_t memoryarea[2000];
const uint8_t* externalMockMemory = &memoryarea;

extern volatile uint8_t *reset_fpga;

void initialise_mockRegister(void) {
    DDR_FPGA_PROGRAM_B = &ddr_fpga_program_b;
    PORT_FPGA_PROGRAM_B = &port_fpga_program_b;

    DDR_FPGA_POWER_SRAM =&ddr_fpga_power_sram;
    PORT_FPGA_POWER_SRAM =&port_fpga_power_sram;
    DDR_FPGA_POWER_AUX = &ddr_fpga_power_aux;
    PORT_FPGA_POWER_AUX = &port_fpga_power_aux;
    DDR_FPGA_POWER_IO = &ddr_fpga_power_io;
    PORT_FPGA_POWER_IO = &port_fpga_power_io;
    DDR_FPGA_POWER_INT = &ddr_fpga_power_int;
    PORT_FPGA_POWER_INT = &port_fpga_power_int;

    DDR_FPGA_CCLK = &ddr_fpga_cclk;
}

void test_elasticnode_fpgaPowerOn_internal(void) {
    initialise_mockRegister();

    //set pin high of program B
    BitManipulation_setBit_Expect(&port_fpga_program_b, (1 << P_FPGA_PROGRAM_B));
    BitManipulation_setBit_Expect(&ddr_fpga_program_b, (1 << P_FPGA_PROGRAM_B));

    BitManipulation_setBit_Expect(&ddr_fpga_power_sram, (1 << P_FPGA_POWER_SRAM));
    BitManipulation_clearBit_Expect(&port_fpga_power_sram, (1 << P_FPGA_POWER_SRAM));
    BitManipulation_setBit_Expect(&ddr_fpga_power_aux, (1 << P_FPGA_POWER_AUX));
    BitManipulation_clearBit_Expect(&port_fpga_power_aux, (1 << P_FPGA_POWER_AUX));
    BitManipulation_setBit_Expect(&ddr_fpga_power_io, (1 << P_FPGA_POWER_IO));
    BitManipulation_clearBit_Expect(&port_fpga_power_io, (1 << P_FPGA_POWER_IO));
    BitManipulation_setBit_Expect(&ddr_fpga_power_int, (1 << P_FPGA_POWER_INT));
    BitManipulation_clearBit_Expect(&port_fpga_power_int, (1 << P_FPGA_POWER_INT));

    //single control --> register do not exist

    //disable interface
    BitManipulation_clearBit_Expect(&ddr_fpga_cclk, (1 << P_FPGA_CCLK));

    BitManipulation_setBit_Expect(&port_fpga_program_b, (1 << P_FPGA_PROGRAM_B));

    elasticnode_fpgaPowerOn_internal();
}

void test_elasticnode_fpgaPowerOff_internal(void) {
    initialise_mockRegister();

    BitManipulation_clearBit_Expect(&port_fpga_program_b, ( 1 << P_FPGA_PROGRAM_B));

    //enable interface
    BitManipulation_setBit_Expect(&ddr_fpga_cclk, (1 << P_FPGA_CCLK));

    BitManipulation_setBit_Expect(&ddr_fpga_power_sram, ( 1 << P_FPGA_POWER_SRAM));
    BitManipulation_setBit_Expect(&port_fpga_power_sram, ( 1 << P_FPGA_POWER_SRAM));
    BitManipulation_setBit_Expect(&ddr_fpga_power_aux, ( 1 << P_FPGA_POWER_AUX));
    BitManipulation_setBit_Expect(&port_fpga_power_aux, ( 1 << P_FPGA_POWER_AUX));
    BitManipulation_setBit_Expect(&ddr_fpga_power_io, ( 1 << P_FPGA_POWER_IO));
    BitManipulation_setBit_Expect(&port_fpga_power_io, ( 1 << P_FPGA_POWER_IO));
    BitManipulation_setBit_Expect(&ddr_fpga_power_int, ( 1 << P_FPGA_POWER_INT));
    BitManipulation_setBit_Expect(&port_fpga_power_int, ( 1 << P_FPGA_POWER_INT));

    BitManipulation_setBit_Expect(&port_fpga_program_b, ( 1 << P_FPGA_PROGRAM_B));
    BitManipulation_clearBit_Expect(&ddr_fpga_program_b, (1 << P_FPGA_PROGRAM_B));

    elasticnode_fpgaPowerOff_internal();
}

void test_elasticnode_setFpgaSoftReset_internal(void) {
    initialise_mockRegister();
    elasticnode_setFpgaSoftReset_internal();
    TEST_ASSERT_EQUAL_UINT8((*reset_fpga), 0x1);
}

void test_elasticnode_clearFpgaSoftReset_internal(void) {
    initialise_mockRegister();
    elasticnode_clearFpgaSoftReset_internal();
    TEST_ASSERT_EQUAL_UINT8((*reset_fpga), 0x0);
}