#include "pch.h"
#include "CClutchAssenbler.h"


CClutchAssenbler::CClutchAssenbler(double _D, double _L, double _l, double _b1, double _D1, double _d, double _c, double _d1, double _c1, double _D2, double _b, double _r, double _f)
{
	D = _D;
	L = _L;
	l = _l;
	b1 = _b1;
	D1 = _D1;
	d = _d;
	c = _c;
	d1 = _d1;
	c1 = _c1;
	D2 = _D2;
	b = _b;
	r = _r;
	f = _f;
}

void CClutchAssenbler::Assemble()
{
	// TODO: добавьте свой код обработчика уведомлений



	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!m_pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			m_pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				m_pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&m_pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	m_pKompasApp5->Visible = true;

	CreateCollar();
}
void CClutchAssenbler::CreateCollar()
{
	m_pDoc3D = m_pKompasApp5->Document3D();

	m_pDoc3D->Create(false, true);

	m_pPart = m_pDoc3D->GetPart(pTop_Part);


	ksEntityPtr pSketch1 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pSketch1->GetDefinition();

	pSketch1Def->SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch1->Create();

	m_pDoc2D = pSketch1Def->BeginEdit();
	
	
	m_pDoc2D -> ksLineSeg(0,0,0,D/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(0,D/2,l,D/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(l, D / 2,l,D1/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(l,D1/2,l+b1,D1/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(l+b1,D1/2,l+b1,D/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(l+b1,D/2,L,D/2, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(L, D / 2,L,0, MAIN_LINE);
	m_pDoc2D -> ksLineSeg(L, 0,0,0, MAIN_LINE);

	m_pDoc2D->ksLineSeg(0, 0, -10, 0, HATCH_LINE);

	pSketch1Def->EndEdit();

	ksEntityPtr pRotate1 = m_pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotate1Def = pRotate1->GetDefinition();

	pRotate1Def -> SetSketch(pSketch1);
	pRotate1Def -> SetSideParam(TRUE, 360);
	pRotate1 -> Create();











	ksEntityPtr pSketch2 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch2Def = pSketch2->GetDefinition();

	pSketch2Def -> SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch2 -> Create();

	m_pDoc2D = pSketch2Def -> BeginEdit();

	m_pDoc2D -> ksLineSeg(0,0,0,d/2,MAIN_LINE);
	m_pDoc2D -> ksLineSeg(0,d/2,L,d/2,MAIN_LINE);
	m_pDoc2D -> ksLineSeg(L,d/2,L,0,MAIN_LINE);
	m_pDoc2D -> ksLineSeg(L,0,0,0,MAIN_LINE);

	m_pDoc2D -> ksLineSeg(0,0,-100,0,HATCH_LINE);

	pSketch2Def->EndEdit();


	ksEntityPtr pCutRotate1 = m_pPart -> NewEntity(o3d_cutRotated);
	ksCutRotatedDefinitionPtr pCutRotate1Def = pCutRotate1 -> GetDefinition();

	pCutRotate1Def -> SetSideParam(TRUE,360);
	pCutRotate1Def -> SetSketch(pSketch2);

	pCutRotate1 -> Create();




	ksEntityPtr pSketch3 = m_pPart -> NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch3Def = pSketch3 -> GetDefinition();
	pSketch3Def -> SetPlane(m_pPart->GetDefaultEntity(ZOY));

	pSketch3 -> Create();

	m_pDoc2D = pSketch3Def->BeginEdit();

	m_pDoc2D->ksLineSeg(-b/2, 0, -b/2, D2/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b/2,D2/2,b/2,D2/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(b/2,D2/2,b/2,0,MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b/2,0,b/2,0,MAIN_LINE);

	pSketch3Def->EndEdit();


	ksEntityPtr pCutExtrusion1 = m_pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutExtrusion1Def = pCutExtrusion1->GetDefinition();


	pCutExtrusion1Def -> SetSketch(pSketch3);
	pCutExtrusion1Def -> SetSideParam(true, etThroughAll, 0, 0, false);
	pCutExtrusion1Def -> directionType = dtNormal;

	pCutExtrusion1->Create();
}