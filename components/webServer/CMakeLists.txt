idf_component_register(SRCS "webServer.cpp" "file_server.cpp" "Data2Web.cpp"
                        REQUIRES "esp_http_server" "json" "SDCard"

                    INCLUDE_DIRS "include")
    