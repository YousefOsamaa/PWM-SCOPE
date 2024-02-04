//#include "../mcal/sreg/sreg_interface.h"
//#include "../mcal/dio/dio_interface.h"
//#include "../hal/nokia5110/nokia5110_interface.h"
//#include <util/delay.h>
//
//
//void main(void)
//{
//
	//
	////initializaions
	//nokia5110_enu_initialization();
//
	//// nokia5110_enu_drawcharacter(0x1e, 0,0 , nokia5110_black_colour,1,1);
	//// nokia5110_enu_drawcharacter(0x1f, 8,0 , nokia5110_black_colour,1,1);
	//// nokia5110_enu_drawcharacter(0xe, 16,0 , nokia5110_black_colour,1,1);
	//nokia5110_enu_drawcharacter(234, 20, 37, nokia5110_black_colour);
	//
	//
//
	//while(1)
	//{
//
	//}
//
//
	//
//}
//
//// void main()
//// {
//// 	u8 local_u8_data = 0, local_u8_spi_state, local_u16_counter = 200, local_u16_counter2 = 0, local_u8_ss = dio_high;
//// 	u8 local_u8_pinvalue = dio_high;
//// 	u8 local_u8_dataold = 256;
//
	//
//// 	#if code == master
//// 		dio_enu_setpindiretion(dio_pin_group_b, dio_pin_5, dio_pin_write); //mosi as output 
//// 		dio_enu_setpindiretion(dio_pin_group_b, dio_pin_7, dio_pin_write); //sck  as output
//
//// 		dio_enu_setpindiretion(dio_pin_group_a, dio_pin_1, dio_pin_read ); //pb 
//
//// 		dio_enu_setpinvalue(slave_1_group, slave_1_pin, dio_high); //setting slave_1 as high
//// 		dio_enu_setpindiretion(slave_1_group, slave_1_pin, dio_pin_write);//configuring slave_1 as output
//// 		_delay_ms(5000);
//
//// 	#elif cpde == slave
//
//// 		dio_enu_setpindiretion(dio_pin_group_b, dio_pin_6, dio_pin_write); //miso as output
//
//// 		local_u8_data = 1;
//
//// 	#endif
//
//
//// 	//initializations
//// 	spi_enu_initialization();
//// 	lcd_enu_initialization();
//
//// 	sreg_vid_enablebiti();
//
//// 	while(1)
//// 	{
//// 		#if code == master
//
//// 			dio_enu_getpinvalue(dio_pin_group_a, dio_pin_1, &local_u8_pinvalue ); //getting pb value
					//
//// 			spi_enu_getcommstate(&local_u8_spi_state);
				//
//// 			if((local_u8_spi_state == spi_free) && (local_u8_pinvalue == dio_low)) //communication condition
//// 			{
//// 				local_u8_data++;
//
//// 				dio_enu_setpinvalue(slave_1_group, slave_1_pin, dio_low); //holding ss low
				//
//// 				spi_enu_mastersend(local_u8_data); //sending data via spi if loc_u8_state is spi_free only
//// 			} 
			//
//// 			spi_enu_getcommstate(&local_u8_spi_state);
			//
//// 			if(local_u8_spi_state == spi_free) //checking if the spi finished sending the data
//// 			{	
//// 				dio_enu_setpinvalue(slave_1_group, slave_1_pin, dio_high); //holding ss high
//// 			}
//
//// 			local_u16_counter++;
//
//// 		#else
//
//// 			dio_enu_getpinvalue(dio_pin_group_b, dio_pin_4, &local_u8_ss);
//
//// 			if(local_u8_ss == dio_low)
//// 			{
//// 				spi_enu_setcommstatebusy();
//// 			}
			//
//// 			spi_enu_slavereceive(&local_u8_data);
//// 		#endif
//
//// 		// lcd_enu_clearpage(lcd_page_1);
//// 		lcd_enu_sendstring("                ");
//// 		lcd_enu_writeintegernum(local_u8_data, lcd_row_1, lcd_column_1, lcd_page_1);
//
//// 	}
//
//// }
//
////  void main()
////  {
////  	//variables	
////  	f32 local_af32_signalsparameters[2] = {0}; //an array to place signal parameters in [0] period and [1] duty
////  	f32 local_f32_frequencyhz;
////  	f32 local_f32_dutypercentage;
////  	u8 local_u8_systemstate = 0xff;
//
//
//
////  	//initializations
////  	lcd_enu_initialization();
	//
