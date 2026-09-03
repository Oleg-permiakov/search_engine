#include <iostream>
#include <filesystem>
#include <string>
#include "ConverterJSON.h"
#include <vector>
#include "invertedIndex.h"
#include "searchServer.h"
#include <fstream>
#include <nlohmann/json.hpp>



int main() {
    ConverterJSON searcher;
    auto input_docs = searcher.GetTextDocuments(); /*обновление текста документов*/

    auto rent = searcher.GetResponsesLimit(); /*колличество запросов*/
    std::cout << "Maximum number of request: " << rent << std::endl;

    auto queries_input = searcher.GetRequests(); /*список запросов по строкам словам*/

    InvertedIndex idx;
    idx.UpdateDocumentBase(input_docs);

    SearchServer search_server(idx);
    auto result = search_server.search(queries_input);

    searcher.putAnswers(result);

    return 0;
}
