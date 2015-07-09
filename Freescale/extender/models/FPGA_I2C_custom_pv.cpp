
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
//* This file contains the PV class for FPGA_I2C_custom.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.1beta1
//* Generated on: Mar. 12, 2015 03:13:17 PM, (user: markca)
//*>



#include "FPGA_I2C_custom_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
FPGA_I2C_custom_pv::FPGA_I2C_custom_pv(sc_module_name module_name) 
  : FPGA_I2C_custom_pv_base(module_name),
    state(0),
    size_state(0) {

  ifp = fopen("input.txt", "rb");
  if (ifp == NULL) {
    fprintf(stderr, "Can't open input file\n");
    exit(1);
  }
  fseek(ifp, 0L, SEEK_END);
  ifp_size = ftell(ifp);
  fseek(ifp, 0L, SEEK_SET);

}   

struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

// Read callback for slave port.
// Returns true when successful.
bool FPGA_I2C_custom_pv::slave_callback_read(mb_address_type address, unsigned char* data, unsigned size) {

  unsigned char bytes[4];
  bytes[0] = (ifp_size >> 24) & 0xFF;
  bytes[1] = (ifp_size >> 16) & 0xFF;
  bytes[2] = (ifp_size >> 8) & 0xFF;
  bytes[3] = ifp_size & 0xFF;

  printf(" FPGA ifp_size = 0x%x\n",ifp_size);
  printf("byte[0] = 0x%x\n",bytes[0]);
  printf("byte[1] = 0x%x\n",bytes[1]);
  printf("byte[2] = 0x%x\n",bytes[2]);
  printf("byte[3] = 0x%x\n",bytes[3]);

  switch(state) {
  case 1:  

     data[0] = bytes[size_state++];
     printf(" FPGA bytes[size_state++] = 0x%x\n @ size_state = 0x%x\n",data[0],size_state);
    break;

  case 2:

      data[0] = fgetc(ifp);
    break;

  default:
    break;
  }
  cout << name() << " @ " << sc_time_stamp() << " address : " << hex << address << " READ, sending: " << hex(data[0]) << endl;
  return true;
}

// Write callback for slave port.
// Returns true when successful.
bool FPGA_I2C_custom_pv::slave_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  cout << name() << " @ " << sc_time_stamp() << " address : " << hex << address << " WRITE " << (unsigned int) (*data) << endl;

  state = *data;

  switch(*data) {
  case 0:
    fclose(ifp);
    size_state = 0;
    ifp = fopen("input.txt", "rb");
    if (ifp == NULL) {
      fprintf(stderr, "Can't open input file\n");
      exit(1);
    }
    fseek(ifp, 0L, SEEK_END);
    ifp_size = ftell(ifp);
    fseek(ifp, 0L, SEEK_SET);
    break;

  default:
    break;
  }
  return true;
} 




unsigned FPGA_I2C_custom_pv::slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned FPGA_I2C_custom_pv::slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool FPGA_I2C_custom_pv::slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
