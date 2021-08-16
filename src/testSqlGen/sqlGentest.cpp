#include "../core/relation.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace SECYAN;

void test_sqlGen(){
    std::string query = "select table1.o_orderkey, table2.o_orderdate, table3.o_shippriority,"\
                        "sum(l_extendedprice * (1 - l_discount)) as revenue\n"\
                        "from customer, orders, lineitem\n"\
                        "where c_mktsegment = 'AUTOMOBILE'\n"\
                        "and o_custkey LIKE 'o_custkey'\n"\
                        "and l_orderkey = o_orderkey\n"\
                        "and o_orderdate < date '1995-03-13'\n"\
                        "and l_shipdate > date '1995-03-13'\n"\
                        "group by o_orderkey, o_orderdate, o_shippriority;";
    std::string annot_name = "q3_annot";
    std::string relation_name = "lineitem_1m";
    // std::vector<std::string> attrNames = {"l_orderkey", "l_partkey", "l_suppkey", "l_linenumber", "l_quantity", "l_extendedprice", "l_discount",
    //          "l_tax", "l_returnflag", "l_linestatus", "l_shipdate", "l_commitdate", "l_receiptdate", "l_shippinstruct",
    //          "l_shipmode", "l_comment"};


    Relation::RelationInfo lineitem_ri = {
            "",
            CLIENT,
            false,
            {"o_orderkey", "l_partkey", "l_suppkey", "l_linenumber", "l_quantity", "l_extendedprice", "l_discount",
             "l_tax", "l_returnflag", "l_linestatus", "l_shipdate", "l_commitdate", "l_receiptdate", "l_shippinstruct",
             "l_shipmode", "l_comment"},
            {Relation::INT, Relation::INT, Relation::INT, Relation::INT, Relation::DECIMAL, Relation::DECIMAL,
             Relation::DECIMAL, Relation::DECIMAL, Relation::STRING, Relation::STRING, Relation::DATE, Relation::DATE,
             Relation::DATE, Relation::STRING, Relation::STRING, Relation::STRING},
            20,
            false
    };
    Relation::AnnotInfo lineitem_ai = {false, true};
    Relation lineitem(lineitem_ri, lineitem_ai);


    std::string sql = lineitem.annotSqlGen(query, annot_name, relation_name);
    std::cout << sql << std::endl;
}

int main(){
    std::cout << "run test of sqlGen" << std::endl;
    test_sqlGen();
}