
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
  //* This file contains the PV class for LinuxFrameBufferDisplay.
  //* This is a template file: You may modify this file to implement the 
  //* behavior of your component. 
  //* 
  //* Model Builder version: 3.8.1RND2
  //* Generated on: Jul. 30, 2014 11:26:19 AM, (user: markca)
//* Automatically merged on: Jul. 30, 2014 11:59:01 AM, (user: markca)
//*>

#include "LinuxFrameBufferDisplay_pv.h"
#include <iostream>
#include <stdlib.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

namespace {
class fb_sdl_client : public mb::physical_io::sdl_client {

 public:
  fb_sdl_client(const char* title)
    : sdl_client(title) {
  }

  void kbd_put_keycode(int keycode) {
    ::kbd_put_keycode(keycode);
  }

  int kbd_mouse_is_absolute() {
    return ::kbd_mouse_is_absolute();
  }

  void kbd_mouse_event(int dx, int dy, int dz, int buttons_state) {
    ::kbd_mouse_event(dx, dy, dz, buttons_state);
  }
};
}

//constructor
LinuxFrameBufferDisplay_pv::LinuxFrameBufferDisplay_pv(sc_module_name module_name) 
  : LinuxFrameBufferDisplay_pv_base(module_name),
    m_client(0) {

  frame_refresh_rate = sc_core::sc_time(refresh, sc_core::SC_MS);

  m_client = new fb_sdl_client(displayName);
  m_client->set_size(width, height);

  SC_THREAD(updateDisplay);
}

void
LinuxFrameBufferDisplay_pv::updateDisplay()
{
  while(1) {
    sc_core::sc_time start = sc_core::sc_time_stamp();
    m_client->update(0, 0, width, height);
    sc_core::sc_time now = sc_core::sc_time_stamp();
    if (now - start < frame_refresh_rate) {
      wait(frame_refresh_rate - (now - start));
    }
  }
} 

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 


// Read callback for from_bus port.
// Returns true when successful.
bool LinuxFrameBufferDisplay_pv::from_bus_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  return true;
}

// Write callback for from_bus port.
// Returns true when successful.
bool LinuxFrameBufferDisplay_pv::from_bus_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  return true;
} 

unsigned LinuxFrameBufferDisplay_pv::from_bus_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned LinuxFrameBufferDisplay_pv::from_bus_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool LinuxFrameBufferDisplay_pv::from_bus_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  dmiData.allow_read_write();
  dmiData.set_dmi_ptr((unsigned char*) m_client->get_buffer());
  dmiData.set_start_address(0);
  dmiData.set_end_address(width * height * 4);
  return true;
}

