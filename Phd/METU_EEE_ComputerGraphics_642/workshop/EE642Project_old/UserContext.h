#pragma once

class CUserContext
{
protected:
	CString m_contextName;
	CUserContext(void);
public:
	virtual ~CUserContext(void);
	virtual void SetMenuArea()=0;
	CString GetContextName() { return m_contextName;};
	virtual void SetInputArea();
};

class CMainContext
	:public CUserContext
{
private:
	static CMainContext* m_context;
	CMainContext();
public:
	~CMainContext();
	void SetMenuArea();
	void SetInputArea();
	static CUserContext* GetInstance();
};


class C2DObjectContext
	:public CUserContext
{
private:
	static C2DObjectContext* m_context;
	C2DObjectContext();
public:
	~C2DObjectContext();
	void SetMenuArea();
	void SetInputArea();
	static CUserContext* GetInstance();
};
