
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
//*>


#pragma once

#include "Process_model.h"

using namespace tlm;

//This class inherits from the Process_pv_base class
class Process_pv : public Process_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(Process_pv);
  Process_pv(sc_core::sc_module_name module_name);    

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
  bool slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   


 private:
  void thread();
};

