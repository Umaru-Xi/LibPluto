#include "libpluto.h"

double pluto_get_tx_gain()
{
    double tx_gain = 0;
    _pluto_attr_get(
        (void *)&tx_gain,
        pluto_dev.rf_phy, (char *)"voltage0", true,
        (char *)"hardwaregain", "TX Gain",
        "double");
    return tx_gain;
}

long long pluto_get_tx_samprate()
{
    long long samprate = 0;
    _pluto_attr_get(
        (void *)&samprate,
        pluto_dev.rf_phy, (char *)"voltage0", true,
        (char *)"sampling_frequency", "TX Sampling Rate",
        "longlong");
    return samprate;
}

long long pluto_get_tx_bandwidth()
{
    long long tx_bandwidth = 0;
    _pluto_attr_get(
        (void *)&tx_bandwidth,
        pluto_dev.rf_phy, (char *)"voltage0", true,
        (char *)"rf_bandwidth", "TX Bnadwidth",
        "longlong");
    return tx_bandwidth;
}

bool pluto_get_tx_fir_is_enable()
{
    bool is_enable = false;
    _pluto_attr_get(
        (void *)&is_enable,
        pluto_dev.rf_phy, (char *)"voltage0", true,
        (char *)"filter_fir_en", "TX FIR Filter Status",
        "bool");
    return is_enable;
}

bool pluto_get_rx_is_enable()
{
    bool is_enable = false;
    bool value = false;
    _pluto_attr_get(
        (void *)&value,
        pluto_dev.rf_phy, (char *)"altvoltage0", true,
        (char *)"powerdown", "RX Enable Status",
        "bool");
    is_enable = !value;
    return is_enable;
}

bool pluto_get_tx_is_enable()
{
    bool is_enable = false;
    bool value = false;
    _pluto_attr_get(
        (void *)&value,
        pluto_dev.rf_phy, (char *)"altvoltage1", true,
        (char *)"powerdown", "TX Enable Status",
        "bool");
    is_enable = !value;
    return is_enable;
}

long long pluto_get_rx_freq()
{
    long long rx_freq = 0;
    _pluto_attr_get(
        (void *)&rx_freq,
        pluto_dev.rf_phy, (char *)"altvoltage0", true,
        (char *)"frequency", "RX Frequency",
        "longlong");
    return rx_freq;
}

long long pluto_get_rx_samprate()
{
    long long samprate = 0;
    _pluto_attr_get(
        (void *)&samprate,
        pluto_dev.rf_phy, (char *)"voltage0", false,
        (char *)"sampling_frequency", "RX Sampling Rate",
        "longlong");
    return samprate;
}

long long pluto_get_rx_bandwidth()
{
    long long rx_bandwidth = 0;
    _pluto_attr_get(
        (void *)&rx_bandwidth,
        pluto_dev.rf_phy, (char *)"voltage0", false,
        (char *)"rf_bandwidth", "RX Bandwidth",
        "longlong");
    return rx_bandwidth;
}

long long pluto_get_rx_gain()
{
    long long rx_gain = 0;
    _pluto_attr_get(
        (void *)&rx_gain,
        pluto_dev.rf_phy, (char *)"voltage0", false,
        (char *)"hardwaregain", "RX Gain",
        "longlong");
    return rx_gain;
}

bool pluto_get_rx_fir_is_enable()
{
    bool is_enable = false;
    _pluto_attr_get(
        (void *)&is_enable,
        pluto_dev.rf_phy, (char *)"voltage0", false,
        (char *)"filter_fir_en", "RX FIR Filter Status",
        "bool");
    return is_enable;
}

long long pluto_get_tx_freq()
{
    long long tx_freq = 0;
    _pluto_attr_get(
        (void *)&tx_freq,
        pluto_dev.rf_phy, (char *)"altvoltage1", true,
        (char *)"frequency", "TX Frequency",
        "longlong");
    return tx_freq;
}

int pluto_set_tx_samprate(long long tx_samprate)
{
    long long value_min, value_max, value_inc;
    value_min = 2083334; value_max = 61439999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&tx_samprate, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", true, (char *)"sampling_frequency",
        "TX Sampling Rate", "longlong");
}

