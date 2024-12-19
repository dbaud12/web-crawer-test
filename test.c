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


