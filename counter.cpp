#include "systemc.h"

SC_MODULE (counter) {
    sc_in_clk clock;
    sc_in<bool> reset;
    sc_in<bool> enable;
    sc_out<sc_uint<4> > counter_out;

    sc_uint<4> count;         // Internal count

    void incr () {
        if (reset.read() == 1){
            count = 0;
        }
        else if (enable.read() == 1) {
            count = count + 1;
            // Print to sdout
            cout<<"@" << sc_time_stamp() <<"Increment counter" << counter_out.read() << endl;
        }
        counter_out.write(count);
    }

    SC_CTOR(counter) {
        cout<<"Executing new"<<endl;
        SC_METHOD(incr);
        sensitive << reset;
        sensitive << clock.pos();

    }
};
