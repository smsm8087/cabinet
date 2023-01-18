// StackCalc.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

using namespace std;

bool IsOperator(string& in)
{
	if (in == "(" ||
		in == ")" ||
		in == "+" ||
		in == "-" ||
		in == "*" ||
		in == "/")
	{
		return true;
	}
	return false;
}

bool IsOperator(string& in, int& n)
{
	if (in[n] == '(' ||
		in[n] == ')' ||
		in[n] == '+' ||
		in[n] == '*' ||
		in[n] == '/')
	{
		return true;
	}

	if (in[n] == '-')
	{
		if (in[n - 1] != '(')
		{
			return true;
		}
	}
	return false;
}

bool GetToken(string& in, string& out, int& n)
{
	if (in.length() == n)
		return false;
	
	out = "";
	if (IsOperator(in, n))
	{
		out = string(1, in[n++]);
		return true;
	}
	
	while (!IsOperator(in, n))
	{
		out += string(1, in[n++]);
	}
	return true;
}

int main()
{
	FILE* fp = NULL;

	fopen_s(&fp, "data.txt", "r");

	char szBuf[1024];
	fgets(szBuf, 1024, fp);
	//cout << szBuf;
	string sIn = "(" + string(szBuf) + ")";
	string sOut;
	int n = 0;

	map<string, int> mapOperatorPriority;
	mapOperatorPriority["("] = 0;
	mapOperatorPriority[")"] = 0;
	mapOperatorPriority["+"] = 1;
	mapOperatorPriority["-"] = 1;
	mapOperatorPriority["*"] = 2;
	mapOperatorPriority["/"] = 2;

	vector<string> vecPostfix;
	stack<string> stkOperator;

	while (GetToken(sIn, sOut, n))
	{
		//cout << sOut << endl;
		if (!IsOperator(sOut))
		{
			vecPostfix.push_back(sOut);
		}
		else
		{
			if (sOut == "(")
			{
				stkOperator.push(sOut);
			}
			else if (sOut == ")")
			{
				while (true)
				{
					string sTop = stkOperator.top();
					stkOperator.pop();
					if (sTop == "(")
					{
						break;
					}
					vecPostfix.push_back(sTop);
				}
			}
			else// if (!stkOperator.empty())
			{
				string sTop = stkOperator.top();
				while (!stkOperator.empty() &&
					mapOperatorPriority[sTop] >= mapOperatorPriority[sOut])
				{
					stkOperator.pop();
					vecPostfix.push_back(sTop);
					sTop = stkOperator.top();
				}
				stkOperator.push(sOut);
			}
		}
	}

	while (!stkOperator.empty())
	{
		string sTop = stkOperator.top();
		stkOperator.pop();
		vecPostfix.push_back(sTop);
	}
	
	fclose(fp);

	stack<float> stkOperand;
	for (size_t i = 0; i < vecPostfix.size(); i++)
	{
		if (!IsOperator(vecPostfix[i]))
		{
			stkOperand.push((float)atof(vecPostfix[i].c_str()));
		}
		else
		{
			float f2 = stkOperand.top();
			stkOperand.pop();
			float f1 = stkOperand.top();
			stkOperand.pop();
			if (vecPostfix[i] == "+")
			{
				stkOperand.push(f1 + f2);
			}
			else if (vecPostfix[i] == "-")
			{
				stkOperand.push(f1 - f2);
			}
			else if (vecPostfix[i] == "*")
			{
				stkOperand.push(f1 * f2);
			}
			else if (vecPostfix[i] == "/")
			{
				stkOperand.push(f1 / f2);
			}
		}
	}

	printf("%f\n", stkOperand.top());
	//cout << (float)stkOperand.top() << endl;
    return 0;
}

