#include "systemc.h"
#include "myownram.cpp"
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
    sc_signal<bool> read_signal;
    sc_signal<bool> write_signal;
    sc_signal<sc_uint<4> > counter_out;
    sc_signal<sc_uint<16> > address_bus;
    sc_signal<sc_uint<16> > data_bus;
    int i = 0;

    // Connect the DUT
    counter counter("my_counter");
    counter.clock(clock);
    counter.reset(reset);
    counter.enable(enable);
    counter.counter_out(counter_out);

    myownram ram0("ram0");
    ram0.address_bus(address_bus);
    ram0.data_bus(data_bus);
    ram0.read_signal(read_signal);
    ram0.write_signal(write_signal);

    sc_start(1.0, SC_NS);

    // Set trace up
    sc_trace_file *wf = sc_create_vcd_trace_file("counter_trace");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, enable, "enable");
    sc_trace(wf, counter_out, "counter_out");
    sc_trace(wf, write_signal, "write_signal");
    sc_trace(wf, read_signal, "read_signal");
    sc_trace(wf, address_bus, "address_bus");
    sc_trace(wf, data_bus, "data_bus");

    // Initialize environment
    reset = 0;
    enable = 1;
    write_signal = 0;
    read_signal = 0;
    data_bus = 0;
    write_signal = 1;
    // try a first write
    for (i=0; i<5; i++){
        cout<< "try write" << endl;
        data_bus = i;
        address_bus = i*2;
        sc_start(1.0, SC_NS);
    }

    write_signal = 0;
    read_signal = 1;
    sc_start(1.0, SC_NS);
    for (i=4; i>=0; i--){
        cout<< "try read" << endl;
        address_bus = i*2;
        sc_start(1.0, SC_NS);
    }
    read_signal = 0;

    return 0;
}