int pluto_set_tx_bandwidth(long long tx_bandwidth)
{
    long long value_min, value_max, value_inc;
    value_min = 200001; value_max = 39999999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&tx_bandwidth, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", true, (char *)"rf_bandwidth",
        "TX Bandwidth", "longlong");
}

int pluto_set_tx_gain(double tx_gain)
{
    double value_min, value_max, value_inc;
    value_min = -90.00; value_max = -0.25; value_inc = 0.25;
    return _pluto_attr_set(
        (void *)&tx_gain, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", true, (char *)"hardwaregain",
        "TX Gain", "double");
}

int pluto_set_tx_fir_en(bool is_enable)
{
    int return_code = iio_channel_attr_write_bool(
        iio_device_find_channel(pluto_dev.rf_phy, "voltage0", true),
        "filter_fir_en", is_enable);
    return return_code;
}

int pluto_set_tx_freq(long long tx_freq)
{
    long long value_min, value_max, value_inc;
    value_min = 46875002; value_max = 5999999999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&tx_freq, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"altvoltage1", true, (char *)"frequency",
        "TX Frequency", "longlong");
}

int pluto_set_rx_en(bool is_enable)
{
    bool value;
    value = !is_enable;
    return _pluto_attr_set(
        (void *)&value, false, (void *)NULL, (void *)NULL, (void *)NULL,
        pluto_dev.rf_phy, (char *)"altvoltage0", true, (char *)"powerdown",
        "RX Enable Status", "bool");
}

int pluto_set_tx_en(bool is_enable)
{
    bool value;
    value = !is_enable;
    return _pluto_attr_set(
        (void *)&value, false, (void *)NULL, (void *)NULL, (void *)NULL,
        pluto_dev.rf_phy, (char *)"altvoltage1", true, (char *)"powerdown",
        "TX Enable Status", "bool");
}

int pluto_init_transmitter(size_t samples_cnt)
{
    pluto_dev.tx_dev = iio_context_find_device(pluto_dev.pluto_ctx, "cf-ad9361-dds-core-lpc");
        if(pluto_dev.tx_dev == NULL) return 1;
    pluto_dev.tx_i = iio_device_find_channel(pluto_dev.tx_dev, "voltage0", true);
        if(pluto_dev.tx_i == NULL)  return 2;
    pluto_dev.tx_q = iio_device_find_channel(pluto_dev.tx_dev, "voltage1", true);
        if(pluto_dev.tx_q == NULL) return 2;
    iio_channel_enable(pluto_dev.tx_i);
    iio_channel_enable(pluto_dev.tx_q);
    pluto_dev.tx_buf = _pluto_create_buffer(pluto_dev.tx_dev, samples_cnt);
        if(pluto_dev.tx_buf == NULL)return 3;
    return 0;
}

int pluto_set_rx_fir_en(bool is_enable)
{
    return _pluto_attr_set(
        (void *)&is_enable, false, (void *)NULL, (void *)NULL, (void *)NULL,
        pluto_dev.rf_phy, (char *)"voltage0", false, (char *)"filter_fir_en",
        "RX FIR Filter", "bool");
}

int pluto_set_rx_gain(long long rx_gain)
{
    long long value_min, value_max, value_inc;
    value_min =0; value_max = 72; value_inc = 1;
    return _pluto_attr_set(
        (void *)&rx_gain, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", false, (char *)"hardwaregain",
        "RX Gain", "longlong");
}

int pluto_set_rx_bandwidth(long long rx_bandwidth)
{
    long long value_min, value_max, value_inc;
    value_min = 200001; value_max = 55999999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&rx_bandwidth, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", false, (char *)"rf_bandwidth",
        "RX Bandwidth", "longlong");
}

int pluto_set_rx_samprate(long long samprate)
{
    long long value_min, value_max, value_inc;
    value_min = 2083334; value_max = 61439999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&samprate, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"voltage0", false, (char *)"sampling_frequency",
        "RX Sampling Rate", "longlong");
}

