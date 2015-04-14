
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
//* This file contains the PV class for FileCanData.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9.0
//* Generated on: Mar. 31, 2015 03:29:10 PM, (user: jon)
//*>



#include "FileCanData_pv.h"
#include "MemoryMap.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
FileCanData_pv::FileCanData_pv(sc_module_name module_name) 
  : FileCanData_pv_base(module_name) {
  string fname("data/");
  fname.append(name());
cout<<"fname = "<<fname<<endl;
  ifile.open(fname.c_str(), std::ifstream::in);

  SC_THREAD(thread);
}    

// callback for any change in signal: rxi of type: sc_in<bool>
void FileCanData_pv::rxi_callback() {
}

void FileCanData_pv::thread() {
  string s;
  unsigned int t_us, ident, size, rtr, ide;
  long long data;
  sc_time ctime = sc_time_stamp();

  ifile >> s;
  while (ifile.good()) {
    if (s[0] == '#') {
      getline(ifile, s);
      ifile >> s;
    } else {
      ifile >> dec >> t_us >> hex >> ident >> size >> rtr >> ide >> data;
cout << dec << t_us<<" 0x"<<hex<<ident<<" "<<size<<" "<<rtr<<" "<<ide<<" 0x"<<data<<endl;
      ifile >> s;

      ctime = sc_time_stamp();
      if (ctime < sc_time(t_us, SC_US))
        wait(sc_time(t_us, SC_US) - ctime);

      m_write(CAN_SIZE, size);
      m_write(CAN_RTR, rtr);
      m_write(CAN_IDE, ide);
      m_write(CAN_DATA, data);
      m_write(CAN_IDENT, ident);
    }
  }
}
