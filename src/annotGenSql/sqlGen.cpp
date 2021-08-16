#include "sqlGen.h"

std::string opToStr(const hsql::OperatorType& op){
  static const std::map<const hsql::OperatorType, const std::string> operatorToToken = {
      {hsql::kOpNone, "None"},
      {hsql::kOpBetween, "BETWEEN"},
      {hsql::kOpCase, "CASE"},
      {hsql::kOpCaseListElement, "CASE LIST ELEMENT"},
      {hsql::kOpPlus, "+"},
      {hsql::kOpMinus, "-"},
      {hsql::kOpAsterisk, "*"},
      {hsql::kOpSlash, "/"},
      {hsql::kOpPercentage, "%"},
      {hsql::kOpCaret, "^"},
      {hsql::kOpEquals, "="},
      {hsql::kOpNotEquals, "!="},
      {hsql::kOpLess, "<"},
      {hsql::kOpLessEq, "<="},
      {hsql::kOpGreater, ">"},
      {hsql::kOpGreaterEq, ">="},
      {hsql::kOpLike, "LIKE"},
      {hsql::kOpNotLike, "NOT LIKE"},
      {hsql::kOpILike, "ILIKE"},
      {hsql::kOpAnd, "AND"},
      {hsql::kOpOr, "OR"},
      {hsql::kOpIn, "IN"},
      {hsql::kOpConcat, "CONCAT"},
      {hsql::kOpNot, "NOT"},
      {hsql::kOpUnaryMinus, "-"},
      {hsql::kOpIsNull, "IS NULL"},
      {hsql::kOpExists, "EXISTS"}
    };
    std::string optostr;
    const auto found = operatorToToken.find(op);
    if (found == operatorToToken.cend()) {
      optostr =  static_cast<uint64_t>(op);
    } else {
      optostr = (*found).second;
    }
    return optostr;
}

void addOperatorExpression_Annot(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot){
  if (expr == nullptr) {
      sql += "null";
      return;
    }
  sql += " ( ";
  addExpression(expr->expr, sql, attr_flag, annot_owner, IsInAnnot);
  sql += " ";
  sql += opToStr(expr->opType);
  sql += " ";
  if (expr->expr2 != nullptr) {
      addExpression(expr->expr2, sql, attr_flag, annot_owner, IsInAnnot);
  } else if (expr->exprList != nullptr) {
      for (hsql::Expr* e : *expr->exprList) 
        addExpression(e, sql, attr_flag, annot_owner, IsInAnnot);
  }
  sql += " ) ";
}

void addOperatorExpression_Where(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot){
  if (expr == nullptr) {
      sql += "null";
      return;
    }
    // the order is right first then left

    // the first expression on the right of AND
    // check the right part
    if(checkIsCondIsOwner(expr->expr2, attr_flag)){
      std::string tmp_str("");
      // is condition clause?
      if(sql.size()){
        sql += "and";
      }
      // last param = true, so that this can give the string form of op expression
      // but do not want to change annot_owner , so set it to true
      bool tmp_annot_owner = true;
      addExpression(expr->expr2, tmp_str, attr_flag, tmp_annot_owner, true);
      sql += tmp_str;
    }
    // check the left part
    if(expr->expr != nullptr){
      if(expr->expr->opType == hsql::kOpAnd){
        addOperatorExpression_Where(expr->expr, sql, attr_flag, annot_owner, IsInAnnot);
      }  
      else{
        // op is not AND, means end of where clause
        // handle the last op expression
        // expr->expr = the last op expression
        if(checkIsCondIsOwner(expr->expr, attr_flag)){
          std::string tmp_str("");
          // is condition clause?
          if(sql.size())
            sql += "and";
          // last param = true, so that this can give the string form of op expression
          // but do not want to change annot_owner , so set it to true
          bool tmp_annot_owner = true;
          addExpression(expr->expr, tmp_str, attr_flag, tmp_annot_owner, true);
          sql += tmp_str;
        }
      }
    }

    //TODO: consider when the expression on the left is a combined one
    // expr->exprLists
}

bool checkIsCondIsOwner(hsql::Expr* expr, std::string attr_flag){
  // expr is an expression with an operator
  // check 
  bool flag = true;
  // IsOwner
  
  std::string tmp_str = std::string(expr->expr->name);
  if(tmp_str.substr(0,tmp_str.find("_")) != attr_flag)
      flag = false;
  // IsCondition
  // is not columnref type
  if(expr->expr2->isType(hsql::kExprColumnRef))
    flag = false;
  
  return flag;
}

