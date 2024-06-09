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


void SearchServer::calcAbsoluteRelevance (  std::map<size_t, size_t>& absRel, 
                                            std::string& querie, size_t& maxRel) {
    for (auto word:getUniqueWord(querie)) {
        for (auto dataByDocs:index.getWordCount(word)) {

            absRel[dataByDocs.docId]+=dataByDocs.count;

            if (absRel[dataByDocs.docId] > maxRel){
                maxRel = absRel[dataByDocs.docId];
            }
        }
    }
};


void SearchServer::calcRelativeRelevance (  std::vector<RelativeIndex>& queryResults, 
                                            std::map<size_t,size_t>& absRel, size_t& maxRel) {
    for (auto value:absRel){

        RelativeIndex relativeRelevance(value.first,float(value.second)/float(maxRel));
        queryResults.push_back(relativeRelevance);
    }

    std::sort(begin(queryResults),end(queryResults),[](RelativeIndex a, RelativeIndex b){
        return (a.rank>b.rank);
    });

};
    

std::vector<std::vector<RelativeIndex>> SearchServer::search (  const std::vector<std::string>& queries, 
                                                                const int& responsesLimit){
    std::vector<std::vector<RelativeIndex>> relativeIndex;
    for (auto querie:queries) {
        
        std::map<size_t,size_t>absoluteRelevance;
        size_t maxRelevance = 1;
        calcAbsoluteRelevance(absoluteRelevance,querie,maxRelevance);

        std::vector<RelativeIndex> queryResults;
        calcRelativeRelevance(queryResults,absoluteRelevance,maxRelevance);

        if (queryResults.size() > responsesLimit) { 
            queryResults.erase(queryResults.begin() + responsesLimit,queryResults.end());
        }
       
        relativeIndex.emplace_back(queryResults);
    }

    return relativeIndex;

};