
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

#pragma once

#include "model_builder.h"
#include "M4_model.h"


class M4_pv : public ::mb::models::arm::cortex_m4,
                      public M4_pv_base_parameters {
  
 public:
  typedef mb::tlm20::irq_target_socket<> irq_target_socket;


  mb::tlm20::irq_target_socket<>& irq_0;
  mb::tlm20::irq_target_socket<>& irq_1;
  mb::tlm20::irq_target_socket<>& irq_2;
  mb::tlm20::irq_target_socket<>& irq_3;

 public:
  M4_pv(sc_module_name name)  : 
    ::mb::models::arm::cortex_m4(name, 4),
    M4_pv_base_parameters(this)
, irq_0(irqs[0]), irq_1(irqs[1]), irq_2(irqs[2]), irq_3(irqs[3])
  {
  }
};
