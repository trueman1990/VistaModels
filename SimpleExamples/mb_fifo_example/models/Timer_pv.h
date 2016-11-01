
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
//* This file contains the PV class for Timer.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.2.1
//* Generated on: Nov. 01, 2016 11:08:42 AM, (user: markca)
//*>


#pragma once

#include "Timer_model.h"

using namespace tlm;

//This class inherit from the Timer_pv_base
class Timer_pv : public Timer_pv_base {

 public:
  // Constructor
  // Do not add parameters here.
  // In order to add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(Timer_pv);
  Timer_pv(sc_module_name module_name);

 /////////////////////////////////////////
 // write callbacks of registers
 /////////////////////////////////////////
 public: 
  virtual void cb_write_clear_irq(unsigned int newValue);
  virtual void cb_write_restart(unsigned int newValue); 
 

 ////////////////////////////////////////
 // target ports read callbacks
 //////////////////////////////////////// 
 public:
  // This function will be called whenever the port host is read
  virtual bool host_callback_read(config::uint64 address, unsigned char* data, unsigned size); 

 ////////////////////////////////////////
 // target ports write callbacks
 //////////////////////////////////////// 
 public: 
  // This function will be called whenever the port host is written
  virtual bool host_callback_write(config::uint64 address, unsigned char* data, unsigned size);

 private:
  void timer_func();
  
 private:
  unsigned int m_count;
  sc_event m_timer_event;
};
