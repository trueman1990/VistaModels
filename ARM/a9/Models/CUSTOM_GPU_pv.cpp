
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
//* This file contains the PV class for CUSTOM_GPU.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.7.0
//* Generated on: Oct. 19, 2013 08:58:55 AM, (user: markca)
//* Automatically merged on: Oct. 19, 2013 08:59:41 AM, (user: markca)
//*>



#include "CUSTOM_GPU_pv.h"
#include <iostream>

#include "../software/tinygl/zbuffer.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

//constructor
CUSTOM_GPU_pv::CUSTOM_GPU_pv(sc_module_name module_name) 
  : CUSTOM_GPU_pv_base(module_name) {
}   

/////////////////////////////////////////////////////////////////////////////////
// Use these functions to define the behavior of your model when there is a 
// write event on one of the registers as defined in the Model Builder form.
// These functions are called before the write callbacks on the port.
///////////////////////////////////////////////////////////////////////////////// 

void*
CUSTOM_GPU_pv::getHostMemory(unsigned int inputAdr) {
  tlm::tlm_dmi dmi_data;
  if(mem_access_get_direct_memory_ptr(tlm::TLM_WRITE_COMMAND, 
                                      (mb_address_type) inputAdr,
                                      dmi_data)) {

    unsigned char* dmi_ptr = dmi_data.get_dmi_ptr();
    sc_dt::uint64 gpu_zero = inputAdr;
    return(dmi_ptr + (gpu_zero - dmi_data.get_start_address()));
  }
  return 0;
}

// Write callback for GPU_ZERO_SIZE register.
// The newValue has been already assigned to the GPU_ZERO_SIZE register.
void CUSTOM_GPU_pv::cb_write_GPU_ZERO_SIZE(unsigned int zero_size) {
  unsigned char* hostMem = (unsigned char*) getHostMemory(GPU_ZERO_START);
  if(hostMem) {
    memset(hostMem, 0, zero_size);
  }
}
  
// Write callback for GPU_TRIANGLE_P2 register.
void CUSTOM_GPU_pv::cb_write_GPU_TRIANGLE_DRAW(unsigned int mode) {
  ZBufferPoint *p0 = (ZBufferPoint*) getHostMemory(GPU_TRIANGLE_P0);
  ZBufferPoint *p1 = (ZBufferPoint*) getHostMemory(GPU_TRIANGLE_P1);
  ZBufferPoint *p2 = (ZBufferPoint*) getHostMemory(GPU_TRIANGLE_P2);

  ZBuffer zb;
  memcpy(&zb, (ZBuffer*) getHostMemory(GPU_TRIANGLE_ZB), sizeof(ZBuffer));
 
  zb.zbuf = (unsigned short*) getHostMemory((uintptr_t) zb.zbuf);
  zb.pbuf = (PIXEL*) getHostMemory((intptr_t) zb.pbuf);

  switch(mode) {
  case 1:
    ZB_fillTriangleFlat(&zb, p0, p1, p2);
    break;
  case 2:
    ZB_fillTriangleSmooth(&zb, p0, p1, p2);
    break;
  case 3:
    ZB_fillTriangleMapping(&zb, p0, p1, p2);
    break;
  case 4:
    ZB_fillTriangleMappingPerspective(&zb, p0, p1, p2);
    break;
  default:
    break;
  }
}


// Read callback for reg_access port.
// Returns true when successful.
bool CUSTOM_GPU_pv::reg_access_callback_read(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
}

// Write callback for reg_access port.
// Returns true when successful.
bool CUSTOM_GPU_pv::reg_access_callback_write(mb_address_type address, unsigned char* data, unsigned size) {
  
  return true;
} 



unsigned CUSTOM_GPU_pv::reg_access_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

unsigned CUSTOM_GPU_pv::reg_access_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size) {
  return 0;
} 

bool CUSTOM_GPU_pv::reg_access_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData) {
  return false;
}

 
void CUSTOM_GPU_pv::cb_transport_dbg_GPU_ZERO_SIZE(tlm::tlm_generic_payload& trans) {}

void CUSTOM_GPU_pv::cb_transport_dbg_GPU_TRIANGLE_DRAW(tlm::tlm_generic_payload& trans) {}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ZB_fillTriangleFlat(ZBuffer *zb,
                         ZBufferPoint *p0, ZBufferPoint *p1, ZBufferPoint *p2)
{
  int color;

#define ZCMP(z,zpix) ((z) >= (zpix))
  
#define INTERP_Z
  
#define DRAW_INIT()				\
  {						\
    color=RGB_TO_PIXEL(p2->r,p2->g,p2->b);	\
  }
  
#define PUT_PIXEL(_a)				\
  {						\
    zz=z >> ZB_POINT_Z_FRAC_BITS;                       \
    if (ZCMP(zz,pz[_a])) {				\
      pp[_a]=color;                                     \
      pz[_a]=zz;                                        \
    }                                                   \
    z+=dzdx;                                            \
  }
#include "../software/tinygl/ztriangle.h"
}


