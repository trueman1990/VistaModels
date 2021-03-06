
/**************************************************************/
/*                                                            */
/*      Copyright Mentor Graphics Corporation 2006 - 2012     */
/*                  All Rights Reserved                       */
/*                                                            */
/*       THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY      */
/*         INFORMATION WHICH IS THE PROPERTY OF MENTOR        */
/*         GRAPHICS CORPORATION OR ITS LICENSORS AND IS       */
/*                 SUBJECT TO LICENSE TERMS.                  */
/*                                                            */
/**************************************************************/

//*<
//* Generated By Model Builder, Mentor Graphics Computer Systems, Inc.
//*
//* This file contains the PV class for TestBench.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.1beta2
//* Generated on: May. 18, 2015 08:48:31 AM, (user: markca)
//*>



#include "TestBench_pv.h"
#include <iostream>

#include "../../../splatform/models/MemoryMap.h"

#include <stdint.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
TestBench_pv::TestBench_pv(sc_module_name module_name) 
  : TestBench_pv_base(module_name) {

   SC_THREAD(thread);
}    

void TestBench_pv::thread() {
  uint32_t speed;
  uint32_t revs;
  speed = 0;
  revs = 0;
  uint8_t interrupt_signal = 1;
  while(1) {  
    wait(10, SC_MS);
    RXIDENT = SPEEDID;
    RXDATA = (speed / 100) % 140;
    irq_write(0, interrupt_signal);
    wait(e1);

    wait(10, SC_MS);
    RXIDENT = RPMID;
    RXDATA = revs % 8000;
    irq_write(0, interrupt_signal);
    wait(e1);

    speed += 1;
    revs += 2;
  }
}

void TestBench_pv::cb_write_ACK(unsigned int newValue) {
  e1.notify();
}

void TestBench_pv::cb_transport_dbg_ACK(tlm::tlm_generic_payload& trans)
{
}

// Read callback for slave port.
// Returns true when successful.
bool TestBench_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for slave port.
// Returns true when successful.
bool TestBench_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
} 




unsigned TestBench_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned TestBench_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool TestBench_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
