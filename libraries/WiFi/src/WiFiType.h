/*
 ESP8266WiFiType.h - esp8266 Wifi support.
 Copyright (c) 2011-2014 Arduino.  All right reserved.
 Modified by Ivan Grokhotkov, December 2014
 Reworked by Markus Sattler, December 2015

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ESP32WIFITYPE_H_
#define ESP32WIFITYPE_H_

#define WIFI_SCAN_RUNNING (-1)
#define WIFI_SCAN_FAILED  (-2)

typedef enum
{
  WIFI_MODE_NULL = 0, /**< null mode */
  WIFI_MODE_STA,      /**< WiFi station mode */
  WIFI_MODE_AP,       /**< WiFi soft-AP mode */
  WIFI_MODE_APSTA,    /**< WiFi station + soft-AP mode */
  WIFI_MODE_MAX
} wifi_mode_t;

#define WiFiMode_t  wifi_mode_t
#define WIFI_OFF    WIFI_MODE_NULL
#define WIFI_STA    WIFI_MODE_STA
#define WIFI_AP     WIFI_MODE_AP
#define WIFI_AP_STA WIFI_MODE_APSTA

typedef enum
{
  ARDUINO_EVENT_WIFI_READY = 0,
  ARDUINO_EVENT_WIFI_SCAN_DONE,
  ARDUINO_EVENT_WIFI_STA_START,
  ARDUINO_EVENT_WIFI_STA_STOP,
  ARDUINO_EVENT_WIFI_STA_CONNECTED,
  ARDUINO_EVENT_WIFI_STA_DISCONNECTED,
  ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE,
  ARDUINO_EVENT_WIFI_STA_GOT_IP,
  ARDUINO_EVENT_WIFI_STA_GOT_IP6,
  ARDUINO_EVENT_WIFI_STA_LOST_IP,
  ARDUINO_EVENT_WIFI_AP_START,
  ARDUINO_EVENT_WIFI_AP_STOP,
  ARDUINO_EVENT_WIFI_AP_STACONNECTED,
  ARDUINO_EVENT_WIFI_AP_STADISCONNECTED,
  ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED,
  ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED,
  ARDUINO_EVENT_WIFI_AP_GOT_IP6,
  ARDUINO_EVENT_WIFI_FTM_REPORT,
  ARDUINO_EVENT_ETH_START,
  ARDUINO_EVENT_ETH_STOP,
  ARDUINO_EVENT_ETH_CONNECTED,
  ARDUINO_EVENT_ETH_DISCONNECTED,
  ARDUINO_EVENT_ETH_GOT_IP,
  ARDUINO_EVENT_ETH_GOT_IP6,
  ARDUINO_EVENT_WPS_ER_SUCCESS,
  ARDUINO_EVENT_WPS_ER_FAILED,
  ARDUINO_EVENT_WPS_ER_TIMEOUT,
  ARDUINO_EVENT_WPS_ER_PIN,
  ARDUINO_EVENT_WPS_ER_PBC_OVERLAP,
  ARDUINO_EVENT_SC_SCAN_DONE,
  ARDUINO_EVENT_SC_FOUND_CHANNEL,
  ARDUINO_EVENT_SC_GOT_SSID_PSWD,
  ARDUINO_EVENT_SC_SEND_ACK_DONE,
  ARDUINO_EVENT_PROV_INIT,
  ARDUINO_EVENT_PROV_DEINIT,
  ARDUINO_EVENT_PROV_START,
  ARDUINO_EVENT_PROV_END,
  ARDUINO_EVENT_PROV_CRED_RECV,
  ARDUINO_EVENT_PROV_CRED_FAIL,
  ARDUINO_EVENT_PROV_CRED_SUCCESS,
  ARDUINO_EVENT_MAX
} arduino_event_id_t;

/*typedef union {
  wifi_event_sta_scan_done_t        wifi_scan_done;
  wifi_event_sta_authmode_change_t  wifi_sta_authmode_change;
  wifi_event_sta_connected_t        wifi_sta_connected;
  wifi_event_sta_disconnected_t     wifi_sta_disconnected;
  wifi_event_sta_wps_er_pin_t       wps_er_pin;
  wifi_event_sta_wps_fail_reason_t  wps_fail_reason;
  wifi_event_ap_probe_req_rx_t      wifi_ap_probereqrecved;
  wifi_event_ap_staconnected_t      wifi_ap_staconnected;
  wifi_event_ap_stadisconnected_t   wifi_ap_stadisconnected;
  wifi_event_ftm_report_t           wifi_ftm_report;
  ip_event_ap_staipassigned_t       wifi_ap_staipassigned;
  ip_event_got_ip_t                 got_ip;
  ip_event_got_ip6_t                got_ip6;
  smartconfig_event_got_ssid_pswd_t sc_got_ssid_pswd;
  esp_eth_handle_t                  eth_connected;
  wifi_sta_config_t                 prov_cred_recv;
  wifi_prov_sta_fail_reason_t       prov_fail_reason;
} arduino_event_info_t;*/

typedef size_t wifi_event_id_t;

#define WiFiEvent_t arduino_event_id_t
//#define WiFiEventInfo_t arduino_event_info_t
#define WiFiEventId_t wifi_event_id_t

typedef enum
{
  WIFI_AUTH_OPEN = 0,        /**< authenticate mode : open */
  WIFI_AUTH_WEP,             /**< authenticate mode : WEP */
  WIFI_AUTH_WPA_PSK,         /**< authenticate mode : WPA_PSK */
  WIFI_AUTH_WPA2_PSK,        /**< authenticate mode : WPA2_PSK */
  WIFI_AUTH_WPA_WPA2_PSK,    /**< authenticate mode : WPA_WPA2_PSK */
  WIFI_AUTH_WPA2_ENTERPRISE, /**< authenticate mode : WPA2_ENTERPRISE */
  WIFI_AUTH_WPA3_PSK,        /**< authenticate mode : WPA3_PSK */
  WIFI_AUTH_WPA2_WPA3_PSK,   /**< authenticate mode : WPA2_WPA3_PSK */
  WIFI_AUTH_WAPI_PSK,        /**< authenticate mode : WAPI_PSK */
  WIFI_AUTH_MAX
} wifi_auth_mode_t;

typedef enum
{
  WL_NO_SHIELD       = 255, // for compatibility with WiFi Shield library
  WL_IDLE_STATUS     = 0,
  WL_NO_SSID_AVAIL   = 1,
  WL_SCAN_COMPLETED  = 2,
  WL_CONNECTED       = 3,
  WL_CONNECT_FAILED  = 4,
  WL_CONNECTION_LOST = 5,
  WL_DISCONNECTED    = 6
} wl_status_t;

#endif /* ESP32WIFITYPE_H_ */
