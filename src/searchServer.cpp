#include "searchServer.h"
#include <vector>

std::set<std::string> SearchServer::getUniqueWord(std::string &query){
    std::set<std::string> uniqueWords;

    if (query.empty()){
        std::cout << "Query is empty!" << std::endl;
    }
    else {
        std::regex pat{R"((\w+))"};
        for (std::sregex_iterator it(query.begin(),query.end(),pat); 
                                  it!=std::sregex_iterator{}; ++it){

            uniqueWords.insert(it->str());

        }
    }
    return uniqueWords;
};


std::vector<std::vector<RelativeIndex>> SearchServer::search (  const std::vector<std::string>& queries, 
                                                                const int& responsesLimit){

    std::vector<std::vector<RelativeIndex>> relativeIndex;
    std::vector<std::set<std::string>> uniqueWordsList;

    for (auto querie:queries) {

        uniqueWordsList.push_back(getUniqueWord(querie));

    }

    for (auto &uniqueWords: uniqueWordsList) {

        std::map<size_t,size_t> absoluteRelevance;
        size_t maxRelevance = 1;

        for (auto word:uniqueWords) {

            std::vector<Entry> repetWordInDocs = index.getWordCount(word);
            
            if (!repetWordInDocs.empty()) {
                for (auto dataByDocs:repetWordInDocs) {

                    absoluteRelevance[dataByDocs.docId]+=dataByDocs.count;

                    if (absoluteRelevance[dataByDocs.docId] > maxRelevance){
                        
                        maxRelevance = absoluteRelevance[dataByDocs.docId];
                    }   
                }
            }
        }

        std::vector<RelativeIndex> queryResults;

        if (!absoluteRelevance.empty()){

            for (auto ell:absoluteRelevance){

                RelativeIndex relativeRelevance(ell.first,float(ell.second)/float(maxRelevance));
                queryResults.push_back(relativeRelevance);
            }

            std::sort(begin(queryResults),end(queryResults),[](RelativeIndex a, RelativeIndex b){

                return (a.rank>b.rank);

            });
            
            if (queryResults.size()>responsesLimit) { 
                queryResults.erase(queryResults.begin()+responsesLimit,queryResults.end());
            }
        }
        relativeIndex.push_back(queryResults);
    }

    return relativeIndex;

};