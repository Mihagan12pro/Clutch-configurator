
// ClutchConfiguratorDoc.h: интерфейс класса CClutchConfiguratorDoc 
//


#pragma once
class CAssembleTree;
class CClutchConfiguratorDoc;
class CMainFrame;

class CClutchConfiguratorDoc : public CDocument
{
protected: // создать только из сериализации
	CClutchConfiguratorDoc() noexcept;
	DECLARE_DYNCREATE(CClutchConfiguratorDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	
	virtual ~CClutchConfiguratorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CAssembleTree* m_pAssembleTree;
	CClutchConfiguratorDoc* m_pClutchConfigView;

	friend class CMainFrame;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
