
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
//* This file contains the PV class for supermodel.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2.1
//* Generated on: Sep. 16, 2016 01:43:41 PM, (user: markca)
//* Automatically merged on: Sep. 16, 2016 01:54:02 PM, (user: markca)
//*>


#pragma once

#include "supermodel_model.h"

using namespace tlm;

//This class inherits from the supermodel_pv_base class
class supermodel_pv : public supermodel_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(supermodel_pv);
  supermodel_pv(sc_core::sc_module_name module_name);  

  void thread();
  mb::mb_fifo<unsigned> mbFifo;

 protected:
  /////////////////////////////////////////
  // write callbacks of registers
  ////////////////////////////////////////// 
  void cb_write_CTL(unsigned int newValue);  

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool slave_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool slave_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size); 
  virtual void cb_transport_dbg_CTL(tlm::tlm_generic_payload& trans); 
  bool slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   
};

