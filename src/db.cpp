#include "db.hpp"
#include "utils.hpp"

DB::DB() {

}

DB::~DB() {

}

void DB::init() {
    print("system", "INIT: DATABASE");
    print("system", "RUN: INITIALIZING DATABASE");
    load();
}

void DB::load() {
    print("system", "RUN: DATABASE LOADING..");

    print("system", "RUN: READ DATABASE FILE");
    db_file = fopen("db.json", "r");

    print("system", "RUN: CHECK DATABASE FILE");
    if (!db_file) {
        print("system", "RUN: WRITE DATABASE FILE");
        db_file = fopen("db.json", "w");
        fputs("{}", db_file);
        fclose(db_file);
    }

    char readBuffer[BUFFER_SIZE];

    rapidjson::FileReadStream is(db_file, readBuffer, sizeof(readBuffer));

    d.ParseStream(is);

    fclose(db_file);
}

void DB::save(bool withPrettier = false) {
    print("system", "RUN: SAVE DATABASE CHANGES..");

    print("system", "RUN: WRITE DATABASE FILE");
    db_file = fopen("db.json", "w");

    char writeBuffer[BUFFER_SIZE];

    rapidjson::FileWriteStream os(db_file, writeBuffer, sizeof(writeBuffer));

    if (withPrettier) {
        rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
        d.Accept(writer);
    } else {
        rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
        d.Accept(writer);
    }

    fclose(db_file);
}