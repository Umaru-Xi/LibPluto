#include "PlutoDevice.h"

long long pluto_sdr::pluto_kHz(double kHz)
{
    return kHz * 1000;
}

long long pluto_sdr::pluto_MHz(double MHz)
{
    return MHz * 1000000;
}

long long pluto_sdr::pluto_GHz(double GHz)
{
    return GHz * 1000000000;
}

int pluto_sdr::pluto_set_tx_samprate(long long tx_samprate)
{
    if(tx_samprate < 2083334 || tx_samprate > 61439999)
    {
        pluto_message_generate("TX Sampling Rate must in [2083334, 61439999].", 2);
        return 1;
    }
    pluto_message_generate("TX Sampling Rate has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", true),
                "sampling_frequency", tx_samprate);
}

int pluto_sdr::pluto_set_tx_bandwidth(long long tx_bandwidth)
{
    if(tx_bandwidth < 200001 || tx_bandwidth > 39999999)
    {
        pluto_message_generate("TX Bandwidth must in [200001, 39999999].", 2);
        return 1;
    }
    pluto_message_generate("TX Bandwidth has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", true),
                "rf_bandwidth", tx_bandwidth);
}

int pluto_sdr::pluto_set_tx_gain(double tx_gain)
{
    if(tx_gain < -90.00 || tx_gain > -0.25)
    {
        pluto_message_generate("TX Gain must in [-90.00 : 0.25 : -0.25].", 2);
        return 1;
    }
    pluto_message_generate("TX Gain has been set.", 0);
    return iio_channel_attr_write_double(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", true),
                "hardwaregain", tx_gain);
}

int pluto_sdr::pluto_set_tx_fir_en(bool is_enable)
{
    int return_code = iio_channel_attr_write_bool(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", true),
                "filter_fir_en", is_enable);
    if(return_code == 0) pluto_message_generate("TX FIR Filter has been set.", 0);
    else pluto_message_generate("Can not set TX FIR Filter.", 2);
    return return_code;
}

int pluto_sdr::pluto_set_tx_freq(long long tx_freq)
{
    if(tx_freq < 46875002 || tx_freq > 5999999999)
    {
        pluto_message_generate("TX Frequency must in [46875002, 5999999999].", 2);
        return 1;
    }
    pluto_message_generate("TX Frequency has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "altvoltage1", true),
                "frequency", tx_freq);
}

int pluto_sdr::pluto_set_tx_en(bool is_enable)
{
    int return_code = iio_channel_attr_write_bool(
                iio_device_find_channel(pluto_dev.rf_phy, "altvoltage1", true),
                "powerdown", !is_enable);
    if(return_code == 0) pluto_message_generate("TX has been set.", 0);
    else pluto_message_generate("Can not set TX.", 2);
    return return_code;
}

int pluto_sdr::pluto_init_transmitter(size_t samples_cnt)
{
    pluto_dev.tx_dev = iio_context_find_device(pluto_dev.pluto_ctx, "cf-ad9361-dds-core-lpc");
        if(pluto_dev.tx_dev == NULL)
        {
            pluto_message_generate("Can not find TX Core(cf-ad9361-dds-core-lpc).", 2);
            return 1;
        }
    pluto_dev.tx_i = iio_device_find_channel(pluto_dev.tx_dev, "voltage0", true);
        if(pluto_dev.tx_i == NULL)
        {
            pluto_message_generate("Can not find TX Imaginary Channel.", 2);
            return 2;
        }
    pluto_dev.tx_q = iio_device_find_channel(pluto_dev.tx_dev, "voltage1", true);
        if(pluto_dev.tx_q == NULL)
        {
            pluto_message_generate("Can not find TX Real Channel.", 2);
            return 2;
        }
    iio_channel_enable(pluto_dev.tx_i);
    iio_channel_enable(pluto_dev.tx_q);
    pluto_dev.tx_buf = _pluto_create_buffer(pluto_dev.tx_dev, samples_cnt);
        if(pluto_dev.tx_buf == NULL)
        {
            pluto_message_generate("Create TX Buffer failed.", 2);
            return 3;
        }
    pluto_message_generate("Transmitter has been initialized.", 0);
    return 0;
}