int pluto_set_rx_freq(long long rx_freq)
{
    long long value_min, value_max, value_inc;
    value_min = 70000001; value_max = 5999999999; value_inc = 1;
    return _pluto_attr_set(
        (void *)&rx_freq, true, (void *)&value_min, (void *)&value_max, (void *)&value_inc,
        pluto_dev.rf_phy, (char *)"altvoltage0", true, (char *)"frequency",
        "RX Frequency", "longlong");
}

int pluto_init(char * device_uri)
{
    pluto_dev.pluto_ctx = iio_create_context_from_uri(device_uri);
        if(pluto_dev.pluto_ctx == NULL) return 1;
    pluto_dev.rf_phy = iio_context_find_device(pluto_dev.pluto_ctx, "ad9361-phy");
        if(pluto_dev.rf_phy == NULL) return 2;
    pluto_dev.soc_phy = iio_context_find_device(pluto_dev.pluto_ctx, "xadc");
        if(pluto_dev.soc_phy == NULL) return 2;
    pluto_dev.pwr_phy = iio_context_find_device(pluto_dev.pluto_ctx, "adm1177-iio");
        if(pluto_dev.pwr_phy == NULL) return 2;
    return 0;
}

int pluto_init_receiver(size_t samples_cnt)
{
    pluto_dev.rx_dev = iio_context_find_device(pluto_dev.pluto_ctx, "cf-ad9361-lpc");
        if(pluto_dev.rx_dev == NULL) return 1;
    pluto_dev.rx_i = iio_device_find_channel(pluto_dev.rx_dev, "voltage0", false);
        if(pluto_dev.rx_i == NULL) return 2;
    pluto_dev.rx_q = iio_device_find_channel(pluto_dev.rx_dev, "voltage1", false);
        if(pluto_dev.rx_q == NULL) return 2;
    iio_channel_enable(pluto_dev.rx_i);
    iio_channel_enable(pluto_dev.rx_q);
    pluto_dev.rx_buf = _pluto_create_buffer(pluto_dev.rx_dev, samples_cnt);
        if(pluto_dev.rx_buf == NULL) return 3;
    return 0;
}

int pluto_schedule_tx_buff()
{
    if(iio_buffer_push(pluto_dev.tx_buf) < 0) return 1;
    pluto_transmitter.tx_ptr_inc = iio_buffer_step(pluto_dev.tx_buf);
    pluto_transmitter.tx_ptr_end = iio_buffer_end(pluto_dev.tx_buf);
    pluto_transmitter.tx_ptr_start = iio_buffer_first(pluto_dev.tx_buf, pluto_dev.tx_i);
    return 0;
}

int pluto_get_rx_data()
{
    if(iio_buffer_refill(pluto_dev.rx_buf) < 0) return 1;
    pluto_receiver.rx_ptr_inc = iio_buffer_step(pluto_dev.rx_buf);
    pluto_receiver.rx_ptr_end = iio_buffer_end(pluto_dev.rx_buf);
    pluto_receiver.rx_ptr_start = iio_buffer_first(pluto_dev.rx_buf, pluto_dev.rx_i);
    return 0;
}

double pluto_get_rf_temp()
{
    double rf_temp = 0;
    long long rf_temp_raw;
    if(iio_channel_attr_read_longlong(pluto_dev.rf_temperature, "input", &rf_temp_raw) < 0) return 1;
    else rf_temp =rf_temp_raw / 1000.0;
    return rf_temp;
}

double pluto_get_soc_temp()
{
    double soc_temp = 0;
    double soc_temp_scale;
    long long soc_temp_raw, soc_temp_offset;
    if(iio_channel_attr_read_double(pluto_dev.soc_temperature, "scale", &soc_temp_scale) < 0) return 1;
    if(iio_channel_attr_read_longlong(pluto_dev.soc_temperature, "raw", &soc_temp_raw) < 0) return 1;
    if(iio_channel_attr_read_longlong(pluto_dev.soc_temperature, "offset", &soc_temp_offset) < 0) return 1;
    soc_temp = (soc_temp_raw + soc_temp_offset) * soc_temp_scale / 1000.0;
    return soc_temp;
}

