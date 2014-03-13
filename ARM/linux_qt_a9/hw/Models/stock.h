#pragma once
#include "mgc_vista_schematics.h"
$includes_begin;
#include <systemc.h>
#include "APB_model.h"
#include "models_catalogue.h"
#include "MEMORY_model.h"
#include "AXI_APB_model.h"
#include "AXI_model.h"
#include "PL111_model.h"
#include "A9x1_model.h"
#include "LAN9118_model.h"
#include "EHCI_model.h"
$includes_end;

$module_begin("stock");
SC_MODULE(stock) {
public:
  stock(::sc_core::sc_module_name name):
    ::sc_core::sc_module(name)
    $initialization_begin
$init("console0"),
console0(0)
$end
$init("ram"),
ram(0)
$end
$init("bridge"),
bridge(0)
$end
$init("uart0"),
uart0(0)
$end
$init("cpu"),
cpu(0)
$end
$init("axi_bus"),
axi_bus(0)
$end
$init("apb_bus"),
apb_bus(0)
$end
$init("lcd"),
lcd(0)
$end
$init("usb"),
usb(0)
$end
$init("ethernet"),
ethernet(0)
$end
    $initialization_end
{
    $elaboration_begin;
$create_component("console0");
console0 = new UART_Visualization_Middleware_pvt("console0");
$end;
$create_component("ram");
ram = new MEMORY_pvt("ram");
$end;
$create_component("bridge");
bridge = new AXI_APB_pvt("bridge");
$end;
$create_component("uart0");
uart0 = new UART_PL011_pvt("uart0");
$end;
$create_component("cpu");
cpu = new A9x1_pvt("cpu");
$end;
$create_component("axi_bus");
axi_bus = new AXI_pvt("axi_bus");
$end;
$create_component("apb_bus");
apb_bus = new APB_pvt("apb_bus");
$end;
$create_component("lcd");
lcd = new PL111_pvt("lcd");
$end;
$create_component("usb");
usb = new EHCI_pvt("usb");
$end;
$create_component("ethernet");
ethernet = new LAN9118_pvt("ethernet");
$end;
$bind("console0->nUARTRTS","uart0->nUARTCTS");
vista_bind(console0->nUARTRTS, uart0->nUARTCTS);
$end;
$bind("axi_bus->ram_master","ram->slave");
vista_bind(axi_bus->ram_master, ram->slave);
$end;
$bind("axi_bus->bridge_master","bridge->slave");
vista_bind(axi_bus->bridge_master, bridge->slave);
$end;
$bind("uart0->UARTTXD","console0->UARTRXD");
vista_bind(uart0->UARTTXD, console0->UARTRXD);
$end;
$bind("cpu->master0","axi_bus->a9_slave0");
vista_bind(cpu->master0, axi_bus->a9_slave0);
$end;
$bind("console0->UARTTXD","uart0->UARTRXD");
vista_bind(console0->UARTTXD, uart0->UARTRXD);
$end;
$bind("cpu->master1","axi_bus->a9_slave1");
vista_bind(cpu->master1, axi_bus->a9_slave1);
$end;
$bind("uart0->nUARTRTS","console0->nUARTCTS");
vista_bind(uart0->nUARTRTS, console0->nUARTCTS);
$end;
$bind("bridge->master","apb_bus->bus_slave");
vista_bind(bridge->master, apb_bus->bus_slave);
$end;
$bind("uart0->UARTINTR","cpu->irq_0");
vista_bind(uart0->UARTINTR, cpu->irq_0);
$end;
$bind("axi_bus->lcd_master","lcd->ctrl_slave");
vista_bind(axi_bus->lcd_master, lcd->ctrl_slave);
$end;
$bind("lcd->master","axi_bus->lcd_slave");
vista_bind(lcd->master, axi_bus->lcd_slave);
$end;
$bind("axi_bus->ethernet_master","ethernet->host");
vista_bind(axi_bus->ethernet_master, ethernet->host);
$end;
$bind("ethernet->irq","cpu->irq_1");
vista_bind(ethernet->irq, cpu->irq_1);
$end;
$bind("usb->irq","cpu->irq_2");
vista_bind(usb->irq, cpu->irq_2);
$end;
$bind("usb->dma_port","axi_bus->usb_slave");
vista_bind(usb->dma_port, axi_bus->usb_slave);
$end;
$bind("axi_bus->usb_master","usb->host");
vista_bind(axi_bus->usb_master, usb->host);
$end;
$bind("apb_bus->uart0_master","uart0->AMBA_APB");
vista_bind(apb_bus->uart0_master, uart0->AMBA_APB);
$end;
    $elaboration_end;
  $vlnv_assign_begin;
m_library = "Models";
m_vendor = "";
m_version = "";
  $vlnv_assign_end;
  }
  ~stock() {
    $destructor_begin;
$destruct_component("console0");
delete console0; console0 = 0;
$end;
$destruct_component("ram");
delete ram; ram = 0;
$end;
$destruct_component("bridge");
delete bridge; bridge = 0;
$end;
$destruct_component("uart0");
delete uart0; uart0 = 0;
$end;
$destruct_component("cpu");
delete cpu; cpu = 0;
$end;
$destruct_component("axi_bus");
delete axi_bus; axi_bus = 0;
$end;
$destruct_component("apb_bus");
delete apb_bus; apb_bus = 0;
$end;
$destruct_component("lcd");
delete lcd; lcd = 0;
$end;
$destruct_component("usb");
delete usb; usb = 0;
$end;
$destruct_component("ethernet");
delete ethernet; ethernet = 0;
$end;
    $destructor_end;
  }
public:
  $fields_begin;
$component("console0");
UART_Visualization_Middleware_pvt *console0;
$end;
$component("ram");
MEMORY_pvt *ram;
$end;
$component("bridge");
AXI_APB_pvt *bridge;
$end;
$component("uart0");
UART_PL011_pvt *uart0;
$end;
$component("cpu");
A9x1_pvt *cpu;
$end;
$component("axi_bus");
AXI_pvt *axi_bus;
$end;
$component("apb_bus");
APB_pvt *apb_bus;
$end;
$component("lcd");
PL111_pvt *lcd;
$end;
$component("usb");
EHCI_pvt *usb;
$end;
$component("ethernet");
LAN9118_pvt *ethernet;
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