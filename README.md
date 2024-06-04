# Search Engine - корпоративный поисковый движок.
### Сборка проекта под  ОС Windows:
___
Для сборки нам понадобится: 
1. [CMake версии 3.27.7](https://cmake.org/download/),
2. Компилятор 
[MinGW версии 13.2.0](https://github.com/niXman/mingw-builds-binaries/releases/tag/13.2.0-rt_v11-rev1).
___
1. Скачиваем проект себе на компьютер. В корне проекта создаем папку  build и переходим в нее.
<pre>
C:\>cd search-engine-main
C:\search-engine-main>md build
C:\search-engine-main>cd build
C:\search-engine-main\build>
</pre>

2. Генерируем с помошью cmake и компилятора MinGW сборочные файлы.
<pre>
C:\search-engine-main\build>cmake .. -G "MinGW Makefiles"

3. Собираем проект
<pre>
C:\search-engine-main\build>cmake --build .
</pre>
Собранный файл ___search_engine.exe___ находится в папке ___src___ дирректории ___build___.
Мы можем перейти в папку ___src___ и попробовать запустить его.
<pre>
C:\search-engine-main\build\srs> search_engine.exe
</pre>
Но программа выдаст нам ошибку:
<pre>
Error! File config.json is missing
</pre>
Для корректной работы программы необходимо в диреректорию с исполняемым файлом добавить файл конфигурации  ___config.json___, 
файл с запросами  ___requests.json.___ и файлы по которым будет осуществляться поиск.
Примеры всех этих файлов находятся папке ___examples___.


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
####  Пример answers.json
<pre>
{"answers":{"request_1":{"relevance":[{"docid":0,"rank":1.0},{"docid":2,"rank":1.0}],"result":true},"request_2":{"relevance":[{"docid":1,"rank":1.0},{"docid":0,"rank":0.7142857313156128},{"docid":2,"rank":0.5714285969734192}],"result":true},"request_3":[{"docid":0,"rank":1.0}],"request_4":{"result":false},"request_5":{"result":false}}}
</pre>
### Классы:
___
Проект содержит три основных класса ___"ConverterJSON"___, ___"InvertedIndex"___, ___"SearchServer"___.

___ConverterJSON___ имеет методы, позволяющие извлекать данные из JSON-файлов, и наоборот, 
конвертировать и сохранять данные в JSON-файлы.

___InvertedIndex___ имеет методы, позволяющие обновлять базу данных документов, и получать
количество встречи слова в тексте документов из базы данных.

___SearchServer___ имеет метод поиска и вычисления релевантности документов 
на основе полученных запросов.
___


### Библиотеки:
___
1. библиотека ___[nlohmann/json](https://github.com/nlohmann/json?ysclid=lrq5qo3vz517308901)___ для работы с форматом JSON.
2. библиотека ___[Google Tests](https://github.com/google/googletest?ysclid=lrq6bc00wy323673298)___ 
для тестирования отдельных модулей проекта. 
___


