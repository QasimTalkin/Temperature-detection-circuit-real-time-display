////////////////////////////////////////////////////////////////////////////
////   Library for a Dallas 1621 Temperature chip                       ////
////                                                                    ////
////   init_temp();          Call before the other functions are used   ////
////                                                                    ////
////   d = read_high_temp(); Read the temperature in degrees F (0-255)  ////
////                                                                    ////
////   d = read_low_temp();  Read the temp in degrees F (-67 to 127)    ////
////                                                                    ////
////   d = read_full_temp(); Read the temp in degrees F (-67 to 257)    ////
////                                                                    ////
////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////


#ifndef DAL_SCL
#define DAL_SCL PIN_B0
#define DAL_SDA PIN_B1
#endif

#define read_temp    read_high_temp // for backwards compatability

#use i2c(master,sda=DAL_SDA, scl=DAL_SCL)


void temp_config(BYTE data,int address)// adress declarion 
{

   i2c_start();
   i2c_write(address); //  i have used address so as to use any value.
   i2c_write(0xac);
   i2c_write(data);
   i2c_stop();
}


void init_temp(int address) // define address
{
   output_high(DAL_SDA);
   output_high(DAL_SCL);
   i2c_start();
   i2c_write(address);    // write the address value
   i2c_write(0x51);
   i2c_stop();
   temp_config(0xc,address);  // configure address
}


signed long read_full_temp(int address) {  // Returns hundreths of degrees F (-67 to 257)
   signed int  datah, datal;
   signed long data;

   i2c_start();
   i2c_write(address); //  i have used address so as to use any value.
   i2c_write(0xaa);
   i2c_start();
   i2c_write(address+1);  // add 1 to the original address
   datah=i2c_read();
   datal=i2c_read(0);
   i2c_stop();

   data=(signed long)datah*100;
   data=data+(((datal >> 4 )*(long)50)/16);
   data=data*9;
   data = (data / 5) + 3200;

   return(data);
}


