// thanks to pragma

#include <qevent.h>
#include <qstring.h>

#define THREAD_EVENT (((int)QEvent::User) + 2000)

// id's
#define THREAD_EVENT_END_SUCCESS 10
#define THREAD_EVENT_DIAG_FAILED 20
#define THREAD_EVENT_DIAG_RICHARDSON_FAILED 30

class ThreadEvent : public QEvent {
public:
	ThreadEvent(int eventId) : QEvent((QEvent::Type)THREAD_EVENT), m_eventId(eventId) {}
	
    int id() { return m_eventId; };
protected:
	int m_eventId;
};
 
template<class TData> class ThreadDataEvent : public ThreadEvent
{
public:
    ThreadDataEvent(int eventId) : ThreadEvent(eventId) , m_pData(0) {};
    ~ThreadDataEvent(){ if(m_pData) delete m_pData; };
	
    void setData(TData * d){ if(m_pData)delete m_pData; m_pData = d; };
    TData * getData(){ TData * aux = m_pData; m_pData = 0; return aux; };
protected:
    TData * m_pData;
};

