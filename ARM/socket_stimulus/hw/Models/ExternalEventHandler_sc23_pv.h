
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
//* This file contains the PV class for ExternalEventHandler_sc23.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.8.1RND2
//* Generated on: Jul. 25, 2014 02:39:56 PM, (user: markca)
//*>


#pragma once

#include "ExternalEventHandler_sc23_model.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <deque>

// thread_safe_event.h requires SystemC 2.3
#include "thread_safe_event.h"
#include "DataType.h"

using namespace tlm;

//This class inherits from the ExternalEventHandler_sc23_pv_base class
class ExternalEventHandler_sc23_pv : public ExternalEventHandler_sc23_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(ExternalEventHandler_sc23_pv);
  ExternalEventHandler_sc23_pv(sc_core::sc_module_name module_name);     

  void input();		// SystemC process which waits for asynchronous input from external process
  void output();	// SystemC process which takes data from input and writes out through the tlm port

 private:
  // call_startReader is a wrapper function that allows a member function to be used as pthread argument.
  static void* call_startReader(void *arg) { return ((ExternalEventHandler_sc23_pv*)arg)->startReader(); }
  void *startReader();	// C++ pthread which will fork and exec the external process then wait for input
                        // from the external process.  It will forward and call notify on safe_ev

  pthread_t readerThread;
  pthread_mutex_t mutex;	// Used to safely pass data from startReader to input processes.
  
  thread_safe_event safe_ev;	// Thread safe event used to notify from startReader to input processes.

  std::deque<DataType *> q;	// queue holding data passed from startReader to input processes
  tlm::tlm_fifo<DataType *> fifo;  // queue holding data passed from input to output processes
       

  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
};

