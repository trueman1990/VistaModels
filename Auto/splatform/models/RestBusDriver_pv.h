
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
//* This file contains the PV class for RestBusDriver.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9.0
//* Generated on: Mar. 31, 2015 03:29:11 PM, (user: jon)
//*>


#pragma once

#include "RestBusDriver_model.h"

using namespace tlm;

//This class inherits from the RestBusDriver_pv_base class
class RestBusDriver_pv : public RestBusDriver_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(RestBusDriver_pv);
  RestBusDriver_pv(sc_core::sc_module_name module_name);       

 protected:
  ////////////////////////////////////////
  // signals callbacks
  //////////////////////////////////////// 
  void rxi_callback(); 
};

