#pragma once
#include "mgc_vista_schematics.h"
$includes_begin;
#include <systemc.h>
#include "AXI_BUS_model.h"
#include "MEMORY_model.h"
#include "PL110_LCD_model.h"
#include "CORTEX_A9_uni_model.h"
$includes_end;

$module_begin("top");
SC_MODULE(top) {
public:
  top(::sc_core::sc_module_name name):
    ::sc_core::sc_module(name)
    $initialization_begin
$init("cpu"),
cpu(0)
$end
$init("axi"),
axi(0)
$end
$init("video_mem"),
video_mem(0)
$end
$init("low_mem"),
low_mem(0)
$end
$init("high_mem"),
high_mem(0)
$end
$init("lcd"),
lcd(0)
$end
    $initialization_end
{
    $elaboration_begin;
$create_component("cpu");
cpu = new CORTEX_A9_uni_pvt("cpu");
$end;
$create_component("axi");
axi = new AXI_BUS_pvt("axi");
$end;
$create_component("video_mem");
video_mem = new MEMORY_pvt("video_mem");
$end;
$create_component("low_mem");
low_mem = new MEMORY_pvt("low_mem");
$end;
$create_component("high_mem");
high_mem = new MEMORY_pvt("high_mem");
$end;
$create_component("lcd");
lcd = new PL110_LCD_pvt("lcd");
$end;
$bind("axi->low_mem","low_mem->slave");
vista_bind(axi->low_mem, low_mem->slave);
$end;
$bind("axi->video_mem","video_mem->slave");
vista_bind(axi->video_mem, video_mem->slave);
$end;
$bind("lcd->master","axi->from_lcd");
vista_bind(lcd->master, axi->from_lcd);
$end;
$bind("axi->to_lcd","lcd->ctrl_slave");
vista_bind(axi->to_lcd, lcd->ctrl_slave);
$end;
$bind("axi->high_mem","high_mem->slave");
vista_bind(axi->high_mem, high_mem->slave);
$end;
$bind("cpu->insn_initiator","axi->cpu_1");
vista_bind(cpu->insn_initiator, axi->cpu_1);
$end;
$bind("cpu->data_initiator","axi->cpu_0");
vista_bind(cpu->data_initiator, axi->cpu_0);
$end;
    $elaboration_end;
  $vlnv_assign_begin;
m_library = "Models";
m_vendor = "";
m_version = "";
  $vlnv_assign_end;
  }
  ~top() {
    $destructor_begin;
$destruct_component("cpu");
delete cpu; cpu = 0;
$end;
$destruct_component("axi");
delete axi; axi = 0;
$end;
$destruct_component("video_mem");
delete video_mem; video_mem = 0;
$end;
$destruct_component("low_mem");
delete low_mem; low_mem = 0;
$end;
$destruct_component("high_mem");
delete high_mem; high_mem = 0;
$end;
$destruct_component("lcd");
delete lcd; lcd = 0;
$end;
    $destructor_end;
  }
public:
  $fields_begin;
$component("cpu");
CORTEX_A9_uni_pvt *cpu;
$end;
$component("axi");
AXI_BUS_pvt *axi;
$end;
$component("video_mem");
MEMORY_pvt *video_mem;
$end;
$component("low_mem");
MEMORY_pvt *low_mem;
$end;
$component("high_mem");
MEMORY_pvt *high_mem;
$end;
$component("lcd");
PL110_LCD_pvt *lcd;
$end;
  $fields_end;
  $vlnv_decl_begin;
public:
const char* m_library;
const char* m_vendor;
const char* m_version;
  $vlnv_decl_end;
};
$module_end;