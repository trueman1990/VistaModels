
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
//* This file contains the PV class for AXI_APB.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.7.1
//* Generated on: Feb. 21, 2014 07:28:59 AM, (user: markca)
//*>



#include "AXI_APB_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
AXI_APB_pv::AXI_APB_pv(sc_module_name module_name) 
  : AXI_APB_pv_base(module_name) {
}    

// Read callback for slave port.
// Returns true when successful.
bool AXI_APB_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  return master_read(address, data, size);
}

// Write callback for slave port.
// Returns true when successful.
bool AXI_APB_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  return master_write(address, data, size);
} 




unsigned AXI_APB_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned AXI_APB_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool AXI_APB_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 