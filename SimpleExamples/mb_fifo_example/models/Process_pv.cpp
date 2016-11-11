
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
//* This file contains the PV class for Process.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2.1
//* Generated on: Nov. 01, 2016 10:04:38 AM, (user: markca)
//* Automatically merged on: Nov. 11, 2016 10:36:57 AM, (user: markca)
//* Automatically merged on: Nov. 11, 2016 10:38:21 AM, (user: markca)
//* Automatically merged on: Nov. 11, 2016 02:27:34 PM, (user: markca)
//*>



#include "Process_pv.h"
#include <iostream>
#include <bitset>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
Process_pv::Process_pv(sc_module_name module_name) 
  : Process_pv_base(module_name) {

  fifo.set_minimal_delay(fifo_delay);
  fifo.nb_bound(fifo_bound);

  add_parameter_listener(this->name(), "enabled", this);

  SC_THREAD(thread);
}      

// Read callback for slave port.
// Returns true when successful.
bool Process_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  if(enabled) {
    return true;
  }
  return false;
}

// Write callback for slave port.
// Returns true when successful.
bool Process_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  if(enabled) {
    unsigned int value = (unsigned int) *data;
    cout << "                        " << "PRO @ " << sc_time_stamp() << " FIFO PUTTING " << hex << value << " : " << enabled << endl;
    fifo.put(value);
    return true;
  }
  return false;
} 


unsigned Process_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned Process_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool Process_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 

// in order to minimize merging conflicts, we recommend to add your functions after this comment

void Process_pv::thread() {
  unsigned int value;
  while(1) {
    value = fifo.peek();
    if(enabled) {
      cout << "                        " << "PRO @ " << sc_time_stamp() << " WRITING " << hex << value << endl;
      master_write(0x0, &value, 1);
    }
    fifo.get();
  }
}

void Process_pv::parameter_changed(const std::string& parameter,
                                   const std::string& old_value,
                                   const std::string& new_value) {
  if(parameter == "enabled") {
    int num;
    num = atoi(new_value.c_str());
    enabled = (num == 1);
    cout << "                        " << "PRO @ " << sc_time_stamp() << " " << parameter << " : " << enabled << endl;
  }
}
