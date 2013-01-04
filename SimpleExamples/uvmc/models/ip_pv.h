
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
//* This file contains the PV class for ip.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.5.0
//* Generated on: Jan. 03, 2013 12:10:26 PM, (user: markca)
//*>


#pragma once

#include "ip_model.h"

using namespace tlm;

#include <simple_initiator_socket.h>
using tlm_utils::simple_initiator_socket;

#include <uvmc.h>
using namespace uvmc;

//This class inherits from the ip_pv_base class
class ip_pv : public ip_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(ip_pv);
  ip_pv(sc_core::sc_module_name module_name);   

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool ip_slave_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned ip_slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool ip_slave_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned ip_slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size); 
  bool ip_slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   

public:
  simple_initiator_socket<ip_pv> master;
  sc_event done;
};