double pluto_get_power()
{
    double sys_power = 0;
    double current, voltage;
    if(pluto_get_current(&current) != 0) return 1;
    if(pluto_get_voltage(&voltage) != 0) return 1;
    sys_power = current * voltage;
    return sys_power;
}

double pluto_get_voltage()
{
    double sys_voltage = 0;
    double voltage_scale;
    long long voltage_raw;
    if(iio_channel_attr_read_double(pluto_dev.pwr_voltage, "scale", &voltage_scale) < 0) return 1;
    if(iio_channel_attr_read_longlong(pluto_dev.pwr_voltage, "raw", &voltage_raw) < 0) return 1;
    sys_voltage = voltage_raw * voltage_scale / 1000.0;
    return sys_voltage;
}

double pluto_get_current()
{
    double sys_current = 0;
    double current_scale;
    long long current_raw;
    if(iio_channel_attr_read_double(pluto_dev.pwr_current, "scale", &current_scale) <0) return 1;
    if(iio_channel_attr_read_longlong(pluto_dev.pwr_current, "raw", &current_raw) < 0) return 1;
    sys_current = current_raw * current_scale / 1000.0;
    return sys_current;
}

int pluto_init_sensors()
{
    pluto_dev.pwr_current =iio_device_find_channel(pluto_dev.pwr_phy, "current0", false);
        if(pluto_dev.pwr_current == NULL) return 1;
    pluto_dev.pwr_voltage =iio_device_find_channel(pluto_dev.pwr_phy, "voltage0", false);
        if(pluto_dev.pwr_voltage == NULL) return 1;
    pluto_dev.rf_temperature = iio_device_find_channel(pluto_dev.rf_phy, "temp0", false);
        if(pluto_dev.rf_temperature == NULL) return 1;
    pluto_dev.soc_temperature = iio_device_find_channel(pluto_dev.soc_phy, "temp0", false);
        if(pluto_dev.soc_temperature == NULL) return 1;
    iio_channel_enable(pluto_dev.pwr_current);
    iio_channel_enable(pluto_dev.pwr_voltage);
    iio_channel_enable(pluto_dev.rf_temperature);
    iio_channel_enable(pluto_dev.soc_temperature);
    return 0;
}

struct iio_buffer *_pluto_create_buffer(struct iio_device *device, size_t samples_cnt)
{
    struct iio_buffer *buf;
    buf = iio_device_create_buffer(device, samples_cnt, false);
    return buf;
}

void _pluto_destroy_context()
{
    iio_context_destroy(pluto_dev.pluto_ctx);
    return;
}

void _pluto_destroy_buffer_rx()
{
    iio_buffer_destroy(pluto_dev.rx_buf);
    return;
}

void pluto_destroy()
{
    _pluto_destroy_buffer_rx();
    _pluto_destroy_context();
    return;
}

int _pluto_attr_set(
        void *value, bool is_limited, void *value_min, void *value_max, void *value_inc,
        struct iio_device *device, char *channel, bool is_output, char *attr,
        char *value_name, char *type_name)
{
    int type_code, return_code;
    bool out_of_limit;
    if(!strcmp(type_name, "bool"))
    {
        type_code = 0;
        out_of_limit = false;
    }
    else if(!strcmp(type_name, "long long") || !strcmp(type_name, "longlong"))
    {
        type_code = 1;
        out_of_limit = (is_limited && (*(long long *)value < *(long long *)value_min
            || *(long long *)value > *(long long *)value_max
            || *(long long *)value % *(long long *)value_inc != 0
            ))? true : false;
    }
    else if(!strcmp(type_name, "double"))
    {
        type_code = 2;
        out_of_limit = (is_limited && (*(double *)value < *(double *)value_min
            || *(double *)value > *(double *)value_max
            || *(double *)value - (floor(*(double *)value / *(double *)value_inc) * (*(double *)value_inc)) != 0.00
            ))? true : false;
    }
    else
    {
        type_code = 3;
        out_of_limit = false;
    }
    if(out_of_limit) return 1;
    switch(type_code)
    {
        case 0:
        {
            return_code = iio_channel_attr_write_bool(
                iio_device_find_channel(device, channel, is_output),
                attr, *(bool *)value); break;
        }
        case 1:
        {
            return_code = iio_channel_attr_write_longlong(
                iio_device_find_channel(device, channel, is_output),
                attr, *(long long *)value); break;
        }
        case 2:
        {
            return_code = iio_channel_attr_write_double(
                iio_device_find_channel(device, channel, is_output),
                attr, *(double *)value); break;
        }
        default:
            return_code = 1;
    }
    return return_code;
}

