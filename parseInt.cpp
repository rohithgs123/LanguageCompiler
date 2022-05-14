#include <vector>
#include <string>
#include<cmath>
#include "parseInt.h"
#include "val.h"
//#include "lex.cpp"
using namespace std;
map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; // Container of temporary locations of Value objects for results of expressions, variables values and constants
queue<Value> *ValQue;			 // declare a pointer variable to a queue of Value objects

namespace Parser// cout << "convering to real" <<endl;
{
	bool pushed_back = false;// cout << "convering to real" <<endl;
	LexItem pushed_token;// cout << "convering to real" <<endl;

	static LexItem GetNextToken(istream &in, int &line)// cout << "convering to real" <<endl;
	{
		if (pushed_back)// cout << "convering to real" <<endl;
		{
			pushed_back = false;// cout << "convering to real" <<endl;
			return pushed_token;// cout << "convering to real" <<endl;
		}
		return getNextToken(in, line);// cout << "convering to real" <<endl;
	}

	static void PushBackToken(LexItem &t)// cout << "convering to real" <<endl;
	{
		if (pushed_back)// cout << "convering to real" <<endl;
		{
			abort();// cout << "convering to real" <<endl;
		}
		pushed_back = true;// cout << "convering to real" <<endl;
		pushed_token = t;// cout << "convering to real" <<endl;
	}

}

static int error_count = 0;// cout << "convering to real" <<endl;

int ErrCount()// cout << "convering to real" <<endl;
{
	return error_count;// cout << "convering to real" <<endl;
}

void ParseError(int line, string msg)// cout << "convering to real" <<endl;
{
	++error_count;// cout << "convering to real" <<endl;
	cout << line << ": " << msg << endl;// cout << "convering to real" <<endl;
}

bool checkVar(string lexeme, int &line)// cout << "convering to real" <<endl;
{

	if (!(defVar.find(lexeme)->second))// cout << "convering to real" <<endl;
	{
		ParseError(line, "Using Undefined Variable");// cout << "convering to real" <<endl;
		return false;// cout << "convering to real" <<endl;
	}
	return true;// cout << "convering to real" <<endl;
}

void unaryOperation(int plusminus, Value &retValue)// cout << "convering to real" <<endl;
{
	if (plusminus == 0){// cout << "convering to real" <<endl;
		return;// cout << "convering to real" <<endl;
	}

	if (retValue.IsInt())// cout << "convering to real" <<endl;
	{
		retValue.SetInt(retValue.GetInt() * plusminus);// cout << "convering to real" <<endl;
	}
	else if (retValue.IsReal())// cout << "convering to real" <<endl;
	{
		retValue.SetReal(retValue.GetReal() * plusminus);// cout << "convering to real" <<endl;
	}
	else{
		retValue = Value();// cout << "convering to real" <<endl;
	}
}

bool updateValues(string varname, Value value, int line)// cout << "convering to real" <<endl;
{
	if (!checkVar(varname, line))// cout << "convering to real" <<endl;
	{
		ParseError(line, "Using Undefined Variable");// cout << "convering to real" <<endl;
		return false;// cout << "convering to real" <<endl;
	}

	Token tk = SymTable.find(varname)->second;// cout << "convering to real" <<endl;

	if (((tk == STRING) || (tk == SCONST)) || (value.GetType() == VSTRING)){// cout << "convering to real" <<endl;
		if (!(((tk == STRING) || (tk == SCONST)) & (value.GetType() == VSTRING))){// cout << "convering to real" <<endl;
			// cout << (tk==STRING)  << " "<< value.GetType() << endl;
			return false;// cout << "convering to real" <<endl;
		}
	}

	if (tk == REAL){
		if (value.IsInt()){
			// cout << "convering to real" <<endl;
			value = Value((float)value.GetInt());// cout << "convering to real" <<endl;
		}
	}

	if (tk == INTEGER){// cout << "convering to real" <<endl;
		if (value.IsReal()){// cout << "convering to real" <<endl;
			// cout << "convering to real" <<endl;
			value = Value((int)value.GetReal());// cout << "convering to real" <<endl;
		}
	}

	if (TempsResults.find(varname) != TempsResults.end()){// cout << "convering to real" <<endl;
		TempsResults.find(varname)->second = value;// cout << "convering to real" <<endl;
	}
	else{// cout << "convering to real" <<endl;
		TempsResults.insert({varname, value});// cout << "convering to real" <<endl;
	}

	return true;// cout << "convering to real" <<endl;
}

