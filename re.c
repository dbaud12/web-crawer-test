#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

// HTML에서 URL 추출 함수
void extract_urls(const char *file_path) {
    // HTML 파일 파싱
    htmlDocPtr doc = htmlReadFile(file_path, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse HTML file: %s\n", file_path);
        return;
    }

    // XPath를 사용하여 <a> 태그의 href 속성 추출
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)"//a/@href", context);

    if (result && result->nodesetval) {
        xmlNodeSetPtr nodes = result->nodesetval;
        printf("Extracted URLs:\n");
        for (int i = 0; i < nodes->nodeNr; i++) {
            xmlNodePtr node = nodes->nodeTab[i];
            if (node->type == XML_ATTRIBUTE_NODE) {
                printf("- %s\n", (const char *)node->children->content);
            }
        }
    } else {
        printf("No URLs found in the HTML.\n");
    }

    // 리소스 해제
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
}

int main() {
    const char *url = "http://www.joungul.co.kr/";
    const char *output_file = "downloaded.html";

    // 1. wget을 사용하여 HTML 다운로드
    char command[256];
    snprintf(command, sizeof(command), "wget -q -O %s %s", output_file, url);
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to execute wget for URL: %s\n", url);
        return 1;
    }
    printf("HTML downloaded successfully to %s\n", output_file);

    // 2. 다운로드한 HTML 파일에서 URL 추출
    extract_urls(output_file);

    return 0;
}

