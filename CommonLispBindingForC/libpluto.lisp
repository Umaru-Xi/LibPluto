(defpackage "libpluto")
(in-package "libpluto")
(EVAL-WHEN (compile) (setq FFI:*OUTPUT-C-FUNCTIONS* t))
(ffi:default-foreign-language :stdc)
;; Init Devices
(ffi:def-call-out pluto_init
    (:library "./libpluto.so")
    (:return-type ffi:int)
    (:arguments (device_uri ffi:c-string)))
(ffi:def-call-out pluto_init_sensors
    (:library "./libpluto.so")
    (:return-type ffi:int))
(ffi:def-call-out pluto_init_receiver
    (:library "./libpluto.so")
    (:arguments (samples_cnt ffi:uint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_init_transmitter
    (:library "./libpluto.so")
    (:arguments (samples_cnt ffi:uint64))
    (:return-type ffi:int))
;; Get TX Values
(ffi:def-call-out pluto_get_tx_gain
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_get_tx_samprate
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_tx_bandwidth
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_tx_fir_is_enable
    (:library "./libpluto.so")
    (:return-type ffi:boolean))
(ffi:def-call-out pluto_get_tx_freq
    (:library "./libpluto.so")
    (:return-type ffi:int))
(ffi:def-call-out pluto_get_tx_is_enable
    (:library "./libpluto.so")
    (:return-type ffi:boolean))
;; Get RX Values
(ffi:def-call-out pluto_get_rx_is_enable
    (:library "./libpluto.so")
    (:return-type ffi:boolean))
(ffi:def-call-out pluto_get_rx_freq
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_rx_samprate
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_rx_bandwidth
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_rx_gain
    (:library "./libpluto.so")
    (:return-type ffi:sint64))
(ffi:def-call-out pluto_get_rx_fir_is_enable
    (:library "./libpluto.so")
    (:return-type ffi:boolean))
;; Get Sensors Values
(ffi:def-call-out pluto_get_rf_temp
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_get_soc_temp
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_get_power
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_get_voltage
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_get_current
    (:library "./libpluto.so")
    (:return-type ffi:double-float))
;; Set TX Values 
(ffi:def-call-out pluto_set_tx_samprate
    (:library "./libpluto.so")
    (:arguments (tx_samprate ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_bandwidth
    (:library "./libpluto.so")
    (:arguments (tx_bandwidth ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_gain
    (:library "./libpluto.so")
    (:arguments (tx_gain ffi:double-float))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_fir_en
    (:library "./libpluto.so")
    (:arguments (is_enable ffi:boolean))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_freq
    (:library "./libpluto.so")
    (:arguments (tx_freq ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_en
    (:library "./libpluto.so")
    (:arguments (is_enable ffi:boolean))
    (:return-type ffi:int))
;; Set RX Values
(ffi:def-call-out pluto_set_rx_en
    (:library "./libpluto.so")
    (:arguments (is_enable ffi:boolean))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_rx_fir_en
    (:library "./libpluto.so")
    (:arguments (is_enable ffi:boolean))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_rx_gain
    (:library "./libpluto.so")
    (:arguments (rx_gain ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_rx_bandwidth
    (:library "./libpluto.so")
    (:arguments (rx_bandwidth ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_rx_samprate
    (:library "./libpluto.so")
    (:arguments (rx_samprate ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_rx_freq
    (:library "./libpluto.so")
    (:arguments (rx_freq ffi:sint64))
    (:return-type ffi:int))
;; Other Functions
(ffi:def-call-out pluto_schedule_tx_buff
    (:library "./libpluto.so")
    (:return-type ffi:int))
(ffi:def-call-out pluto_get_rx_data
    (:library "./libpluto.so")
    (:return-type ffi:int))
(ffi:def-call-out pluto_set_tx_data
    (:library "./libpluto.so")
    (:return-type ffi:int))
(ffi:def-call-out pluto_destroy
    (:library "./libpluto.so")
    (:return-type nil))
;; Utilities
(ffi:def-call-out pluto_util_init_all
    (:library "./libpluto.so")
    (:arguments (device_uri ffi:c-string) 
                (rx_samples_cnt ffi:sint64)
                (tx_samples_cnt ffi:sint64))
    (:return-type ffi:int))
(ffi:def-call-out pluto_util_get_rx_power
    (:library "./libpluto.so")
    (:arguments (rx_freq ffi:sint64) 
                (rx_bandwidth ffi:sint64)
                (rx_samprate ffi:sint64))
    (:return-type ffi:double-float))
(ffi:def-call-out pluto_util_set_tx_power
    (:library "./libpluto.so")
    (:arguments (tx_freq ffi:sint64) 
                (tx_bandwidth ffi:sint64)
                (tx_samprate ffi:sint64)
                (tx_gain ffi:double-float))
    (:return-type nil))
