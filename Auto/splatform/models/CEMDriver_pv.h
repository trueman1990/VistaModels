
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
//* This file contains the PV class for CEMDriver.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.1beta2
//* Generated on: Apr. 28, 2015 09:59:38 AM, (user: jon)
//* Automatically merged on: May. 07, 2015 01:44:01 PM, (user: markca)
//* Automatically merged on: May. 07, 2015 03:27:52 PM, (user: markca)
//*>


#pragma once

#include "CEMDriver_model.h"

using namespace tlm;

//This class inherits from the CEMDriver_pv_base class
class CEMDriver_pv : public CEMDriver_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(CEMDriver_pv);
  CEMDriver_pv(sc_core::sc_module_name module_name);       

  void body_thread();
  void prop_thread();
  void chassis_thread();

 protected:
  ////////////////////////////////////////
  // signals callbacks
  //////////////////////////////////////// 
  void propRXI_callback();
  void chassisRXI_callback();
  void bodyRXI_callback(); 

 private:
  struct DataType {
    unsigned int id;
    unsigned int s;
    unsigned char d[9];

    DataType(unsigned int n_id, unsigned int n_s, unsigned char *n_d) :
      id(n_id),
      s(n_s)
    {
      memcpy(d, n_d, 9);
    }
  };

  mb::mb_fifo<DataType*> bodyff;
  mb::mb_fifo<DataType*> propff;
  mb::mb_fifo<DataType*> chassisff;
};

