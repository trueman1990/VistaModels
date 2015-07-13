
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
//* This file contains the PV class for FPGA_GPIO_OUT_custom.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.1beta1
//* Generated on: Mar. 14, 2015 10:00:00 AM, (user: markca)
//* Automatically merged on: Jun. 05, 2015 03:47:24 PM, (user: markca)
//* Automatically merged on: Jul. 10, 2015 02:58:18 PM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 10:41:37 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:33:33 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:43:31 AM, (user: markca)
//*>


#pragma once

#include "FPGA_GPIO_OUT_custom_model.h"

using namespace tlm;

//This class inherits from the FPGA_GPIO_OUT_custom_pv_base class
class FPGA_GPIO_OUT_custom_pv : public FPGA_GPIO_OUT_custom_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(FPGA_GPIO_OUT_custom_pv);
  FPGA_GPIO_OUT_custom_pv(sc_core::sc_module_name module_name);        

 protected:
  ////////////////////////////////////////
  // signals callbacks
  //////////////////////////////////////// 
  void slave_callback(); 
};

