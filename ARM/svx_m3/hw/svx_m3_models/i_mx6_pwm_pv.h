
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
//* This file contains the PV class for i_mx6_pwm.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9Beta1
//* Generated on: Jun. 05, 2014 12:03:36 PM, (user: monas)
//* Automatically merged on: Jun. 09, 2014 11:58:43 AM, (user: monas)
//*>


#pragma once

#include "i_mx6_pwm_model.h"

using namespace tlm;

//This class inherits from the i_mx6_pwm_pv_base class
class i_mx6_pwm_pv : public i_mx6_pwm_pv_base, public mb::sysc::Counter::OverflowAction {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(i_mx6_pwm_pv);
  i_mx6_pwm_pv(sc_core::sc_module_name module_name); 

 protected:
  ////////////////////////////////////////
  // read callbacks of registers
  ////////////////////////////////////////// 
  unsigned int cb_read_PWMSR_FIFOAV();
  unsigned int cb_read_PWMSAR();
  unsigned int cb_read_PWMCNR(); 
  
 protected:
  /////////////////////////////////////////
  // write callbacks of registers
  ////////////////////////////////////////// 
  void cb_write_PWMCR(unsigned int newValue);
  void cb_write_PWMSR(unsigned int newValue);
  void cb_write_PWMIR(unsigned int newValue);
  void cb_write_PWMSAR(unsigned int newValue);
  void cb_write_PWMPR(unsigned int newValue); 

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool SLAVE_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned SLAVE_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool SLAVE_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned SLAVE_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size); 
  virtual void cb_transport_dbg_PWMCR(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMSR(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMSR_FIFOAV(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMIR(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMSAR(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMPR(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_PWMCNR(tlm::tlm_generic_payload& trans); 
  bool SLAVE_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);  

 protected:
  ////////////////////////////////////////
  // signals callbacks
  //////////////////////////////////////// 
  void RST_callback(); 

 private:
 class Counter_comperator : public mb::mb_module, public mb::sysc::Counter::OverflowAction {

 public:
  Counter_comperator(sc_core::sc_module_name module_name, i_mx6_pwm_pv* pwm_pv, mb::sysc::CounterWithComparators* counter)
    : mb::mb_module(module_name), m_pwm_pv(pwm_pv),
      m_counter(counter) {
  }

 public:
  i_mx6_pwm_pv* m_pwm_pv;
  void counter_overflow();

 private:
  mb::sysc::CounterWithComparators* m_counter;
 };


private:
  mb::sysc::CounterWithComparators m_counter;
  mb::sysc::CounterWithComparators::Comparator m_comparator;
  void counter_overflow();


private:

  bool m_EN;
  unsigned m_prescalar;
  unsigned m_frozen_count_value;
  unsigned m_current_sample_value;   //Sample value being currently used
  unsigned m_sample_repeat;
  mb::utl::RingContainer<unsigned short> m_sample_fifo;

//General variables and functions
  void PWM_software_reset(unsigned int & value);
  void PWM_init();  //Initialize internal vriables and counter
  void PWM_enable(); //Enable model
  void PWM_disable(); //Disable model
  bool PWM_check_mode();  //Check operating mode paramter and whether timer is enabled in it
  bool PWM_set_period();  //Set counter period - Return false if clock is off
  void PWM_update_interrupt();   //Update interrupt based on satatus and mask register values
  bool PWM_get_sample();   //Get Sample from FIFO & set comperator. It returns True if succeed to get a new sample value from FIFO, else it returns False


  void parameter_changed(const std::string& old_value, const std::string& new_value);
  
};
