#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>

#include <mongocxx/exception/exception.hpp>

#include <mongocxx/instance.hpp>

#include <mongocxx/uri.hpp>

#include <iostream>

//for query
#include <bsoncxx/builder/stream/document.hpp>
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::finalize;

int main()
{
    //Create a mongocxx::instance
    mongocxx::instance instance;
    //Create a MongoDB Client
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["APR_DB"]; // Get the database
    mongocxx::collection apr_status_col = db["APR_Status"]; // Get the collection
    mongocxx::collection locations_col = db["Locations"];

    try
    {
        // Start example code here
        // End example code here
        auto admin = client["admin"];
        admin.run_command(bsoncxx::from_json(R"({ "ping": 1 })"));
        std::cout << "Successfully pinged the MongoDB server." << std::endl;

        //Retrieve all documents in a collection, use find() without any arguments
        // auto cursor = locations_col.find({});
        // for (auto&& document : cursor) 
        // {
        //     std :: string json_str = bsoncxx::to_json(document);
        //     std::cout << json_str << std::endl;
        // }

        //Retrieve documents matching specific crieria,pass a query docment
        auto builder = document{};
        builder << "lift_level1" << 50;
        bsoncxx::document::value query = builder.extract();

        auto cursor = locations_col.find(query.view());
        for (auto&& document : cursor) 
        {
            std::cout << bsoncxx::to_json(document) << std::endl;
        }

    }
    catch (const mongocxx::exception &e)
    {
        std::cout << "An exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}