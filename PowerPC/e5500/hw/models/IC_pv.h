
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
//* This file contains the PV class for IC.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.9Beta1
//* Generated on: May. 19, 2014 08:13:02 PM, (user: nlevy)
//* Automatically merged on: May. 20, 2014 05:30:42 PM, (user: nlevy)
//* Automatically merged on: May. 20, 2014 05:37:03 PM, (user: nlevy)
//* Automatically merged on: May. 25, 2014 12:29:21 PM, (user: nlevy)
//* Automatically merged on: May. 25, 2014 02:50:32 PM, (user: nlevy)
//* Automatically merged on: May. 25, 2014 04:36:45 PM, (user: nlevy)
//* Automatically merged on: May. 25, 2014 04:42:18 PM, (user: nlevy)
//* Automatically merged on: Aug. 05, 2014 06:21:11 PM, (user: ibirger)
//*>


#pragma once

#include "IC_model.h"

using namespace tlm;
//forward declaration
struct IRQQueue;
struct IRQDest;
class OpenPICState;
/* OpenPIC have 5 outputs per CPU connected and one IRQ out single output */
enum {
    OPENPIC_OUTPUT_INT = 0, /* IRQ                       */
    OPENPIC_OUTPUT_CINT,    /* critical IRQ              */
    OPENPIC_OUTPUT_MCK,     /* Machine check event       */
    OPENPIC_OUTPUT_DEBUG,   /* Inconditional debug event */
    OPENPIC_OUTPUT_RESET,   /* Core reset event          */
    OPENPIC_OUTPUT_NB,
};

#define MAX_CPU     32
#define MAX_MSI     8


#define OPENPIC_MODEL_RAVEN       0
#define OPENPIC_MODEL_FSL_MPIC_20 1
#define OPENPIC_MODEL_FSL_MPIC_42 2

#define OPENPIC_MAX_SRC     256
#define OPENPIC_MAX_TMR     4
#define OPENPIC_MAX_IPI     4
#define OPENPIC_MAX_IRQ     (OPENPIC_MAX_SRC + OPENPIC_MAX_IPI + \
                             OPENPIC_MAX_TMR)

#define GCR_MODE_PASS    0x00000000
#define GCR_MODE_MIXED   0x20000000
#define GCR_MODE_PROXY   0x60000000
#define GCR_RESET        0x80000000

#define OPENPIC_FLAG_ILR          (2 << 0)
#define VID_REVISION_1_2   2
#define VIR_GENERIC      0x00000000 /* Generic Vendor ID */
#define IVPR_MASK_SHIFT       31
#define IVPR_MASK_MASK        (1U << IVPR_MASK_SHIFT)

#define FRR_NIRQ_SHIFT    16
#define FRR_NCPU_SHIFT     8
#define FRR_VID_SHIFT      0

//This class inherits from the IC_pv_base class
class IC_pv : public IC_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(IC_pv);
  IC_pv(sc_core::sc_module_name module_name);  

 protected:
  /////////////////////////////////////////
  // io_memory callbacks
  ///////////////////////////////////////// 
  virtual void cb_write_global_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_global_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_write_tmr_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_tmr_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_write_msi_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_msi_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_write_summary_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_summary_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_write_src_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_src_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_write_cpu_reg(uint64_t offset, unsigned char* data, unsigned length);
  virtual void cb_read_cpu_reg(uint64_t offset, unsigned char* data, unsigned length); 

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool bus_slave_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned bus_slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

  bool IACK_read_callback_read(mb_address_type address, unsigned char* data, unsigned size);
 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool bus_slave_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned bus_slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size){ return 0; }
  bool bus_slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);  

  void set_bit(int32_t nr, uint32_t *addr);
  void clear_bit(int32_t nr, uint32_t *addr);
  int  test_bit(int32_t nr, const uint32_t *addr);
  uint32_t find_next_bit(const uint32_t *addr, uint32_t size,
                              uint32_t offset);
  void IRQ_setbit(IRQQueue*, int);
  void IRQ_resetbit(IRQQueue*, int);
  int  IRQ_testbit(IRQQueue*, int);
  void IRQ_check(OpenPICState*, IRQQueue*);
  void IRQ_local_pipe(OpenPICState*, int, int, bool, bool);
  int  IRQ_get_next(OpenPICState *opp, IRQQueue *q);
  int  get_current_cpu(void);
  uint32_t read_IRQreg_idr(OpenPICState *opp, int n_IRQ);
  uint32_t read_IRQreg_ivpr(OpenPICState *opp, int n_IRQ);
  uint32_t read_IRQreg_ilr(OpenPICState *opp, int n_IRQ);
  int  output_to_inttgt(int output);
  int  inttgt_to_output(int inttgt);
  void write_IRQreg_idr(OpenPICState *opp, int n_IRQ, uint32_t val);
  void write_IRQreg_ivpr(OpenPICState *opp, int n_IRQ, uint32_t val);
  //  void qemu_set_irq(void *irq, int level);
  void set_irq(int type, int level);
  void openpic_update_irq(OpenPICState*, int);
  void openpic_set_irq(void*, int, int);
  uint32_t openpic_cpu_read_internal(void *opaque, uint64_t addr, int idx);
  uint32_t openpic_iack(OpenPICState *opp, IRQDest *dst, int cpu);
  void openpic_cpu_write_internal(OpenPICState *opp, uint64_t addr, uint32_t val, int idx);
  void openpic_gcr_write(OpenPICState *opp, uint64_t val);
  void write_IRQreg_ilr(OpenPICState *opp, int n_IRQ, uint32_t val);

 protected:
  void reset(OpenPICState *opp);
  void init();
  ////////////////////////////////////////
  // signals callbacks
  //////////////////////////////////////// 
  void EIRQ0_callback();
  void Internal0_callback();
  void Internal1_callback();
  void Internal2_callback();
  void Internal3_callback();
  void Internal4_callback(); 
};

