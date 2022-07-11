#include <QtWidgets/QApplication>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QDebug>

#include "PlutoDev.h"

QT_USE_NAMESPACE

int transmit_test(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    transmit_test(argc, argv);

    qDebug("#INFO: Test Finished.");

}

int transmit_test(int argc, char *argv[])
{
    int return_code;
    QApplication app(argc, argv);
    QMainWindow window0;
    QLineSeries *series0 = new QLineSeries();
    QChart *chart0 = new QChart();
    QChartView *chartView0 = new QChartView(chart0);
    QMainWindow window1;
    QLineSeries *series1 = new QLineSeries();
    QChart *chart1 = new QChart();
    QChartView *chartView1 = new QChartView(chart1);

    pluto_sdr pluto;

    return_code = pluto.pluto_init((char *)"ip:192.168.2.1");
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_init_sensors();
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();

    qDebug("#INFO: Before Scan:");
    qDebug("#INFO: \tSystem Power: \t%lf W", pluto.pluto_get_power());
    qDebug("#INFO: \tDevice Voltage: \t%lf A", pluto.pluto_get_voltage());
    qDebug("#INFO: \tDevice Current: \t%lf V", pluto.pluto_get_current());
    qDebug("#INFO: \tSoC Temperature: \t%lf °C", pluto.pluto_get_soc_temp());
    qDebug("#INFO: \tRF Temperature: \t%lf °C", pluto.pluto_get_rf_temp());

    void *point;
    long long samprate = 2083334;
    size_t samp_cnt = 4096;

    long long rx_start = pluto.pluto_GHz(0.98);
    long long rx_inc = pluto.pluto_MHz(1.00);
    long long rx_end =pluto.pluto_GHz(1.02);
    long long tx_freq = pluto.pluto_GHz(1.00);
    double tx_gain = -30.00;

    long long rx_freq = rx_start;
    long long index_max = (rx_end - rx_start) / rx_inc;
    double pwr_sum = 0;
    long long pwr_cnt = 0;

    return_code = pluto.pluto_set_rx_samprate(samprate);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_init_receiver(samp_cnt);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();

    long long index = 0;
    for(index = 0; index < index_max; ++index)
    {
        return_code = pluto.pluto_set_rx_freq(rx_freq);
            //qDebug("%s", pluto.pluto_message.c_str());
            if(return_code != 0) return app.exec();
        return_code = pluto.pluto_get_rx_data();
            //qDebug("%s", pluto.pluto_message.c_str());
            if(return_code != 0) return app.exec();
        pwr_cnt = 0;
        pwr_sum = 0;
        for (point = pluto.pluto_receiver.rx_ptr_start;
             point < pluto.pluto_receiver.rx_ptr_end;
             point = (void *)((ptrdiff_t)point + pluto.pluto_receiver.rx_ptr_inc))
        {
            const int16_t i = ((int16_t*)point)[0];
            const int16_t q = ((int16_t*)point)[1];
            const double pwr = sqrt(pow(i,2) + pow(q,2));
            pwr_sum += pwr;
            pwr_cnt += 1;
        }
        pwr_sum /= pwr_cnt;
        series0->append(rx_freq, pwr_sum);
        rx_freq += rx_inc;
    }

    qDebug("#INFO: After Scan:");
    qDebug("#INFO: \tSystem Power: \t%lf W", pluto.pluto_get_power());
    qDebug("#INFO: \tDevice Voltage: \t%lf A", pluto.pluto_get_voltage());
    qDebug("#INFO: \tDevice Current: \t%lf V", pluto.pluto_get_current());
    qDebug("#INFO: \tSoC Temperature: \t%lf °C", pluto.pluto_get_soc_temp());
    qDebug("#INFO: \tRF Temperature: \t%lf °C", pluto.pluto_get_rf_temp());

    chart0->legend()->hide();
    chart0->addSeries(series0);
    chart0->createDefaultAxes();
    chart0->setTitle("Freq Scanner Before Transmit");

    chartView0->setRenderHint(QPainter::Antialiasing);

    window0.setCentralWidget(chartView0);
    window0.resize(400, 300);
    window0.show();

    return_code = pluto.pluto_set_tx_samprate(samprate);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_set_tx_freq(tx_freq);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_init_transmitter(samp_cnt);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_set_tx_gain(tx_gain);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    return_code = pluto.pluto_set_tx_en(true);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();

    return_code = pluto.pluto_schedule_tx_buff();
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();
    for (point = pluto.pluto_transmitter.tx_ptr_start; point < pluto.pluto_transmitter.tx_ptr_end; point = (void *)((ptrdiff_t)point + pluto.pluto_transmitter.tx_ptr_inc))
    {
        ((int16_t*)point)[0] = 256 << 4;
        ((int16_t*)point)[1] = 256 << 4;
    }

    rx_freq = rx_start;
    for(index = 0; index < index_max; ++index)
    {
        return_code = pluto.pluto_set_rx_freq(rx_freq);
            //qDebug("%s", pluto.pluto_message.c_str());
            if(return_code != 0) return app.exec();
        return_code = pluto.pluto_get_rx_data();
            //qDebug("%s", pluto.pluto_message.c_str());
            if(return_code != 0) return app.exec();
        pwr_cnt = 0;
        pwr_sum = 0;
        for (point = pluto.pluto_receiver.rx_ptr_start;
             point < pluto.pluto_receiver.rx_ptr_end;
             point = (void *)((ptrdiff_t)point + pluto.pluto_receiver.rx_ptr_inc))
        {
            const int16_t i = ((int16_t*)point)[0];
            const int16_t q = ((int16_t*)point)[1];
            const double pwr = sqrt(pow(i,2) + pow(q,2));
            pwr_sum += pwr;
            pwr_cnt += 1;
        }
        pwr_sum /= pwr_cnt;
        series1->append(rx_freq, pwr_sum);
        rx_freq += rx_inc;
    }

    return_code = pluto.pluto_set_tx_en(false);
        qDebug("%s", pluto.pluto_message.c_str());
        if(return_code != 0) return app.exec();

    qDebug("#INFO: After Transmit:");
    qDebug("#INFO: \tSystem Power: \t%lf W", pluto.pluto_get_power());
    qDebug("#INFO: \tDevice Voltage: \t%lf A", pluto.pluto_get_voltage());
    qDebug("#INFO: \tDevice Current: \t%lf V", pluto.pluto_get_current());
    qDebug("#INFO: \tSoC Temperature: \t%lf °C", pluto.pluto_get_soc_temp());
    qDebug("#INFO: \tRF Temperature: \t%lf °C", pluto.pluto_get_rf_temp());

    pluto.pluto_destroy();
        qDebug("%s", pluto.pluto_message.c_str());

    chart1->legend()->hide();
    chart1->addSeries(series1);
    chart1->createDefaultAxes();
    chart1->setTitle("Freq Scanner After Transmit");

    chartView1->setRenderHint(QPainter::Antialiasing);

    window1.setCentralWidget(chartView1);
    window1.resize(400, 300);
    window1.show();

    return app.exec();
}