void addExpression(hsql::Expr* expr, std::string& sql, std::string attr_flag, bool& annot_owner, bool IsInAnnot) {
    if (!expr) return;
    switch (expr->type) {
    case hsql::kExprStar:
      sql += "*";
      break;
    case hsql::kExprColumnRef:
      sql += " ";
      sql += expr->name;
      if(IsInAnnot && !annot_owner){
        annot_owner = std::string (expr->name).substr(0,std::string (expr->name).find("_")) == attr_flag;
      }
      break;
    case hsql::kExprLiteralFloat:
      sql += expr->fval;
      break;
    case hsql::kExprLiteralInt:
      sql += " ";
      sql += std::to_string(expr->ival);
      sql += " ";
      break;
    case hsql::kExprLiteralString:
      sql += "'";
      sql += expr->name;
      sql += "'";
      break;
    case hsql::kExprLiteralDate:
      sql += "'";
      sql += expr->name;
      sql += "'";
      break;
    case hsql::kExprLiteralNull:
      sql += "NULL";
      break;
    case hsql::kExprFunctionRef:
      //sql += expr->name;
      for (hsql::Expr* e : *expr->exprList) addExpression(e, sql, attr_flag, annot_owner, IsInAnnot);
      break;
    case hsql::kExprOperator:
      if(IsInAnnot)
        addOperatorExpression_Annot(expr, sql, attr_flag, annot_owner, IsInAnnot);
      else
        addOperatorExpression_Where(expr, sql, attr_flag, annot_owner, IsInAnnot);
      break;
    case hsql::kExprParameter:
      sql += expr->ival;
      break;
    default:
      std::cerr << "Unrecognized expression type " << expr->type << std::endl;
      return;
    }
    if (expr->alias != nullptr) {
      //sql += " as tb";
      return;
    }
  }

std::string get_attr_flag(std::vector<std::string> ri){
  return ri[0].substr(0,ri[0].find('_'));
}

std::string output_sql(std::string query, std::string annot_name, std::string relation_name, std::vector<std::string> attrNames) {
  std::string attr_flag = get_attr_flag(attrNames);
  //std::cout << attr_flag << std::endl;
  bool annot_owner = false;

  // parse a given query
  hsql::SQLParserResult result;
  hsql::SQLParser::parse(query, &result);

  // result sql
  std::string sql;

  // check whether the parsing was successful
  
  if (result.isValid()) {
    for (auto i = 0u; i < result.size(); ++i) {
      // Print a statement summary.
      const hsql::SQLStatement* statement = result.getStatement(i);
      // select clause
      if(statement->isType(hsql::kStmtSelect)){
        // select is the whole query, including where clause
          const auto* select = static_cast<const hsql::SelectStatement*>(statement);
          //std::cout << (*select->selectList).size() << std::endl;
          std::string annot;
          // select clause
          for (hsql::Expr* expr : *select->selectList){
            // annotation clause part
            if(expr->isType(hsql::kExprFunctionRef)){
              addExpression(expr, annot, attr_flag, annot_owner, true);
            }
          }
          // where clause part
          std::string sql_where;
          addExpression(select->whereClause, sql_where, attr_flag, annot_owner, false);
        sql += "select *,\n";
        //std::cout << annot_owner << std::endl;
        if(annot_owner){
          if(!sql_where.empty()){
            sql += "case\n";
            sql += "when" + sql_where + " then cast( " + annot + "as Integer)\n";
            sql += "else 0\n";
            sql += "end as " + annot_name + "\n";
            sql += "from " + relation_name + ";";
          }
          else{
            sql += annot + " as " + annot_name + "\n";
            sql += "from " + relation_name + ";";
          }
        }
        else{
            if(!sql_where.empty()){
            sql += "case\n";
            sql += "when" + sql_where + " then 1 \n";
            sql += "else 0\n";
            sql += "end as " + annot_name + "\n";
            sql += "from " + relation_name + ";";
          }
          else{
            sql += "1 as " + annot_name + "\n";
            sql += "from " + relation_name + ";";
          }
        }
      }
    }
    return sql;
  } else {
    fprintf(stderr, "Given string is not a valid SQL query.\n");
    fprintf(stderr, "%s (L%d:%d)\n",
            result.errorMsg(),
            result.errorLine(),
            result.errorColumn());
    return "";
  }
}