void ZB_fillTriangleSmooth(ZBuffer *zb,
			   ZBufferPoint *p0,ZBufferPoint *p1,ZBufferPoint *p2)
{

        int _drgbdx;


#define INTERP_Z
#define INTERP_RGB

#define SAR_RND_TO_ZERO(v,n) (v / (1<<n))

#define DRAW_INIT() 				\
{						\
  _drgbdx=(SAR_RND_TO_ZERO(drdx,6) << 22) & 0xFFC00000;		\
  _drgbdx|=SAR_RND_TO_ZERO(dgdx,5) & 0x000007FF;		\
  _drgbdx|=(SAR_RND_TO_ZERO(dbdx,7) << 12) & 0x001FF000; 	\
}


#define PUT_PIXEL(_a)				\
{						\
    zz=z >> ZB_POINT_Z_FRAC_BITS;		\
    if (ZCMP(zz,pz[_a])) {				\
      tmp=rgb & 0xF81F07E0;			\
      pp[_a]=tmp | (tmp >> 16);			\
      pz[_a]=zz;				\
    }						\
    z+=dzdx;					\
    rgb=(rgb+drgbdx) & ( ~ 0x00200800);		\
}

#define DRAW_LINE()							   \
{									   \
  register unsigned short *pz;					   \
  register PIXEL *pp;					   \
  register unsigned int tmp,z,zz,rgb,drgbdx;				   \
  register int n;							   \
  n=(x2 >> 16) - x1;							   \
  pp=pp1+x1;								   \
  pz=pz1+x1;								   \
  z=z1;									   \
  rgb=(r1 << 16) & 0xFFC00000;						   \
  rgb|=(g1 >> 5) & 0x000007FF;						   \
  rgb|=(b1 << 5) & 0x001FF000;						   \
  drgbdx=_drgbdx;							   \
  while (n>=3) {							   \
    PUT_PIXEL(0);							   \
    PUT_PIXEL(1);							   \
    PUT_PIXEL(2);							   \
    PUT_PIXEL(3);							   \
    pz+=4;								   \
    pp+=4;								   \
    n-=4;								   \
  }									   \
  while (n>=0) {							   \
    PUT_PIXEL(0);							   \
    pz+=1;								   \
    pp+=1;								   \
    n-=1;								   \
  }									   \
}

#include "../software/tinygl/ztriangle.h"
}

void ZB_fillTriangleMapping(ZBuffer *zb,
			    ZBufferPoint *p0,ZBufferPoint *p1,ZBufferPoint *p2)
{
    PIXEL *texture;

#define INTERP_Z
#define INTERP_ST

#define DRAW_INIT()				\
{						\
  texture=zb->current_texture;			\
}

#define PUT_PIXEL(_a)				\
{						\
   zz=z >> ZB_POINT_Z_FRAC_BITS;		\
     if (ZCMP(zz,pz[_a])) {				\
       pp[_a]=texture[((t & 0x3FC00000) | s) >> 14];	\
       pz[_a]=zz;				\
    }						\
    z+=dzdx;					\
    s+=dsdx;					\
    t+=dtdx;					\
}

#include "../software/tinygl/ztriangle.h"
}

void ZB_fillTriangleMappingPerspective(ZBuffer *zb,
                            ZBufferPoint *p0,ZBufferPoint *p1,ZBufferPoint *p2)
{
    PIXEL *texture;
    float fdzdx,fndzdx,ndszdx,ndtzdx;

#define INTERP_Z
#define INTERP_STZ

#define NB_INTERP 8

#define DRAW_INIT()				\
{						\
  texture=zb->current_texture;\
  fdzdx=(float)dzdx;\
  fndzdx=NB_INTERP * fdzdx;\
  ndszdx=NB_INTERP * dszdx;\
  ndtzdx=NB_INTERP * dtzdx;\
}

#define PUT_PIXEL(_a)				\
{						\
   zz=z >> ZB_POINT_Z_FRAC_BITS;		\
     if (ZCMP(zz,pz[_a])) {				\
       pp[_a]=*(PIXEL *)((char *)texture+ \
               (((t & 0x3FC00000) | (s & 0x003FC000)) >> (17 - PSZSH)));\
       pz[_a]=zz;				\
    }						\
    z+=dzdx;					\
    s+=dsdx;					\
    t+=dtdx;					\
}


#define DRAW_LINE()				\
{						\
  register unsigned short *pz;		\
  register PIXEL *pp;		\
  register unsigned int s,t,z,zz;	\
  register int n,dsdx,dtdx;		\
  float sz,tz,fz,zinv; \
  n=(x2>>16)-x1;                             \
  fz=(float)z1;\
  zinv=1.0 / fz;\
  pp=(PIXEL *)((char *)pp1 + x1 * PSZB); \
  pz=pz1+x1;					\
  z=z1;						\
  sz=sz1;\
  tz=tz1;\
  while (n>=(NB_INTERP-1)) {						   \
    {\
      float ss,tt;\
      ss=(sz * zinv);\
      tt=(tz * zinv);\
      s=(int) ss;\
      t=(int) tt;\
      dsdx= (int)( (dszdx - ss*fdzdx)*zinv );\
      dtdx= (int)( (dtzdx - tt*fdzdx)*zinv );\
      fz+=fndzdx;\
      zinv=1.0 / fz;\
    }\
    PUT_PIXEL(0);							   \
    PUT_PIXEL(1);							   \
    PUT_PIXEL(2);							   \
    PUT_PIXEL(3);							   \
    PUT_PIXEL(4);							   \
    PUT_PIXEL(5);							   \
    PUT_PIXEL(6);							   \
    PUT_PIXEL(7);							   \
    pz+=NB_INTERP;							   \
    pp=(PIXEL *)((char *)pp + NB_INTERP * PSZB);\
    n-=NB_INTERP;							   \
    sz+=ndszdx;\
    tz+=ndtzdx;\
  }									   \
    {\
      float ss,tt;\
      ss=(sz * zinv);\
      tt=(tz * zinv);\
      s=(int) ss;\
      t=(int) tt;\
      dsdx= (int)( (dszdx - ss*fdzdx)*zinv );\
      dtdx= (int)( (dtzdx - tt*fdzdx)*zinv );\
    }\
  while (n>=0) {							   \
    PUT_PIXEL(0);							   \
    pz+=1;								   \
    pp=(PIXEL *)((char *)pp + PSZB);\
    n-=1;								   \
  }									   \

#include "../software/tinygl/ztriangle.h"
}
  

}