
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
//* This file contains the PV class for sink.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.7.0
//* Generated on: Oct. 19, 2013 09:50:07 AM, (user: jon)
//*>



#include "sink_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
sink_pv::sink_pv(sc_module_name module_name) 
  : sink_pv_base(module_name) {
}    

// Read callback for a port.
// Returns true when successful.
bool sink_pv::a_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for a port.
// Returns true when successful.
bool sink_pv::a_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  DataType *d = (DataType *) data;

  cout << sc_time_stamp()<<", "<<name()<<" "<<d->id<<" = ("<<d->x<<","<<d->y<<")"<<endl;
  
  return true;
} 




unsigned sink_pv::a_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned sink_pv::a_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool sink_pv::a_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
