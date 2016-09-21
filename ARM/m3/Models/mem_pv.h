
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
//* This file contains the PV class for mem.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.5.0
//* Generated on: Jan. 03, 2013 02:43:57 PM, (user: jon)
//* Automatically merged on: Nov. 24, 2015 07:25:35 AM, (user: jon)
//*>


#pragma once

#include "mem_model.h"
#include "model_builder.h"

using namespace tlm;

//This class inherits from the mem_pv_base class
class mem_pv : public mem_pv_base, public mb::models::memory_if::Invalidator {

 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(mem_pv);
  mem_pv(sc_module_name module_name); 

public: 
  virtual void slave_callback(tlm::tlm_base_protocol_types::tlm_payload_type& trans, sc_core::sc_time& t);
  virtual unsigned slave_callback_dbg(tlm::tlm_base_protocol_types::tlm_payload_type& trans);
  virtual bool slave_get_direct_memory_ptr_callback(tlm::tlm_base_protocol_types::tlm_payload_type& trans,
                                                        tlm::tlm_dmi& dmiData);

public:
  virtual void do_invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range);

 private:
  mb::models::memory_if m_memory_if;
};