int pluto_sdr::pluto_set_rx_fir_en(bool is_enable)
{
    int return_code = iio_channel_attr_write_bool(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", false),
                "filter_fir_en", is_enable);
    if(return_code == 0) pluto_message_generate("RX FIR Filter has been set.", 0);
    else pluto_message_generate("Can not set RX FIR Filter.", 2);
    return return_code;
}

int pluto_sdr::pluto_set_rx_gain(long long rx_gain)
{
    if(rx_gain < -2 || rx_gain > 70)
    {
        pluto_message_generate("RX Gain must in [-2, 70].", 2);
        return 1;
    }
    pluto_message_generate("RX Gain has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", false),
                "hardwaregain", rx_gain);
}

int pluto_sdr::pluto_set_rx_bandwidth(long long rx_bandwidth)
{
    if(rx_bandwidth < 200001 || rx_bandwidth > 55999999)
    {
        pluto_message_generate("RX Bandwidth must in [200001, 55999999].", 2);
        return 1;
    }
    pluto_message_generate("RX Bandwidth has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", false),
                "rf_bandwidth", rx_bandwidth);
}

void pluto_sdr::pluto_message_generate(std::string msg, int code)
{
    if(code < 0 || code > 2)
    {
        pluto_message = "#ERRO: Pluto message generation failed, unknown message code.";
    }
    else
    {
        switch(code)
        {
        case 0:
            pluto_message = "#INFO: ";
            pluto_message.append(msg);
            break;
        case 1:
            pluto_message = "#WARN: ";
            pluto_message.append(msg);
            break;
        case 2:
            pluto_message = "#ERRO: ";
            pluto_message.append(msg);
            break;
        }
    }
    return;
}

int pluto_sdr::pluto_set_rx_samprate(long long samprate)
{
    if(samprate < 2083334 || samprate > 61439999)
    {
        pluto_message_generate("RX Sampling Rate must in [2083334, 61439999].", 2);
        return 1;
    }
    pluto_message_generate("RX Sampling Rate has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "voltage0", false),
                "sampling_frequency", samprate);
}

int pluto_sdr::pluto_set_rx_freq(long long rx_freq)
{
    if(rx_freq < 70000001 || rx_freq > 5999999999)
    {
        pluto_message_generate("RX Frequency must in [70000001, 5999999999].", 2);
        return 1;
    }
    pluto_message_generate("RX Frequency Rate has been set.", 0);
    return iio_channel_attr_write_longlong(
                iio_device_find_channel(pluto_dev.rf_phy, "altvoltage0", true),
                "frequency", rx_freq);
}

int pluto_sdr::pluto_init(char * device_uri)
{
    pluto_dev.pluto_ctx = iio_create_context_from_uri(device_uri);
        if(pluto_dev.pluto_ctx == NULL)
        {
            pluto_message_generate("Can not connect ADALM-Pluto by URI.", 2);
            return 1;
        }
    pluto_dev.rf_phy = iio_context_find_device(pluto_dev.pluto_ctx, "ad9361-phy");
        if(pluto_dev.rf_phy == NULL)
        {
            pluto_message_generate("Can not find RF Chipset(AD936X).", 2);
            return 2;
        }
    pluto_dev.soc_phy = iio_context_find_device(pluto_dev.pluto_ctx, "xadc");
        if(pluto_dev.soc_phy == NULL)
        {
            pluto_message_generate("Can not find Xilinx APSoC(Zynq-70X0).", 2);
            return 2;
        }
    pluto_dev.pwr_phy = iio_context_find_device(pluto_dev.pluto_ctx, "adm1177-iio");
        if(pluto_dev.pwr_phy == NULL)
        {
            pluto_message_generate("Can not find Power Manager Chipset(ADM1177).", 2);
            return 2;
        }
    pluto_message_generate("ADALM-Pluto has been initialized.", 0);
    return 0;
}

