
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
//* This file contains the PV class for FPGA_GPIO_OUT_custom.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 4.1beta1
//* Generated on: Mar. 14, 2015 10:00:00 AM, (user: markca)
//* Automatically merged on: Jun. 05, 2015 03:47:24 PM, (user: markca)
//* Automatically merged on: Jul. 10, 2015 02:58:18 PM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 10:41:37 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:33:33 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:43:31 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:55:23 AM, (user: markca)
//* Automatically merged on: Jul. 13, 2015 11:58:54 AM, (user: markca)
//*>



#include "FPGA_GPIO_OUT_custom_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
FPGA_GPIO_OUT_custom_pv::FPGA_GPIO_OUT_custom_pv(sc_module_name module_name) 
  : FPGA_GPIO_OUT_custom_pv_base(module_name) {
}      

 

// callback for any change in signal: slave of type: sc_in<bool>
void FPGA_GPIO_OUT_custom_pv::slave_callback() {
  cout << name() << " @ " << sc_time_stamp() << " value = " << slave << endl;
}
