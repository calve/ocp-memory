#include "systemc.h"
#include "stim.h"
#include "exor2.h"
#include "mon.h"
#include "ram.h"
#include "counter.cpp"

// void next_cycle(sc_signal<bool> &signal_clk)
// {
//     signal_clk = false;
//     sc_start(1.0, SC_NS1, SC_N);
//     signal_clk = true;
//     sc_start(1.0, SC_NS1, SC_N);
// }


// int sc_main(int argc, char* argv[])
// {
//     int i;
//     sc_signal<sc_bv<8> > address_bus_signal;
//     sc_signal<sc_bv<16> > data_bus_signal;
//     sc_signal<bool> clk_signal;
//     sc_signal<bool> read_signal;
//     sc_signal<bool> write_signal;

//     sc_trace_file *trace_file;
//     trace_file = sc_create_vcd_trace_file("ram_trace");
//     sc_trace(trace_file, clk_signal, "clk");
//     sc_trace(trace_file, read_signal, "read_signal");
//     sc_trace(trace_file, write_signal, "write_signal");

//     ram *ram0;
//     ram0->address_bus(address_bus_signal);
//     ram0->data_bus(data_bus_signal);
//     ram0->read_signal(read_signal);
//     ram0->write_signal(write_signal);

// }

int sc_main(int argc, char*argv[]) {
    sc_signal<bool> clock;
    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4> > counter_out;
    int i = 0;

    // Connect the DUT
    counter counter("my_counter");
    counter.clock(clock);
    counter.reset(reset);
    counter.enable(enable);
    counter.counter_out(counter_out);

    sc_start(1.0, SC_NS);

    sc_trace_file *wf = sc_create_vcd_trace_file("counter_trace");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, enable, "enable");
    sc_trace(wf, counter_out, "counter_out");

    // Initialize environment
    reset = 0;
    enable = 1;
    for (i=0; i<5; i++){
        clock = 0;
        sc_start(1.0, SC_NS);
        clock = 1;
        sc_start(1.0, SC_NS);
    }
    // Initialize environment
    reset = 1;
    for (i=0; i<5; i++){
        clock = 0;
        sc_start(1.0, SC_NS);
        clock = 1;
        sc_start(1.0, SC_NS);
    }
    reset = 0;
    for (i=0; i<5; i++){
        clock = 0;
        sc_start(1.0, SC_NS);
        clock = 1;
        sc_start(1.0, SC_NS);
    }
    return 0;
}
