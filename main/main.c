#include "header/wifi_setup.h"
#include <esp_http_server.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "http_parser.h"
#include <stdlib.h>


int switch_pins[] = {0, 2, 4, 16, 17, 18, 19, 27};
static const char *TAG = "http_server";

typedef struct token_t {
    char *name;
    char *value;
}token_t;

token_t get_token(char *body, char *name){
    token_t ret;
    ret.name = name;
    char *token_position = strstr(body, name);
    char *value_start = token_position + strlen(name) + 1;
    char current = *(value_start);
    int buf_len = 0;
    
    while(current != '&' && current != '\0'){
        buf_len++;
        current = *(value_start+buf_len);
    }
    
    ret.value = malloc(buf_len);
    strncpy(ret.value, value_start, buf_len);
    
    *(ret.value + buf_len) = '\0';
    return ret;
}


static esp_err_t post_switchboard_handler(httpd_req_t *req){
    int buf_length = req->content_len;
    char buf[buf_length];
    httpd_req_recv(req, buf, sizeof(buf));
    buf[buf_length] = '\0';
    ESP_LOGI(TAG, "Data Received : %s", buf);
    
    token_t switch_number = get_token(buf, "switch_number");
    token_t switch_state = get_token(buf, "switch_state");

    int pin = atoi(switch_number.value);
    if(!strcmp(switch_state.value, "true")){
        gpio_set_level(switch_pins[pin-1], 1);
    }else if(!strcmp(switch_state.value, "false")){
        gpio_set_level(switch_pins[pin-1], 0);
    }
    free(switch_number.value);
    free(switch_state.value);
    httpd_resp_send(req, req->user_ctx, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static const httpd_uri_t toggleswitch = {
    .uri = "/toggleswitch",
    .method = HTTP_POST,
    .handler = post_switchboard_handler,
    .user_ctx = "Data Received"
};

static httpd_handle_t start_webserver(){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;
    
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &toggleswitch);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void app_main(void)
{
    initialize_nvs();
    initialize_wifi();
    for(int i=0; i<=7; i++){
        gpio_set_direction(switch_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(switch_pins[i], 0);
    }
    
    start_webserver();
}