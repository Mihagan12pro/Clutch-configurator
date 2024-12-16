#include "pch.h"
#include "CClutchAssembler.h"


CClutchAssembler::CClutchAssembler(double _D, double _L, double _l, double _b1, double _D1, double _d, double _c, double _d1, double _c1, double _D2, double _b, double _r, double _f)
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

void CClutchAssembler::Assemble()
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
void CClutchAssembler::CreateCollar()
{
	m_pDoc3D = m_pKompasApp5->Document3D();

	m_pDoc3D->Create(false, true);

	m_pPart = m_pDoc3D->GetPart(pTop_Part);


	ksEntityPtr pSketch1 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pSketch1->GetDefinition();

	pSketch1Def->SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch1->Create();

	m_pDoc2D = pSketch1Def->BeginEdit();


	m_pDoc2D->ksLineSeg(0, 0, 0, D / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(0, D / 2, l, D / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(l, D / 2, l, D1 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(l, D1 / 2, l + b1, D1 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(l + b1, D1 / 2, l + b1, D / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(l + b1, D / 2, L, D / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, D / 2, L, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, 0, 0, 0, MAIN_LINE);

	m_pDoc2D->ksLineSeg(0, 0, -10, 0, HATCH_LINE);

	pSketch1Def->EndEdit();

	ksEntityPtr pRotate1 = m_pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotate1Def = pRotate1->GetDefinition();

	pRotate1Def->SetSketch(pSketch1);
	pRotate1Def->SetSideParam(TRUE, 360);
	pRotate1->Create();











	ksEntityPtr pSketch2 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch2Def = pSketch2->GetDefinition();

	pSketch2Def->SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch2->Create();

	m_pDoc2D = pSketch2Def->BeginEdit();

	m_pDoc2D->ksLineSeg(0, 0, 0, d / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(0, d / 2, L, d / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, d / 2, L, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, 0, 0, 0, MAIN_LINE);

	m_pDoc2D->ksLineSeg(0, 0, -100, 0, HATCH_LINE);

	pSketch2Def->EndEdit();


	ksEntityPtr pCutRotate1 = m_pPart->NewEntity(o3d_cutRotated);
	ksCutRotatedDefinitionPtr pCutRotate1Def = pCutRotate1->GetDefinition();

	pCutRotate1Def->SetSideParam(TRUE, 360);
	pCutRotate1Def->SetSketch(pSketch2);

	pCutRotate1->Create();




	ksEntityPtr pSketch3 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch3Def = pSketch3->GetDefinition();
	pSketch3Def->SetPlane(m_pPart->GetDefaultEntity(ZOY));

	pSketch3->Create();

	m_pDoc2D = pSketch3Def->BeginEdit();

	m_pDoc2D->ksLineSeg(-b / 2, 0, -b / 2, D2 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b / 2, D2 / 2, b / 2, D2 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(b / 2, D2 / 2, b / 2, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b / 2, 0, b / 2, 0, MAIN_LINE);
	/*m_pDoc2D->ksLineSeg(b / 2, D2 / 2, b / 2, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b / 2, D2 / 2, b / 2, D2 / 2, MAIN_LINE);*/
	pSketch3Def->EndEdit();


	ksEntityPtr pCutExtrusion1 = m_pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutExtrusion1Def = pCutExtrusion1->GetDefinition();


	pCutExtrusion1Def->SetSketch(pSketch3);
	pCutExtrusion1Def->SetSideParam(true, etThroughAll, 0, 0, false);
	pCutExtrusion1Def->directionType = dtNormal;

	pCutExtrusion1->Create();






	ksEntityPtr pChamfer1 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer1Def = pChamfer1->GetDefinition();

	pChamfer1Def->tangent = true;
	pChamfer1Def->SetChamferParam(true, c, c);

	ksEntityCollectionPtr pEdges = m_pPart->EntityCollection(o3d_edge);
	ksEntityCollectionPtr pChamfers = pChamfer1Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(0, d / 2, 0);



	pChamfers->Add(pEdges->GetByIndex(0));



	pChamfer1->Create();



	ksEntityPtr pChamfer2 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer2Def = pChamfer2->GetDefinition();

	pChamfer2Def->tangent = true;
	pChamfer2Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer2Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(L, D / 2, 0);


	pChamfers->Add(pEdges->GetByIndex(0));



	pChamfer2->Create();


	ksEntityPtr pChamfer3 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer3Def = pChamfer3->GetDefinition();

	pChamfer3Def->tangent = true;
	pChamfer3Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer3Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(L, d / 2, 0);


	pChamfers->Add(pEdges->GetByIndex(0));



	pChamfer3->Create();




	ksEntityPtr pChamfer4 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer4Def = pChamfer4->GetDefinition();

	pChamfer4Def->tangent = true;
	pChamfer4Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer4Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(0, d / 2, 0);


	pChamfers->Add(pEdges->GetByIndex(0));



	pChamfer4->Create();




	ksEntityPtr pChamfer5 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer5Def = pChamfer5->GetDefinition();

	pChamfer5Def->SetChamferParam(true, f, f);
	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer5Def->array();
	pChamfers->Clear();

	//pEdges->SelectByPoint(-10, -7.94, 1);


	//pChamfers->Add(pEdges->GetByIndex(0));

	for (int i = 0;i < pEdges->GetCount();i++)
	{
		ksEntityPtr ed = pEdges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		if (def->GetOwnerEntity() == pCutExtrusion1)
		{
			ksVertexDefinitionPtr vert = def->GetVertex(true);
			double x, y, z;
			vert->GetPoint(&x, &y, &z);
			if (x != 0 && fabs(y) < d / 2)
			{

				ed->Putname("HoleEdge");
				pChamfers->Add(ed);
			}
		}

		pChamfer5->Create();
	}



	ksEntityPtr pFillet1 = m_pPart->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr pFillet1Def = pFillet1 -> GetDefinition();

	pFillet1Def->radius = r;

	ksEntityCollectionPtr pFillets = pFillet1Def->array();
	pFillets->Clear();


	for (int i = 0; i < pEdges->GetCount(); i++)
	{
		ksEntityPtr ed = pEdges -> GetByIndex(i);
		ksEdgeDefinitionPtr def = ed -> GetDefinition();

		if (def->GetOwnerEntity() == pCutExtrusion1)
		{
			
			

				ksVertexDefinitionPtr vert = def->GetVertex(true);
				double x, y, z;
				if(vert != NULL)
				{
					vert->GetPoint(&x, &y, &z);

					if (x >= c && y == -10 )
					{
						if (x == L)
						{
							pEdges->SelectByPoint(L-c,y,-1);
						
							pFillets->Add(pEdges->GetByIndex(0));

						}
						else
						{

							ed->Putname("fillet");
							pFillets->Add(ed);
						}

						
					}
				}
			}
		
			
		
	}
	pFillet1 -> Create();

	ksEntityPtr pMirrorCopy1 = m_pPart->NewEntity(o3d_mirrorOperation);
	ksMirrorCopyDefinitionPtr pMirrorCopy1Def = pMirrorCopy1->GetDefinition();

	pMirrorCopy1Def->SetPlane(m_pPart->GetDefaultEntity(XOY));
	
	pEdges = ksEntityCollectionPtr(pMirrorCopy1Def->GetOperationArray());
	pEdges->Clear();

	pEdges->Add(pFillet1);

	pMirrorCopy1->Create();



	pEdges->Clear();

	ksEntityPtr pCircularCopy1 = m_pPart->NewEntity(o3d_circularCopy);
	ksCircularCopyDefinitionPtr pCircularCopy1Def = pCircularCopy1->GetDefinition();

	//pCircularCopy1Def->count1 = 2;
	pCircularCopy1Def->SetCopyParamAlongDir(2, 45, FALSE, FALSE);
	
	

	pEdges = ksEntityCollectionPtr(pCircularCopy1Def->GetOperationArray());

	pCircularCopy1Def->SetAxis(m_pPart->GetDefaultEntity(o3d_axisOX));

	pEdges->Add(pCutExtrusion1);
	pEdges->Add(pFillet1);
	pEdges->Add(pChamfer5);
	pEdges->Add(pMirrorCopy1);
	

	pCircularCopy1->Create();
}