Value getValueFromVariable(LexItem tk, int line)// cout << "convering to real" <<endl;
{
	if (!checkVar(tk.GetLexeme(), line))// cout << "convering to real" <<endl;
	{
		ParseError(line, "Using Undefined Variable");// cout << "convering to real" <<endl;
		return Value();
	}
	// cout << "Value of variable " << tk.GetLexeme() << " is " << TempsResults.find(tk.GetLexeme())->second << endl;
	if (TempsResults.find(tk.GetLexeme()) != TempsResults.end()){// cout << "convering to real" <<endl;
		return TempsResults.find(tk.GetLexeme())->second;// cout << "convering to real" <<endl;
	}
	return Value();// cout << "convering to real" <<endl;
}

Value valueFromConstToken(LexItem Lexi, int line)// cout << "convering to real" <<endl;
{
	Token tk = Lexi.GetToken();// cout << "convering to real" <<endl;
	string lexme = Lexi.GetLexeme();
	// cout << "value from const " << Lexi << " " << lexme << endl;
	if (tk == ICONST)// cout << "convering to real" <<endl;
		return Value(stoi(lexme));// cout << "convering to real" <<endl;
	else if (tk == RCONST)// cout << "convering to real" <<endl;
		return Value(stof(lexme));// cout << "convering to real" <<endl;
	else if (tk == SCONST)// cout << "convering to real" <<endl;
		return Value(lexme);// cout << "convering to real" <<endl;
	else if (tk == IDENT)// cout << "convering to real" <<endl;
		return getValueFromVariable(Lexi, line);// cout << "convering to real" <<endl;

	return Value();// cout << "convering to real" <<endl;
}


Value initializeValue(LexItem tk, int line)// cout << "convering to real" <<endl;
{

	if (!checkVar(tk.GetLexeme(), line))// cout << "convering to real" <<endl;

	{
		ParseError(line, "Using Undefined Variable");// cout << "convering to real" <<endl;

		return Value();// cout << "convering to real" <<endl;

	}
	Token token = SymTable.find(tk.GetLexeme())->second;// cout << "convering to real" <<endl;


	if (token == INTEGER)// cout << "convering to real" <<endl;

		return Value((int)0);// cout << "convering to real" <<endl;

	else if (token == REAL)// cout << "convering to real" <<endl;

		return Value((float)0.0);// cout << "convering to real" <<endl;

	else if (token == STRING)// cout << "convering to real" <<endl;

		return Value("");// cout << "convering to real" <<endl;

	return Value();// cout << "convering to real" <<endl;

}

bool addVar(string lexeme, Token tk, int &line)// cout << "convering to real" <<endl;

{
	// cout << "adding" << lexeme << endl;
	if (!(defVar.find(lexeme) == defVar.end()))// cout << "convering to real" <<endl;

	{
		ParseError(line, "Variable Redefinition");// cout << "convering to real" <<endl;

		return false;// cout << "convering to real" <<endl;

	}
	defVar.insert({lexeme, true});// cout << "convering to real" <<endl;

	// SymTable.insert({lexeme, tk});
	return true;// cout << "convering to real" <<endl;

}

void updateSymTable(Token tk){// cout << "convering to real" <<endl;


	map<string, bool>::iterator it;// cout << "convering to real" <<endl;


	for (it = defVar.begin(); it != defVar.end(); it++){// cout << "convering to real" <<endl;

		if (SymTable.find(it->first) == SymTable.end()){// cout << "convering to real" <<endl;

			SymTable.insert({it->first, tk});// cout << "convering to real" <<endl;

		}

	}
}
// bool IdentList(istream &in, int &line, vector<string> &IdList);

bool Prog(istream &in, int &line)// cout << "convering to real" <<endl;

{

	LexItem tk = Parser::GetNextToken(in, line);
	// Token prog = tk.GetToken();
	if (tk != PROGRAM)
	{
		ParseError(line, "Missing PROGRAM.");
		return false;
	}
	tk = Parser::GetNextToken(in, line);
	if (tk != IDENT)
	{
		ParseError(line, "Missing Program Name");
		return false;
	}
	// if (!addVar(tk.GetLexeme(), prog, line))
	// {
	// 	ParseError(line, "Variable exists");
	// 	return false;
	// }

	tk = Parser::GetNextToken(in, line);
	if (tk != SEMICOL)
	{
		ParseError(line, "no semicolon");
		return false;
	}

	if (!DeclBlock(in, line))
	{
		ParseError(line, "error in decl body");
		return false;
	};
	if (!ProgBody(in, line))
	{
		ParseError(line, "error in prog body");
		return false;
	};

	return true;
}

