
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
//* This file contains the PV class for drive.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.8.0
//* Generated on: Sep. 23, 2014 09:34:54 AM, (user: jon)
//*>


#pragma once
#include "drive_model.h"

using namespace tlm;

//This class inherits from the drive_pv_base class
class drive_pv : public drive_pv_base {

 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(drive_pv);
  drive_pv(sc_module_name module_name);

 protected:
  // SC_THREAD created for CPU
  void thread();    
   

 ////////////////////////////////////////
 // signals callbacks
 //////////////////////////////////////// 
 protected: 
  void irq_callback(); 
};


