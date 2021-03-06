
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



#include "i_mx6_pwm_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;using namespace std;


//Debug Directive
//#define MB_DEBUG_PWM 1

#define PWMSR_FWE 1 << 6
#define PWMSR_CMP 1 << 5
#define PWMSR_ROV 1 << 4
#define PWMSR_FE  1 << 3
#define PWMSR_MASK 0x00000078
#define PWMIR_MASK 0x00000007
#define POUTC_SET_AT_ROLLOVER 0
#define POUTC_SET_AT_MATCH 1

# if defined(MB_DEBUG_PWM) && MB_DEBUG_PWM > 0
#define DPRINTF(fmt, ...) \
  do { cout << "@" << sc_time_stamp() << " "; printf(": " fmt , ## __VA_ARGS__); } while (0)  
#else
#define DPRINTF(fmt, ...) do {} while(0)
# endif 

#define FIFO_DEPTH 4

//constructor
i_mx6_pwm_pv::i_mx6_pwm_pv(sc_module_name module_name) 
  : i_mx6_pwm_pv_base(module_name), m_counter("cnt"),
    m_comparator(&m_counter, "comparator"), m_sample_fifo(FIFO_DEPTH) {

    m_counter.set_overflow_action(this);
    m_comparator.set_action(new Counter_comperator("Comparator", this, &m_counter));
    m_sample_fifo.setAutoExpand(false);
    PWM_init();
} 

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// read event on one of the registers as defined in the Model Builder form.
// These functions are called before the read callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

// Read callback for PWMSR_FIFOAV register.
// The value that this function returns, will be returned to the initiator port that requested its value.
unsigned int i_mx6_pwm_pv::cb_read_PWMSR_FIFOAV() {
  unsigned data_in_fifo_size = m_sample_fifo.size();
  DPRINTF("%s: Reading FIFO size of %d. \n", this->name(), data_in_fifo_size);
  return data_in_fifo_size;
}
 

// Read callback for PWMSAR register.
// The value that this function returns, will be returned to the initiator port that requested its value.
unsigned int i_mx6_pwm_pv::cb_read_PWMSAR() {
 //Returns value of current sample being used 

//The register can only be read when the PWM is enabled
  if(!m_EN) {
    mb::sysc::issue_warning(" warning! (PWM:3) Cannot read PWMSAR register while PWM is disabled." ,this-> name());
    return 0;
  }
  return (m_current_sample_value & 0x0000FFFF);

}
 

// Read callback for PWMCNR register.
// The value that this function returns, will be returned to the initiator port that requested its value.
unsigned int i_mx6_pwm_pv::cb_read_PWMCNR() {
  //Returns the current counter value
  unsigned count_value;
  bool is_running = m_counter.is_running();
  if(is_running){
 	count_value = m_counter.get_value();
  }
  else {
 	count_value = m_frozen_count_value;
  }
  DPRINTF("%s: Reading current count value of 0x %x. \n", this->name(), count_value);
  return count_value;
}
  

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

// Write callback for PWMCR register.
// The newValue has been already assigned to the PWMCR register.
void i_mx6_pwm_pv::cb_write_PWMCR(unsigned int newValue) {
//Check SWR 
  if(PWMCR_SWR != 0) PWM_software_reset(newValue);
//Check EN
  bool is_enabled = ((newValue & 0x1) != 0);  //EN
  unsigned prescalar = (newValue >> 4) & 0xFFF;  //PRESCALAR

  if(!m_EN && is_enabled) {
    PWM_enable();
  }
  else if(m_EN && !is_enabled) {
    PWM_disable();
  }
  else if (m_EN && (m_prescalar != (prescalar))) {
    m_prescalar = prescalar;
    if(!PWM_set_period()) PWM_disable();
  }
  
//Bits 31:28 are RAZ
//SWR, bit 3, is selfClearing so assure it is zero
  PWMCR = newValue & 0x0FFFFFF7; 
}
 

// Write callback for PWMSR register.
// The newValue has been already assigned to the PWMSR register.
void i_mx6_pwm_pv::cb_write_PWMSR(unsigned int newValue) {
  unsigned mask = newValue & PWMSR_MASK;
  PWMSR = (PWMSR & PWMSR_MASK) & (~(mask));
  PWM_update_interrupt(); 
}
 

// Write callback for PWMIR register.
// The newValue has been already assigned to the PWMIR register.
void i_mx6_pwm_pv::cb_write_PWMIR(unsigned int newValue) {
  PWMIR &= PWMIR_MASK;
  PWM_update_interrupt();   
}
 

// Write callback for PWMSAR register.
// The newValue has been already assigned to the PWMSAR register.
void i_mx6_pwm_pv::cb_write_PWMSAR(unsigned int newValue) {
  unsigned short sample; 
  DPRINTF("%s: Sample register is written. New value is 0x %x. \n", this->name(), newValue);
  if(!m_sample_fifo.full()) {
    if(PWMCR_HCTR){
      sample = (unsigned short)(newValue >> 16);
      DPRINTF("%s: Performing Half word swap. Sample value is 0x %x. \n", this->name(), sample);
    }
    else {
      sample = (unsigned short)(newValue & 0x0000FFFF);
    }

    if(PWMCR_BCTR){
      sample = (sample >> 8) | ((sample << 8) & 0xFF00);
      DPRINTF("%s: Performing Byte swap. Sample value is 0x %x. \n", this->name(), sample);
    }

    DPRINTF("%s: Pushing new sample of value 0x %x to sample FIFO. \n", this->name(), sample);
    m_sample_fifo.write(&sample, 1);
  }
  else {
    DPRINTF("%s: Trying to write to a full buffer. \n", this->name());
    mb::sysc::issue_warning(" Warning! (PWM:4) The sample data FIFO is full. New written sample is discarded." ,this-> name());
    //Update status register
    PWMSR |= PWMSR_FWE;
  }
}
 

// Write callback for PWMPR register.
// The newValue has been already assigned to the PWMPR register.
void i_mx6_pwm_pv::cb_write_PWMPR(unsigned int newValue) {
    bool is_running = m_counter.is_running();
    if(is_running) m_counter.stop();
    PWMPR &= 0x0000FFFF;
    unsigned limit = (PWMPR == 0xFFFF) ? 0xFFFF : PWMPR + 1;
    DPRINTF("%s: Setting counter limit to %d. \n", this->name(), limit);
    m_counter.set_limit(limit);  
    m_counter.set_value(0);
    if(is_running){
      DPRINTF("%s: Restarting counter. \n", this->name());
      m_counter.start();   
    }
}
  

// Read callback for SLAVE port.
// Returns true when successful.
bool i_mx6_pwm_pv::SLAVE_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for SLAVE port.
// Returns true when successful.
bool i_mx6_pwm_pv::SLAVE_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
} 




unsigned i_mx6_pwm_pv::SLAVE_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned i_mx6_pwm_pv::SLAVE_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool i_mx6_pwm_pv::SLAVE_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
void i_mx6_pwm_pv::cb_transport_dbg_PWMCR(tlm::tlm_generic_payload& trans) {}
void i_mx6_pwm_pv::cb_transport_dbg_PWMSR(tlm::tlm_generic_payload& trans) {}
void i_mx6_pwm_pv::cb_transport_dbg_PWMSR_FIFOAV(tlm::tlm_generic_payload& trans) {
  if (trans.is_read()) {
    unsigned size = trans.get_data_length() < (sizeof(unsigned int)) ?
      trans.get_data_length() : sizeof(unsigned int);
    unsigned int value = cb_read_PWMSR_FIFOAV();
    memcpy(trans.get_data_ptr(), &value, size);
  }
}
void i_mx6_pwm_pv::cb_transport_dbg_PWMIR(tlm::tlm_generic_payload& trans) {}
void i_mx6_pwm_pv::cb_transport_dbg_PWMSAR(tlm::tlm_generic_payload& trans) {
  if (trans.is_read()) {
    unsigned size = trans.get_data_length() < (sizeof(unsigned int)) ?
      trans.get_data_length() : sizeof(unsigned int);
    unsigned int value = cb_read_PWMSAR();
    memcpy(trans.get_data_ptr(), &value, size);
  }
}
void i_mx6_pwm_pv::cb_transport_dbg_PWMPR(tlm::tlm_generic_payload& trans) {}
void i_mx6_pwm_pv::cb_transport_dbg_PWMCNR(tlm::tlm_generic_payload& trans) {
  if (trans.is_read()) {
    unsigned size = trans.get_data_length() < (sizeof(unsigned int)) ?
      trans.get_data_length() : sizeof(unsigned int);
    unsigned int value = cb_read_PWMCNR();
    memcpy(trans.get_data_ptr(), &value, size);
  }
}

// callback for any change in signal: RST of type: sc_in<bool>
void i_mx6_pwm_pv::RST_callback() {
if(RST == 1) {
    DPRINTF("%s: Hardware reset signal is raised. \n", this->name());
    reset_model();
    PWM_init();
  }
}



/******************************************** Core Functionality Implementation *********************************************/


void i_mx6_pwm_pv::PWM_init(){

  DPRINTF("%s: PWM Initialize. \n", this->name());
  //Initialize internal vriables and counter
  m_EN = false;
  m_prescalar = 0;
  m_frozen_count_value = 0;
  m_current_sample_value = 0;

  //Counter and match timer settings
  m_counter.stop();

  unsigned limit = (PWMPR == 0xFFFF) ? 0xFFFF: PWMPR + 1; 
  m_counter.set_limit(limit);
  m_counter.set_increment(1);
  m_counter.set_value(0);

//Flush FIFO
  m_sample_fifo.clear();
  m_comparator.set_value(0xFFFFFFFF);   
  m_sample_repeat = 0;
}

void i_mx6_pwm_pv::PWM_software_reset(unsigned int & value){

  DPRINTF("%s: PWM software reset. \n", this->name());
//retain values of EN, ENMOD, STOPEN, DBGEN, WAITEN
//Bits 0, 22, 23, 24, 25
  unsigned retain_value = PWMCR & 0x03C00001;

  reset_model();
  value = retain_value;

  PWM_init();
}

void i_mx6_pwm_pv::PWM_enable(){
 //Enable model
  DPRINTF("%s: PWM  model is enabled. \n", this->name());
  //Check if it can be run
  if(!PWM_check_mode()) return;
  //Adjust period
  m_prescalar = PWMCR_PRESCALAR;
  if(!PWM_set_period()) return;
  //Start counters
  m_EN = true;
  //Adjust sample
  if(m_sample_repeat == 0){
    if(PWM_get_sample()){
      m_sample_repeat = 1 << PWMCR_REPEAT;
      DPRINTF("%s: Sample repeat is set to %d. \n", this->name(), m_sample_repeat);
    }
  }

  //Adjust output

   //Set output pin according to POUTC configuration
   if(PWMCR_POUTC == POUTC_SET_AT_ROLLOVER) {
        DPRINTF("%s: Set PWM output. \n", this->name());
        PWMO.write(1);
   }
   else if(PWMCR_POUTC == POUTC_SET_AT_MATCH){
        DPRINTF("%s: Clear PWM output. \n", this->name());
        PWMO.write(0);
   }

  m_counter.start();
}

void i_mx6_pwm_pv::PWM_disable(){
 //Disable model
  DPRINTF("%s: PWM model is disabled. \n", this->name());
  m_EN = false;
 //Stop counter   
  m_frozen_count_value = m_counter.get_value();
  m_counter.stop();
}


bool i_mx6_pwm_pv::PWM_check_mode(){
  //Check operating mode paramter and whether timer is enabled in it
//Check operating mode paramter and whether timer is enabled in it
  switch(Mode){
  case 0: //Normal 
    return true;
  case 1: //Stop Mode
    return (PWMCR_STOPEN != 0);
  case 2: //Wait Mode
    return PWMCR_WAITEN;
  case 3: //Debug Mode
    return PWMCR_DBGEN;     
  case 4: //DOZE Mode
    return PWMCR_DOZEN;     
  default: 
        mb::sysc::issue_warning(" Warning! (PWM:2) The Mode parameter setting is not valid. The PWM will operate in the default normal mode." ,this-> name());    
    return true;
  }
}

bool i_mx6_pwm_pv::PWM_set_period(){
  //Set counter period - Return false if clock is off
sc_core::sc_time eff_period;
  switch (PWMCR_CLKSRC){
  case 0: //clock is off
    mb::sysc::issue_warning(" Warning! (PWM:1) The CLKSRC is set to off. No valid clock source is selected. The counter will not start." ,this-> name());
    return false;
  case 1: //peripheral clock
    DPRINTF("%s: Peripheral clock is selcted. \n", this->name());
    eff_period = Periph_clock;
    break;
  case 2: //High-frequency reference clock   
    DPRINTF("%s: High-frequency clock is selcted. \n", this->name());
    eff_period = High_freq_clock;
    break;
  case 3: //Low-frequency reference clock   
    DPRINTF("%s: Low-frequency clock is selcted. \n", this->name());
    eff_period = Low_freq_clock;
    break;
  default : return false;
  }
  eff_period = eff_period * (m_prescalar + 1);  
  DPRINTF("%s: Prescalar value is %d. \n", this->name(), m_prescalar);
  m_counter.set_period(eff_period);
  return true;
}



bool i_mx6_pwm_pv::PWM_get_sample(){
  //Get Sample from FIFO & set comperator
  bool success;
  if(m_sample_fifo.empty()){
    mb::sysc::issue_warning(" Warning! (PWM:5) The counter is running while FIFO is empty. No sample value is being compared." ,this-> name());    
    m_comparator.set_value(0xFFFFFFFF);  
    success = false;
  }
  else{
    unsigned short sample;
    m_sample_fifo.read(&sample, 1);
    DPRINTF("%s: Setting comparator to sample value of 0x %x read from FIFO. \n", this->name(), sample);
    m_current_sample_value = sample;
    m_comparator.set_value(sample); 
    success = true;
  }
  if(m_sample_fifo.room() > PWMCR_FWM) {
        DPRINTF("%s: Setting FIFO empty flag. \n", this->name());
        PWMSR |= PWMSR_FE;
        PWM_update_interrupt();
  }
  return success;
}

void i_mx6_pwm_pv::PWM_update_interrupt(){
  if(m_EN) {
    //Update interrupt based on satatus and mask register values
    if((PWMIR & (PWMSR >> 3)) != 0){
      DPRINTF("%s: Asserting Interrupt. \n", this->name());
      IRQ.write(1);
    }
    else{
      DPRINTF("%s: Deasserting Interrupt. \n", this->name());
      IRQ.write(0);
    }
  }
}

void i_mx6_pwm_pv::counter_overflow() {
   DPRINTF("%s: Counter Overflow \n", this->name());
   m_counter.stop();

   //Set Rollover event
   DPRINTF("%s: Setting Rollover flag. \n", this->name());
   PWMSR |= PWMSR_ROV;
   PWM_update_interrupt();

   //Set output pin according to POUTC configuration
   if(PWMCR_POUTC == POUTC_SET_AT_ROLLOVER) {
        DPRINTF("%s: Set PWM output. \n", this->name());
        PWMO.write(1);
   }
   else if(PWMCR_POUTC == POUTC_SET_AT_MATCH){
        DPRINTF("%s: Clear PWM output. \n", this->name());
        PWMO.write(0);
   }
  
   //Adjust Sample
   --m_sample_repeat; 
   if(m_sample_repeat == 0){
    if(PWM_get_sample()){
      m_sample_repeat = 1 << PWMCR_REPEAT;
      DPRINTF("%s: Sample repeat is set to %d. \n", this->name(), m_sample_repeat);
    }
   }

   //Restart Counter
   DPRINTF("%s: Restarting counter. \n", this->name());
   m_counter.set_value(0);
   m_counter.start();

}


void i_mx6_pwm_pv::Counter_comperator::counter_overflow() {
   DPRINTF("%s: Compare Match \n", this->name());
   DPRINTF("%s: Setting Compare flag. \n", this->name());
   m_pwm_pv->PWMSR |= PWMSR_CMP;
   m_pwm_pv->PWM_update_interrupt();  


   //Set output pin according to POUTC configuration
   if(m_pwm_pv->PWMCR_POUTC == POUTC_SET_AT_ROLLOVER) {
        DPRINTF("%s: Clear PWM output. \n", this->name());
        m_pwm_pv->PWMO.write(0);
   }
   else if(m_pwm_pv->PWMCR_POUTC == POUTC_SET_AT_MATCH){
        DPRINTF("%s: Set PWM output. \n", this->name());
        m_pwm_pv->PWMO.write(1);
   }
}
