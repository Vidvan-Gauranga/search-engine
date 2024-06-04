# Search Engine - корпоративный поисковый движок.

### Принцип работы поискового движка:
___
1. В конфигурационном файле ___config.json___  в поле ___files___ перед запуском приложения
задаются названия файлов, по которым движок будет осуществлять поиск.
2. Поисковый движок обходит все файлы и индексирует их.
3. Пользователь задаёт запрос через JSON-файл ___requests.json.___ Запрос — это
набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
максимальное количество возможных документов в ответе задаётся в
конфигурационном файле ___config.json.___ в поле ___max_response___
7. В конце программа формирует файл ___answers.json,___ в который записывает
результаты поиска.

___Для корректной работы файлы config.json и requests.json необходимо расположить в директории с проекта.___

___

#### Пример config.json
<pre>
{
    "config":
    {
        "max_responses":5,
        "name":"SkillboxSearchEngine",
        "version":"0.1"
    },
    "files":
    [
        "resources/file000.txt",
        "resources/file001.txt",
        "resources/file002.txt"
    ]
}
</pre>

####  Пример requests.json
<pre>
{
    "requests":
    [
        "hello world",
        "the program",
        "fundamental components",
        "Moscow",
        "metropolitan"
    ]
}
</pre>
___
Проект содержит три основных класса ___"ConverterJSON"___, ___"InvertedIndex"___, ___"SearchServer"___.

___ConverterJSON___ имеет методы, позволяющие извлекать данные из JSON-файлов, и наоборот, 
конвертировать и сохранять данные в JSON-файлы.

___InvertedIndex___ имеет методы, позволяющие обновлять базу данных документов, и получать
количество встречи слова в тексте документов из базы данных.

___SearchServer___ имеет единственный метод поиска и вычисления релевантности документов 
на основе полученных запросов.
___
Проект для сборки использует: 
1. [CMake версии 3.27.7](https://cmake.org/download/),
2. Компилятор 
[MinGW версии 13.2.0](https://github.com/niXman/mingw-builds-binaries/releases/tag/13.2.0-rt_v11-rev1).

В проекте использовались:
1. библиотека ___[nlohmann/json](https://github.com/nlohmann/json?ysclid=lrq5qo3vz517308901)___ для работы с форматом JSON.
2. библиотека ___[Google Tests](https://github.com/google/googletest?ysclid=lrq6bc00wy323673298)___ 
для тестирования отдельных модулей проекта. 
___
