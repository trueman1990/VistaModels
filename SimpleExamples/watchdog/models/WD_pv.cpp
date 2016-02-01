
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
//* This file contains the PV class for WD.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2alpha1
//* Generated on: Feb. 01, 2016 08:36:23 AM, (user: markca)
//* Automatically merged on: Feb. 01, 2016 10:07:20 AM, (user: markca)
//*>



#include "WD_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
WD_pv::WD_pv(sc_module_name module_name) 
  : WD_pv_base(module_name)
{
  irq.initialize(false);
  wd_state = IDLE;

  SC_METHOD(wd_timer);
  sensitive << wd_timer_start;
  SC_METHOD(wd_timer_interrupt);
  sensitive << wd_timer_expired;
}   

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

// Read callback for slave port.
// Returns true when successful.
bool WD_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for slave port.
// Returns true when successful.
bool WD_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {

  if(*data == 0x0) {
    // Stop Watchdog
    cout << name() << " @ " << sc_time_stamp() << " : Stopping watchdog" << endl;
    wd_state = IDLE;
    wd_timer_expired.cancel();
  }
  else if(*data == 0x1) {
    // Reset and start Watchdog
    cout << name() << " @ " << sc_time_stamp() << " : Starting watchdog" << endl;
    irq.write(false);
    wd_timer_expired.cancel();
    wd_state = ENABLED;
    wd_timer_start.notify();
  }
  
  return true;
} 


unsigned WD_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned WD_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool WD_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}


void WD_pv::wd_timer () {
  if(wd_state == ENABLED) {
    wd_timer_started = sc_simulation_time();
    wd_timer_expired.notify(1000, SC_MS); // 1 second time out
  }
}

void WD_pv::wd_timer_interrupt() {
  if(wd_state == ENABLED) {
    cout << name() << " @ " << sc_time_stamp() << " : Timer expired, triggering interrupt" << endl;
    irq.write(true);
  }
}
