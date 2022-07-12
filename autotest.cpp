#include "PlutoDevice.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    char device_uri[] = "ip:192.168.2.1";
    size_t rx_buff_size = 4096;
    size_t tx_buff_size = 4096;

    int return_code;
    printf("\n#TEST: This is the autotest program for PlutoDevice library.\n");
    printf("#TEST: \tAuthor: Umaru Aya.\n");
    printf("#TEST: \tLicense: BSD 3-Clause.\n");
    printf("#TEST: Test start.\n");
    printf("= = = = = = = = = = = = = = = =\n");
    pluto_sdr pluto;

    printf("#Step 0: Message generator test, please check if the following 6 lines are same between each 2 lines.\n");
    printf("#Step 0: \tIf the message generator broken, you can not read the debug information from PlutoDevice library.\n");
    printf("#Step 0: \t#INFO: ADALM-Pluto Test Program by Umaru Aya.\n");
    pluto.pluto_message_generate("ADALM-Pluto Test Program by Umaru Aya.", 0);
        printf("%s\n", pluto.pluto_message.c_str());
    printf("#Step 0: \t#WARN: ADALM-Pluto Test Program by Umaru Aya.\n");
    pluto.pluto_message_generate("ADALM-Pluto Test Program by Umaru Aya.", 1);
        printf("%s\n", pluto.pluto_message.c_str());
    printf("#Step 0: \t#ERRO: ADALM-Pluto Test Program by Umaru Aya.\n");
    pluto.pluto_message_generate("ADALM-Pluto Test Program by Umaru Aya.", 2);
        printf("%s\n", pluto.pluto_message.c_str());
    printf("#WARN: This program can not check if this step passed, please check it by yourself.\n");
    printf("= = = = = = = = = = = = = = = =\n");


    printf("#Step 1: Unit tools test, .\n");
    printf("#Step 1: \tIf the unit tools broken, you can not convert simplified value to completed type.\n");
    if(pluto.pluto_kHz(1.234) != 1234){
        printf("#ERRO: Unit tools pluto_kHz() broken.\n"); return 1;}
    else printf("#INFO: Unit tools pluto_kHz() works fine.\n");
    if(pluto.pluto_MHz(1.234) != 1234000){
        printf("#ERRO: Unit tools pluto_MHz() broken.\n"); return 1;}
    else printf("#INFO: Unit tools pluto_MHz() works fine.\n");
    if(pluto.pluto_GHz(1.234) != 1234000000){
        printf("#ERRO: Unit tools pluto_GHz() broken.\n"); return 1;}
    else printf("#INFO: Unit tools pluto_GHz() works fine.\n");
    printf("#Step 1: Passed.\n");
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 2: Initializers test, please check the following lines when something wrongs.\n");
    printf("#Step 2: \tIf the initializers broken, you can not connect to the broken part of ADALM-Pluto.\n");
    printf("#Step 2: Inilizing ADALM_Pluto from uri: \t%s.\n", device_uri);
    return_code = pluto.pluto_init(device_uri);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_init_sensors();
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_init_receiver(rx_buff_size);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_init_transmitter(tx_buff_size);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    printf("#Step 2: Passed.\n");
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 3: Sensors test, please check the following lines when something wrongs.\n");
    printf("#Step 3: \tIf the sensors broken, you can not check if your ADALM-Pluto is healthy.\n");
    double rf_temp, soc_temp, sys_power, sys_voltage, sys_current;
    return_code = pluto.pluto_get_rf_temp(&rf_temp);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_soc_temp(&soc_temp);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_power(&sys_power);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_voltage(&sys_voltage);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_current(&sys_current);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    printf("#Step 3: Passed, the following is report.\n");
    printf("#Step 3: \tRF chicpset's temperature:\t%lf\t°C\n", rf_temp);
    printf("#Step 3: \tSoC temperature:\t%lf\t°C\n", soc_temp);
    printf("#Step 3: \tSystem power:\t%lf\tW\n", sys_power);
    printf("#Step 3: \tSystem voltage:\t%lf\tV\n", sys_voltage);
    printf("#Step 3: \tSystem current:\t%lf\tA\n", sys_current);
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 4: Buffer test, please check the following lines when something wrongs.\n");
    printf("#Step 4: \tIf the buffer broken, you can not transmit or receive data from the hardware.\n");
    return_code = pluto.pluto_get_rx_data();
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_schedule_tx_buff();
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    printf("#Step 4: Passed, the following is report.\n");
    printf("#Step 4: \tRX buffer start address:\t%lld\t\n",(long long)pluto.pluto_receiver.rx_ptr_start);
    printf("#Step 4: \tRX buffer end address:\t%lld\t\n",(long long)pluto.pluto_receiver.rx_ptr_end);
    printf("#Step 4: \tRX buffer unit size:\t%lld\t\n",(long long)pluto.pluto_receiver.rx_ptr_inc);
    printf("#Step 4: \tTX buffer start address:\t%lld\t\n",(long long)pluto.pluto_transmitter.tx_ptr_start);
    printf("#Step 4: \tTX buffer end address:\t%lld\t\n",(long long)pluto.pluto_transmitter.tx_ptr_end);
    printf("#Step 4: \tTX buffer unit size:\t%lld\t\n",(long long)pluto.pluto_transmitter.tx_ptr_inc);
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 5: RX parameter controller test, please check the following lines when something wrongs.\n");
    printf("#Step 5: \tIf the RX parameter controller broken, you can not config the receiver functions.\n");
    bool set_bool_value0 = false;
    bool get_bool_value0;
    return_code = pluto.pluto_set_rx_en(set_bool_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_rx_is_enable(&get_bool_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_bool_value0 != get_bool_value0){
        printf("#ERRO: RX Enable Status has got wrong value.\n"); return 1;}
    bool set_bool_value1 = false;
    bool get_bool_value1;
    return_code = pluto.pluto_set_rx_fir_en(set_bool_value1);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_rx_fir_is_enable(&get_bool_value1);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_bool_value1 != get_bool_value1){
        printf("#ERRO: RX FIR Filter Enable Status has got wrong value.\n"); return 1;}
    long long set_long_value0 = pluto.pluto_GHz(1.00);
    long long get_long_value0;
    return_code = pluto.pluto_set_rx_freq(set_long_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_rx_freq(&get_long_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value0 != get_long_value0){
        printf("#ERRO: RX Frequency has got wrong value.\n"); return 1;}
    long long set_long_value1 = pluto.pluto_MHz(2.40);
    long long get_long_value1;
    return_code = pluto.pluto_set_rx_samprate(set_long_value1);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_rx_samprate(&get_long_value1);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value1 - 1 != get_long_value1){
        printf("#ERRO: RX Sampling Rate has got wrong value.\n"); return 1;}
    long long set_long_value2 = pluto.pluto_MHz(1.00);
    long long get_long_value2;
    return_code = pluto.pluto_set_rx_bandwidth(set_long_value2);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_rx_bandwidth(&get_long_value2);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value2 != get_long_value2){
        printf("#ERRO: RX Bandwidth has got wrong value.\n"); return 1;}
