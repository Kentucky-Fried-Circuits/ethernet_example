/**
 * Http Server
 *
 * 07/17/2023 Ruizhe He
 * Currently, this file is still WIP, the full website html code is still missing.
 * The web server starting and stopping functions are implemented, but the web
 * server doesn't start here and that is done in EthernetConnect.cpp.
 * Basic usage:
 * 1. Create a hanlder function
 * 2. Create a URI handler
 * 3. Register the handler in start_webserver()
 */

#include "WebServer.h"

// All the CSS, HTML, and JS code stored in const char*
#include "supporting_js.h"
#include "css.h"
#include "index_html.h"
#include "json_string.h"
#include "hist_html.h"
#include "hist_Month_html.h"

// Content type constants
#define CONTENT_TYPE_CSS "text/css"
#define CONTENT_TYPE_CSV "text/csv"
#define CONTENT_TYPE_HTML "text/html"
#define CONTENT_TYPE_JS "text/javascript"
#define CONTENT_TYPE_JSON "application/json"

// A time for the timertick function in html
long long this_time = 1692628297000;
struct file_server_data *server_data;
httpd_handle_t server;

/*NOTE:All handlers under here are for returning JSON texts*/

/**
 * This will return channel json string. Channel seems to hold
 * definition and explaining info for data return in dataNow.json
 */
