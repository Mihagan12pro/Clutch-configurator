#include "pch.h"
#include "CClutchAssemble.h"
CClutchAssemble::CClutchAssemble(CString _NM)
{
	NM = _NM;
}
CClutchAssemble::CClutchAssemble(double _D, double _L, double _l, double _b1, double _D1, double _c, double _d1, double _c1, double _r, double _f, CGOST1139 &gost1,  CGOST1139 &gost2)
{
	D = _D;
	L = _L;
	l = _l;
	b1 = _b1;
	D1 = _D1;
	c = _c;
	d1 = _d1;
	c1 = _c1;
	r = _r;
	f = _f;

	m_gosts1193Top = gost1;
	m_gosts1193Bottom = gost2;
}
CGOST1139 CClutchAssemble::GetGOST1139(GOST gost)
{
	if (gost == GOST_TOP)
	{
		return m_gosts1193Top;
	}
	return m_gosts1193Bottom;
}
double CClutchAssemble::Getf()
{
	return f;
}

double CClutchAssemble::Getr()
{
	return r;
}


double CClutchAssemble::Getc1()
{
	return c1;
}

double CClutchAssemble::Getd1()
{
	return d1;
}

double CClutchAssemble::Getc()
{
	return c;
}

double CClutchAssemble::GetD1()
{
	return D1;
}
double CClutchAssemble::Getb1()
{
	return b1;
}

double CClutchAssemble::Getl()
{
	return l;
}

double CClutchAssemble::GetL()
{
	return L;
}

double CClutchAssemble::GetD()
{
	return D;
}