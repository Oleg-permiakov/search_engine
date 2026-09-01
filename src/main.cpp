#include <iostream>
#include <filesystem>
#include <string>
#include "ConverterJSON.h"
#include <vector>
#include <exception>
#include "invertedIndex.h"
#include "searchServer.h"


int main() {
    ConverterJSON searcher;
    auto input_docs = searcher.GetTextDocuments(); /*обновление текста документов*/
    // std::cout << input_docs.size() << std::endl;
    // for (auto input_doc: input_docs) {
    //     std::cout << input_doc << std::endl;
    // }


    auto rent = searcher.GetResponsesLimit(); /*колличество запросов*/
    std::cout << "Maximum number of request: " << rent << std::endl;

    auto queries_input = searcher.GetRequests(); /*список запросов по строкам словам*/
    // for (auto i : queries_input) {
    //     std::cout << i << std::endl;
    // }

    InvertedIndex idx;
    idx.UpdateDocumentBase(input_docs);
    // auto res = idx.GetWordCount("milk", input_docs);
    // for (auto re: res) {
    //     std::cout << "{"<<re.doc_id<<", "<<re.count<<"}" << std::endl;
    // }

    // auto dict = idx.GetFreqDictionary();
    // for (std::map<std::string, std::vector<Entry>>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    //     std::cout << it->first << " : ";
    //     for (auto res: it->second) {
    //         std::cout <<"{"<< res.doc_id << ", " << res.count <<"}"<< ", ";
    //     }
    //     std::cout << std::endl;
    // }



    SearchServer search_server(idx);
    auto result = search_server.search(queries_input);

    for (auto rel: result) {
        for (auto relative_index: rel) {
            std::cout <<"{"<< relative_index.docs_id <<", "<<relative_index.rank<<"} ";
        }
        std::cout << std::endl;
    }

    searcher.putAnswers(result);


    return 0;
}