// This library have not be able to config AGC to Manual mode.
//    long long set_long_value3 = 2;
//    long long get_long_value3;
//    return_code = pluto.pluto_set_rx_gain(set_long_value3);
//        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
//    return_code = pluto.pluto_get_rx_gain(&get_long_value3);
//        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
//    if(set_long_value3 != get_long_value3){
//        printf("#ERRO: RX Gain has got wrong value.\n"); return 1;}
    printf("#Step 5: Passed.\n");
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 6: TX parameter controller test, please check the following lines when something wrongs.\n");
    printf("#Step 6: \tIf the TX parameter controller broken, you can not config the transmitter functions.\n");
    bool set_bool_value2 = true;
    bool get_bool_value2;
    return_code = pluto.pluto_set_tx_en(set_bool_value2);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_is_enable(&get_bool_value2);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_bool_value2 != get_bool_value2){
        printf("#ERRO: TX Enable Status has got wrong value.\n"); return 1;}
    return_code = pluto.pluto_set_tx_en(false);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    bool set_bool_value3 = false;
    bool get_bool_value3;
    return_code = pluto.pluto_set_tx_fir_en(set_bool_value3);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_fir_is_enable(&get_bool_value3);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_bool_value3 != get_bool_value3){
        printf("#ERRO: TX FIR Filter Enable Status has got wrong value.\n"); return 1;}
    long long set_long_value4 = pluto.pluto_GHz(1.00);
    long long get_long_value4;
    return_code = pluto.pluto_set_tx_freq(set_long_value4);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_freq(&get_long_value4);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value4 != get_long_value4){
        printf("#ERRO: TX Frequency has got wrong value.\n"); return 1;}
    long long set_long_value5 = pluto.pluto_MHz(2.40);
    long long get_long_value5;
    return_code = pluto.pluto_set_tx_samprate(set_long_value5);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_samprate(&get_long_value5);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value5 - 1 != get_long_value5){
        printf("#ERRO: TX Sampling Rate has got wrong value.\n"); return 1;}
    long long set_long_value6 = pluto.pluto_MHz(1.00);
    long long get_long_value6;
    return_code = pluto.pluto_set_tx_bandwidth(set_long_value6);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_bandwidth(&get_long_value6);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_long_value6 != get_long_value6){
        printf("#ERRO: TX Bandwidth has got wrong value.\n"); return 1;}
    double set_double_value0 = -1.00;
    double get_double_value0;
    return_code = pluto.pluto_set_tx_gain(set_double_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    return_code = pluto.pluto_get_tx_gain(&get_double_value0);
        printf("%s\n", pluto.pluto_message.c_str()); if(return_code != 0) return 1;
    if(set_double_value0 != get_double_value0){
        printf("#ERRO: TX Gain has got wrong value.\n"); return 1;}
    printf("#Step 6: Passed.\n");
    printf("= = = = = = = = = = = = = = = =\n");

    printf("#Step 7: Parameter limitation test, please check the following lines when something wrongs.\n");
    printf("#Step 7: \tIf this part broken, you can not config the functions correctly.\n");
    if(pluto.pluto_set_tx_freq(0) != 1){
        printf("#ERRO: TX Frequency limitation broken.\n"); return 1;}
    if(pluto.pluto_set_tx_samprate(0) != 1){
        printf("#ERRO: TX Sampling Rate limitation broken.\n"); return 1;}
    if(pluto.pluto_set_tx_bandwidth(0) != 1){
        printf("#ERRO: TX Bandwidth limitation broken.\n"); return 1;}
    if(pluto.pluto_set_tx_gain(0.00) != 1){
        printf("#ERRO: TX Gain limitation broken.\n"); return 1;}
    if(pluto.pluto_set_rx_freq(0) != 1){
        printf("#ERRO: RX Frequency limitation broken.\n"); return 1;}
    if(pluto.pluto_set_rx_samprate(0) != 1){
        printf("#ERRO: RX Sampling Rate limitation broken.\n"); return 1;}
    if(pluto.pluto_set_rx_bandwidth(0) != 1){
        printf("#ERRO: RX Bandwidth limitation broken.\n"); return 1;}
    if(pluto.pluto_set_rx_gain(-3.0) != 1){
        printf("#ERRO: RX Gain limitation broken.\n"); return 1;}
    printf("#Step 7: Passed.\n");
    printf("= = = = = = = = = = = = = = = =\n");

    pluto.pluto_destroy();
        printf("%s\n", pluto.pluto_message.c_str());
    printf("#TEST: All test passed.\n");
    return 0;
}
