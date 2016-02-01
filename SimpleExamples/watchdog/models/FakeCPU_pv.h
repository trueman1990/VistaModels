
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
//* This file contains the PV class for FakeCPU.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2alpha1
//* Generated on: Feb. 01, 2016 09:46:12 AM, (user: markca)
//* Automatically merged on: Feb. 01, 2016 10:07:19 AM, (user: markca)
//*>


#pragma once
#include "FakeCPU_model.h"

using namespace tlm;

//This class inherits from the FakeCPU_pv_base class
class FakeCPU_pv : public FakeCPU_pv_base {

 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(FakeCPU_pv);
  FakeCPU_pv(sc_module_name module_name);

 protected:
  // SC_THREAD created for CPU
  void thread();    
   

 ////////////////////////////////////////
 // signals callbacks
 //////////////////////////////////////// 
 protected: 
  void int_source_callback(); 
};