int _pluto_attr_get(void *value, struct iio_device *device, char *channel, bool is_output, char *attr, char *value_name, char *type_name)
{
    int return_code;
    if(!strcmp(type_name, "bool"))
        return_code = iio_channel_attr_read_bool(
            iio_device_find_channel(device, channel, is_output),
            attr, (bool *)value);
    else if(!strcmp(type_name, "long long") || !strcmp(type_name, "longlong"))
        return_code = iio_channel_attr_read_longlong(
            iio_device_find_channel(device, channel, is_output),
            attr, (long long *)value);
    else if(!strcmp(type_name, "double"))
        return_code = iio_channel_attr_read_double(
            iio_device_find_channel(device, channel, is_output),
            attr, (double *)value);
    else return_code = 1;
    return return_code;
}

int pluto_util_init_all(char * device_uri, size_t rx_samples_cnt, size_t tx_samples_cnt)
{
    if(pluto_init(device_uri) != 0) return 1;
    if(pluto_init_sensors() != 0) return 2;
    if(pluto_init_receiver(rx_samples_cnt) != 0) return 3;
    if(pluto_init_transmitter(tx_samples_cnt)) return 4;
    return 0;
}

double pluto_util_get_rx_power(long long rx_freq, long long rx_bandwidth, long long rx_samprate)
{
    void *point;
    pluto_set_rx_en(false);
    pluto_set_rx_samprate(rx_samprate);
    pluto_set_rx_bandwidth(rx_bandwidth);
    pluto_set_rx_freq(rx_freq);
    pluto_set_rx_en(true);
    pluto_get_rx_data();
    double sum = 0;
    int index = 0;
    for (point = pluto_receiver.rx_ptr_start; 
         point < pluto_receiver.rx_ptr_end; 
         point = (void *)((ptrdiff_t)point + pluto_receiver.rx_ptr_inc))
    {
        const int16_t i = ((int16_t*)point)[0];
        const int16_t q = ((int16_t*)point)[1];
        const int32_t i2 = pow(i, 2);
        const int32_t q2 = pow(q, 2);
        const double rx_sqrt = sqrt(i2 + q2);
        sum += rx_sqrt;
        ++ index;
    }
    sum /= index;
    long long rx_gain = pluto_get_rx_gain();
    double rx_exp = exp(rx_gain/10.0);
    sum /= rx_exp;
    return sum;
}

void pluto_util_set_tx_power(long long tx_freq, long long tx_bandwidth, long long tx_samprate, double tx_gain)
{
    void *point;
    pluto_set_tx_en(false);
    pluto_set_tx_samprate(tx_samprate);
    pluto_set_tx_bandwidth(tx_bandwidth);
    pluto_set_tx_freq(tx_freq);
    pluto_set_tx_gain(tx_gain);
    pluto_schedule_tx_buff();
    
    for (point = pluto_transmitter.tx_ptr_start;
         point < pluto_transmitter.tx_ptr_end;
         point = (void *)((ptrdiff_t)point + pluto_transmitter.tx_ptr_inc))
    {
        const int16_t i = 32767 >> 4;
        const int16_t q = 32767 >> 4;
        ((int16_t*)point)[0] = i << 4;
        ((int16_t*)point)[1] = q << 4;
    }
    pluto_set_tx_en(true);
}

/*
void __pluto_receiver_example()
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
            // Process here //
        }
    }
    pluto_destroy();
}

void __pluto_transmitter_example()
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
}*/

