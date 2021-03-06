
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
//* This file contains the PV class for OutOrder.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.2.0
//* Generated on: Mar. 30, 2012 09:14:43 AM, (user: jon)
//*>


#include "OutOrder_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
OutOrder_pv::OutOrder_pv(sc_module_name module_name) 
  : OutOrder_pv_base(module_name) {
  SC_THREAD(thread);
}    

void OutOrder_pv::thread() {
  unsigned int d = 1;
  TP = 0;
  x_write(0x0, d);
  x_read(0x0, &d, 1);
  y_write(0x0, d);

  wait (10*clock);
}

