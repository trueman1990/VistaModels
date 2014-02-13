
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
//* This file contains the PV class for OpenGL_Bridge.
//* This is a template file: You may modify this file to implement the 
//* behavior of your component. 
//* 
//* Model Builder version: 3.7.0
//* Generated on: Feb. 07, 2014 04:02:07 PM, (user: markca)
//* Automatically merged on: Feb. 07, 2014 04:03:52 PM, (user: markca)
//*>


#pragma once

#include "OpenGL_Bridge_model.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "../software/opengl_bridge_reg.h"

using namespace tlm;

//This class inherits from the OpenGL_Bridge_pv_base class
class OpenGL_Bridge_pv : public OpenGL_Bridge_pv_base {
 public:
  typedef esl::tlm_types::Address mb_address_type;
 public:
  // Constructor
  // Do not add parameters here.
  // To add parameters - use the Model Builder form (under PV->Parameters tab)
  SC_HAS_PROCESS(OpenGL_Bridge_pv);
  OpenGL_Bridge_pv(sc_core::sc_module_name module_name);   

  void* getHostMemory(unsigned int inputAdr);

 protected:
  ////////////////////////////////////////
  // target ports read callbacks
  //////////////////////////////////////// 
  bool slave_callback_read(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned slave_callback_read_dbg(mb_address_type address, unsigned char* data, unsigned size); 

 protected:
  ////////////////////////////////////////
  // target ports write callbacks
  //////////////////////////////////////// 
  bool slave_callback_write(mb_address_type address, unsigned char* data, unsigned size);
  
  unsigned slave_callback_write_dbg(mb_address_type address, unsigned char* data, unsigned size);  
  bool slave_get_direct_memory_ptr(mb_address_type address, tlm::tlm_dmi& dmiData);   

  protected:
        SDL_Window* mainWindow;
        SDL_GLContext mainGLContext;

        double args[8]; //, arg1, arg2, arg3, arg4, arg5, arg6, arg7;   
        unsigned int lastTicks;
        sc_time sysCTime;
        unsigned int fps;

        void sdl2Open(void);
        void sdl2Swap(void);
        void sdl2Close(void);      

        void bglBegin();
        void bglCallList();
        void bglClear();
        void bglClearColor();
        void bglColor3f();
        void bglDisable();
        void bglEnable();
        void bglEnd();
        void bglEndList();
        void bglFlush();
        void bglFrustum();
        void bglGenLists();
        void bglLightf();
        void bglLightfv();
        void bglLoadIdentity();
        void bglMaterialfv();
        void bglMatrixMode();
        void bglNewList();
        void bglNormal3f();
        void bglOrtho();
        void bglPopMatrix();
        void bglPolygonMode();
        void bglPushMatrix();
        void bglRectf();
        void bglRotatef();
        void bglScalef();
        void bglShadeModel();
        void bglTexCoord2f();
        void bglTranslatef();
        void bglVertex2f();
        void bglVertex3f();
        void bglViewport();
};