////  	dio_enu_setpindiretion(dio_pin_group_c, dio_pin_1, dio_pin_write);
//
////  	icu_enu_initialization();
//
//
////   	// printing the display screen
////  	lcd_enu_gotoposition(lcd_row_1,lcd_column_1,lcd_page_1);
////  	lcd_enu_sendstring("freq: ");
////  	lcd_enu_gotoposition(lcd_row_1,lcd_column_15,lcd_page_1);
////  	lcd_enu_sendstring("hz");
//
////  	lcd_enu_gotoposition(lcd_row_2,lcd_column_1,lcd_page_1);
////  	lcd_enu_sendstring("duty: ");
////  	lcd_enu_gotoposition(lcd_row_2,lcd_column_15,lcd_page_1);
////  	lcd_enu_sendstring("%");
//
//
//
////  	// enabling gie
////  	sreg_vid_enablebiti();
//
	//
//
//
//
////  	icu_enu_startcapture();
////  	//superloop
////  	while(1)
////  	{
//
////  		icu_enu_calculateparameters(local_af32_signalsparameters); //calculating parameters
		//
////  		local_f32_frequencyhz = local_af32_signalsparameters[0];
////  		local_f32_dutypercentage = local_af32_signalsparameters[1];
		//
////  		lcd_enu_writefloatnum(local_af32_signalsparameters[0], lcd_row_1, lcd_column_8, lcd_page_1);
////  		lcd_enu_writefloatnum(local_f32_dutypercentage,lcd_row_2,lcd_column_8,lcd_page_1);	
////  	}
////  }
//
//
//
//// void main()
//// {
	//
//// 	f32 local_af32_signalsparameters[2] = {0}; //an array to place signal parameters in [0] period and [1] duty
//// 	f32 local_f32_frequencyhz;
//// 	f32 local_f32_dutypercentage;
//// 	u8 local_u8_systemstate = 0xff;
//
//// 	lcd_enu_initialization();//initializing lcd
	//
//
//// 	//icu_enu_initialization();//initialzing icu
	//
//
//// 	// printing the display screen
//// 	// lcd_enu_gotoposition(lcd_row_1,lcd_column_1,lcd_page_1);
//// 	// lcd_enu_sendstring("freq: ");
//// 	// lcd_enu_gotoposition(lcd_row_1,lcd_column_15,lcd_page_1);
//// 	// lcd_enu_sendstring("hz");
//
//// 	// lcd_enu_gotoposition(lcd_row_2,lcd_column_1,lcd_page_1);
//// 	// lcd_enu_sendstring("duty: ");
//// 	// lcd_enu_gotoposition(lcd_row_2,lcd_column_15,lcd_page_1);
//// 	// lcd_enu_sendstring("%");
//
//// 	//enabling gie
//// 	sreg_vid_enablebiti();
//
	//
//// 	u16 local_u16_test = 0;
//
//// 	//icu_enu_startcapture();
//// 	while(1)
//// 	{
		//
//// 		// icu_enu_calculateparameters(local_af32_signalsparameters); //calculating parameters
		//
//// 		// local_f32_frequencyhz = local_af32_signalsparameters[0];
//// 		// local_f32_dutypercentage = local_af32_signalsparameters[1];
		//
//// 		// lcd_enu_writefloatnum(local_af32_signalsparameters[0], lcd_row_1, lcd_column_8, lcd_page_1);
//// 		// lcd_enu_writefloatnum(local_f32_dutypercentage,lcd_row_2,lcd_column_8,lcd_page_1);	
//// 	}
//// }
//
//
//
//
//
//
//// void send (void* copy_pvid_parameters)
//// {
//// 	u8 local_u8_flag = *(u8*)(copy_pvid_parameters);
//
//// 	local_u8_flag = true;
//// }
//// int main()
//// {
//// 	u8 local_au8_string [] = "h";
//// 	u8 local_u8_flag = false;
//
//// 	//initializng usart
//// 	usart_enu_initialization();
//
//// 	//setting callback function
//// 	u8 flag = usart_enu_setcallback(send, &local_u8_flag);
//
//// 	while(1)
//// 	{
//// 		_delay_ms(5000);
//// 		usart_enu_senddata(65);
//// 	}
//
//
	//// dio_enu_setpindiretion(0,0,1);
//
	//// if(flag == es_out_of_range)
	//// {
	//// 	dio_enu_getpinvalue(0,0,1);
	//// }
	//// else
	//// {
	//// 	dio_enu_setpinvalue(0,0,0);
	//// }
//
	//// //usart_enu_senddata(0xff);
