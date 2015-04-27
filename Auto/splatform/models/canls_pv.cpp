
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
//* This file contains the PV class for canls.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9.0
//* Generated on: Apr. 01, 2015 08:18:19 AM, (user: jon)
//* Automatically merged on: Apr. 17, 2015 09:10:31 AM, (user: jon)
//*>



#include "canls_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
canls_pv::canls_pv(sc_module_name module_name) 
  : canls_pv_base(module_name), iff(4) {
  SC_THREAD(thread);
  SC_THREAD(thread_c);
  SC_THREAD(thread_r);
  SC_THREAD(thread_b);
  SC_THREAD(thread_ap);
}    

// Read callback for r_tx port.
// Returns true when successful.
bool canls_pv::r_tx_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}


// Read callback for ap_tx port.
// Returns true when successful.
bool canls_pv::ap_tx_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}


// Read callback for c_tx port.
// Returns true when successful.
bool canls_pv::c_tx_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}


// Read callback for b_tx port.
// Returns true when successful.
bool canls_pv::b_tx_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for r_tx port.
// Returns true when successful.
bool canls_pv::r_tx_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  mb::mb_token_ptr tokenptr = get_current_token();
  DataType *d = new DataType(address, size, tokenptr);
  pq.push(d);
  iff.put(1);
  return true;
} 

// Write callback for ap_tx port.
// Returns true when successful.
bool canls_pv::ap_tx_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  mb::mb_token_ptr tokenptr = get_current_token();
  DataType *d = new DataType(address, size, tokenptr);
  pq.push(d);
  iff.put(1);
  return true;
} 

// Write callback for c_tx port.
// Returns true when successful.
bool canls_pv::c_tx_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  DataType *d = new DataType(address, size, get_current_token());
  pq.push(d);
  iff.put(1);
  return true;
} 

// Write callback for b_tx port.
// Returns true when successful.
bool canls_pv::b_tx_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  mb::mb_token_ptr tokenptr = get_current_token();
  DataType *d = new DataType(address, size, tokenptr);
  pq.push(d);
  iff.put(1);
  return true;
} 

unsigned canls_pv::r_tx_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned canls_pv::r_tx_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool canls_pv::r_tx_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

unsigned canls_pv::ap_tx_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned canls_pv::ap_tx_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool canls_pv::ap_tx_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

unsigned canls_pv::c_tx_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned canls_pv::c_tx_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool canls_pv::c_tx_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}





unsigned canls_pv::b_tx_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned canls_pv::b_tx_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool canls_pv::b_tx_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
void canls_pv::thread() {
  DataType *d;
  while(iff.get()) {
    wait(generic_clock);// One clock delay for the start bit.
    d = pq.top();	// Take the priority message at the end of the start bit.
    pq.pop();
    // ReceiveCount used to know when data pointer can be deleted. Must be set to number of receivers.
    d->m_tokenptr->setField("ReceiveCount", 4);
    set_current_token(d->m_tokenptr);
    cff.put(d);
    rff.put(d);
    bff.put(d);
    apff.put(d);
  }
}

void canls_pv::thread_c() {
  DataType *d;
  while(d = cff.get()) {
    c_rx_write(d->m_ident, d->m_data, d->m_size);
  }
}

void canls_pv::thread_r() {
  DataType *d;
  while(d = rff.get()) {
    r_rx_write(d->m_ident, d->m_data, d->m_size);
  }
}

void canls_pv::thread_b() {
  DataType *d;
  while(d = bff.get()) {
    b_rx_write(d->m_ident, d->m_data, d->m_size);
  }
}

void canls_pv::thread_ap() {
  DataType *d;
  while(d = apff.get()) {
    ap_rx_write(d->m_ident, d->m_data, d->m_size);
  }
}