int pluto_sdr::pluto_init_receiver(size_t samples_cnt)
{
    pluto_dev.rx_dev = iio_context_find_device(pluto_dev.pluto_ctx, "cf-ad9361-lpc");
        if(pluto_dev.rx_dev == NULL)
        {
            pluto_message_generate("Can not find RX Core(cf-ad936x-lpc).", 2);
            return 1;
        }
    pluto_dev.rx_i = iio_device_find_channel(pluto_dev.rx_dev, "voltage0", false);
        if(pluto_dev.rx_i == NULL)
        {
            pluto_message_generate("Can not find RX Imaginary Channel.", 2);
            return 2;
        }
    pluto_dev.rx_q = iio_device_find_channel(pluto_dev.rx_dev, "voltage1", false);
        if(pluto_dev.rx_q == NULL)
        {
            pluto_message_generate("Can not find RX Real Channel.", 2);
            return 2;
        }
    iio_channel_enable(pluto_dev.rx_i);
    iio_channel_enable(pluto_dev.rx_q);
    pluto_dev.rx_buf = _pluto_create_buffer(pluto_dev.rx_dev, samples_cnt);
        if(pluto_dev.rx_buf == NULL)
        {
            pluto_message_generate("Create RX Buffer failed.", 2);
            return 3;
        }
    pluto_message_generate("Receiver has been initialized.", 0);
    return 0;
}

int pluto_sdr::pluto_schedule_tx_buff()
{
    if(iio_buffer_push(pluto_dev.tx_buf) < 0)
    {
        pluto_message_generate("Schedule TX Buffer failed.", 2);
        return 1;
    }
    pluto_transmitter.tx_ptr_inc = iio_buffer_step(pluto_dev.tx_buf);
    pluto_transmitter.tx_ptr_end = iio_buffer_end(pluto_dev.tx_buf);
    pluto_transmitter.tx_ptr_start = iio_buffer_first(pluto_dev.tx_buf, pluto_dev.tx_i);
    pluto_message_generate("TX Buffer has been scheduled.", 0);
    return 0;
}

int pluto_sdr::pluto_get_rx_data()
{
    if(iio_buffer_refill(pluto_dev.rx_buf) < 0)
    {
        pluto_message_generate("Refill RX Buffer failed.", 2);
        return 1;
    }
    pluto_receiver.rx_ptr_inc = iio_buffer_step(pluto_dev.rx_buf);
    pluto_receiver.rx_ptr_end = iio_buffer_end(pluto_dev.rx_buf);
    pluto_receiver.rx_ptr_start = iio_buffer_first(pluto_dev.rx_buf, pluto_dev.rx_i);
    pluto_message_generate("RX Data has been gotten.", 0);
    return 0;
}

double pluto_sdr::pluto_get_rf_temp()
{
    long long rf_temp_raw;
    double rf_temp;
    iio_channel_attr_read_longlong(pluto_dev.rf_temperature, "input", &rf_temp_raw);
    rf_temp =rf_temp_raw / 1000.0;
    pluto_message_generate("RF Chipset's Temperature has been gotten.", 0);
    return rf_temp;
}

double pluto_sdr::pluto_get_soc_temp()
{
    double soc_temp_scale;
    long long soc_temp_raw, soc_temp_offset;
    iio_channel_attr_read_double(pluto_dev.soc_temperature, "scale", &soc_temp_scale);
    iio_channel_attr_read_longlong(pluto_dev.soc_temperature, "raw", &soc_temp_raw);
    iio_channel_attr_read_longlong(pluto_dev.soc_temperature, "offset", &soc_temp_offset);
    pluto_message_generate("APSoC's Temperature has been gotten.", 0);
    return (soc_temp_raw + soc_temp_offset) * soc_temp_scale / 1000.0;
}

double pluto_sdr::pluto_get_power()
{
    double current, voltage;
    current = pluto_get_current();
    voltage = pluto_get_voltage();
    pluto_message_generate("System Power has been calculated.", 0);
    return current * voltage;
}

double pluto_sdr::pluto_get_voltage()
{
    double voltage_scale;
    long long voltage_raw;
    iio_channel_attr_read_double(pluto_dev.pwr_voltage, "scale", &voltage_scale);
    iio_channel_attr_read_longlong(pluto_dev.pwr_voltage, "raw", &voltage_raw);
    pluto_message_generate("System Voltage has been gotten.", 0);
    return voltage_raw * voltage_scale / 1000.0;
}

double pluto_sdr::pluto_get_current()
{
    double current_scale;
    long long current_raw;
    iio_channel_attr_read_double(pluto_dev.pwr_current, "scale", &current_scale);
    iio_channel_attr_read_longlong(pluto_dev.pwr_current, "raw", &current_raw);
    pluto_message_generate("System Current has been gotten.", 0);
    return current_raw * current_scale / 1000.0;
}

