#pragma once
#include"afx.h"
class CGOST1139
{
	private:
		double Z,  d, D2,  b;
		CString m_tittle;
	public:
		CGOST1139()
		{

		}
		CGOST1139(double _Z,double _d,double _D2,double _b,CString tittle)
		{
			Z = _Z;
			d = _d;
			D2 = _D2;
			b = _b;
			m_tittle = tittle;
		}
		CString GetTittle()
		{
			return m_tittle;
		}
		double GetZ()
		{
			return Z;
		}
		double Getd()
		{
			return d;
		}
		double GetD2()
		{
			return D2;
		}
		double Getb()
		{
			return b;
		}
	

};