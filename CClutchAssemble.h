#pragma once
#define Assemble CClutchAssemble
#include"GOST1139.h"
#include"Other.h"
class CAssemblesCollection;
class CClutchAssemble
{
	protected:
		CGOST1139 m_gosts1193Top;
		CGOST1139 m_gosts1193Bottom;
		double D, L, l, b1, D1,  c, d1, c1,  r, f;
		CString NM;
	public:
		CClutchAssemble();
		CClutchAssemble(CString _NM);
		CClutchAssemble(double D, double L, double l, double b1, double D1, double c, double d1, double c1, double r, double f,CGOST1139 &gost1,  CGOST1139 &gost2);
		double Getf();
		double Getr();
		double Getc1();
		double Getd1();
		double Getc();
		double GetD1();
		double Getb1();
		double Getl();
		double GetL();
		double GetD();
		CString GetNM();
		CGOST1139 GetGOST1139(GOST gost);
protected:
	friend class CAssemblesCollection;
};

