// 180604_계산기.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<vector>
#include<stack>
#include<string>

//숫자 구조체
struct S_NUM
{
	float num;
}; 

//연산자 구조체
struct S_OPER
{
	char oper;
	int  opernum;
};

stack<S_NUM>		 m_stkNum;		//숫자만담은스택
stack<S_OPER>		 m_stkOper;		//연산자만담은 스택
stack<S_OPER>		 m_stkOperTemp;	//팝한연산자를 잠시 담을 벡터

S_OPER				 m_soperTemp;	//연산자구조체 임시변수
S_OPER				 m_soper;		//연산자 구조체
S_NUM				 m_snum;		//숫자   구조체
S_NUM				 m_snumTemp1;	//숫자구조체 임시변수
S_NUM				 m_snumTemp2;	//숫자구조체 임시변수
S_NUM				 m_snumTotal;   //연산결과를 담은 임시변수

FILE* fp = NULL;
float f = 0.0f;			//시작숫자 음수인걸방지
char c = ' ';			//연산자초기화

int  m_opernum;			//연산자우선순위


int main()
{
	char prev;				//이전부호

	
	
	//freopen_s(&fp, "data.txt", "r",stdin);
	freopen_s(&fp, "data.txt", "r",stdin);

	//처음글자를 읽어서 처음부호가 -인걸 연산자로빼는것을 방지한다.
	fscanf_s(fp, "%f", &f);
	////////////////첫번쨔숫자 스택에 넣기
	
	m_snum.num = f;
	m_stkNum.push(m_snum);
	m_stkNum; m_stkOperTemp; m_stkOper;
	////////////////


	while (!feof(fp)) 
	{
		if (fp)
		{
			prev = c;
		}
		
		cin >> c;
		//숫자 다넣기
		//if (c == '-')
		//{
		//	if (m_stkOper.empty())
		//	{
		//		fscanf_s(fp, "%f", &f);
		//		m_snum.num = f;
		//		m_stkNum.push(m_snum);
		//	}
		//	else
		//	{
		//		if (prev == '(')
		//		{
		//			fscanf_s(fp, "%f", &f);
		//			m_snum.num = f;
		//			m_stkNum.push(m_snum);
		//		}
		//		else 
		//		{
		//			if (m_soper.opernum < 1)
		//			{
		//				m_soper.oper = c;
		//				m_soper.opernum = 1;
		//				m_stkOper.push(m_soper);
		//			}
		//			//전의연산자가 -,+이거나 *,/ 인경우
		//			else
		//			{
		//				while (m_soper.opernum >= 1)
		//				{
		//					m_soperTemp = m_soper;
		//					m_stkOperTemp.push(m_soper);
		//					m_stkOper.pop();

		//					//연산
		//					//임시변수에 먼저 담고 팝!
		//					if (!m_stkNum.empty())
		//					{
		//						m_snumTemp1 = m_stkNum.top();
		//						m_stkNum.pop();
		//						float a = m_snumTemp1.num;//두번째숫자

		//												  //2개를연산해야하므로 또 하나 팝
		//						m_snumTemp2 = m_stkNum.top();
		//						m_stkNum.pop();
		//						float b = m_snumTemp2.num; //처음숫자
		//												   //b 연산 a 를 해야 값이 맞음




		//						if (m_soper.oper == '+')
		//						{
		//							m_snumTotal.num = b + a;
		//							m_stkNum.push(m_snumTotal);
		//							m_stkOperTemp.pop();
		//						}
		//						if (m_soper.oper == '-')
		//						{
		//							m_snumTotal.num = b - a;
		//							m_stkNum.push(m_snumTotal);
		//							m_stkOperTemp.pop();
		//						}
		//						if (m_soper.oper == '*')
		//						{
		//							m_snumTotal.num = b * a;
		//							m_stkNum.push(m_snumTotal);
		//							m_stkOperTemp.pop();
		//						}
		//						if (m_soper.oper == '/')
		//						{
		//							m_snumTotal.num = b / a;
		//							m_stkNum.push(m_snumTotal);
		//							m_stkOperTemp.pop();
		//						}
		//						if (!m_stkOper.empty())
		//						{
		//							m_soper = m_stkOper.top();
		//							if (m_soper.oper == '(' || m_soper.oper == ')')
		//							{
		//								//원래연산자를 푸쉬를한다.
		//								m_soper.oper = c;
		//								m_soper.opernum = 1;
		//								m_stkOper.push(m_soper);
		//								break;
		//							}
		//							else
		//							{
		//								m_soper.oper = c;
		//								m_soper.opernum = 1;
		//								m_stkOper.push(m_soper);
		//								break;
		//							}
		//						}
		//						else
		//						{
		//							m_soper.oper = c;
		//							m_soper.opernum = 1;
		//							m_stkOper.push(m_soper);
		//							break;
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
		
		if (c == '+' || c == '-')
		{
			//스택이비어있으면 연산자와 연산자우선순위를넣는다.
			if (m_stkOper.empty())
			{
				m_soper.oper = c;
				m_soper.opernum = 1;
				m_stkOper.push(m_soper);
			}
			else
			{
				if (m_soper.opernum < 1)
				{
					m_soper.oper = c;
					m_soper.opernum = 1;
					m_stkOper.push(m_soper);
				}
				//전의연산자가 -,+이거나 *,/ 인경우
				else
				{
					while (m_soper.opernum >= 1)
					{
						m_soperTemp = m_soper;
						m_stkOperTemp.push(m_soper);
						m_stkOper.pop();

						//연산
						//임시변수에 먼저 담고 팝!
						if (!m_stkNum.empty())
						{
							m_snumTemp1 = m_stkNum.top();
							m_stkNum.pop();
							float a = m_snumTemp1.num;//두번째숫자

							//2개를연산해야하므로 또 하나 팝
							m_snumTemp2 = m_stkNum.top();
							m_stkNum.pop();
							float b = m_snumTemp2.num; //처음숫자
							 //b 연산 a 를 해야 값이 맞음




							if (m_soper.oper == '+')
							{
								m_snumTotal.num = b + a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '-')
							{
								m_snumTotal.num = b - a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '*')
							{
								m_snumTotal.num = b * a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '/')
							{
								m_snumTotal.num = b / a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (!m_stkOper.empty())
							{
								m_soper = m_stkOper.top();
								if (m_soper.oper == '(' || m_soper.oper == ')')
								{
									//원래연산자를 푸쉬를한다.
									m_soper.oper = c;
									m_soper.opernum = 1;
									m_stkOper.push(m_soper);
									break;
								}
								else
								{
									m_soper.oper = c;
									m_soper.opernum = 1;
									m_stkOper.push(m_soper);
									break;
								}
							}
							else
							{
								m_soper.oper = c;
								m_soper.opernum = 1;
								m_stkOper.push(m_soper);
								break;
							}
						}
					}
				}
			}
		}
		else if (c == '*'|| c =='/')
		{
			//우선순위가 가장 낮은연산자는 그냥 푸시해서 팝만해주면 된다.
			if (m_stkOper.empty())
			{
				m_soper.oper = c;
				m_soper.opernum = 2;
				m_stkOper.push(m_soper);
			}
			//둘도 똑같이 빼서 연산 해야함
			else
			{
	
				if (m_soper.opernum == 2)
				{
					m_soperTemp = m_soper;
					m_stkOperTemp.push(m_soper);
					m_stkOper.pop();

					//연산
					//임시변수에 먼저 담고 팝!
					if (!m_stkNum.empty())
					{
						m_snumTemp1 = m_stkNum.top();
						m_stkNum.pop();
						float a = m_snumTemp1.num;//두번째숫자
												  //2개를연산해야하므로 또 하나 팝
						m_snumTemp2 = m_stkNum.top();
						m_stkNum.pop();
						float b = m_snumTemp2.num; //처음숫자
												   //b 연산 a 를 해야 값이 맞음
						if (m_soper.oper == '*')
						{
							m_snumTotal.num = b * a;
							m_stkNum.push(m_snumTotal);
							m_stkOperTemp.pop();
						}
						if (m_soper.oper == '/')
						{
							m_snumTotal.num = b / a;
							m_stkNum.push(m_snumTotal);
							m_stkOperTemp.pop();
						}
					}
				}
				else
				{
					m_soper.oper = c;
					m_soper.opernum = 2;
					m_stkOper.push(m_soper);

				}
			}
		}
		else if (c == '(')
		{
			//처음괄호는 그냥 넣어준다.
			m_soper.oper = c;
			m_soper.opernum = 0;
			m_stkOper.push(m_soper);
			
			fscanf_s(fp, "%f", &f);
			m_snum.num = f;
			m_stkNum.push(m_snum);
		}
		else if (c == ')')
		{
			

			while (m_soper.opernum >= 0&& !m_stkOper.empty())
			{
				if (!m_stkOper.empty())
				{
					while (!m_stkOper.empty())
					{

						//닫는소괄호가 여는소괄호를만나게되면
						if (m_soper.oper == '(' && !m_stkOper.empty())
						{
							m_stkOper.pop();
							m_soper= m_stkOper.top();
							break;
						}
						else
						{
							//임시변수에 팝하기전 넣어주고

							m_soperTemp.oper = m_soper.oper;
							m_soperTemp.opernum = m_soper.opernum;

							//팝
							m_stkOper.pop();
							m_stkOperTemp.push(m_soperTemp);

							//임시변수에 먼저 담고 팝!
							m_snumTemp1 = m_stkNum.top();
							m_stkNum.pop();
							float a = m_snumTemp1.num;//두번째숫자

													  //2개를연산해야하므로 또 하나 팝
							m_snumTemp2 = m_stkNum.top();
							m_stkNum.pop();
							float b = m_snumTemp2.num; //처음숫자
													   //b 연산 a 를 해야 값이 맞음


							if (m_soper.oper == '+')
							{
								m_snumTotal.num = b + a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '-')
							{
								m_snumTotal.num = b - a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '*')
							{
								m_snumTotal.num = b * a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}
							if (m_soper.oper == '/')
							{
								m_snumTotal.num = b / a;
								m_stkNum.push(m_snumTotal);
								m_stkOperTemp.pop();
							}

							//증감식
							if (!m_stkOper.empty())
							{
								m_soper = m_stkOper.top();
							}


							//break;//while (!m_stkOper.empty())빠져나옴
						}
							
					}//와일문 빠져나오기 
					break;
				}
				
				
				
				//m_soper = 소괄호 전의 스택에남아있는 연산자
				
			}
		}
		else
		{
			//스택에 숫자들을 아토이를이용해서 넣는다.
			if (!(c == '-'||c == '+' || c == '/' || c == '*' || c == '(' || c == ')'))
			{
				m_snum.num = atoi(&c);
				m_stkNum.push(m_snum);
				/*fscanf_s(fp, "%f", &f);
				m_snum.num = f;
				m_stkNum.push(m_snum);*/
			}
		
		}
	}





	m_snum= m_stkNum.top();
	float x = m_snum.num;
	cout << x<< endl;



    return 0;
}

