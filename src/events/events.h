

#ifndef _EVENTS_
#define _EVENTS_

class Event {
private:
	

public:
	Event();
	~Event();
	virtual void update();
	virtual bool can_start();
	virtual void start();
	virtual bool can_be_destroyed();
	virtual void destroy();
	
	
};


#endif
