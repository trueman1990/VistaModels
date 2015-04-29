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

#pragma once

#include "ChassisCan_model.h"
#include <queue>
#include <vector>

using namespace tlm;

class ChassisCan_pv : public ChassisCan_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;

  SC_HAS_PROCESS(ChassisCan_pv);
  ChassisCan_pv(sc_module_name module_name);

  void thread();
  void RX0_thread();
  void RX1_thread();
  void RX2_thread();
  void RX3_thread();
  void RX4_thread();
  void RX5_thread();
  void RX6_thread();

 protected:

  ///////////////////////////////
  // target write callbacks
  /////////////////////////////// 

  virtual bool TX0_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX1_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX2_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX3_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX4_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX5_callback_write(config::uint64 address, unsigned char* data, unsigned size);
  virtual bool TX6_callback_write(config::uint64 address, unsigned char* data, unsigned size);

 private:
  class DataType {
    public:
    unsigned int m_ident;
    unsigned int m_length;
    unsigned int m_crc;
    unsigned int m_size;
    mb::mb_token_ptr m_tokenptr;
    unsigned char * m_data;

      DataType() {}

      DataType(mb_address_type address, unsigned size, mb::mb_token_ptr tokenptr)
        : m_ident(address), m_size(size)
      {
        m_tokenptr = tokenptr;
        if (m_tokenptr && m_tokenptr->hasField("CANDataPtr")) {
          m_data = (unsigned char *) m_tokenptr->getFieldAsVoidPtr("CANDataPtr");
        } else {
          cout << "Error: ChassisCan_pv DataType constructor.\n";
        }
      }

      bool operator() (const DataType* lhs, const DataType* rhs) const {
        return lhs->m_ident < rhs->m_ident; }
  };

  tlm_fifo<int> iff;
  mb::mb_fifo<DataType*> RX0ff;
  mb::mb_fifo<DataType*> RX1ff;
  mb::mb_fifo<DataType*> RX2ff;
  mb::mb_fifo<DataType*> RX3ff;
  mb::mb_fifo<DataType*> RX4ff;
  mb::mb_fifo<DataType*> RX5ff;
  mb::mb_fifo<DataType*> RX6ff;
  priority_queue<DataType*, vector<DataType*>, DataType> pq;
};
