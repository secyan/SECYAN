#include <stdlib.h>
#include <string>
#include <iostream>
// include the sql parser
#include "SQLParser.h"
#include <map>
#include <vector>

std::string output_sql(std::string query, std::string annot_name, std::string relation_name, std::vector<std::string> attrNames);
std::string opToStr(const hsql::OperatorType& op);
void addExpression(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot);
void addOperatorExpression_Annot(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot);
void addOperatorExpression_Where(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot);
bool checkIsCondIsOwner(hsql::Expr* expr, std::string attr_flag);
std::string get_attr_flag(std::vector<std::string> ri);