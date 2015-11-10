#include "systemc.h"

SC_MODULE (myownram) {
    sc_out<sc_uint<16> > address_bus;
    sc_inout<sc_uint<16> > data_bus;
    sc_in<bool> read_signal;
    sc_in<bool> write_signal;
    sc_lv<16> ram_data[256];
    int current_data;
    int current_addr;

    void process_data() {
        current_data = data_bus.read();
        current_addr = address_bus.read();
        if (read_signal && !write_signal){
            data_bus.write(ram_data[address_bus.read()]);
            cout <<"read data : " << data_bus << " at " << current_addr << endl;
        }
        else if (!read_signal && write_signal){
            cout<<"writing data " << current_data << " at " << current_addr << endl;
            ram_data[current_addr] = current_data;
            data_bus.write(current_data);
        }
    };

    SC_CTOR(myownram)
    {
        SC_METHOD(process_data);
        sensitive << address_bus << read_signal << write_signal << data_bus;
    }
};
