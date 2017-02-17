#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdlib>

#include <bson.h>
#include <mongoc.h>

#include "messaging/MessageTypes.h"

const char * m1 = R"foo(BM+353e7d40-7cbf-4276-8ab8-05dcac4e5d9a+20170710T123456.123+0:0’
FR+b034089d-ba71-49ab-96c1-dbf0e65fed15’
GP+D1+43.123456:-0.842344+875.43+345.43+82.35+7+20170710T123456.123’
TP+S1+12.33:11.28:00.00’
EM+353e7d40-7cbf-4276-8ab8-05dcac4e5d9a+5’)foo";

const char * m2 = R"foo(BM+b0419197-96e2-4a7b-b868-256f63084c7f+20170710T123458.000+0:0’
FR+b034089d-ba71-49ab-96c1-dbf0e65fed15’
GP+D1+43.123460:-0.842360+877.43+355.43+82.35+7+20170710T123456.123’
TP+S1+12.33’
EM+b0419197-96e2-4a7b-b868-256f63084c7f+5’)foo";

template<class T>
void imprime(const std::string v, const T &t) {
    std::cerr << v  << ": ";
    if (t == nullptr) {
        std::cerr << "nulo";
    } else {
        std::cerr << *t;
    }
    std::cerr << std::endl;
}

/*
 * 
 */
int main(int argc, char** argv) {

    mongoc_init();

    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;

    client = mongoc_client_new("mongodb://localhost/?appname=insert-example");
    database = mongoc_client_get_database(client, "test");
    collection = mongoc_client_get_collection(client, "test", "devices");
    
    iot::messaging::Message m(m1);
    std::cerr << m.toString() << std::endl;
    
    m.fromString(m2);
    std::cerr << m.toString() << std::endl;
    
    iot::messaging::Message mm;
    const std::string s = mm.toString();
    
    std::cerr << mm.toString() << std::endl;    
    
    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_client_destroy(client);

    mongoc_cleanup();

    return EXIT_SUCCESS;
}

