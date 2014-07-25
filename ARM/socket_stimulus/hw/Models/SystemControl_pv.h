
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
//* This file contains the PV class for SystemControl.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.8.1RND2
//* Generated on: Jul. 25, 2014 02:42:44 PM, (user: markca)
//* Automatically merged on: Jul. 25, 2014 02:43:32 PM, (user: markca)
//* Automatically merged on: Jul. 25, 2014 03:56:52 PM, (user: markca)
//*>


#pragma once

#include "SystemControl_model.h"

using namespace tlm;

//This class inherits from the SystemControl_pv_base class
class SystemControl_pv : public SystemControl_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(SystemControl_pv);
  SystemControl_pv(sc_core::sc_module_name module_name); 

 protected:
  ////////////////////////////////////////
  // read callbacks of registers
  ////////////////////////////////////////// 
  unsigned int cb_read_STATE(); 
  
 protected:
  /////////////////////////////////////////
  // write callbacks of registers
  ////////////////////////////////////////// 
  void cb_write_STATE(unsigned int newValue); 

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool from_event_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned from_event_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size);
  bool from_bus_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned from_bus_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool from_event_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned from_event_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size);
  bool from_bus_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned from_bus_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size); 
  virtual void cb_transport_dbg_STATE(tlm::tlm_generic_payload& trans); 
  bool from_event_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);  
  bool from_bus_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   
};

