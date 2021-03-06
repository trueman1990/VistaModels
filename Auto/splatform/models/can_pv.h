
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
//* This file contains the PV class for can.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9.0
//* Generated on: Mar. 31, 2015 03:44:29 PM, (user: jon)
//* Automatically merged on: Mar. 31, 2015 03:55:28 PM, (user: jon)
//* Automatically merged on: Apr. 01, 2015 10:59:08 AM, (user: jon)
//* Automatically merged on: Apr. 01, 2015 11:03:00 AM, (user: jon)
//* Automatically merged on: Apr. 01, 2015 11:05:01 AM, (user: jon)
//* Automatically merged on: Apr. 09, 2015 09:02:52 AM, (user: jon)
//* Automatically merged on: May. 07, 2015 01:44:01 PM, (user: markca)
//* Automatically merged on: May. 07, 2015 03:27:53 PM, (user: markca)
//*>


#pragma once

#include "can_model.h"
#include <map>
#include <queue>
class AccelDriver_pv;

using namespace tlm;

//This class inherits from the can_pv_base class
class can_pv : public can_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(can_pv);
  can_pv(sc_core::sc_module_name module_name);  
  
 protected:
  /////////////////////////////////////////
  // write callbacks of registers
  ////////////////////////////////////////// 
  void cb_write_m_ident(unsigned int newValue);
  void cb_write_m_ack(unsigned int newValue);

 protected:
  /////////////////////////////////////////
  // io_memory callbacks
  ///////////////////////////////////////// 
  virtual void cb_write_m_rxmem(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_m_rxmem(uint64_t offset, unsigned char* data, unsigned length); 

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool reg_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned reg_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size);
  bool RX0_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned RX0_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool reg_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned reg_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size);
  bool RX0_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned RX0_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size); 
  virtual void cb_transport_dbg_m_ident(tlm::tlm_generic_payload& trans);
  virtual void cb_transport_dbg_m_ack(tlm::tlm_generic_payload& trans); 
  bool reg_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);  
  bool RX0_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   

  mb::mb_token_ptr get_current_token_from_payload(tlm::tlm_generic_payload* payload_for_token);

 private:
  struct CANDataType {
    unsigned int ident;
    bool rtr;
    bool ide;
    unsigned int length;
    unsigned char d[9];
    unsigned int crc;
    bool ack;

    unsigned int CRCstep(unsigned inp, unsigned num, unsigned c) {
      int inv;
      for (int i=num-1; i>=0; i--) {
        inv = ((c >> 14) & 0x1) ^ ((inp >> i) & 0x1);
        c = (c << 1) & 0x7FFF;
        if (inv) c = c ^ 0x4599;
      }
      return c;
    }

    unsigned int calcCRC() {
      unsigned int c = 0;
      c = CRCstep(ident&0x7FF, 11, c);
      c = CRCstep((unsigned) rtr, 1, c);
      c = CRCstep((unsigned) ide, 1, c);
      c = CRCstep(0x0, 1, c);
      if (ide) c = CRCstep((ident>>11)&0x3FFFF, 18, c);
      c = CRCstep(length, 4, c);
      for (int i=0; i<length; i++)
        c = CRCstep((unsigned) d[i], 8, c);
      return c;
    }
  };

  mb::mb_fifo<mb::mb_token_ptr> tpff;
  tlm_fifo<CANDataType *> securityff;
  queue<CANDataType *> securityq;
  map<unsigned int, CANDataType *> identmap;
  unsigned char rxmem[8];
  unsigned int corruptId;
};