int pluto_sdr::pluto_init_sensors()
{
    pluto_dev.pwr_current =iio_device_find_channel(pluto_dev.pwr_phy, "current0", false);
        if(pluto_dev.pwr_current == NULL)
        {
            pluto_message_generate("Can not find System Current Channel.", 2);
            return 1;
        }
    pluto_dev.pwr_voltage =iio_device_find_channel(pluto_dev.pwr_phy, "voltage0", false);
        if(pluto_dev.pwr_voltage == NULL)
        {
            pluto_message_generate("Can not find System Voltage Channel.", 2);
            return 1;
        }
    pluto_dev.rf_temperature = iio_device_find_channel(pluto_dev.rf_phy, "temp0", false);
        if(pluto_dev.rf_temperature == NULL)
        {
            pluto_message_generate("Can not find RF Chipset's Temperature Channel.", 2);
            return 1;
        }
    pluto_dev.soc_temperature = iio_device_find_channel(pluto_dev.soc_phy, "temp0", false);
        if(pluto_dev.soc_temperature == NULL)
        {
            pluto_message_generate("Can not find APSoC's Temperature Channel.", 2);
            return 1;
        }
    iio_channel_enable(pluto_dev.pwr_current);
    iio_channel_enable(pluto_dev.pwr_voltage);
    iio_channel_enable(pluto_dev.rf_temperature);
    iio_channel_enable(pluto_dev.soc_temperature);
    pluto_message_generate("Sensors has been initialized.", 0);
    return 0;
}

struct iio_buffer *pluto_sdr::_pluto_create_buffer(iio_device *device, size_t samples_cnt)
{
    struct iio_buffer *buf;
    buf = iio_device_create_buffer(device, samples_cnt, false);
    return buf;
}

void pluto_sdr::_pluto_destroy_context()
{
    iio_context_destroy(pluto_dev.pluto_ctx);
    return;
}

void pluto_sdr::_pluto_destroy_buffer_rx()
{
    iio_buffer_destroy(pluto_dev.rx_buf);
    return;
}

void pluto_sdr::pluto_destroy()
{
    _pluto_destroy_buffer_rx();
    _pluto_destroy_context();
    pluto_message_generate("ADALM-Pluto can be disconnected now.", 0);
    return;
}

void pluto_sdr::__pluto_receiver_example()
{
    void *point;
    char *uri = (char *)"ip:192.168.2.1"; // "ip:xxx.xxx.xxx.xxx" or "usb:XX.XX.X";
    long long samprate = 2000000;
    long long rx_freq = 24000000;
    size_t samp_cnt = 4096;

    pluto_init(uri);
    pluto_set_rx_samprate(samprate);
    pluto_set_rx_freq(rx_freq);
    pluto_init_receiver(samp_cnt);

    while (true) {
        pluto_get_rx_data();
        for (point = pluto_receiver.rx_ptr_start; point < pluto_receiver.rx_ptr_end; point = (void *)((ptrdiff_t)point + pluto_receiver.rx_ptr_inc))
        {
            //const int16_t i = ((int16_t*)point)[0]; // Real (I)
            //const int16_t q = ((int16_t*)point)[1]; // Imag (Q)
            /* Process here */
        }
    }
    pluto_destroy();
}

void pluto_sdr::__pluto_transmitter_example()
{
    void *point;
    char *uri = (char *)"ip:192.168.2.1"; // "ip:xxx.xxx.xxx.xxx" or "usb:XX.XX.X";
    long long samprate = 2000000;
    long long tx_freq = 24000000;
    size_t samp_cnt = 4096;

    pluto_init(uri);
    pluto_set_tx_samprate(samprate);
    pluto_set_tx_freq(tx_freq);
    pluto_init_transmitter(samp_cnt);
    pluto_set_tx_gain(-1.00);
    pluto_set_tx_en(true);

    while (true) {
        pluto_schedule_tx_buff();
        for (point = pluto_transmitter.tx_ptr_start; point < pluto_transmitter.tx_ptr_end; point = (void *)((ptrdiff_t)point + pluto_transmitter.tx_ptr_inc))
        {
            //((int16_t*)point)[0] = i << 4; // Real (I)
            //((int16_t*)point)[1] = q << 4; // Imag (Q)
        }
    }
    // Others Code
    pluto_set_tx_en(false);
    pluto_destroy();
}

