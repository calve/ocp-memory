#include "systemc.h"

SC_MODULE (myownram) {
    sc_out<sc_uint<16> > address_bus;
    sc_inout<sc_uint<16> > data_bus;
    sc_in<bool> read_signal;
    sc_in<bool> write_signal;
    sc_lv<16> ram_data[256];
    int current_data;
    int current_addr;

    void read_data() {
        if (read_signal && !write_signal){
            data_bus.write(ram_data[address_bus.read()]);
            cout <<"read data : " << data_bus << endl;
        } else {
            data_bus.write(0);
        }
    };

    void write_data() {
        if (!read_signal && write_signal){
            current_data = data_bus.read();
            current_addr = address_bus.read();
            cout<<"writing data " << current_data << " at " << current_addr << endl;
            ram_data[current_addr] = current_data;
            data_bus.write(current_data);
        }
    };

    SC_CTOR(myownram)
    {
        SC_METHOD(read_data);
        sensitive << address_bus << read_signal << write_signal;
        SC_METHOD(write_data);
        sensitive << address_bus << read_signal << write_signal << data_bus;
    }
};
