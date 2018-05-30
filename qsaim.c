#include<the_file.c>
void main()
   {
   char string_hour;
   char string_min;
   char string_sec;
   int hour, min, sec,last_sec;
   unsigned long fval,cval;
      //byte sec2;
      rtc_init ();   //initiate real time clock
      rtc_set_datetime (hour, min );
      while(1)

      { // start while

      rtc_get_time(hour, min, sec); // get time
      printf(lcd_putc,"\n%02u:%02u:%02u\n", hour, min, sec );//  Display time

    if(input(Pin_A4)) // if pin A4 is not pressed on Board
          {
               lcd_init();  //  // initiate lcd
               init_temp(0x90);// initiate temp for 90 mapping
                  fval = read_full_temp (0x90); // set fval equal to full temp
                  fval  /= 100;  //  fval equal to 100
                  printf(lcd_putc,"\fIN.F%3.2ld",fval );  //  show temperature on lcd in F
                  cval=5*(fval -32)/9;   // convert temperature in celcius
                  printf(lcd_putc,"in.c%3.2ld",cval);   //  show temperature on lcd in C
                  output_high(pin_e1),output_low(Pin_a1); // output Led at E1
               }
           else
           {
                   lcd_init();    // initiate lcd
                   init_temp(0x92);   // initiate temp for 92 mapping
                   fval  = read_full_temp (0x92); // set fval equal to full temp
                   fval  /= 100; //  fval equal to 100
                   printf(lcd_putc,"\fot.f%3.2ld",fval );  //  show temperature on lcd in F
                   cval =5*(fval -32)/9; // convert temperature in celcius
                   printf(lcd_putc,"ot.c%3.2ld",fval );  //  show temperature on lcd in C
                   output_high(pin_a1),output_low(Pin_e1);   // output Led at E1
           }

              if(fval  <=80 )   // if value is less then or equal to 80
                  output_low(pin_A5),output_low(pin_b5);  //  Light LED at pin A5 and B5
                  else
                  output_high(pin_a5),output_high(Pin_b5); // turn off LED and turn on THE MOTOR

                  if (fval <=75)         //  if temperature is less then or equal to 75
                  output_high(pin_a2),output_low(pin_a3);//  Light LED at pin A3
              else
                  output_high(pin_a3),output_low(pin_a2);//  Light LED at pin A2


   }// end of while

   }// end main
