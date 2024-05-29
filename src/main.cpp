#include <iostream>
#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"

main() {

    ConverterJSON converterJSON;
    InvertedIndex base;
    if (converterJSON.configCheck()) {
        base.updateDocumentBase(converterJSON.GetTextDocuments());

        SearchServer searchServer (base);
        converterJSON.putAnswers(searchServer.search(converterJSON.GetRequests(),
                                                    converterJSON.GetResponsesLimit()));
    }

        return 0;
}
