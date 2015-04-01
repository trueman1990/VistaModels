
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
//* This file contains the PV class for RestBusDriver.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9.0
//* Generated on: Mar. 31, 2015 03:29:11 PM, (user: jon)
//*>



#include "RestBusDriver_pv.h"
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
RestBusDriver_pv::RestBusDriver_pv(sc_module_name module_name) 
  : RestBusDriver_pv_base(module_name) {
}    

 

// callback for any change in signal: rxi of type: sc_in<bool>
void RestBusDriver_pv::rxi_callback() {
}