bool DeclBlock(istream &in, int &line)
{
	LexItem tk = Parser::GetNextToken(in, line);
	// cout << tk.GetLexeme() << endl;
	if (tk != VAR)
	{
		ParseError(line, "Non-recognizable Declaration Block.");
		return false;
	}

	Token token = SEMICOL;
	while (token == SEMICOL)
	{
		bool decl = DeclStmt(in, line);
		tk = Parser::GetNextToken(in, line);
		token = tk.GetToken();
		// cout << "here" << tk.GetLexeme() << endl;
		if (tk == BEGIN)
		{
			Parser::PushBackToken(tk);
			break;
		}
		if (!decl)
		{
			ParseError(line, "decl block error");
			return false;
		}
		if (tk != SEMICOL)
		{
			ParseError(line, "semi colon missing");
			return false;
		}
	}

	return true;
}
bool DeclStmt(istream &in, int &line)
{
	LexItem tk = Parser::GetNextToken(in, line);
	if (tk == BEGIN)
	{
		Parser::PushBackToken(tk);
		return false;
	}
	while (tk == IDENT)
	{
		if (!addVar(tk.GetLexeme(), tk.GetToken(), line))
		{
			ParseError(line, "Incorrect variable in Declaration Statement.");
			return false;
		}
		tk = Parser::GetNextToken(in, line);
		if (tk == COLON)
		{
			break;
		}
		if (tk != COMMA)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tk.GetLexeme() << ")" << endl;
			return false;
		}
		tk = Parser::GetNextToken(in, line);
	}

	tk = Parser::GetNextToken(in, line);
	// cout << tk.GetLexeme() << endl;

	if (!((tk == INTEGER) || (tk == REAL) || (tk == STRING)))
	{
		ParseError(line, "Incorrect Declaration Type");
		return false;
	}
	updateSymTable(tk.GetToken());

	return true;
}
bool ProgBody(istream &in, int &line)
{
	LexItem tk = Parser::GetNextToken(in, line);
	// cout << "in prog body" << tk.GetLexeme() << endl;

	if (tk != BEGIN)
	{
		ParseError(line, "begin missing");
		return false;
	}

	Token token = SEMICOL;
	while (token == SEMICOL)
	{
		bool stmt = Stmt(in, line);
		tk = Parser::GetNextToken(in, line);
		token = tk.GetToken();
		// cout << "here body " << tk.GetLexeme() << endl;
		if (tk.GetToken() == END)
		{
			Parser::PushBackToken(tk);
			break;
		}
		if (!stmt)
		{
			ParseError(line, "Syntactic error in Program Body.");
			return false;
		}
		if (tk != SEMICOL)
		{
			ParseError(line, "Missing semicolon in Statement.");
			return false;
		}
	}

	tk = Parser::GetNextToken(in, line);

	if (tk.GetToken() != END)
	{
		ParseError(line, "end not found");
		return false;
	}

	return true;
}
bool Stmt(istream &in, int &line)
{
	bool status;
	LexItem t = Parser::GetNextToken(in, line);
	// cout << "STMT " << t.GetLexeme()  << t.GetToken() << endl;
	if (t.GetToken() == END)
	{
		Parser::PushBackToken(t);
		return false;
	}
	switch (t.GetToken())
	{
	case WRITELN:
		status = WriteLnStmt(in, line);
		break;
	case IF:
		status = IfStmt(in, line);
		break;
	case IDENT:
		if (!checkVar(t.GetLexeme(), line))
		{
			ParseError(line, "Variable exists");
			return false;
		}
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		break;
	default:
		Parser::PushBackToken(t);
		return false;
	}
	return status;
}
// WriteStmt:= wi, ExpreList
bool WriteLnStmt(istream &in, int &line)
{
	LexItem t;
	// cout << "in WriteStmt" << endl;
	ValQue = new queue<Value>;
	t = Parser::GetNextToken(in, line);
	if (t != LPAREN)
	{

		ParseError(line, "Missing Left Parenthesis");
		return false;
	}

	bool ex = ExprList(in, line);

	if (!ex)
	{
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN)
	{

		ParseError(line, "Missing Right Parenthesis");
		return false;
	}

	// Evaluate: print out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;

	return ex;
} // End of WriteLnStmt
bool IfStmt(istream &in, int &line)
{
	Value val1;
	LexItem tk = Parser::GetNextToken(in, line);
	if (tk != LPAREN)
	{
		ParseError(line, "left paren missing");
		return false;
	}

	bool ex = LogicExpr(in, line, val1);
	if (!ex)
	{
		ParseError(line, "error in Logic");
		return false;
	}
	tk = Parser::GetNextToken(in, line);

	if (tk != RPAREN)
	{
		ParseError(line, "right paren missing");
		return false;
	}

	tk = Parser::GetNextToken(in, line);
	if (tk != THEN)
	{
		ParseError(line, "If-Stmt Syntax Error");
		return false;
	}

	bool stmt;
	if (val1.GetBool())
	{
		stmt = Stmt(in, line);
		if (!stmt)
		{
			ParseError(line, "error in statement");
			return false;
		}
		while(tk != SEMICOL){
			tk = Parser::GetNextToken(in, line);
		}
		Parser::PushBackToken(tk);
	}
	else
	{
		while (tk != ELSE)
		{
			tk = Parser::GetNextToken(in, line);
		}
		Parser::PushBackToken(tk);

		tk = Parser::GetNextToken(in, line);
		if (tk != ELSE)
		{
			Parser::PushBackToken(tk);
		}
		else
		{
			stmt = Stmt(in, line);
			if (!stmt)
			{
				ParseError(line, "error in statement");
				return false;
			}
		}
	}

	return true;
}
bool AssignStmt(istream &in, int &line)
{
	LexItem tk = Parser::GetNextToken(in, line);
	string varname = tk.GetLexeme();
	Value val1 = Value();// initializeValue(tk, line);

	tk = Parser::GetNextToken(in, line);
	if (tk != ASSOP)
	{
		ParseError(line, "Missing Assignment Operator");
		return false;
	}

	bool ex = Expr(in, line, val1);
	if (!ex)
	{
		ParseError(line, "Invalid expression");
		return false;
	}
	// cout <<"Assign " << val1 << tk << endl;
	if (!updateValues(varname, val1, line)){
		ParseError(line, "Illegal Assignment Operation");
		return false;
	}

	return true;
}
bool Var(istream &in, int &line, LexItem &idtok)
{
	LexItem tk = Parser::GetNextToken(in, line);
	if (tk != IDENT)
	{
		ParseError(line, "ident not found");
		return false;
	}
	if (!checkVar(tk.GetLexeme(), line))
	{
		ParseError(line, "wrong expression");
		return false;
	}
	return true;
}
bool ExprList(istream &in, int &line)
{
	Value val1;
	bool expr = Expr(in, line, val1);
	if (!expr)
	{
		ParseError(line, "wring expression");
		return false;
	}

	ValQue->push(val1);

	LexItem tk = Parser::GetNextToken(in, line);
	while (tk == COMMA)
	{

		expr = Expr(in, line, val1);
		if (!expr)
		{
			ParseError(line, "wrong expression");
			return false;
		}
		ValQue->push(val1);
		tk = Parser::GetNextToken(in, line);
	}

	Parser::PushBackToken(tk);
	return true;
}
bool LogicExpr(istream &in, int &line, Value &retVal)
{
	Value val1, val2;
	bool exp = Expr(in, line, val1);

	if (!exp)
	{
		ParseError(line, "Missing expression after relational operator");
		return false;
	}

	LexItem tk = Parser::GetNextToken(in, line);
	// cout << "logic expression " << tk  << " " << tk.GetLexeme() << endl;

	if (!(tk == EQUAL || tk == LTHAN || tk == GTHAN))
	{
		ParseError(line, "symbol not found");
		return false;
	}

	exp = Expr(in, line, val2);

	if (tk == EQUAL) retVal = val1 == val2;
	else if (tk == LTHAN) retVal = val1 < val2;
	else if (tk == GTHAN) retVal = val1 > val2;

	// cout << "retval logic " << retVal.GetBool() << val1 << val2 << endl;

	if (retVal.IsErr()){
		ParseError(line, "Run-Time Error-Illegal Mixed Type Operands for a Logic Expression");
		return false;
	}

	if (!exp)
	{
		ParseError(line, "expression is invalid");
		return false;
	}

	return true;
}
// Expr:= Term {(+|-) Term}
bool Expr(istream &in, int &line, Value &retVal)
{
	Value val1, val2;
	// cout << "in Expr" << endl;
	bool t1 = Term(in, line, val1);
	LexItem tok;

	if (!t1)
	{
		return false;
	}
	retVal = val1;
	// cout << "dsdsd " << retVal << endl;

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	// Evaluate: evaluate the expression for addition or subtraction
	while (tok == PLUS || tok == MINUS)
	{
		t1 = Term(in, line, val2);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == PLUS)
		{
			retVal = retVal + val2;
			if (retVal.IsErr())
			{
				ParseError(line, "Illegal addition operation.");
				// cout << "(" << tok.GetLexeme() << ")" << endl;
				return false;
			}
		}
		else if (tok == MINUS)
		{
			retVal = retVal - val2;
			if (retVal.IsErr())
			{
				ParseError(line, "Illegal subtraction operation.");
				return false;
			}
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
} // end of Expr
bool Term(istream &in, int &line, Value &retVal)
{

	bool lparen = false;
	LexItem tk = Parser::GetNextToken(in, line);
	// cout <<"Term" << tk.GetLexeme() << tk << endl;
	if (tk == LPAREN)
	{
		// tk = Parser::GetNextToken(in, line);
		lparen = true;
	}
	else{
		Parser::PushBackToken(tk);
	}
	Value val1, val2;
	bool sf = SFactor(in, line, val1);
	if (!sf)
	{
		// ParseError(line, "error in pattern");
		return false;
	}

	retVal = val1;

	tk = Parser::GetNextToken(in, line);
	while ((tk == DIV) || (tk == MULT))
	{
		sf = SFactor(in, line, val2);
		if (!sf)
		{
			// ParseError(line, "error in pattern");
			return false;
		}
		if (tk == DIV)
		{
			// cout << "val2 here " << val2  << " " << val2.IsInt() << val2.IsReal() << endl;
			if (val2.IsReal()) if (abs(val2.GetReal()) < 1e-14){

				ParseError(line, "Run-Time Error-Illegal Division by Zero.");
				// cout << "(" << tok.GetLexeme() << ")" << endl;
				return false;
			}
			if (val2.IsInt()) if (val2.GetInt() == 0){

				ParseError(line, "Run-Time Error-Illegal Division by Zero.");
				// cout << "(" << tok.GetLexeme() << ")" << endl;
				return false;
			}
			retVal = val1 / val2;
			if (retVal.IsErr())
			{
				ParseError(line, "Illegal division operation.");
				// cout << "(" << tok.GetLexeme() << ")" << endl;
				return false;
			}
		}
		else if (tk == MULT)
		{
			retVal = val1 * val2;
			if (retVal.IsErr())
			{
				ParseError(line, "Illegal multiplication operation.");
				// cout << "(" << tok.GetLexeme() << ")" << endl;
				return false;
			}
		}
		tk = Parser::GetNextToken(in, line);
	}

	Parser::PushBackToken(tk);
	// cout << "Term " << tk.GetLexeme() << endl;
	if (lparen)
	{
		tk = Parser::GetNextToken(in, line);
		if (tk != RPAREN)
		{
			ParseError(line, "Missing ) after expression");
			return false;
		}
	}

	return true;
}
bool SFactor(istream &in, int &line, Value &retVal)
{
	bool lparen = false;
	int sign = 0;
	LexItem tk = Parser::GetNextToken(in, line);
	// cout <<"SFactor " << tk.GetLexeme() << tk << endl;
	if (tk == LPAREN)
	{
		tk = Parser::GetNextToken(in, line);
		lparen = true;
	}
	if (!(tk == PLUS || tk == MINUS))
	{
		Parser::PushBackToken(tk);
	}
	else
	{
		if (tk == MINUS)
		{
			sign = -1;
		}
		else if (tk == PLUS){
			sign = 1;
		}
	}

	if (tk == EQUAL || tk == MULT || tk == DIV)
	{
		// ParseError(line, "invalid symbol");
		return false;
	}

	bool fac = Factor(in, line, sign, retVal);
	if (!fac)
	{
		// ParseError(line, "the variable or const not available");
		return false;
	}

	if (lparen)
	{
		tk = Parser::GetNextToken(in, line);
		if (tk != RPAREN)
		{
			ParseError(line, "Missing ) after expression");
			return false;
		}
	}

	return true;
}
bool Factor(istream &in, int &line, int sign, Value &retVal)
{
	LexItem tk = Parser::GetNextToken(in, line);
	if (!(tk == IDENT || tk == ICONST || tk == RCONST || tk == SCONST))
	{
		Parser::PushBackToken(tk);
		bool expr = Expr(in, line, retVal);
		if (!expr)
		{
			ParseError(line, "invalid expression");
			return false;
		}
	}
	else
	{
		Value val1 = valueFromConstToken(tk, line);
		// cout << "Factor value " << val1 << val1.IsErr() << tk.GetLexeme()<< endl;
		if (val1.IsErr()){
			ParseError(line, "Undefined Variable");
			return false;
		}
		unaryOperation(sign, val1);
		if (val1.IsErr()){
			ParseError(line, "Illegal Operand Type for Sign Operator");
			return false;
		}
		retVal = val1;
		// cout << "in factor " << retVal << endl;
	}
	if (tk == IDENT)
	{
		if (!checkVar(tk.GetLexeme(), line))
		{
			ParseError(line, "Undeclared Variable");
			return false;
		}
	}

	return true;
}
