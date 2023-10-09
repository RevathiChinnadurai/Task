#include "stdafx.h"
#include "Helper.h"


CAutoLock::CAutoLock(CCriticalSection * plock)
{
    m_pLock = plock;
    m_pLock->Lock();
};

CAutoLock::~CAutoLock() {
    m_pLock->Unlock();
};

CAutoLock& CAutoLock::operator=(const CAutoLock& refAutoLock)
{
    this->m_pLock = refAutoLock.m_pLock;
    return *this;
}
