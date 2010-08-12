/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkLogicSensor_h_
#define _gkLogicSensor_h_

#include "gkLogicBrick.h"


class gkLogicSensor : public gkLogicBrick
{
public:
	enum Pulse
	{
		PM_IDLE     = (1 << 0),
		PM_TRUE     = (1 << 1),
		PM_FALSE    = (1 << 2),
	};


protected:

	gkControllers m_controllers;


	int     m_freq, m_tick, m_pulse;
	bool    m_invert, m_positive, m_suspend, m_tap, m_firstExec;
	bool    m_sorted, m_isDetector;
	int     m_dispatchType;


	// state cache
	int     m_oldState;

	// tap detection
	int m_firstTap, m_lastTap;


	void cloneImpl(gkLogicLink *link, gkGameObject *dest);


public:

	gkLogicSensor(gkGameObject *object, gkLogicLink *link, const gkString &name);
	virtual ~gkLogicSensor();

	void connect(void);
	void disconnect(void);

	void link(gkLogicController *cont);

	// Process pending events.
	void execute(void);

	// Do test on subclass to see if a pulse is wanted.
	virtual bool query(void) = 0;

	void sort(void);

	// Reset to initial state.
	void reset(void);

	// Events have been queried, now pass to
	// connected controllers for further processing.
	void dispatch(void);


	bool isPositive(void);

	GK_INLINE gkControllers &getControllers(void) {return m_controllers;}


	GK_INLINE bool isNegativePulseMode(void) {return (m_pulse& PM_FALSE)!=0;}
	GK_INLINE bool isPositivePulseMode(void) {return (m_pulse& PM_TRUE)!=0;}
	GK_INLINE void setFrequency(int v)      {m_freq = (int)((((float)v)+.5)/2.0);}
	GK_INLINE int  getFrequency(void)       {return m_freq;}
	GK_INLINE void setMode(int m)           {m_pulse = m;}
	GK_INLINE int  getMode(void)            {return m_pulse;}
	GK_INLINE void invert(bool v)           {m_invert = v;}
	GK_INLINE bool isInverse(void)          {return m_invert;}
	GK_INLINE void suspend(bool v)          {m_suspend = v;}
	GK_INLINE bool isSuspended(void)        {return m_suspend;}
	GK_INLINE void setTap(bool v)           {m_tap = v;}
	GK_INLINE bool isTap(void)              {return m_tap;}
	GK_INLINE void setDetector(bool v)      {m_isDetector = v;}
	GK_INLINE bool isDetector(void)         {return m_isDetector;}
	GK_INLINE void setStartState(int v)     {m_oldState = v;}
	GK_INLINE int  getDispatcher(void)      {return m_dispatchType;}

};


#endif//_gkLogicSensor_h_