esp_err_t channel_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);
    return httpd_resp_send(req, channel_string, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t channel_handler = {
    .uri = "/channel.json",
    .method = HTTP_GET,
    .handler = channel_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = NULL};

/**
 * This will return the host info. It contains
 * memory info of the SD. It's only dummy value here.
 */
esp_err_t hostinfo_get_handler(httpd_req_t *req)
{
    memoryLogging();
    ESP_LOGI(TAG_WEB, "current memory %zu", esp_get_free_heap_size());
    std::string hostInfo = getHostInfoJson();
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);
    return httpd_resp_send(req, hostInfo.c_str(), HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t hostinfo_handler = {
    .uri = "/hostinfo.json",
    .method = HTTP_GET,
    .handler = hostinfo_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * Battery chart and amp in/out need some data to start with. This
 * is just some dummy data to jump start both charts.
 */
esp_err_t chartData_get_handler(httpd_req_t *req)
{
    std::string chartString = getRecentData();
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);
    return httpd_resp_send(req, chartString.c_str(), HTTPD_RESP_USE_STRLEN);
}
const httpd_uri_t chartData = {
    .uri = "/recent.json",
    .method = HTTP_GET,
    .handler = chartData_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = NULL};

esp_err_t dayStatsData_get_handler(httpd_req_t *req)
{
    std::string dayStatsJson = getDaysStats();
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);
    return httpd_resp_send(req, dayStatsJson.c_str(), HTTPD_RESP_USE_STRLEN);
}
const httpd_uri_t dayStatsData = {
    .uri = "/dayStats.json",
    .method = HTTP_GET,
    .handler = dayStatsData_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = NULL};

/**
 * This will return dataNow information. This should be generated in
 * real time in the actual project. This is the data shown under
 * "Now" table
 */
esp_err_t dataNow_get_handler(httpd_req_t *req)
{
    std::string dataNowString = getDataNow(this_time);
    this_time += 10000;
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);
    return httpd_resp_send(req, dataNowString.c_str(), HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t dataNow = {
    .uri = "/dataNow.json",
    .method = HTTP_GET,
    .handler = dataNow_get_handler,
    .user_ctx = NULL};

/**
 * This function retrieves the history file json string for the historical data page
 */
esp_err_t historyFiles_get_handler(httpd_req_t *req)
{
    std::string historyFileString = getHistoryFiles();
    this_time += 10000;
    httpd_resp_set_type(req, CONTENT_TYPE_JSON);

    return httpd_resp_send(req, historyFileString.c_str(), HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t histFile = {
    .uri = "/historyFiles.json",
    .method = HTTP_GET,
    .handler = historyFiles_get_handler,
    .user_ctx = NULL};

/* NOTE:Supporting files' handlers are below here*/

/**
 * This returns a css file for the html. Each external file requires a
 * separated handler.
 */
esp_err_t magnum_style_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_CSS);
    return httpd_resp_send(req, magnum_css, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t magnumStyle = {
    .uri = "/magnum_style.css",
    .method = HTTP_GET,
    .handler = magnum_style_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

esp_err_t get_url_param_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, GET_URL_PARAM, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t getUrlParam = {
    .uri = "/jquery.getUrlParam.js",
    .method = HTTP_GET,
    .handler = get_url_param_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t magnum_js_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, magnum_js, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t magnumjs = {
    .uri = "/magnum.js",
    .method = HTTP_GET,
    .handler = magnum_js_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t jquery_11_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, jquery_1_11, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t jquery_11 = {
    .uri = "/jquery-1.11.1.min.js",
    .method = HTTP_GET,
    .handler = jquery_11_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t excanas_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, excanvas, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t excanvasJS = {
    .uri = "/excanvas.min.js",
    .method = HTTP_GET,
    .handler = excanas_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t jquery_float_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, jqueryfloat, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t jquery_float = {
    .uri = "/jquery.flot.js",
    .method = HTTP_GET,
    .handler = jquery_float_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t jquery_threshold_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, jqery_threshold, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t jquery_threshold = {
    .uri = "/jquery.flot.threshold.js",
    .method = HTTP_GET,
    .handler = jquery_threshold_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t howler_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, howler, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t howler_handler = {
    .uri = "/howler.min.js",
    .method = HTTP_GET,
    .handler = howler_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t alarm_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, alarm_js, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t alarm_handler = {
    .uri = "/alarm.js",
    .method = HTTP_GET,
    .handler = alarm_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/**
 * This will return a required javascript file for html.
 */
esp_err_t date_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_JS);
    return httpd_resp_send(req, date_js, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t date_handler = {
    .uri = "/date.js",
    .method = HTTP_GET,
    .handler = date_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = (void *)""};

/* NOTE: Action on the page handler*/

esp_err_t download_handler(httpd_req_t *req)
{
    char filepath[FILE_PATH_MAX];
    char filename[FILE_PATH_MAX];
    FILE *fd = NULL;
    struct stat file_stat;

    get_path_from_uri(req->uri, DOWNLOAD_URI, filepath, filename);

    ESP_LOGI(TAG_WEB, "filename is %s, uri is %s, path is %s", filename, req->uri, filepath);
    if (!filename)
    {
        ESP_LOGE(TAG_WEB, "Filename is too long");
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Filename too long");
        return ESP_FAIL;
    }

    if (stat(filepath, &file_stat) == -1)
    {
        /* Respond with 404 Not Found */
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "File does not exist");
        return ESP_FAIL;
    }

    fd = fopen(filepath, "r");
    if (!fd)
    {
        ESP_LOGE(TAG_WEB, "Failed to read existing file : %s", filepath);
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG_WEB, "Sending file : %s (%ld bytes)...", filename, file_stat.st_size);
    httpd_resp_set_type(req, CONTENT_TYPE_CSV);

    /* Retrieve the pointer to scratch buffer for temporary storage */
    char *chunk = server_data->scratch;
    size_t chunksize;
    do
    {
        /* Read file in chunks into the scratch buffer */
        chunksize = fread(chunk, 1, SCRATCH_BUFSIZE, fd);

        if (chunksize > 0)
        {
            /* Send the buffer contents as HTTP response chunk */
            if (httpd_resp_send_chunk(req, chunk, chunksize) != ESP_OK)
            {
                fclose(fd);
                ESP_LOGE(TAG_WEB, "File sending failed!");
                /* Abort sending file */
                httpd_resp_sendstr_chunk(req, NULL);
                /* Respond with 500 Internal Server Error */
                httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file");
                return ESP_FAIL;
            }
        }

        /* Keep looping till the whole file is sent */
    } while (chunksize != 0);

    /* Close file after sending complete */
    fclose(fd);
    ESP_LOGI(TAG_WEB, "File sending complete");

    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

/* URI handler for getting uploaded files */
httpd_uri_t downloadFile = {
    .uri = "/download/*", // Match all URIs of type /path/to/file
    .method = HTTP_GET,
    .handler = download_handler,
    .user_ctx = (void *)"" // Pass server data as context
};

/* Handler to delete a file from the server */
esp_err_t delete_post_handler(httpd_req_t *req)
{
    char filepath[FILE_PATH_MAX];
    char filename[FILE_PATH_MAX];
    struct stat file_stat;

    /* Skip leading "/delete" from URI to get filename */
    /* Note sizeof() counts NULL termination hence the -1 */
    get_path_from_uri(req->uri, DELETE_URI, filepath, filename);

    if (!filename)
    {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Filename too long");
        return ESP_FAIL;
    }

    /* Filename cannot have a trailing '/' */
    if (filename[strlen(filename) - 1] == '/')
    {
        ESP_LOGE(TAG_WEB, "Invalid filename : %s", filename);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Invalid filename");
        return ESP_FAIL;
    }

    if (!hasFile(filepath))
    {
        ESP_LOGE(TAG_WEB, "File does not exist : %s", filename);
        /* Respond with 400 Bad Request */
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "File does not exist");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG_WEB, "Deleting file : %s", filename);
    /* Delete file */
    deleteFile(filepath);

    /* Redirect onto root to see the updated file list */
    httpd_resp_set_status(req, "303 See Other");
    httpd_resp_set_hdr(req, "Location", "/");
    httpd_resp_sendstr(req, "File deleted successfully");
    return ESP_OK;
}

httpd_uri_t file_delete = {
    .uri = "/delete/*", // Match all URIs of type /delete/path/to/file
    .method = HTTP_POST,
    .handler = delete_post_handler,
    .user_ctx = (void *)"" // Pass server data as context
};

/* NOTE: Handlers under this line are for retrieving webpages */

// TODO: Finish this function
esp_err_t historialMonthPage_get_handler(httpd_req_t *req)
{
    initi_sd_card();
    httpd_resp_set_type(req, CONTENT_TYPE_HTML);
    return httpd_resp_send(req, currentConditionPage, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t histMonthPage = {
    .uri = "/currentSettings",
    .method = HTTP_GET,
    .handler = historialMonthPage_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = NULL};

// TODO: Finish this function
esp_err_t historialPage_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_HTML);
    return httpd_resp_send(req, HISTORICAL_DATA_PAGE, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t histPage = {
    .uri = "/historical",
    .method = HTTP_GET,
    .handler = historialPage_get_handler,
    .user_ctx = NULL};

// This function will handle the ip/ request
// It will return a website
esp_err_t indexPage_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, CONTENT_TYPE_HTML);
    return httpd_resp_send(req, currentConditionPage, HTTPD_RESP_USE_STRLEN);
}

const httpd_uri_t indexPage = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = indexPage_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx = NULL};

// Starting the server, if it fails to start the server, then returns NULL.
httpd_handle_t start_webserver()
{
    server_data = initFileServer();

    server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 21;
    config.lru_purge_enable = true;
    config.stack_size = 20480;

    /*This option allows the usage of wildcard*/
    config.uri_match_fn = httpd_uri_match_wildcard;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        ESP_LOGI(TAG_WEB, "WEB server started");
        httpd_register_uri_handler(server, &hostinfo_handler);
        httpd_register_uri_handler(server, &dataNow);
        httpd_register_uri_handler(server, &chartData);
        httpd_register_uri_handler(server, &dayStatsData);
        httpd_register_uri_handler(server, &histFile);

        httpd_register_uri_handler(server, &channel_handler);
        httpd_register_uri_handler(server, &magnumjs);
        httpd_register_uri_handler(server, &magnumStyle);
        httpd_register_uri_handler(server, &jquery_11);
        httpd_register_uri_handler(server, &excanvasJS);
        httpd_register_uri_handler(server, &jquery_float);
        httpd_register_uri_handler(server, &jquery_threshold);
        httpd_register_uri_handler(server, &howler_handler);
        httpd_register_uri_handler(server, &alarm_handler);
        httpd_register_uri_handler(server, &date_handler);
        httpd_register_uri_handler(server, &getUrlParam);

        httpd_register_uri_handler(server, &downloadFile);
        httpd_register_uri_handler(server, &file_delete);

        httpd_register_uri_handler(server, &indexPage);
        httpd_register_uri_handler(server, &histPage);
        httpd_register_uri_handler(server, &histMonthPage);

        ESP_LOGI(TAG_WEB, "Current free heap %zu", esp_get_free_heap_size());

        return server;
    }
    ESP_LOGI(TAG_WEB, "WEB failed to start");
    return NULL;
}

/**
 * Stop the webserver and free the file server allocated memory
 */
void stop_webserver(httpd_handle_t server)
{
    if (server_data)
        free(server_data);
    // Stop the httpd server
    httpd_stop(server);
    ESP_LOGI(TAG_WEB, "This server has stopped");
}