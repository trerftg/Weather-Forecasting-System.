#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_URL "https://api.openweathermap.org/data/2.5/weather?q=kolkata&appid=1ee4b410571f815e21ff5b4b544f704d"

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((char *)contents)[size * nmemb] = '\0';
    printf("%s", (char *)contents);
    printf("\n");
    return size * nmemb;
}

int main()
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Failed to retrieve weather data: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
