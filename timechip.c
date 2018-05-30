////////////////////////////////////////////////////////////////////////////
////                              NJU6355.C                             ////
////                     Driver for Real Time Clock                     ////
////                                                                    ////
////  rtc_init()                                   Call after power up  ////
////                                                                    ////
////  rtc_set_datetime(day,mth,year,dow,hour,min)  Set the date/time    ////
////                                                                    ////
////  rtc_get_date(day,mth,year,dow)               Get the date         ////
////                                                                    ////
////  rtc_get_time(hr,min,sec)                     Get the time         ////
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

#ifndef RTC_DATA

#define RTC_DATA  PIN_B6
#define RTC_CLK   PIN_B7
#define RTC_CE    PIN_B2
#define RTC_IO    PIN_B4
#endif

void rtc_init()
   {
      output_low(RTC_CE);
      output_low(RTC_IO);
   }

void write_rtc_byte(BYTE data_byte, BYTE number_of_bits)
   {
      BYTE i;

      for(i=0; i<number_of_bits; ++i)
         {
            if((data_byte & 1)==0)
               output_low(RTC_DATA);
            else
               output_high(RTC_DATA);

            data_byte=data_byte>>1;
            output_high(RTC_CLK);
            output_low(RTC_CLK);
         }
   }


BYTE read_rtc_byte(BYTE number_of_bits)
   {
      BYTE i,data;

      for(i=0;i<number_of_bits;++i)
         {
            output_high(RTC_CLK);
            shift_right(&data,1,input(RTC_DATA));
            output_low(RTC_CLK);
         }
      return(data);
   }


void rtc_set_datetime(  BYTE hour, BYTE min)
   {

      output_low(RTC_CLK);
      output_high(RTC_IO);
      output_high(RTC_CE);

      write_rtc_byte(hour,8);
      write_rtc_byte(min,8);

      output_low(RTC_CE);
      output_low(RTC_IO);
   }


void rtc_get_time(BYTE& hr, BYTE& min, BYTE& sec)
   {
      output_low(RTC_CLK);
      output_low(RTC_IO);
      output_high(RTC_CE);
      read_rtc_byte(8*3+4);
      hr=read_rtc_byte(8);
      min=read_rtc_byte(8);
      sec=read_rtc_byte(8);

      output_low(RTC_CE);
      output_low(RTC_IO);
   }
