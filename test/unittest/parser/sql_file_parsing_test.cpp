//
// Created by jinhai on 23-3-5.
//

#include <gtest/gtest.h>
#include "base_test.h"
#include "common/types/internal_types.h"
#include "parser/parser_result.h"
#include "parser/sql_parser.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <streambuf>

class SQLFileParsingTest : public BaseTest {
    void
    SetUp() override {
    }

    void
    TearDown() override {
    }
};

TEST_F(SQLFileParsingTest, tpch) {
    using namespace infinity;

    SharedPtr <SQLParser> parser = MakeShared<SQLParser>();
    SharedPtr <ParserResult> result = MakeShared<ParserResult>();

    // Get all tpch sql text;
    std::filesystem::path file_path("../../../test/unittest/parser/test_data/tpch");

    for(const auto& p: std::filesystem::recursive_directory_iterator(file_path)) {
//        std::cout << p.path().c_str() << std::endl;
        std::ifstream t(p.path().c_str());
        String input_sql((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        parser->Parse(input_sql, result);
        result->Reset();
    }
}

void
ReadSQLs(const String& file_path, Vector<String>& sqls) {
    std::ifstream infile(file_path);
    String line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        // Skip comments.
        if (line[0] == '#' || (line[0] == '-' && line[1] == '-')) {
            continue;
        }
        if(line[0] == '!') {
            line = line.substr(1);
        }
        sqls.emplace_back(line);
    }
}

TEST_F(SQLFileParsingTest, hyrise) {
    using namespace infinity;

    SharedPtr <SQLParser> parser = MakeShared<SQLParser>();
    SharedPtr <ParserResult> result = MakeShared<ParserResult>();

    // Get all tpch sql text;
    std::filesystem::path good_sql_path("../../../test/unittest/parser/test_data/hyrise/good.sql");
    std::filesystem::path bad_sql_path("../../../test/unittest/parser/test_data/hyrise/bad.sql");

    Vector<String> sqls;
    ReadSQLs(good_sql_path, sqls);
    for(auto& input_sql: sqls) {
//        std::cout << input_sql << std::endl;
        parser->Parse(input_sql, result);
        result->Reset();
    }

    ReadSQLs(bad_sql_path, sqls);
    for(auto& input_sql: sqls) {
//        std::cout << input_sql << std::endl;
        parser->Parse(input_sql, result);
        result->Reset();
    }
}