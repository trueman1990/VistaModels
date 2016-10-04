
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
//* This file contains the PV class for FAULT.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2.1
//* Generated on: Aug. 09, 2016 11:44:05 AM, (user: markca)
//*>


#pragma once

#include "FAULT_model.h"

using namespace tlm;

//This class inherits from the FAULT_pv_base class
class FAULT_pv : public FAULT_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(FAULT_pv);
  FAULT_pv(sc_core::sc_module_name module_name);   

 protected:
  void thread();       

  static void irqZeroThread(sc_core::sc_object* object_handle, double time, sc_core::sc_time_unit time_unit);
  static void my_cb(sc_core::sc_object* object_handle);

};

