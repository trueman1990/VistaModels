
/**************************************************************/
/*                                                            */
/*      Copyright Mentor Graphics Corporation 2006 - 2015     */
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
//* This file contains the PV class for FPGA.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2.1
//* Generated on: Aug. 04, 2016 06:05:57 PM, (user: markca)
//*>



#include "FPGA_pv.h"
#include <iostream>
#include <bitset>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
FPGA_pv::FPGA_pv(sc_module_name module_name) 
  : FPGA_pv_base(module_name) {

  SC_THREAD(thread);
}   

void FPGA_pv::thread() {
  while(1) {
    mbFifo.peek(); // block/wait until start bit is written

    unsigned int v = 0x12345678;
    unsigned char *d = (unsigned char*) &v;

    cout << name() << " @ " << sc_time_stamp() << " going to send " << hex << v << " to " << ADR << endl;
    master_write(ADR, d, 4);
    cout << name() << " @ " << sc_time_stamp() << " completed" << endl;

    irq.write(true);

    mbFifo.get();  // release Fifo, Done.
  }
}


/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// Write callback for CTL register.
// The newValue has been already assigned to the CTL register.
void FPGA_pv::cb_write_CTL(unsigned int newValue) {
  std::string binary = std::bitset<32>(newValue).to_string(); //to binary
  cout << name() << " @ " << sc_time_stamp() << " value = " << binary << endl;

  if (CHECK_BIT(newValue, 0)) {
    mbFifo.put(1);
  } else {
    irq.write(false);
  }

}
    

// Read callback for slave port.
// Returns true when successful.
bool FPGA_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for slave port.
// Returns true when successful.
bool FPGA_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
} 




unsigned FPGA_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned FPGA_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool FPGA_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
void FPGA_pv::cb_transport_dbg_CTL(tlm::tlm_generic_payload& trans) {}

// in order to minimize merging conflicts, we recommend to add your functions after this comment