//
	//// while(1)
	//// {
	//// 	u8 i = 5;
	//// 	if(local_u8_flag)
	//// 	{
	//// 		//usart_enu_sendstring(local_au8_string);
	//// 		usart_enu_senddata(i);
//
	//// 		local_u8_flag = false;
//
	//// 		i++;
	//// 	}
	//// }
//
	////return 0;
////}
//
//
//// typedef struct
//// {
//// 	u16 count;
//// 	u8 flag;
//
//// }count_t;
//
//// #define count_d ((count_t*)(copy_pvid_parameters))->count
//// #define flag_d ((count_t*)(copy_pvid_parameters))->flag
//
//// void tog (void* copy_pvid_parameters)
//// {
//// 	count_t* local_pstr_parameterspointer =  (count_t*)(copy_pvid_parameters);
//
	//
//// 	(local_pstr_parameterspointer->count)++;
//
//// 	if(local_pstr_parameterspointer->count == 4883)
//// 	{
//// 		local_pstr_parameterspointer->flag = true;
//// 	}
//
//// 	// dio_enu_togglepinvalue(dio_pin_group_a,dio_pin_0);
//
	//
	//
//
//// }
//
//
//
//
//
//
//
//
//
//
//
//
//
//// int main()
//// {
//// 	count_t local_str_timercount = {48 , false};
//
//// 	dio_enu_setpindiretion(dio_pin_group_a, dio_pin_0, dio_pin_write);
//// 	dio_enu_setpinvalue(dio_pin_group_a, dio_pin_0, dio_low);
//
//// 	//initializing oc0 pin
//// 	dio_enu_setpindiretion(dio_pin_group_b, dio_pin_3, dio_pin_write);
//
//// 	//initializing led pin
//// 	dio_enu_setpindiretion(dio_pin_group_b, dio_pin_0, dio_pin_write);
//// 	dio_enu_setpinvalue(dio_pin_group_b, dio_pin_0, dio_low);
//
//
//// 	//initializing timer
//// 	timer_enu_initialization();
//
//// 	//setting isr
//// 	timer_enu_setcallback(timer_0, timer_normal, tog, &local_str_timercount);
//
//// 	//setting gie
//// 	sreg_vid_enablebiti();
//
//// 	while (1)
//// 	{
//// 		if(local_str_timercount.flag)
//// 		{
//// 			dio_enu_togglepinvalue(dio_pin_group_b, dio_pin_0);
//
//// 			local_str_timercount.count = 48;
//
//// 			local_str_timercount.flag = false;
//// 		}
//// 	}
	//
//
//// 	return 0;
//// }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////counter code
//// typedef struct 
//// {
//// 	u8 flag;
//// }counter_t;
//
//// void loc_vid_maximumreached(void* copy_pvid_parameterspointer)
//// {
//// 	((counter_t*)copy_pvid_parameterspointer)->flag = true;
//// }
//
//// int main (void)
//// {
	//
//// 	counter_t local_str_counter = {false};
//// 	u16 local_u8_count;
//
	//
//
//// 	//placing '10' value in ocr0 register
//// 	timer_enu_setocrxvalue(timer_0,10);
//
//// 	//initializing timer
//// 	timer_enu_initialization();
//
//// 	//initializing timer call back function for timer/counter 0 compare match
//// 	timer_enu_setcallback(timer_0, timer_ctc, loc_vid_maximumreached, &local_str_counter);
	//
//// 	//lcd initialization
//// 	lcd_enu_initialization();
//
//// 	//setting gie
//// 	sreg_vid_enablebiti();
//
//// 	//configuring t0 pin 
//// 	dio_enu_setpindiretion(dio_pin_group_b, dio_pin_0, dio_pin_read);
//// 	dio_enu_setpinvalue(dio_pin_group_b, dio_pin_0, dio_float);
//
//// 	while (1)
//// 	{
//// 		//reading count
//// 		timer_enu_readtcntxvalue(timer_0,&local_u8_count);
//
//// 		lcd_enu_writeintegernum(local_u8_count,lcd_row_1,lcd_column_1,lcd_page_1);
//
//// 		if(local_str_counter.flag)
//// 		{
//// 			lcd_enu_gotoposition(lcd_row_1,lcd_column_1,lcd_page_1);
//
//// 			lcd_enu_sendstring("maximum reached");
			//
//// 			_delay_ms(1000);
//
//// 			local_str_counter.flag = false;
//// 		}
//
//// 	}
//
//
//
//// 	return 0;
//// }
